#include "./inc/pmu.h"


int main(void)
{
    printf("Init FreeRTOS\n\n");

	uint32_t events[] = {MEM_ACCESS_LD, MEM_ACCESS_ST, DATA_MEMORY_ACCESS, CPU_CYCLE, BUS_CYCLE, BUS_ACCESS};
	hc_pmu_start(6, events);

	volatile int a = 0;
	for (int i = 0; i < 5; i++)
		a++;
	
	hc_pmu_stop();	
	return 0;
}
