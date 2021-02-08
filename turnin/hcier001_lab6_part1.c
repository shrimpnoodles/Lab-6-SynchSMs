/*	Author: lab
 *  Partner(s) Name: none
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 *	
 	Submission link: https://drive.google.com/file/d/1sXDZPfbkiWX98v1xCgWPpMFteEpiGVDa/view?usp=sharing
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

void Tick(){
	switch(state) { //transitions
		case start:
			state = zero;
			break;
		case zero:
			state = one;
			break;
		case one:
			state = two;
			break;
		case two:
			state = zero;
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
			break;
		case one:
			PORTB = 0x02;
			break;
		case two:
			PORTB = 0x04;
			break;
		default:
			break;
		}
	}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA =0xff; PORTA =0x00;
	DDRB =0xff; PORTB = 0x00;
		
//	PORTB = 0xff;
	state = start;
	TimerSet(100);
	TimerOn();
    /* Insert your solution below */
    while (1) {
	Tick();
	while(!TimerFlag){}
	TimerFlag=0;
    
    }
    return 1;
}
