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
void Tick(){
	switch(state) { //transitions
		case start:
			state = zero;
			break;
		case zero:
			if((PINA)==0x01){
				state = one;
			}
			else if((PINA) == 0x00){
				state = zero;
			}
			break;
		case one:
			if(PINA==0x01 && i % 2 !=0){
				state = two;
			}
			else if(PINA==0x01 && i % 2 ==0){
				state = zero;
			}
			else if(PINA==0x00){
				state = one;
			}
				
			break;
		case two:
			if(PINA==0x01){
				state = one;
			}
			else if(PINA==0x00){
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
	DDRA =0xff; PORTA =0x00;
	DDRB =0xff; PORTB = 0x00;
		
	i=0;
	state = start;
	TimerSet(200);
	TimerOn();
    /* Insert your solution below */
    while (1) {
	Tick();
	while(!TimerFlag){}
	TimerFlag=0;
    
    }
    return 1;
}
