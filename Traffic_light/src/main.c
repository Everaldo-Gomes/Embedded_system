#include <stdint.h>

#define RCC_BASE_ADDR    0x40023800U
#define GPIOA_BASE_ADDR  0x40020000U
#define SYSCFG_BASE_ADDR 0x40013800U
#define EXIT_BASE_ADDR   0x40013C00U
#define APB2_BASE_ADDR   0x40010000U

void delay();
void setup_regiters();
void button_pressed();


uint32_t *pRCC_AHB1ENR = (uint32_t*) (RCC_BASE_ADDR + 0x30);
uint32_t *pRCC_APB2ENR = (uint32_t*) (RCC_BASE_ADDR + 0x44);

uint32_t *pGPIOA_MODER   = (uint32_t*) (GPIOA_BASE_ADDR + 0x0);
uint32_t *pGPIOA_OTYPER  = (uint32_t*) (GPIOA_BASE_ADDR + 0x04);
uint32_t *pGPIOA_OSPEEDR = (uint32_t*) (GPIOA_BASE_ADDR + 0x08);
uint32_t *pGPIOA_PUPDR   = (uint32_t*) (GPIOA_BASE_ADDR + 0x0C);
uint32_t *pGPIOA_BSRR    = (uint32_t*) (GPIOA_BASE_ADDR + 0x18);

uint32_t *pSYSCFG_EXTICR3 = (uint32_t*) (SYSCFG_BASE_ADDR + 0x10);
uint32_t *pEXTI_IMR       = (uint32_t*) (EXIT_BASE_ADDR + 0x00);
uint32_t *pEXTI_RTSR      = (uint32_t*) (EXIT_BASE_ADDR + 0x08);
uint32_t *EXTI_PR         = (uint32_t*) (EXIT_BASE_ADDR + 0x14);


int main(void)
{
	setup_regiters();

	while (1)
	{
		button_pressed();

		*pGPIOA_BSRR |= (1 << 4); //PA4
		*pGPIOA_BSRR |= (1 << 5); //PA5
		*pGPIOA_BSRR |= (1 << 9); //PA9

		delay();
		*pGPIOA_BSRR |= (1 << 20); //PA4
		*pGPIOA_BSRR |= (1 << 1);  //PA1

		delay();
		*pGPIOA_BSRR |= (1 << 17);//PA1
		*pGPIOA_BSRR |= (1 << 0); //PA0

		delay();
		button_pressed();
		*pGPIOA_BSRR |= (1 << 21); //PA5
		*pGPIOA_BSRR |= (1 << 7);  //PA7

		delay();
		*pGPIOA_BSRR |= (1 << 23); //PA7
		*pGPIOA_BSRR |= (1 << 6);  //PA6

		delay();
		*pGPIOA_BSRR |= (1 << 22); //PA6
		*pGPIOA_BSRR |= (1 << 5);  //PA5

		delay();
		button_pressed();
		*pGPIOA_BSRR |= (1 << 16); //PA0
	}

    return 0;
}


void delay()
{
	uint32_t time = 2050000;
	while (time--)
	{}
}


void setup_regiters()
{
	// =====
	// GPIOA
	// =====

	// enable peripheral clock
	*pRCC_AHB1ENR |= (1 << 0);

	*pGPIOA_MODER |= (1 << 0);  // PA0
	*pGPIOA_MODER |= (1 << 2);  // PA1
	*pGPIOA_MODER |= (1 << 8);  // PA4
	*pGPIOA_MODER |= (1 << 10); // PA5
	*pGPIOA_MODER |= (1 << 12); // PA6
	*pGPIOA_MODER |= (1 << 14); // PA7
	*pGPIOA_MODER |= (1 << 16); // PA8
	*pGPIOA_MODER |= (1 << 18); // PA9
	*pGPIOA_MODER &= ~((1 << 20) | (1 << 21)); // PA10

	*pGPIOA_OTYPER &= ~(1 << 0);  //PA0
	*pGPIOA_OTYPER &= ~(1 << 1);  //PA1
	*pGPIOA_OTYPER &= ~(1 << 4);  //PA4
	*pGPIOA_OTYPER &= ~(1 << 5);  //PA5
	*pGPIOA_OTYPER &= ~(1 << 6);  //PA6
	*pGPIOA_OTYPER &= ~(1 << 7);  //PA7
	*pGPIOA_OTYPER &= ~(1 << 8);  //PA8
	*pGPIOA_OTYPER &= ~(1 << 9);  //PA9

	*pGPIOA_OSPEEDR |= (1 << 0);  //PA0
	*pGPIOA_OSPEEDR |= (1 << 2);  //PA1
	*pGPIOA_OSPEEDR |= (1 << 8);  //PA4
	*pGPIOA_OSPEEDR |= (1 << 10); //PA5
	*pGPIOA_OSPEEDR |= (1 << 12); //PA6
	*pGPIOA_OSPEEDR |= (1 << 14); //PA7
	*pGPIOA_OSPEEDR |= (1 << 16); //PA8
	*pGPIOA_OSPEEDR |= (1 << 18); //PA9
	*pGPIOA_OSPEEDR |= (1 << 20); //PA10

	*pGPIOA_PUPDR &= ~((1 << 0) | (1 << 1));   //PA0
	*pGPIOA_PUPDR &= ~((1 << 2) | (1 << 3));   //PA1
	*pGPIOA_PUPDR &= ~((1 << 8) | (1 << 9));   //PA4
	*pGPIOA_PUPDR &= ~((1 << 10) | (1 << 11)); //PA5
	*pGPIOA_PUPDR &= ~((1 << 12) | (1 << 13)); //PA6
	*pGPIOA_PUPDR &= ~((1 << 14) | (1 << 15)); //PA7
	*pGPIOA_PUPDR &= ~((1 << 16) | (1 << 17)); //PA8
	*pGPIOA_PUPDR &= ~((1 << 18) | (1 << 19)); //PA9

	// PA10 pull-up to prevent changing values due to circuit noises
	*pGPIOA_PUPDR |= (1 << 20);
	*pGPIOA_PUPDR &= ~(1 << 21);

	// enable  SYSCFG
	*pRCC_APB2ENR |= (1 << 14);

	// EXIT config
	*pSYSCFG_EXTICR3 &= ~((1 << 8) | (1 << 9) | (1 << 10) | (1 << 11)); // external interrupt
	*pEXTI_IMR  |= (1 << 10); // disable mask
	*pEXTI_RTSR |= (1 << 10); // set rising edge trigger
	*EXTI_PR    |= (1 << 10); // clear interrupt flag
}


void button_pressed()
{
	if (*EXTI_PR & (1 << 10))
	{
		*EXTI_PR |= (1 << 10);
		*pGPIOA_BSRR |= (1 << 0);
		*pGPIOA_BSRR |= (1 << 5);
		*pGPIOA_BSRR |= (1 << 8);
		*pGPIOA_BSRR |= (1 << 25);

		delay();

		*pGPIOA_BSRR |= (1 << 9);
		*pGPIOA_BSRR |= (1 << 24);
	}
}
