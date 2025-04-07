
all: lesson_3

clean:
	rm -f ../dt_vtechstudy.o
	rm -f ../main.o
	rm -f *.o
	rm -f lesson_3
	rm -f tlmm-broken.dtb
	rm -f tlmm-broken.dts.pp

CPPFLAGS = -I.. -I../../../oss-dtc/libfdt

lesson_3: lesson_3.o get_prop_value.o ../main.o ../dt_vtechstudy.o
	gcc -o lesson_3 get_prop_value.o ../main.o ../dt_vtechstudy.o lesson_3.o ../../../oss-dtc/libfdt/libfdt.a
