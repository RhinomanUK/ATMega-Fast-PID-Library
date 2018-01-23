/*  
  InputCapture_test.ino

  Code to test the use of ICPHandler routines.
  Toggles onboard LED on receipt of an ICP event.
  Note that it doesn't actually use the captured value 
  which is stored in ICRnH and ICRnL as would be expected in a 'real' programme
  
  
  
  This code is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This code is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General
  Public License along with this code; if not, write to the
  Free Software Foundation, Inc., 59 Temple Place, Suite 330,
  Boston, MA  02111-1307  USA
  
  James Holland
  Version 1 - 16th January 2018
*/

#include <avr/interrupt.h>			//needed for ISR() (if not defined elsewhere?)


//declare a function pointer type https://www.eskimo.com/~scs/cclass/int/sx10a.html
typedef void (*funcptr)();
funcptr pfi;


static void nothing(void) {
}


//enable interrupts

void attachICPInterrupt(uint8_t ICPChannel, void (*userFunc)(void), int triggerEdge) {
	
	//set up pointer to the trigger_xxx function
   pfi = userFunc;
	
    // Configure the interrupt mode (trigger on rising edge, or falling edge).
	// the triggerEdge value is the same as the hardware value
    // so 0=rising, 1=falling
	
		// ICNCx: Enable Input Capture Noise Canceler
				// ICESx: =1 for trigger on rising edge
				// CS10: =1 set prescaler to 1x system clock (F_CPU)
      

	switch (ICPChannel) {
		
		case 1:
			TCCR1B = (0<<ICNC1) | (triggerEdge<<ICES1) | (1<<CS10);  		//********************* does this affect the timer????????
			//{ TCCR1B &= ~(1<<ICES1); TIFR1 |= (1<<ICF1); rising = 0; } 	//******** why is this needed?
			TIFR1 = (1<<ICF1);			// clear pending interrupt
			TIMSK1 = (1<<ICIE1);		// and enable
			break;
			
		case 3:
			TCCR3B = (0<<ICNC3) | (triggerEdge<<ICES3) | (1<<CS10);
			TIFR3 = (1<<ICF3);			// clear pending interrupt
			TIMSK3 = (1<<ICIE3);		// and enable
			break;
		
		case 4:
   		TCCR4B = (0<<ICNC4) | (triggerEdge<<ICES4) | (1<<CS10);
			TIFR4 = (1<<ICF4);			// clear pending interrupt
			TIMSK4 = (1<<ICIE4);		// and enable
			break;
		
		case 5:
			TCCR5B = (0<<ICNC5) | (triggerEdge<<ICES5) | (1<<CS10);
			TIFR5 = (1<<ICF5);			// clear pending interrupt
			TIMSK5 = (1<<ICIE5);		// and enable
			break;
			
		default:
			#warning attempt to enable invalid ICP channel.
			break;
	}
}

//disable interrupts

void detachICPInterrupt(uint8_t ICPChannel) {
	
	//clear the interrupt enable bit
  switch(ICPChannel){
	case 1:
			TIMSK1 = (0<<ICIE1);
			break;
			
		case 3:
			TIMSK3 = (0<<ICIE3);
			break;
		
		case 4:
			TIMSK4 = (0<<ICIE4);
			break;
		
		case 5:
			TIMSK5 = (0<<ICIE5);
			break;
			
		default:
			#warning attempt to disable invalid ICP channel.
			break;
	}
}


// ICP ISRs, use the function pointer to call the corrrect routine
// for this test they all point to the same routine

ISR(TIMER1_CAPT_vect) {
	pfi();
}

ISR(TIMER3_CAPT_vect) {
	pfi();
}

ISR(TIMER4_CAPT_vect) {
	pfi();
}

ISR(TIMER5_CAPT_vect) {
	pfi();
}


//************* thats's all folks *************************
  
