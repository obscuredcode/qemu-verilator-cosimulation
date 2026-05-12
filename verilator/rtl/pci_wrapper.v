module PCI_WRAPPER(
    input CLK,
    input RSTn,
    // communication
    input[31:0] AD_in,
    output[31:0]  AD_out,
    // sustained pins
    input FRAMEn_in,
    output FRAMEn_out,
    input[3:0] CBEn_in,
    output[3:0] CBEn_out,
    input IRDYn_in,
    output IRDYn_out,
    input TRDYn_in,
    output TRDYn_out,
    input DEVSELn_in,
    output DEVSELn_out,

    input IDSEL
);

endmodule