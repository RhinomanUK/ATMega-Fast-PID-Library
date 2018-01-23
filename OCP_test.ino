/* Output compare match test code
  
  InputCapture_test.ino

  Code to test the use of the Output Compare function
  Toggles the OCP4A output every time an OCP match occurs
  
  
  
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
*/

#define outPin 6  //OCP4A

uint16_t baseTime = 625;

void setup()
{

  pinMode(outPin, OUTPUT);
  
  // initialize timer4 
  noInterrupts();           // disable all interrupts
  TCCR4A = 0;
  TCCR4B = 0;
  TCNT4  = 0;               // reset the timer

  //initialise OCP4 for a 50Hz square wave

  OCR4A = baseTime;         // compare match register 16MHz/256/625 = 100Hz toggle = 50Hz
  
  // clear OCR4A pin on interrupt match
  TCCR4A |= (1 << COM4A1); 
  TCCR4A &= (0 << COM4A0); 	
  
  //OCR4B and OCR4C are normal pin operation
  //TCCR4A = (0 << COM4B1) | (0 << COM4B0);
  //TCCR4A &= (0 << COM4C1) | (0 << COM4C0);	
  
  TCCR4B &= (0 << WGM11) | (0 << WGM12);    // Normal mode (don't reset timer!!!)
  
  TCCR4B |= (1 << CS12);    // 256 prescaler 
  TIMSK4 |= (1 << OCIE4A);  // enable timer compare interrupt
  interrupts();             // enable all interrupts
}




ISR(TIMER4_COMPA_vect)          // timer compare interrupt service routine
{
	// the pin gets set/cleared on timer match. Here we set the value the pin is set to on the next 
	// timer match
  
  volatile byte nextState;
   
  if( nextState){   
      TCCR4A |= (1 << COM4A1);
      TCCR4A &= (0 << COM4A0);  }   // clear OCR4A pin on interrupt match
  else{ 
      TCCR4A &= (0 << COM4A1);
      TCCR4A |= (1 << COM4A0); }               // or set OCR4A pin on interrupt match

  nextState = digitalRead(outPin) ^ 1;  //get the current (new) pin value and toggle it
  OCR4A += baseTime;     //set up next match
}



void loop()
{
  // nothing to do here
}


//
