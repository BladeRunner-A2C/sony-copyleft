'''
Qualcomm DT Schema support.

This module provides the following additional support to DeviceTree Schema:

    - Support for propertyOrder property.
    - Support for our local devicetree URLs for schema ids.

These changes are implemented in a way that does not require any changes to the
upstream open-source code from the dtschema library.

To use this module, simply import it. All patches are applied automatically.
'''

import dtschema
import importlib
import os
from dtschema.lib import http_handler, schema_cache
from jsonschema import ValidationError


def propertyOrder (validate, value, instance, schema):
    '''
    JSON Schema validator to enforce the order of properties. Note that
    this assumes that the json parser maintains the order of properties.
    '''
    props = list(instance.keys())
    if props[0:len(value)] != value:
        yield ValidationError("properties in wrong order")


def add_property_order_schema():
    '''
    Add support for a propertyOrder schema that allows enforcing the order of
    properties in an object.
    This is done by loading the existing keywords and nodes meta-schemas, patching
    them with the new property, and then saving them into the schema cache so
    they are not reloaded later.
    '''
    dtschema.DTValidator.VALIDATORS['propertyOrder'] = propertyOrder

    keywords_schema = http_handler('http://devicetree.org/meta-schemas/keywords.yaml')
    keywords_schema['definitions']['sub-schemas']['propertyNames']['enum'].append('propertyOrder')
    keywords_schema['properties']['propertyOrder'] = { 
        'type': 'array', 
        'items': { 'pattern': '^([a-zA-Z#][a-zA-Z0-9,+\-._@]{0,63}|\$nodename)$' } 
    }
    schema_cache.append(keywords_schema)

    nodes_schema = http_handler('http://devicetree.org/meta-schemas/nodes.yaml')
    nodes_schema['propertyNames']['enum'].append('propertyOrder')
    schema_cache.append(nodes_schema)


def patch_check_schema_refs():
    '''
    Patch the DTValidator.check_schema_refs function to automatically set the
    $id property to the expected format.
    '''
    check_schema_refs_orig = dtschema.DTValidator.check_schema_refs

    def _check_schema_refs(filename, schema):
        schema['$id'] = "http://devicetree.org/schemas/" + os.path.abspath(filename) + "#"
        return check_schema_refs_orig(filename, schema)

    dtschema.DTValidator.check_schema_refs = _check_schema_refs


def run_main(filename):
    '''
    This functions provides the ability to import a script as if it was run from
    the command line. The purpose is to allow us to patch dtschema before running
    dt-validate for example.
    '''
    loader = importlib.machinery.SourceFileLoader(filename, filename)
    loader.name = "__main__"
    spec = importlib.util.spec_from_loader(filename, loader)
    spec.name = "__main__"
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)


# Invoke the key functions on import.
add_property_order_schema()
patch_check_schema_refs()

