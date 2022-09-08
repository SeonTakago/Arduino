#include <Servo.h>

unsigned long timer;

int var = 0;
int pot = 0;

int emg1 = 0;
int amp1 = 0;
int p1 = 20;
int max1 = 0;
int min1 = 255;
int t1 = 0;

int emg2 = 0;
int amp2 = 0;
int p2 = 20;
int max2 = 0;
int min2 = 255;
int t2 = 0;
int t3 = 0;
int t4 = 0;
int t5 = 0;
Servo servo_thumb1;
Servo servo_index_finger;
Servo servo_middle_finger;
Servo servo_little_ring_finger;
Servo servo_finger;

void setup() {
  Serial.begin(9600);
  timer = millis();
  servo_middle_finger.attach(7);
  servo_little_ring_finger.attach(4);
  servo_thumb1.attach(3);
  servo_index_finger.attach(5);
  servo_finger.attach(6);
}
void calc_amp() {
  for (int k = 0; k < 32; k++) {
    emg1 = analogRead(A0);
    emg2 = analogRead(A1);
    pot = analogRead(A3);
    emg1 = map(emg1, 0, 1023, 0, 255);
    emg2 = map(emg2, 0, 1023, 0, 255);
        if (emg1 > max1)
    max1 = emg1;
    if (emg1 < min1)
    min1 = emg1;
        if (emg2 > max2)
    max2 = emg2;
    if (emg2 < min2)
    min2 = emg2;
  }
  amp1 = 0.3*amp1 + 0.7*(max1 - min1);
  amp2 = 0.3*amp2 + 0.7*(max2 - min2);
  //Serial.println(amp1);
  //Serial.print("    ");
  //Serial.println(amp2);
  Serial.println(pot);
  max1 = 0;
  min1 = 255;
  max2 = 0;
  min2 = 255;
}
void loop() {
calc_amp();
    if (amp1 > p1 && amp2 > p2) {
        if (millis() - timer > 1000) {
      timer = millis();
      var++;    
    }
    }
    switch (var){
      case 0:
      //Serial.println("malo");
     if (amp1 > p1){
        servo_middle_finger.write(t1);
         pinMode(8, OUTPUT);                     
          digitalWrite(8, HIGH);
     }
     if (amp1 < p1){
        servo_middle_finger.write(t1);
pinMode(8, OUTPUT);                     
          digitalWrite(8, LOW);
     }
     if (amp2 > p2){
        servo_index_finger.write(t2);           
pinMode(9, OUTPUT);                     
          digitalWrite(9, HIGH);
}
     if (amp2 < p2){
        servo_index_finger.write(t2);
pinMode(9, OUTPUT);                     
          digitalWrite(9, LOW);
     } 
break;
      case 1:
      //Serial.println("privet");
      if (amp1 > p1){
        servo_finger.write(t5);
pinMode(10, OUTPUT);                     
          digitalWrite(10, HIGH);
      }
     if (amp1 < p1){
        servo_finger.write(t5);
pinMode(10, OUTPUT);                     
          digitalWrite(10, LOW);
     }
           if (amp2 > p2){
        servo_little_ring_finger.write(t3);
pinMode(11, OUTPUT);                     
          digitalWrite(11, HIGH);
           }
     if (amp2 < p2){
        servo_little_ring_finger.write(t3);
pinMode(11, OUTPUT);                     
          digitalWrite(11, LOW);
     }
      break;
      case 2:
     // Serial.println("poka");
      var = 0;
break;
    }
}
