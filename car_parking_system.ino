#include <LiquidCrystal.h> // include the lcd library
#include <Servo.h> // include the servo library

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);

Servo servo;

// IR sensors
int ir_s1 = 3; 
int ir_s2 = 2;

int total_space = 4;
int space;

int flag1 = 0;
int flag2 = 0;
int carPassed = 0;

void setup() {
  pinMode(ir_s1, INPUT);
  pinMode(ir_s2, INPUT);
  
  servo.attach(4);
  servo.write(120); // set servo to the initial position
  
  // lcd setup
  lcd.begin(16, 2);  
  lcd.setCursor(0,0);
  lcd.print("  Car  Parking  ");
  
  lcd.setCursor(0,1);
  lcd.print("     System     ");
  delay (5000);
  lcd.clear();  
  
  space = total_space;
}

void loop(){ 
  // a car tries to enter into the parking lot
  if (digitalRead(ir_s1) == LOW && flag1 == 0 && carPassed == 0) {
    if (space > 0) {
      // the car arrived at the first sensor
      flag1 = 1;

      if (flag2 == 0) {
        // raise the barrier
        servo.write(60); 
        space = space - 1;      
      } else {
        // the car entered into the parking lot
        carPassed = 1;
        delay(1000);
      }
      
    // no empty space available
    } else {
      // print the message on LCD
      lcd.setCursor(0,0);
      lcd.print(" Sorry not Space ");  
      lcd.setCursor(0,1);
      lcd.print("    Available    ");
      delay (1000);
      lcd.clear(); 
    }
  }

  // a car leaves the parking lot
  if (digitalRead(ir_s2) == LOW && flag2 == 0 && carPassed == 0) {
    if (space < total_space) {
      // the car arrived at the second sensor
      flag2 = 1;
    
      if (flag1 == 0) {
        // raise the barrier
        servo.write(60);
        space = space + 1;
      } else {
        // the car left the parking lot
        carPassed = 1;
        delay(1000);
      }
    }
  }

  if (carPassed == 1) {
    // lower the barrier
    servo.write(120);
    delay (2000);
    
    // reset the flags
    carPassed = 0;
    flag1 = 0; 
    flag2 = 0;
  }

  // update the message on LCD
  lcd.setCursor (0,0);
  lcd.print("Total Space: ");
  lcd.print(total_space);
  
  lcd.setCursor (0,1);
  lcd.print("Have  Space: ");
  lcd.print(space);
}
