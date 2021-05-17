#include <Servo.h> //includes the servo library

Servo servo;

int ir_s1 = 3; // primul ir (masina intra in parcare)
int ir_s2 = 2;

int total_space = 5;
int space;

int flag1 = 0; 
int flag2 = 0;
int carPassed = 0;

void setup() {
  pinMode(ir_s1, INPUT);
  pinMode(ir_s2, INPUT);
  
  servo.attach(4);
  servo.write(120); 
  
 // delay (2000);

  space = total_space;
}

void loop(){ 
  // intra in parcare
  if (digitalRead(ir_s1) == LOW && flag1 == 0 && carPassed == 0) {
    if (space > 0) {
      flag1 = 1; // masina a trecut de primul senzor

      if (flag2 == 0) {
        servo.write(60); 
        space = space - 1;
      } else {
        carPassed = 1;
        delay(1000);
      }
    } else {
      //TODO
      // LCD work - print: nu e suficient spatiu
    }
  }

  // iese din parcare
  if (digitalRead(ir_s2) == LOW && flag2 == 0 && carPassed == 0) {
    if (space < total_space) {
      flag2 = 1;
    
      if (flag1 == 0) {
        servo.write(60);
        space = space + 1;
      } else {
        carPassed = 1;
        delay(1000);
    }
    }
  }

  if (carPassed == 1) {
    servo.write(120);
    delay (2000);
    carPassed = 0;
    flag1 = 0; 
    flag2 = 0;
  }
}
