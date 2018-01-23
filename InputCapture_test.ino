/*
   InputCapture_test.ino

   Turns the on board LED off then on each time an input capture event occurs
   The routine that toggles the LED is called using a function pointer from an ICP interrupt,
   as supplied this requires an input signal on ICP4.
   ICPHandler.ino is written to be in the style of Arduino's attachInterrupt() etc..
   
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
  Version 1 - 21st January 2018
*/


 #include "ICPhandler.h"
 
 #define falling 0
 #define rising 1
 


// the setup function runs once when you press reset or power the board
void setup() {
   // initialize digital pin LED_BUILTIN as an output.
   pinMode(LED_BUILTIN, OUTPUT);
   pinMode(ICP4, INPUT);
   attachICPInterrupt(ICP4, toggleLED, falling);
}

// the loop function runs over and over again forever
void loop() {
  //do nothing here its all done in the interrupt
}

// toggleLED is called from the ICP interrupt

void toggleLED(void)
{
    digitalWrite(LED_BUILTIN,!digitalRead(LED_BUILTIN));   // toggle the LED
  
}
