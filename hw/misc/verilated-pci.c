//
// Created by macmi on 5/11/26.
//


#include "qemu/osdep.h"
#include "qemu/log.h"
#include "qemu/units.h"
#include "hw/pci/pci.h"
#include "hw/pci/msi.h"
#include "qemu/timer.h"
#include "qom/object.h"
#include "qemu/main-loop.h" /* iothread mutex */
#include "qemu/module.h"
#include "qapi/visitor.h"

#include <stdint.h>
#include "hw/pci/pci_device.h"
#include "qom/object.h"
#include "qemu/typedefs.h"


#define VERILATED_PCI_DEVICE_ID 0x11e9 // ?
#define VERILATED_PCI_REVISION 0x10



#define TYPE_VERILATED_PCI_DEVICE "verilated"

typedef struct VerilatedPCIState VerilatedPCIState;
DECLARE_INSTANCE_CHECKER(VerilatedPCIState, VerilatedPCI,
                         TYPE_VERILATED_PCI_DEVICE)
struct VerilatedPCIState {
    PCIDevice pdev;
    MemoryRegion mmio;

};



static uint32_t verilated_config_read(PCIDevice* pdev, uint32_t address, int len) {
    return pci_default_read_config(pdev, address, len);
}
static void verilated_config_write(PCIDevice* pdev, uint32_t address, uint32_t value, int len) {
    pci_default_write_config(pdev, address, value, len);
}


static uint64_t verilated_mmio_read(void * opaque, hwaddr addr, unsigned size) {
    VerilatedPCIState *ver = opaque;
    (void)ver;
    return 0;
}

static void verilated_mmio_write(void * opaque, hwaddr addr, uint64_t data, unsigned size) {
    VerilatedPCIState *ver = opaque;
    (void)ver;
}

static const MemoryRegionOps verilated_mmio_ops = {
    .read = verilated_mmio_read,
    .write = verilated_mmio_write,
    .endianness = DEVICE_NATIVE_ENDIAN,
    .valid = {
        .min_access_size = 1,
        .max_access_size = 8,
    },
    .impl = {
        .min_access_size = 1,
        .max_access_size = 8,
    },
};


static void verilated_pci_realize(PCIDevice *pdev, Error **errp) {
    VerilatedPCIState *ver = VerilatedPCI(pdev);
    //uint8_t *pci_conf = pdev->config;
    pdev->config_write = verilated_config_write;
    pdev->config_read = verilated_config_read;
    memory_region_init_io(&ver->mmio, OBJECT(ver), &verilated_mmio_ops, ver, "verilated-pci-mmio", 1 * MiB);
    pci_register_bar(pdev, 0, PCI_BASE_ADDRESS_SPACE_MEMORY, &ver->mmio);


}

static void verilated_pci_uninit(PCIDevice *pdev) {
    //VerilatedPCIState *ver = VerilatedPCI(pdev);
}

static void verilated_instance_init(Object* object) {
    //VerilatedPCIState *ver = VerilatedPCI(object);
}

static void verilated_class_init(ObjectClass *class, const void *data) {
    DeviceClass *dc = DEVICE_CLASS(class);
    PCIDeviceClass *k = PCI_DEVICE_CLASS(class);

    k->realize =  verilated_pci_realize;
    k->exit =   verilated_pci_uninit;
    k->vendor_id = PCI_VENDOR_ID_QEMU;
    k->device_id = VERILATED_PCI_DEVICE_ID;
    k->revision = VERILATED_PCI_REVISION;
    k->class_id = PCI_CLASS_OTHERS;
    set_bit(DEVICE_CATEGORY_MISC, dc->categories);
    dc->desc = "Emulated Verilog PCI Device";
}

static const TypeInfo verilated_pci_types[] = {
    {
        .name          = TYPE_VERILATED_PCI_DEVICE,
        .parent        = TYPE_PCI_DEVICE,
        .instance_size = sizeof(VerilatedPCIState),
        .instance_init = verilated_instance_init,
        .class_init    = verilated_class_init,
        .interfaces = (const InterfaceInfo[]) {
                {INTERFACE_CONVENTIONAL_PCI_DEVICE},
                {}
        }
    }
};

DEFINE_TYPES(verilated_pci_types)