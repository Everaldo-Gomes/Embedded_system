#include "./inc/pmu.h"


int main(void)
{
    printf("FreeRTOS\n\n");
	
	hc_pmu_start();

	volatile int a = 0;
	for (int i = 0; i < 5; i++)
		a++;
	
	//printf("A: %d\n", a);
	
	return 0;
}
