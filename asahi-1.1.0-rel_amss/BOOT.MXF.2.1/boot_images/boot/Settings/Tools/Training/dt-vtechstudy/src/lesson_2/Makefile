
DTBHEXDUMP_O = ../../../common/DTB_Hex_Dump.o

all: lesson_2

clean:
	rm -f ${DTBHEXDUMP_O}
	rm -f ../dt_vtechstudy.o
	rm -f ../main.o
	rm -f *.o
	rm -f *.pp
	rm -f *.dtb
	rm -f lesson_2

CPPFLAGS = -I.. -I../../../oss-dtc/libfdt

lesson_2: lesson_2.o ../main.o ../dt_vtechstudy.o ${DTBHEXDUMP_O}
	gcc -o lesson_2 ../main.o ../dt_vtechstudy.o ${DTBHEXDUMP_O} lesson_2.o ../../../oss-dtc/libfdt/libfdt.a
