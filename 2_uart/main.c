#include "gpio.h"
#include "uart.h"
#include <stdio.h>
#include <stdbool.h>
#include <sys/types.h> // For ssize_t

ssize_t _write(int fd, const void *buf, size_t count){
    char * letter = (char *)(buf);
        for(int i = 0; i < count; i++){
            uart_send(*letter);
            letter++;
        }
    return count;
}


bool leds_are_on = false;
void button_init(){ 
    GPIO->PIN_CNF[13] = (0 << 0) | (3 << 2);  // Input + pullup
    GPIO->PIN_CNF[14] = (0 << 0) | (3 << 2);
    
}

void led_init(){
	for(int i = 17; i <= 20; i++){
		GPIO->DIRSET = (1 << i);
		GPIO->OUTSET = (1 << i);
	}
}

void leds_off(){
	GPIO->OUTSET = (1 << 17);
	GPIO->OUTSET = (1 << 18);
	GPIO->OUTSET = (1 << 19);
	GPIO->OUTSET = (1 << 20);
    leds_are_on = false;
}

void leds_on(){
	GPIO->OUTCLR = (1 <<17);  //trekk porten lav utifra active-low 
	GPIO->OUTCLR = (1 <<18);
	GPIO->OUTCLR = (1 <<19);
	GPIO->OUTCLR = (1 <<20);
    leds_are_on = true;
}

int main(){
    uart_init();
    button_init();
    led_init();

    while (1){

        iprintf("The average grade in TTK%d was in %d was: %c\n\r",4235
            ,2022,'B');
        

        if (!(GPIO->IN & (1 << 13))){
			uart_send('A');
		}
		

		if (!(GPIO->IN & (1 << 14))){
			uart_send('B');
            
            // uart
		}

        char c = uart_read();
        if (c != '\0') {
            if (leds_are_on) {
                leds_off();
            } else {
                leds_on();
            }
        }

    }


return 0;
}