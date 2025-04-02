#include <stdint.h>


#define GPIO ((NRF_GPIO_REGS*)0x50000000)
#define __BUTTON_1_PIN__ 13
#define __BUTTON_2_PIN__ 14
#define __BUTTON_3_PIN__ 15
#define __BUTTON_4_PIN__ 16


typedef struct {
	volatile uint32_t RESERVED0[321];
	volatile uint32_t OUT;
	volatile uint32_t OUTSET;
	volatile uint32_t OUTCLR;
	volatile uint32_t IN;
	volatile uint32_t DIR;
	volatile uint32_t DIRSET;
	volatile uint32_t DIRCLR;
	volatile uint32_t LATCH;
	volatile uint32_t DETECTMODE;
	volatile uint32_t RESERVED1[118]; //(DIRECTMODE - PIN_CNF[0])/4 )
	volatile uint32_t PIN_CNF[32];
} NRF_GPIO_REGS;

void button_init(){ 
    GPIO->PIN_CNF[__BUTTON_1_PIN__] = (0 << 0) | (3 << 2);  //(3 << 16); input, pullup
    GPIO->PIN_CNF[__BUTTON_2_PIN__] = (0 << 0) | (3 << 2);  //(3 << 16); --||--
}
void led_init(){
	for(int i = 17; i <= 20; i++){
		GPIO->DIRSET = (1 << i);
		GPIO->OUTSET = (1 << i);
	}
}

void leds_off(){
	GPIO->OUTSET |= (1 << 17);
	GPIO->OUTSET |= (1 << 18);
	GPIO->OUTSET |= (1 << 19);
	GPIO->OUTSET |= (1 << 20);
}

void leds_on(){
	GPIO->OUTCLR |= (1 <<17);  //trekk porten lav utifra active-low 
	GPIO->OUTCLR |= (1 <<18);
	GPIO->OUTCLR |= (1 <<19);
	GPIO->OUTCLR |= (1 <<20);
}


int main(){
	// Configure LED Matrix
	led_init();
	button_init();
	
	//led_init();

	int sleep = 0;
	while(1){

		
		//Check if button 1 is pressed;
		if (!(GPIO->IN & (1 << __BUTTON_1_PIN__))){
			leds_on();		
		}
		

		if (!(GPIO->IN & (1 << __BUTTON_2_PIN__))){
			leds_off();
		}
		
		//turn on LED matrix if it is. 

		/* Check if button 2 is pressed;
		 * turn off LED matrix if it is. */

		sleep = 10000;
		while(--sleep); // Delay
	}
	return 0;
}
