//
// Created by macmi on 5/11/26.
//

#ifndef QEMU_COSIM_PCI_SPEC_H
#define QEMU_COSIM_PCI_SPEC_H

#define PCI_INT_ACK       0b0000
#define PCI_SPECIAL_CYCLE 0b0001
#define PCI_IO_READ       0b0010
#define PCI_IO_WRITE      0b0011
#define _PCI_RESERVED1    0b0100
#define _PCI_RESERVED2    0b0101
#define PCI_MEM_READ      0b0110
#define PCI_MEM_WRITE     0b0111
#define _PCI_RESERVED3    0b1000
#define _PCI_RESERVED4    0b1001
#define PCI_CONFIG_READ   0b1010
#define PCI_CONFIG_WRITE  0b1011
#define PCI_MEM_READ_MUL  0b1100
#define PCI_DUAL_ADD_CYC  0b1101
#define PCI_MEM_READ_LINE 0b1110
#define PCI_WRITE_AND_INV 0b1111

#endif //QEMU_COSIM_PCI_SPEC_H
