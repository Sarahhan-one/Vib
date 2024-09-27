
/* 
 * CEC VIB prototype
 * Adding bluetooth interface HC-05 to give directional information via laptop
 */

#define F_CPU 8000000UL
#define __DELAY_BACKWARD_COMPATIBLE__

#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>


#define UBRRVAL 51 //initialize USART with 9600 baud rate

//Define input pins
#define SW PC4
#define RX PD0 
#define TX PD1

//Define output pins
#define LED PC5 //LED output
#define STR PD2 //Motor outputs
#define LEFT PD3
#define RIGHT PD4

//Define variables 
uint16_t intensity = 100;
unsigned char  rxdata; 

//Define messages 
unsigned char defaultmsg[] = "Directional Information: \n";

static void init(){
    PORTC &= ~(1<<SW); // ip starts low
    PORTD &= ~((1<<LED)|(1<<STR)|(1<<LEFT)|(1<<RIGHT)); //op starts LOW
    
    DDRC &= ~(1<<SW); // set switch as ip
    DDRD |= ((1<<LED)|(1<<STR)|(1<<LEFT)|(1<<RIGHT)); //set pins as ops
}

void usart_init(void) {
    UBRR0H = (unsigned char)(UBRRVAL>>8); //baud rate register high
    UBRR0L = (unsigned char)UBRRVAL; //baud rate register low
    UCSR0B |= (1<<TXEN0) | (1<<RXEN0); //enable transmitter and receiver
    UCSR0C |= (1<<UCSZ01) | (1<<UCSZ00); //set data frame format: asynchronous mode, no parity, 1 stop bit, 8 bit size
}


unsigned char receivebyte(void) {
    while(!(UCSR0A & (1<<RXC0))); //check all the data is received 
        return UDR0; 
}

static void vibration_on(rxdata, intensity){
    if (rxdata == 'f'){
        PORTD |= (1<<STR);
        _delay_ms(intensity*3);
        PORTD &= ~(1<<STR);
        _delay_ms(intensity*3);
        
        sendstr(defaultmsg); //messages
    } 
    else if (rxdata == 'l') {
        PORTD |= (1<<LEFT);
        _delay_ms(intensity*3);
        PORTD &= ~(1<<LEFT);
        _delay_ms(intensity*3);
        
        sendstr(defaultmsg); //messages  
    } 
    else if (rxdata == 'r') {
        PORTD |= (1<<RIGHT);
        _delay_ms(intensity*3);
        PORTD &= ~(1<<RIGHT);
        _delay_ms(intensity*3);
        
        sendstr(defaultmsg); //messages
    } 
}

static void intensity_on() {//change the vibration intensity
    switch (intensity) {
        case 100: 
            intensity = 500; 
            PORTC |= (1<<LED);//LED ON 
            break; 
        case 500: 
            intensity = 100; 
            PORTC &= ~(1<<LED);//LED OFF
            break; 
    }
}

void sendbyte(unsigned char MSG) {
    while((UCSR0A&(1<<UDRE0))==0);//check if data register, UDR0, is ready to receive new data 
    UDR0 = MSG; 
}

void sendstr(unsigned char *s) {
    unsigned char i = 0;
    while(s[i] != '\0'){
        sendbyte(s[i]);
        i++;
    }
}

int main(){
    init();
    usart_init();
    
    while(1){
        
        rxdata = receivebyte(); //receive the directional input via bluetooth
        
        if (!(PINC&(1<<SW))){ //if switch is pressed (low)
            _delay_ms(100);
            if (PINC&(1<<SW)){ //switch released (High))
                intensity_on();
            }
        }
        vibration_on(rxdata, intensity); //motor vibrates accordingly
    }
    return 0;
}

