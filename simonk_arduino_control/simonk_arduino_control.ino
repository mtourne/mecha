#include <Servo.h>

#define MAX_SIGNAL 2000
#define MIN_SIGNAL 1000
#define MOTOR_PIN 11

#define CALIBRATE 0

#define POT_PIN 0
#define INCREMENT_TOLERANCE 3

Servo motor;

int val = MIN_SIGNAL;
int oldval = MAX_SIGNAL;

void setup() {
  Serial.begin(9600);
  Serial.println("Program begin...");
  Serial.println("This program will calibrate the ESC.");

  motor.attach(MOTOR_PIN);

  if (CALIBRATE) {
    Serial.println("Now writing maximum output.");
    motor.writeMicroseconds(MAX_SIGNAL);

    Serial.println("Turn on power source, then wait 2 seconds and press any key.");

    // Wait for input
    while (!Serial.available());
    Serial.read();

    // Send min output
    Serial.println("Sending minimum output");
    motor.writeMicroseconds(MIN_SIGNAL);
  }
}

void loop() {
  // reads the value of the potentiometer (value between 0 and 1023)
  val = analogRead(POT_PIN);
  if (val < oldval - INCREMENT_TOLERANCE or 
      val > oldval + INCREMENT_TOLERANCE ) {
    // if value has changed at the pot
    oldval = val;
    // scale it to use it with the signal output
    val = map(val, 0, 1023, MIN_SIGNAL, MAX_SIGNAL);
    Serial.print("Setting to: ");
    Serial.println(val);
    motor.writeMicroseconds(val);
  }
}
