
#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zephyr/sys/sys_io.h>
#include <zephyr/dfu/mcuboot.h>


#define OFS0_ADDR     0x0100A100U
#define DUALSEL_ADDR  0x0100A110U
#define OFS1_ADDR     0x0100A180U
#define OFS1_SEC_ADDR 0x0100A200U
#define OFS1_SEL_ADDR 0x0100A280U


#define OFS1_VDSEL1_SHIFT   0
#define OFS1_VDSEL1_MASK    0x3
#define OFS1_LVDAS_SHIFT    2
#define OFS1_HOCOEN_SHIFT   8
#define OFS1_HOCOFRQ1_SHIFT 9
#define OFS1_HOCOFRQ1_MASK  0x3

static void print_word(const char *name, uint32_t addr)
{
	printk("%-9s @0x%08x = 0x%08x\n", name, addr, sys_read32(addr));
}

static void print_ofs1(const char *name, uint32_t addr)
{
	uint32_t value = sys_read32(addr);

	uint32_t vdsel1   = (value >> OFS1_VDSEL1_SHIFT)   & OFS1_VDSEL1_MASK;
	uint32_t lvdas    = (value >> OFS1_LVDAS_SHIFT)    & 0x1;
	uint32_t hocoen   = (value >> OFS1_HOCOEN_SHIFT)   & 0x1;
	uint32_t hocofrq1 = (value >> OFS1_HOCOFRQ1_SHIFT) & OFS1_HOCOFRQ1_MASK;

	printk("%-9s @0x%08x = 0x%08x  VDSEL1=%u LVDAS=%u HOCOEN=%u HOCOFRQ1=%u\n",
	       name, addr, value, vdsel1, lvdas, hocoen, hocofrq1);
}

int main(void)
{

	if (!boot_is_img_confirmed() && boot_is_img_confirmed()) {

	int img_cnf = boot_write_img_confirmed();
	if (img_cnf) {
		printk("confirm failed (%d) - will revert on reboot\n", img_cnf);
	} else {
		printk("image confirmed - now permanent\n");
	}
    }


	printk("--- RA6M5 option-setting memory ---\n");

	print_word("OFS0", OFS0_ADDR);
	print_word("DUALSEL", DUALSEL_ADDR);

	print_ofs1("OFS1", OFS1_ADDR);
	print_ofs1("OFS1_SEC", OFS1_SEC_ADDR);
	print_ofs1("OFS1_SEL", OFS1_SEL_ADDR); 

	while(true){
        printk("Running loop on an new image!\n");
        k_msleep(500);
    }

	return 0;
}