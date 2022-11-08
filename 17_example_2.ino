#include <Servo.h>

// Arduino pin assignment

#define PIN_POTENTIOMETER 3 // Potentiometer at Pin A3
// Add IR Sensor Definition Here !!!
#define PIN_SERVO 10
#define PIN_LED 6

#define PIN_IR 0

#define DIST_MIN 100
#define DIST_MAX 250

#define _DUTY_MIN 553  // servo full clock-wise position (0 degree)
#define _DUTY_NEU 1476 // servo neutral position (90 degree)
#define _DUTY_MAX 2399 // servo full counter-clockwise position (180 degree)

#define LOOP_INTERVAL 20   // Loop Interval (unit: msec)

Servo myservo;
unsigned long last_loop_time;   // unit: msec
float dist_prev = DIST_MAX;        // Distance last-measured
float dist_ema; 

void setup() {
  myservo.attach(PIN_SERVO); 
  myservo.writeMicroseconds(_DUTY_NEU);
  pinMode(PIN_LED,OUTPUT);
  Serial.begin(500000);
}

void loop() {
  float dist_raw ;
  
  unsigned long time_curr = millis();
  int a_value, duty;

  // wait until next event time
  if (time_curr < (last_loop_time + LOOP_INTERVAL))
    return;
  last_loop_time += LOOP_INTERVAL;

  // Read IR Sensor value !!!
  a_value = analogRead(PIN_IR);
  
  // Convert IR sensor value into distance !!!
  dist_raw = (6762.0/(a_value-9)-4.0)*10.0 - 60.0 ;
  
  // we need distance range filter here !!!
  if (dist_raw < DIST_MIN) {
      dist_raw = dist_prev ;
      digitalWrite(PIN_LED, 1) ;
  }
  else if (dist_raw > DIST_MAX){
      dist_raw = dist_prev ;
      digitalWrite(PIN_LED, 1) ;
  }
  else {
      dist_prev = dist_raw ;
      digitalWrite(PIN_LED, 0) ;
  }
  
  // we need EMA filter here !!!
  dist_ema = 0.5*dist_raw + 0.5*dist_ema ;

  // map distance into duty
  duty = ((_DUTY_MAX-_DUTY_MIN)/(250.0-100.0))*(dist_ema-100.0)+_DUTY_MIN ;
  myservo.writeMicroseconds(duty);

  // print IR sensor value, distnace, duty !!!
  Serial.print("MIN:");     Serial.print(DIST_MIN) ;
  Serial.print(",IR:");     Serial.print(a_value) ;
  Serial.print(",dist:");   Serial.print(dist_raw) ;
  Serial.print(",ema:");    Serial.print(dist_ema);
  Serial.print(",servo:");  Serial.print(duty);
  Serial.print(",MAX:");    Serial.print(DIST_MAX);
  Serial.println("");
}
