#include "gpio.h"
#include "uart.h"

#define __UART_INT_TX_PIN__  6
#define __UART_INT_RX_PIN__  8 

void configure_pins(){
    
    GPIO->PIN_CNF[__UART_INT_TX_PIN__] = (uint32_t) (1 << 0);  //output
    GPIO->PIN_CNF[__UART_INT_RX_PIN__] = (uint32_t) (0 << 0);  //input
}

void uart_init(){
    UART->PSELTXD = (uint32_t) __UART_INT_TX_PIN__;
    UART->PSELRXD = (uint32_t) __UART_INT_RX_PIN__;
    UART->BAUDRATE = 0x00275000;
    UART->PSELRTS = 0xFFFFFFFF;
    UART->PSELCTS = 0xFFFFFFFF;
    UART->ENABLE = (uint32_t) 4;
    UART->TASKS_STARTRX = (uint32_t) 1; 
}

void uart_send(char letter){
    UART->TASKS_STARTTX = 1; //start sending command
    UART->TXD = letter;

   while(!UART->EVENTS_TXDRDY){

   }     //clear interupt generated when sending finishes
    
    
    UART->EVENTS_TXDRDY = 0;
    UART->TASKS_STOPTX = 1;  //stop the process of transmitting
}

char uart_read(){

    
    
    if(!UART->EVENTS_RXDRDY){
        return '\0';
    }
    else{
        UART->EVENTS_RXDRDY = 0;   //avoiding packet losss
        return (char) UART->RXD; //typecasting the RXD data into char as first 8 bits are the chars
    }
    
    
}