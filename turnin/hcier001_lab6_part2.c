/*	Author: lab
 *  Partner(s) Name: none
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#include "timer.h"
#endif
enum States{start, zero, one, two} state;
//volatile unsigned char
// TimerFlag=0;
//void
// TimerISR(){TimerFlag=1;}
unsigned char i;
unsigned char button;
void Tick(){
	switch(state) { //transitions
		case start:
			state = zero;
			break;
		case zero:
			if(button == 0x00){
				state = one;
			}
			else if(button == 0x01){
				state = zero;
			}
			break;
		case one:
			if(button == 0x00 && i % 2 !=0){
				state = two;
			}
			else if(button == 0x00 && i % 2 ==0){
				state = zero;
			}
			else if(button == 0x01){
				state = one;
			}
				
			break;
		case two:
			if(button == 0x00){
				state = one;
			}
			else if(button==0x01){
				state = two;
			}

			break;
		default:
			state = start;
			break;
		}
	switch(state){ //actions
		case start:
			break;
		case zero:
			PORTB=0x01;
			i++;
			break;
		case one:
			PORTB = 0x02;
			break;
		case two:
			PORTB = 0x04;
			i++;
			break;
		default:
			break;
		}
	}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA =0x00; PORTA =0xff;
	DDRB =0xff; PORTB = 0x00;
	//	unsigned char led = 0x00;
	 button = 0x00;
	i=0;
	state = start;
	TimerSet(30);
	TimerOn();
    /* Insert your solution below */
    while (1) {
	button = ~PINA;
	Tick();
	while(!TimerFlag){}
	TimerFlag=0;
//
/*	button = ~PINA & 0x01;
	if(button){
		led = (led & 0xfc) | 0x01;
	}
	else{
		led = (led & 0xfc) | 0x02;
	}
	PORTB = led; */
    
    }
    return 1;
}
