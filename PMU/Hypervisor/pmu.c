#include <pmu.h>
#include <printk.h>

	
void PMU_start(uint32_t event_qnt, uint32_t events[])
{
	uint32_t enable_mask = PMCNTENSET_EN_EL0_P;
    pmuserenr_el0(get_pmuserenr_el0() | PMUSERENR_EN_EL0);
	
	for (uint32_t event = 0; event < event_qnt; event++)
	{
		enable_mask |= (1 << event);
		
		switch (event)
		{
		case 0:
			pmselr_el0(PMSELR_EL0_N0);
			pmxevtyper_el0(events[0]);
			break;
		case 1:
			pmselr_el0(PMSELR_EL0_N1);
			pmxevtyper_el0(events[1]);
			break;
		case 2:
			pmselr_el0(PMSELR_EL0_N2);
			pmxevtyper_el0(events[2]);
			break;
		case 3:
			pmselr_el0(PMSELR_EL0_N3);
			pmxevtyper_el0(events[3]);
			break;
		case 4:
			pmselr_el0(PMSELR_EL0_N4);
			pmxevtyper_el0(events[4]);
			break;
		case 5:
			pmselr_el0(PMSELR_EL0_N5);
			pmxevtyper_el0(events[5]);
			break;
		}
	}
	
    pmcr_el0(get_pmcr_el0() | PMCR_E | PMCR_P | PMCR_C);
	pmcntenset_el0(get_pmcntenset_el0() | PMCNTENSET_EN_EL0_C | enable_mask);
}


void PMU_stop()
{
    pmuserenr_el0(get_pmuserenr_el0() & ~PMUSERENR_EN_EL0);
	pmcr_el0(get_pmcr_el0() & ~PMCR_E & ~PMCR_P & ~PMCR_C);
	pmcntenset_el0((get_pmcntenset_el0() & ~PMCNTENSET_EN_EL0_C) & PMCNTENSET_EN_EL0_P);

	print_regs();
	PMU_counters_reset();
}


void PMU_counters_reset()
{
	ASM (
		"msr pmevcntr0_el0, %0\n\t"
        "msr pmevcntr1_el0, %0\n\t"
		"msr pmevcntr2_el0, %0\n\t"
		"msr pmevcntr3_el0, %0\n\t"
		"msr pmevcntr4_el0, %0\n\t"
		"msr pmevcntr5_el0, %0\n\t"
		:: "r" (0):
		);
}


void print_regs() // debug 
{
	uint32_t c0, c1, c2, c3, c4, c5;
	c0 = c1 = c2 = c3 = c4 = c5 = 0;

    ASM (
		"mrs %0, pmevcntr0_el0\n\t"
        "mrs %1, pmevcntr1_el0\n\t"
		"mrs %2, pmevcntr2_el0\n\t"
		"mrs %3, pmevcntr3_el0\n\t"
		"mrs %4, pmevcntr4_el0\n\t"
		"mrs %5, pmevcntr5_el0\n\t"
        : "=r" (c0), "=r" (c1), "=r" (c2), "=r" (c3), "=r" (c4), "=r" (c5)
		::
		);
	
	printk("REGS:\n C0: %lu\n C1: %lu\n C2: %lu\n C3: %lu\n C4: %lu\n C5: %lu\n",
		   c0, c1, c2, c3, c4, c5);
}
