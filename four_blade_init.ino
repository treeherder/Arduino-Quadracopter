#include <Servo.h>

// Initialization settings

int init_throttle = 1000;
int init_delay = 12000;

// Final PWM Objective

int final_throttle = 1500;
int time_until_final = 3000;
long time_at_final = 10000; //10 second hold
int throttle_increment = 50;

int throttle;

Servo x1, x2, y1, y2;

void setup() {

  x1.attach(10);
  x2.attach(6);
  y1.attach(5);
  y2.attach(9);

  Serial.begin(9600);

  //begin init sequence

  Serial.println("Initializing");

  throttle = init_throttle;
  x1.writeMicroseconds(throttle);
  x2.writeMicroseconds(throttle);
  y1.writeMicroseconds(throttle);
  y2.writeMicroseconds(throttle);
  delay(init_delay);

  //calculation for ramp to target speed
  // explanation: time_until_final = number_of_steps * delay_per_step;
  // therefore, delay_per_step = time_until_final/(number_of_steps);
  int number_of_steps = ( final_throttle - init_throttle )/ (throttle_increment );
  int delay_per_step = time_until_final / ( number_of_steps );

  Serial.println("Ramping up Sequence");
  //ramping up to speed
  for ( throttle = init_throttle ; throttle <= final_throttle ; throttle += throttle_increment ) {
      x1.writeMicroseconds(throttle);
      x2.writeMicroseconds(throttle);
      y1.writeMicroseconds(throttle);
      y2.writeMicroseconds(throttle);
      Serial.println(throttle);
      delay(delay_per_step);
    }

  Serial.println("Holding");
  //holding at final_throttle
    delay(time_at_final);


 /* Serial.println("Ramping Down");
  //ramping down
  for ( throttle = final_throttle ; throttle >= init_throttle ; throttle -= throttle_increment ) {
      x1.writeMicroseconds(throttle);
      x2.writeMicroseconds(throttle);
      y1.writeMicroseconds(throttle);
      y2.writeMicroseconds(throttle);
      Serial.println(throttle);
      delay(delay_per_step);
  }*/
  Serial.println("Sequence Completed");
}

void loop() {

  delay(1000);

}
