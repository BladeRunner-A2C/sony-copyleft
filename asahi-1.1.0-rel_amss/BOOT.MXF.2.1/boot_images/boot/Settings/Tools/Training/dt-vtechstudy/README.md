# dt-vtechstudy

This repo contains multiple lessons intended to introduce the audience to DeviceTree basics.  Each lesson has a study-guide (pdf) and a collection of code and DeviceTree files.  The study-guide includes questions to answer and code to fix.

## Repository Layout

- bin/
- - gendtb.py : python script combining cpp (C pre-processor) and dtc
- oss-dtc/
- - header file(s) and library from upstream dtc project
- src/
- - actual lessons, including some common code files shared by all lessons



## Lessons

- - Lesson_1/
  - - Introduce DeviceTree basics and local tools, etc.
    - Simple coding problem that demonstrates an important aspect of data stored in DTB
    - Use of QDTE
    - Use of dtc to generate a dts file from a dtb file
- - Lesson_2/
  - - Fix 2 warnings in sample-machine.dts file
    - Introduce use of command-line parameters to add console output
    - Use QDTE and fdt.h to understand DTB format and why a client can interpret the data in a DTB in any format
    - Answer questions about the DTB format
  - Lesson_3/
  - - Demonstrate lookup performance
    - Use QDTE to edit a property value and see the impact of the change
    - Introduce important new concept that supports a pointer or reference mechanism within DTB
    - Fix a broken DTB
  - Lesson_4/
  - - Demonstrate DTBO (DeviceTree Overlay) capabilities



