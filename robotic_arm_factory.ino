/*
  Controlling a servo position using a potentiometer (variable resistor)
  http://bit.ly/MertArduino
*/

#include <Servo.h>

// create servo object to control a servo
Servo servo_1;
Servo servo_2;
Servo servo_3;
Servo servo_4;

int servo_1_values[] = {2, 4, 8, 3, 6};
int servo_2_values[] = {2, 4, 8, 3, 6};
int servo_3_values[] = {2, 4, 8, 3, 6};
int servo_4_values[] = {2, 4, 8, 3, 6};

// analog pin mappings
int pin_speed = 0; // analog pin used to connect the potentiometer
int pin_height_in = 1;
int pin_height_out = 2;

// digital pin mappings
int pin_valve = 0;
int pin_servo_1 = 1;
int pin_servo_2 = 2;
int pin_servo_3 = 3;
int pin_servo_4 = 4;
int pin_trigger_start = 5;
int pin_trigger_reset_height = 6;

// variables
int height_offset = 0;
int height_step_size = 1;
int step_count;

void setup() {
  // attaches the servos on digital (PWM) pins to the servo object
  servo_1.attach(pin_servo_1);
  servo_2.attach(pin_servo_2);
  servo_3.attach(pin_servo_3);
  servo_4.attach(pin_servo_4);
  step_count = sizeof(servo_1_values) / sizeof(int);
}

void loop() {
  wait_for_trigger_start(pin_trigger_start); // wait for button press on pin_trigger_start
  wait_for_trigger_reset_height(pin_trigger_reset_height); // wait for button press on pin pin_trigger_reset_height
  
  for (byte i = 0; i < step_count; i = i + 1) {
    int speedness  = analogRead(pin_speed) ;   //reading analog voltage and storing it in an integer
    speedness = map(speedness, 0, 1023, 0, 1000);

    int height_offset_out  = height_offset + analogRead(pin_height_in) ;   //reading analog voltage and storing it in an integer
    if (height_offset_out > 1023) {
      height_offset_out = 1023;
    }

    //Serial.println(servo_1_values[i]);

    servo_1.write(servo_1_values[i]);                   // sets the servo position according to the scaled value
    delay(1000 / speedness);                            // waits for the servo to get there

    servo_2.write(servo_2_values[i]);
    delay(1000 / speedness);

    servo_3.write(servo_3_values[i]);
    delay(1000 / speedness);

    servo_4.write(servo_4_values[i]);
    delay(1000 / speedness);

    if (i >= 4) {
      digitalWrite(pin_valve, HIGH);
    } else {
      digitalWrite(pin_valve, LOW);
    }

    if (i == step_count - 1) {
      height_offset = height_offset + height_step_size;
    }
    
    digitalWrite(pin_height_out, height_offset_out);
  }
}

void wait_for_trigger_start(int buttonPin) {
  int buttonState = 0;
  while (1) {
    buttonState = digitalRead(buttonPin);
    if (buttonState == HIGH) {
      return;
    }
  }
}
void wait_for_trigger_reset_height(int buttonPin) {
  int buttonState = 0;
  while (1) {
    buttonState = digitalRead(buttonPin);
    if (buttonState == HIGH) {
      height_offset = 0;
    }
  }
}
