************ Usage Notes ************
1). .dcb_config_SM8650.json file can bot be edited by user, it defines LCP region restriction

2). User can edit variable “config” in the SM8650_LCP_region.py to cpnfigure LCP region start addr and size accornding to needs

3). When the VM LCP start address and/or size changes, update VM region in below DTSI file to align this change. 
            kernel-5.15\kernel_platform\qcom\proprietary\devicetree\qcom\pineapple.dtsi 
            trust_ui_vm_mem: trust_ui_vm_region@f3800000 {
                    compatible = "shared-dma-pool";
                    reg = <0x0 0xf3800000 0x0 0x4400000>;
                    reusable;
                    alignment = <0x0 0x400000>;
            };

            oem_vm_mem: oem_vm_region@f7c00000 {
                    compatible = "shared-dma-pool";
                    reg = <0x0 0xf7c00000 0x0 0x4c00000>;
                    reusable;
                    alignment = <0x0 0x400000>;
            };


************ Usage Example ************
1). Please ensure to have python 3.8.2 or higher version installed. 
    (Execute "python -V" on terminal/command promompt to check python version.)

2). Example to generate a LCP region json file
    python <boot_build_path>\boot_images\boot\QcomPkg\SocPkg\Milos\Tools\LCP\Milos_LCP_region.py --target=SM8650 -o <absolute_path>\output -d <absolute_path>\.dcb_config_SM8650.json

2). Example to update xbl_config.elf to include LCP bin
    python <boot_build_path>\boot_images\boot\QcomPkg\SocPkg\Milos\Tools\LCP\lcp.py --target=SM8650 -v DEBUG -s <meta_build_path>\common\sectoolsv2\ext -o <absolute_path>\output in -l <absolute_path>\LCP.bin -x <absolute_path>\xbl_config.elf

3). Example to update DCB bins to include LCP bin
    python <boot_build_path>\boot_images\boot\QcomPkg\SocPkg\Milos\Tools\LCP\lcp.py --target=SM8650 -v DEBUG -o <absolute_path>\output  in -l <absolute_path>\LCP.bin -x <absolute_path>\<dcb_bin_path>

4). Example to convert lcp josn file to LCP region bin file
    python <boot_build_path>\boot_images\boot\QcomPkg\SocPkg\Milos\Tools\LCP\lcp.py --target=SM8650 -v DEBUG -o <absolute_path>\output convert -d <absolute_path>\.dcb_config_SM8650.json -l <absolute_path>\SM8650_LCP_region.json

5). Example to convert lcp bin file to LCP region json file
    python <boot_build_path>\boot_images\boot\QcomPkg\SocPkg\Milos\Tools\LCP\lcp.py --target=SM8650 -v DEBUG -o <absolute_path>\output convert -d <absolute_path>\.dcb_config_SM8650.json -l <absolute_path>\SM8650_LCP_region.bin
