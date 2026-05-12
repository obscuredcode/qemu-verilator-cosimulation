#include <verilated.h>
#include "pci_spec.h"
#include "obj_dir/Vpci_wrapper.h"

#define SEND(pci,x) {\
    Verilated::timeInc(1);\
    pci->FRAMEn_in = 0\
    pci->IDSEL = 1;\
    pci->IRDYn_in = 1;\
    x\
    pci->CLK = 1; \
    pci->eval(); \
}

void idle_clk(Vpci_wrapper *pci, unsigned int cycles) {
    for (unsigned int i = 0; i < cycles; i++) {
        Verilated::timeInc(1);
        pci->FRAMEn_in = 1;
        pci->IDSEL = 0;
        pci->IRDYn_in = 1;
        pci->CLK = 1;
        pci->eval();

        Verilated::timeInc(1);
        pci->FRAMEn_in = 1;
        pci->IDSEL = 0;
        pci->IRDYn_in = 1;
        pci->CLK = 0;
        pci->eval();

    }
}

int main(int argc, char **argv) {
    Verilated::commandArgs(argc, argv);
    Verilated::traceEverOn(true);

    Vpci_wrapper *vpci_wrapper = new Vpci_wrapper;



    return 0;
}