Building for Windows:-

#Ensure you have Visual Studio 2017 installed.
#In Visual Studio, create a New Project using File->New->Project from Existing code.
#Add "/src" folder to the project.
#Add _CRT_SECURE_NO_WARNINGS and _CRT_NONSTDC_NO_WARNINGS to Preprocessor Definitions
#Execute from menu bar Build->Build Solution (if building for the first time) or Build->Rebuild Solution.
#Please enable /MT flag in the Runtime Library settings for the executable to work on all Windows machines

== Building for Linux ==

#Ensure you have Cmake application installed on your Linux system.
#Open terminal inside the "/src" folder.
#Run "cmake CmakeLists.txt" or <b>"cmake ."</b> on the terminal. 
#Then run "make" to generate the QSaharaServer executable.

== Cross compilation for ARM to generate linux binary ==
1. Install cross compiler tool using the below command.
   sudo apt-get install g++-aarch64-linux-gnu

2. Modify CMake Configuration : Add the following lines to set up cross-compilation environment in CMakeLists.txt
   set(CMAKE_BUILD_TYPE Debug)
   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c")
   set(CMAKE_C_COMPILER aarch64-linux-gnu-gcc)
