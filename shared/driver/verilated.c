#include <linux/module.h>
#include <linux/pci.h>

#define VERILATED_PCI "verilated-pci-driver"

static struct pci_device_id verilated_driver_id_table[] = {
	{PCI_DEVICE(0x1234, 0x11e9)},
	{0,}
};

MODULE_DEVICE_TABLE(pci,verilated_driver_id_table);

static int verilated_probe(struct pci_dev *pdev, const struct pci_device_id *ent);
static void verilated_remove(struct pci_dev *pdev);

static struct pci_driver verilated_driver = {
	.name=VERILATED_PCI,
	.id_table=verilated_driver_id_table,
	.probe=verilated_probe,
	.remove=verilated_remove
};
static int verilated_probe(struct pci_dev *pdev, const struct pci_device_id *ent) {
	u16 vendor, device;
	pci_read_config_word(pdev, PCI_VENDOR_ID, &vendor);
	pci_read_config_word(pdev, PCI_DEVICE_ID, &device);
	printk(KERN_INFO "Device vid: 0x%X did: 0x%X\n", vendor, device);
	return 0;
}

static void verilated_remove(struct pci_dev *pdev) {
	pci_disable_device(pdev);
}


static int __init verilated_init(void);
static void __exit verilated_exit(void);


static int __init verilated_init(void) {
	return pci_register_driver(&verilated_driver);
};

static void __exit verilated_exit(void) {
	pci_unregister_driver(&verilated_driver);
}


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mac Mac Millan <macmillan1702@gmail.com");
MODULE_DESCRIPTION("Emulated Verilog PCI Driver");
MODULE_VERSION("0.1");

module_init(verilated_init);
module_exit(verilated_exit);

