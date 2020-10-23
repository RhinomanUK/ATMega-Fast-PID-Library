void setup() {
  // put your setup code here, to run once:
  
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:

  //digitalWrite(LED_BUILTIN, HIGH);  // digitalwrite takes approx 5.3us/85cycles
  PORTB = 0x80;     //LED on

 //---------------------------------------------------------------------------------  
  
  // fast no division - rescaled for >>16
 
  volatile unsigned long ki = 4072;     // (509*32)
  volatile unsigned long  e = 157;
  // volatile unsigned int  f = 8192; (1/8192 = >>11)
  
  int  i = (ki*e)>>16;

  // answer = 9, takes approx. 7.36us/cycles 
  //---------------------------------------------------------------------------------    
   
  PORTB = 0x00; //LED off

  Serial.println(i);
  delay(1000);
  
}

/*
 * Fixed point binary bit values:     0.630573
 * 0:16 resolution gives a resolution of approx. 0.0000148;
 *        so almost 6 decimal places of accuracy
 * 
 * 10000000 00000000 = 0.5                          1    0.130570
 * 01000000 00000000 = 0.25                         0                  
 * 00100000 00000000 = 0.125                        1    0.00557            
 * 00010000 00000000 = 0.0625                       0      
 * 00001000 00000000 = 0.03125                      0      
 * 00000100 00000000 = 0.015625                     0    
 * 00000010 00000000 = 0.078125                     0   
 * 00000001 00000000 = 0.00380625                   1    0.00176675   
 * 00000000 10000000 = 0.001903125                  0               
 * 00000000 01000000 = 0.0009515625                 1   0.0008151875                      
 * 00000000 00100000 = 0.00047578125                1   0.00033940625
 * 00000000 00010000 = 0.000237890625               1   0.000101515625
 * 00000000 00001000 = 0.0001189453125              0   
 * 00000000 00000100 = 0.00005947265625             1   0.00004204296875
 * 00000000 00000010 = 0.000029736328125            1   0.000012306640625   
 * 00000000 10000001 = 0.0000148681640625           0       
 */
