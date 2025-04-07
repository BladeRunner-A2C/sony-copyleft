SMC invoke API calling example

In SmcInvokeExampleApp.c, there is demo on how to use SMC invoke APIs to:
    1.  load a TA, 
    2.  acquire the loaded TA object, 
    3.  call the services from this loaded TA.

Here is the code snip: 

   Status = ScmProtocol->ScmGetClientEnv(ScmProtocol, &clientEnv);
   IF_NOT_ZERO_EXIT( Status );
   IF_TRUE_EXIT( Object_isNull(clientEnv)); 
                                                                                         
   ret = IClientEnv_open(clientEnv, CAppLoader_UID, &appLoader);
   IF_NOT_ZERO_EXIT( ret );
   IF_TRUE_EXIT(Object_isNull(appLoader));
  
   // load a TA in TZ
   ret = IAppLoader_loadFromBuffer(appLoader, image, imageSize, &appController);
   IF_NOT_ZERO_EXIT( ret );
   IF_TRUE_EXIT(Object_isNull(appController));

   // get the TA object
   ret = IAppController_getAppObject(appController, &appObj);
   IF_NOT_ZERO_EXIT( ret );
   IF_TRUE_EXIT( Object_isNull(appObj));

Once the TA object is acquired, the TA service can be called using the APIs provided by this TA.

Please note:

   1.  This code is just a demo, the test cases may not all pass due to the missing support from TZ. 
   2.  This folder is self contained, it includes all SMC invoke APIs referenced in this demo code.
   3.  The demo TAs, smcinvoke_example_ta64.mbn and smcinvoke_example_svc_ta64.mbn, are embedded in tests.fv
   4.  ScmDxe protocol provides all needed UEFI smc invoke APIs