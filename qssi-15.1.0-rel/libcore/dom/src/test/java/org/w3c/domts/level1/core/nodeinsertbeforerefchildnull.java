
/*
This Java source file was generated by test-to-java.xsl
and is a derived work from the source document.
The source document contained the following notice:


Copyright (c) 2001 World Wide Web Consortium,
(Massachusetts Institute of Technology, Institut National de
Recherche en Informatique et en Automatique, Keio University). All
Rights Reserved. This program is distributed under the W3C's Software
Intellectual Property License. This program is distributed in the
hope that it will be useful, but WITHOUT ANY WARRANTY; without even
the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
PURPOSE.
See W3C License http://www.w3.org/Consortium/Legal/ for more details.

*/

package org.w3c.domts.level1.core;

import org.w3c.dom.*;


import org.w3c.domts.DOMTestCase;
import org.w3c.domts.DOMTestDocumentBuilderFactory;



/**
 *     If the "refChild" is null then the
 *     "insertBefore(newChild,refChild)" method inserts the
 *     node "newChild" at the end of the list of children. 
 *     
 *     Retrieve the second employee and invoke the
 *     "insertBefore(newChild,refChild)" method with
 *     refChild=null.   Since "refChild" is null the "newChild"
 *     should be added to the end of the list.   The last item
 *     in the list is checked after insertion.   The last Element
 *     node of the list should be "newChild".
* @author NIST
* @author Mary Brady
* @see <a href="http://www.w3.org/TR/1998/REC-DOM-Level-1-19981001/level-one-core#ID-952280727">http://www.w3.org/TR/1998/REC-DOM-Level-1-19981001/level-one-core#ID-952280727</a>
*/
public final class nodeinsertbeforerefchildnull extends DOMTestCase {

   /**
    * Constructor.
    * @param factory document factory, may not be null
    * @throws org.w3c.domts.DOMTestIncompatibleException Thrown if test is not compatible with parser configuration
    */
   public nodeinsertbeforerefchildnull(final DOMTestDocumentBuilderFactory factory)  throws org.w3c.domts.DOMTestIncompatibleException {
      super(factory);

    //
    //   check if loaded documents are supported for content type
    //
    String contentType = getContentType();
    preload(contentType, "staff", true);
    }

   /**
    * Runs the test case.
    * @throws Throwable Any uncaught exception causes test to fail
    */
   public void runTest() throws Throwable {
      Document doc;
      NodeList elementList;
      Node employeeNode;
      NodeList childList;
      Node refChild = null;

      Node newChild;
      Node child;
      String childName;
      Node insertedNode;
      doc = (Document) load("staff", true);
      elementList = doc.getElementsByTagName("employee");
      employeeNode = elementList.item(1);
      childList = employeeNode.getChildNodes();
      newChild = doc.createElement("newChild");
      insertedNode = employeeNode.insertBefore(newChild, refChild);
      child = employeeNode.getLastChild();
      childName = child.getNodeName();
      assertEquals("nodeInsertBeforeRefChildNullAssert1", "newChild", childName);
      }
   /**
    *  Gets URI that identifies the test.
    *  @return uri identifier of test
    */
   public String getTargetURI() {
      return "http://www.w3.org/2001/DOM-Test-Suite/level1/core/nodeinsertbeforerefchildnull";
   }
   /**
    * Runs this test from the command line.
    * @param args command line arguments
    */
   public static void main(final String[] args) {
        DOMTestCase.doMain(nodeinsertbeforerefchildnull.class, args);
   }
}

