
all: lesson_1 lesson_1a

clean:
	rm -f ../dt_vtechstudy.o
	rm -f ../main.o
	rm -f lesson_1a.o
	rm -f lesson_1
	rm -f lesson_1a

CPPFLAGS = -I.. -I../../../oss-dtc/libfdt

lesson_1: lesson_1.o ../main.o ../dt_vtechstudy.o
	gcc -o lesson_1 ../main.o ../dt_vtechstudy.o lesson_1.o ../../../oss-dtc/libfdt/libfdt.a

lesson_1a: lesson_1a.o ../main.o ../dt_vtechstudy.o
	gcc -o lesson_1a ../main.o ../dt_vtechstudy.o lesson_1a.o ../../../oss-dtc/libfdt/libfdt.a

