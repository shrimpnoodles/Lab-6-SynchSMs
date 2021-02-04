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
enum States {start, init, p0push, p1push, wait1, wait2, reset} state;
unsigned char portcCount;
unsigned char button;
unsigned char count;
void Tick(){
	switch(state) { //transitions
		case start:
			state = init;
			break;
		case init:
			if(button == 0x01){
				state = p0push;
			}
			else if(button== 0x02){
				state = p1push;
			}
			else if(button== 0x03){
				state = reset;
			}
			break;
		case p0push:
		//	if(button ==0x01){
		//		state = p0push;
		//	}
		//	else{
			state = wait1;
		//	}
			break;
		case wait1:
			if(button == 0x02){
				state = p1push;
			}
			else if(button == 0x03){
				state = reset;
			}
			else if(button==0x00){
				state = init;
			}
			else if(button ==0x01 && count != 0){
				state = wait1;
			}
			else if(button == 0x01 && count ==0){
				state = p0push;
			}
			else{
				state = wait1;
			}
			break;
		case p1push:
		//	if(button == 0x02){
		//		state = p1push;
		//	}
		//	else{
			state = wait2;
		//	}
			break;
		case wait2:
			if(button==0x03){
				state = reset;
			}
			else if(button == 0x00){
				state = init;
			}
			else if(button==0x01){
				state = p0push;
			}
			else if(button == 0x02 && count!=0){
				state = wait2;
			}
			else if(button == 0x02 && count == 0){
				state = p1push;
			}
			else{
				state = wait2;
			}
			break;
		case reset:
			if(button == 0x03){
				state = reset;
			}
			else if(button==0x01){
				state = p0push;
			}
			else if(button==0x02){
				state = p1push;
			}
			break;
		default:
			state = start;
			break;
		}
	switch(state){ //actions
		case init:
			//portcCount = 7;
			break;
		case p0push:
			count = 10;
			if(portcCount < 9){
				portcCount = portcCount +1;
			}
			break;
		case p1push: 
			count = 10;
			if(portcCount > 0){
				portcCount = portcCount -1;
			}
			break;
		case wait1:
			count--;
			break;
		case wait2:
			count--;
			break;
		case reset:
			portcCount =0;
			break;
		default:
			break;
	}
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0X00; PORTA = 0XFF;
	DDRB = 0XFF; PORTB = 0X00;
//	DDRC = 0xFF; PORTC = 0X00;
	button = 0x00;
	count = 10;
	TimerSet(10);
	TimerOn();
	state = start;
	portcCount = 7;
    /* Insert your solution below */
    while (1) {
	button = ~PINA;
	Tick();
	PORTB = portcCount;
	while(!TimerFlag){};
	TimerFlag=0;
    }
    return 1;
}
