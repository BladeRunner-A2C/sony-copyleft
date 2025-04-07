Standard Makefile targets will create Workshop examples from Slide-Deck
to run on x86 Linux Host.

.../dts/
	compatible.dtb
	example-api.dtb
	slice.dtb
	struct-access.dtb
	tlmm.dtb
	uefi-base-small.dtb
	vadc_test.dtb

	latesthyp.dtbo
	overlay-tlmm-1.dtbo
	overlay-tlmm-2.dtbo
	overlay-tlmm-3.dtbo

This provides map between examples and DTB files to use:

	./adc -f ../dts/vadc_test.dtb
	./adversarial -f ../dts/example-api.dtb
	./cache -f ../dts/example-api.dtb
	./compatible -f ../dts/compatible.dtb
	./example -f ../dts/example-api.dtb
	./list-access -f ../dts/example-api.dtb
	./overlay-test -f ../dts/tlmm.dtb
	./packed-struct -f ../dts/struct-access.dtb
	./phandle-access -f ../dts/example-api.dtb
	./slice -f ../dts/slice.dtb
	./struct-access -f ../dts/struct-access.dtb
	./tlmm-example -f ../dts/tlmm.dtb
	./uefi-overlay -f ../dts/uefi-base-small.dtb
