#ifndef PMU_H
#define PMU_H

#include <stdint.h>

#define SMCC64_FID_VND_HYP_SRVC 0x86000000 | 0x40000000


enum
{
    HC_INVAL = 0,
    HC_IPC = 1,
	HC_PMU_START = 2,
	HC_PMU_READ_REG = 3,
	HC_PRINT_REGS = 9
};

static void hc_pmu_start()
{
	const int hc_id = SMCC64_FID_VND_HYP_SRVC | HC_PMU_START;
	
	__asm__ volatile
		(
			"mov x0, %0\n\t"
			"hvc #0\n\t"
			:: "r" (hc_id) : "x0"
		);
}

static void hc_read_pmu_reg()
{
	const int hc_id = SMCC64_FID_VND_HYP_SRVC | HC_PMU_READ_REG;

	__asm__ volatile (
		"mov x0, %0\n\t"
		"hvc #0\n\t"
		:: "r" (hc_id) : "x0"
		);
}

static void hc_print_regs()
{
	const int hc_id = SMCC64_FID_VND_HYP_SRVC | HC_PRINT_REGS;

	__asm__ volatile (
		"mov x0, %0\n\t"
		"hvc #0\n\t"
		:: "r" (hc_id) : "x0"
		);
}



#endif
