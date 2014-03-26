/* 
Author: Allen Downey

Based on http://arduino.cc/en/Tutorial/AnalogInput
Created by David Cuartielles

modified 30 Aug 2011
By Tom Igoe

License: Public Domain



The following Arduino code works with a circuit developed
by Allen Downey and students in Software Systems that plays
sound by altering the signal sent to the speaker. It works
by using 8 pins to act as bits, turned on or off as designated
by the behavior defined in the ISR timer.

*/


// defining which pins relate to the buttons
int buttonPin1 = 2;
int buttonPin2 = 3;


void setup() {
  // sets resolution measured
  Serial.begin(9600);

  // preparing input pins
  pinMode(buttonPin1, INPUT_PULLUP); 
  pinMode(buttonPin2, INPUT_PULLUP);
  attachInterrupt(0, mod, RISING);

  // initializes the pins we'll be using for bytewise operations
  DDRD = B11100000;
  DDRB = B00111111;
  
  cli();//stop interrupt
 
  //set timer2 interrupt at 40kHz
  TCCR2A = 0;// set entire TCCR2A register to 0
  TCCR2B = 0;// same for TCCR2B
  TCNT2  = 0;//initialize counter value to 0

  // set compare match register
  OCR2A = 150;
  // turn on CTC mode
  TCCR2A |= (1 << WGM21);
  // Set CS21 bit for 8 prescaler
  TCCR2B |= (1 << CS21); 
  // enable timer compare interrupt
  TIMSK2 |= (1 << OCIE2A);

  sei();//allow interrupts
}

/* 
writebyte determines which pins are on (bits in the byte, essentially).
The difficulty here comes from the pins we're using being on two
different ports.

We know that the number will only require 8 bits because we integers
being cycled through have a max of 255

*/
void writeByte(int x) {
  // our circuit requires us to invert the number
  x = ~x;

  // We start off by turning off the pins we want to use
  PORTD &= B00111111;

  // Then we flip the bits according to the integer input. This requires us
  // to left shift the byte by 6 since we're only using the final two pins
  PORTD |= (x<<6);

  // Same as before but on this port, which has pins 8 - 15, we need the first
  // six.
  PORTB &= B11000000;

  // The first two bits of x were taken care of on the first port, now we 
  // need to handle the final 6 bits, so the 8 bit number must be right
  // shifted two
  PORTB |= (x>>2);
}


/* 
Interrupt code that changes the compare register, therefore altering
the rate at which the timer initialized in setup will interupt, changing
the frequency of bit writing and thus the frequency of the sound.
*/
void mod() {
  if (OCR2A == 150) {
    OCR2A = 200;}
  else {
    OCR2A = 150;
  }
}


int low = 36;
int high = 255;
int stride = 5;
int counter = low;

/*
Timer that interrupts at a frequency determined in setup (and
altered in mod()). The timer is always counting but doesn't 
act unless button2 is being pressed
*/
ISR(TIMER2_COMPA_vect) {
  int button2 = digitalRead(buttonPin2);
  if (button2) return;

  // increments from 36 to 255 with a stride of 5
  counter += stride;
  if (counter > high) {
    counter = low;
  }

  // write to the digital pins 
  writeByte(counter);
}

// Using timer so we don't need loop()
void loop() {

}