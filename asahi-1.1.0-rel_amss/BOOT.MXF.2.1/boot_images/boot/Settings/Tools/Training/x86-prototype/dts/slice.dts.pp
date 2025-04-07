
/dts-v1/;

/ {
    level1 {
  u8-list = /bits/ 8 <1 2 3 4 5 6 7 8>;
  u16-list = /bits/ 16 <0x11 0x22 0x33 0x44 0x55 0x66 0x77 0x88>;
  u32-list = /bits/ 32 <0x111 0x222 0x333 0x444 0x555 0x666 0x777 0x888>;
        u64-list = /bits/ 64 <0x1111 0x2222 0x3333 0x4444 0x5555 0x6666 0x7777 0x8888>;
    };
    soc: soc { };
    sw: sw { };
};

&soc {
 #address-cells = < 0x1 >;
 #size-cells = < 0x1 >;

 pic_3: pic@100 {
  reg = < 0x100 0x20 >;
  interrupt-controller;
 };
 uart: uart {
  alt-interrupt-parent = < &{/soc/pic@100} >;
  interrupt-parent = < &pic_3 >;
  interrupt-parent-path = &pic_3 ;
 };

 uart1: uart@1000 {
  compatible = "qcom,uart";
  reg = < 0x1000 0x20 0x10000 0x100 0x18000 0x100 >;
  reg-names = "base", "rx", "tx";
  alt-interrupt-parent = < &{/soc/pic@100} >;
  interrupt-parent = < &pic_3 >;
  interrupt-parent-path = &pic_3 ;
 };

 uart2: uart@2000 {
  compatible = "qcom,uart";
  reg = < 0x2000 0x20 >;
  alt-interrupt-parent = < &{/soc/pic@100} >;
  interrupt-parent = < &pic_3 >;
  interrupt-parent-path = &pic_3 ;
 };

 uart3: uart@3000 {
  compatible = "qcom,uart";
  reg = < 0x3000 0x20 >;
  alt-interrupt-parent = < &{/soc/pic@100} >;
  interrupt-parent = < &pic_3 >;
  interrupt-parent-path = &pic_3 ;
 };
};

&sw {
        boot {

                config = <0x0000 0x0000 0x0001>;
        };
};
