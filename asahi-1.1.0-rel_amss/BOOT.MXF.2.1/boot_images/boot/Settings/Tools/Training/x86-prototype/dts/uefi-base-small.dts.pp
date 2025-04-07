
/dts-v1/;
/plugin/;

/ {
 model = "QC-Overlay";
 compatible = "qcom,overlay";

 soc: soc {
 };




 firmware {
  qcom_scm {
  };
 };

};

&soc {
 qcom,wdt@17410000 {
 };
 kryo-erp {
 };
 qcom_tzlog: tz-log@14680720 {
 };
 arch_timer: timer {
 };
};
