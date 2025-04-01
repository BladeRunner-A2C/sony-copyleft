How to build the test application
$ source build/envsetup.sh
$ lunch
$ (select the target device number)
$ cd ./vendor/semc/hardware/charge/charge-service/test
$ mm

How to run the test application
$ adb root
$ adb remount
$ adb push ../../../../../../out/target/product/<oroduct name>/system/bin/charger_test_runner /data/
$ adb shell /data/charger_test_runner
  --> if 'F' is shown, it's failure.
