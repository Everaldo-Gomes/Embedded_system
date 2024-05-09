#ifndef PMU_H
#define PMU_H

#include <pmu_common.h>
#include <stdint.h>

void print_regs(); // debug
void PMU_start(uint32_t event_qnt, uint32_t events[]);
void PMU_stop();
void PMU_counters_reset();


static inline void pmuserenr_el0(uint32_t val)
{
	ASM("msr pmuserenr_el0, %0\n\t" :: "r"(val));
}

static inline uint32_t get_pmuserenr_el0()
{
	uint32_t val;
	ASM("mrs %0, pmuserenr_el0\n\t" : "=r"(val) ::);
	return val;
}

static inline void pmcr_el0(uint32_t val)
{
	ASM("msr pmcr_el0, %0\n\t" :: "r"(val));
}

static inline uint32_t get_pmcr_el0()
{
	uint32_t val;
	ASM("mrs %0, pmcr_el0\n\t" : "=r"(val) ::);
	return val;
}

static inline void pmcntenset_el0(uint32_t val)
{
	ASM("msr pmcntenset_el0, %0\n\t" :: "r"(val));
}

static inline uint32_t get_pmcntenset_el0()
{
	uint32_t val;
	ASM("mrs %0, pmcntenset_el0\n\t" : "=r"(val) ::);
	return val;
}

static inline void pmcntenclr_el0(uint32_t val)
{
	ASM("msr pmcntenclr_el0, %0\n\t" :: "r"(val));
}

static inline uint32_t get_pmcntenclr_el0()
{
	uint32_t val;
	ASM("mrs %0, pmcntenclr_el0\n\t" : "=r"(val) ::);
	return val;
}

static inline void pmselr_el0(uint32_t val)
{
	ASM("msr pmselr_el0, %0\n\t" :: "r"(val));
}

static inline uint32_t get_pmselr_el0()
{
	uint32_t reg;
	ASM("mrs %0, pmselr_el0\n\t" : "=r"(reg) ::);
	return reg;
}

static inline void pmxevtyper_el0(uint32_t event)
{
	ASM("msr pmxevtyper_el0, %0\n\t" :: "r"(event));
}

static inline uint32_t get_pmxevtyper_el0()
{
	uint32_t val;
	ASM("mrs %0, pmxevtyper_el0\n\t" : "=r"(val) ::);
	return val;
}

static inline void pmxevcntr_el0(uint32_t val)
{
	ASM("msr pmxevcntr_el0, %0\n\t" :: "r"(val));
}

static inline uint32_t get_pmxevcntr_el0()
{
	uint32_t val;
	ASM("mrs %0, pmxevcntr_el0\n\t" : "=r"(val) ::);
	return val;
}

static inline void pmovsclr_el0(uint32_t val)
{
	ASM("msr pmovsclr_el0, %0\n\t" :: "r"(val));
}

static inline uint32_t get_pmovsclr_el0()
{
	uint32_t val;
	ASM("mrs %0, pmovsclr_el0\n\t" : "=r"(val) ::);
	return val;
}

static inline void pmswinc_el0(uint32_t val)
{
	ASM("msr pmswinc_el0, %0\n\t" :: "r"(val));
}

static inline uint32_t get_pmswinc_el0()
{
	uint32_t val;
	ASM("mrs %0, pmswinc_el0\n\t" : "=r"(val) ::);
	return val;
}



#endif
