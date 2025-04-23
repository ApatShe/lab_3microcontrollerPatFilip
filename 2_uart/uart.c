#include "gpio.h"
#include "uart.h"

#define __UART_INT_TX_PIN__  6
#define __UART_INT_RX_PIN__  8 

void configure_pins(){
    
    GPIO->PIN_CNF[__UART_INT_TX_PIN__] = (1 << 0) | (0 << 2);  
    GPIO->PIN_CNF[__UART_INT_RX_PIN__] = (0 << 0) | (1 << 2);  
}

void uart_init() {
    configure_pins();  // Must be called first!
    
    UART->PSELTXD = __UART_INT_TX_PIN__;  // No typecast needed for constants
    UART->PSELRXD = __UART_INT_RX_PIN__;
    UART->BAUDRATE = 0x00275000;  // 9600 baud
    UART->PSELRTS = 0xFFFFFFFF;   // Disable RTS
    UART->PSELCTS = 0xFFFFFFFF;   // Disable CTS
    UART->ENABLE = 4;             // Enable UART (4 = enabled)
    UART->TASKS_STARTRX = 1;      // Start receiving
    UART->EVENTS_RXDRDY = 0;
    UART->EVENTS_TXDRDY = 0;

}

void uart_send(char letter){
    UART->EVENTS_TXDRDY = 0; //clear interrupt
    UART->TASKS_STARTTX = 1; //start sending command
    UART->TXD = letter;

   while(!UART->EVENTS_TXDRDY){

   }     //clear interupt generated when sending finishes
    
    
   
    UART->TASKS_STOPTX = 1;  //stop the process of transmitting
}

char uart_read(){

    
    
    if(!UART->EVENTS_RXDRDY){
        return '\0';
    }
    else{
        UART->EVENTS_RXDRDY = 0;   //avoiding packet losss
        return (char) UART->RXD; //typecasting the RXD data into char as first 8 bits is the char
    }
    
    
}