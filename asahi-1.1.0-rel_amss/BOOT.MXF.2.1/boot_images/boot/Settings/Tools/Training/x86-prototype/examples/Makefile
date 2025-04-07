
DTBHEXDUMP_O = ../../common/DTB_Hex_Dump.o

all: libdtbextn example tlmm-example list-access struct-access phandle-access adc packed-struct compatible adversarial cache slice overlay-test uefi-overlay create-dtb recursive-dfs non-recursive-dfs

clean:
	rm -f *.o
	rm -f ${DTBHEXDUMP_O}
	rm -f libdtbextn.a
	rm -f *.cpp
	rm -f example
	rm -f tlmm-example
	rm -f list-access
	rm -f struct-access
	rm -f phandle-access
	rm -f packed-struct
	rm -f compatible
	rm -f adversarial
	rm -f overlay-test
	rm -f uefi-overlay
	rm -f create-dtb
	rm -f recursive-dfs
	rm -f non-recursive-dfs
	rm -f adc
	rm -f cache
	rm -f slice
	rm -f core.*
	rm -f *.dtb
	rm -f $(QCOM_PATH)/Library/DTBExtnLib/*.o

QCOM_PATH = ../../../../../QcomPkg
DFLAGS = -DBUILD_X86 -DPORT_ARMv8 -DINSTRUMENTATION
CPPFLAGS = -ggdb $(DFLAGS) -I. -I../../oss-dtc/libfdt -I$(QCOM_PATH)/Include/Library -I$(QCOM_PATH)/Library/DTBExtnLib
CC = gcc

libdtbextn: $(QCOM_PATH)/Library/DTBExtnLib/DTBExtnLib_blob.o \
$(QCOM_PATH)/Library/DTBExtnLib/DTBExtnLib_node.o \
$(QCOM_PATH)/Library/DTBExtnLib/DTBExtnLib_prop.o \
$(QCOM_PATH)/Library/DTBExtnLib/DTBExtnLib_driver.o \
$(QCOM_PATH)/Library/DTBExtnLib/DTBExtnLib_overlay.o \
$(QCOM_PATH)/Library/DTBExtnLib/DTBExtnLib_create-dtb.o
	ar rcs libdtbextn.a $(QCOM_PATH)/Library/DTBExtnLib/*.o

example: libdtbextn example.o main.o ${DTBHEXDUMP_O}
	gcc -o example main.o ${DTBHEXDUMP_O} example.o -L. -ldtbextn -lfdt

cache: libdtbextn cache.o main.o
	gcc -o cache main.o cache.o -L. -ldtbextn -lfdt

adc: libdtbextn adc.o main.o
	gcc -o adc main.o adc.o -L. -ldtbextn -lfdt

adversarial: libdtbextn adversarial.o main.o
	gcc -o adversarial main.o adversarial.o -L. -ldtbextn -lfdt

compatible: libdtbextn compatible.o main.o
	gcc -o compatible main.o compatible.o -L. -ldtbextn -lfdt

list-access: libdtbextn list-access.o main.o ${DTBHEXDUMP_O}
	gcc -o list-access main.o ${DTBHEXDUMP_O} list-access.o -L. -ldtbextn -lfdt

struct-access: libdtbextn struct-access.o main.o ${DTBHEXDUMP_O}
	gcc -o struct-access main.o ${DTBHEXDUMP_O} struct-access.o -L. -ldtbextn -lfdt

packed-struct: libdtbextn packed-struct.o main.o
	gcc -o packed-struct main.o packed-struct.o -L. -ldtbextn -lfdt

phandle-access: libdtbextn phandle-access.o main.o ${DTBHEXDUMP_O}
	gcc -o phandle-access main.o ${DTBHEXDUMP_O} phandle-access.o -L. -ldtbextn -lfdt

tlmm-example: libdtbextn tlmm-example.o main.o
	gcc -o tlmm-example main.o tlmm-example.o -L. -ldtbextn -lfdt

create-dtb: libdtbextn create-dtb.o main.o
	gcc -o create-dtb main.o create-dtb.o -L. -ldtbextn -lfdt

recursive-dfs: libdtbextn recursive-dfs.o main.o
	gcc -o recursive-dfs main.o recursive-dfs.o -L. -ldtbextn -lfdt

non-recursive-dfs: libdtbextn non-recursive-dfs.o main.o
	gcc -o non-recursive-dfs main.o non-recursive-dfs.o -L. -ldtbextn -lfdt

slice: libdtbextn slice.o main.o ${DTBHEXDUMP_O}
	gcc -o slice main.o ${DTBHEXDUMP_O} slice.o -L. -ldtbextn -lfdt

overlay-test: libdtbextn overlay-test.o main.o
	gcc -o overlay-test main.o overlay-test.o -L. -ldtbextn -lfdt

uefi-overlay: libdtbextn uefi-overlay.o main.o ${DTBHEXDUMP_O}
	gcc -o uefi-overlay main.o ${DTBHEXDUMP_O} uefi-overlay.o -L. -ldtbextn -lfdt
