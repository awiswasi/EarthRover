// This library manages the motors
#include <AFMotor.h>

#define CH1 A0
#define CH2 A1
#define CH6 A2

// Define the 4 motor variables
AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);
 
// Integers to represent values from sticks and pots
int ch1Value;
int ch2Value;
 
// Boolean to represent switch value
bool ch6Value;
 
// Read the number of a specified channel and convert to the range provided.
// If the channel is off, return the default value
int readChannel(int channelInput, int minLimit, int maxLimit, int defaultValue){
  int ch = pulseIn(channelInput, HIGH, 30000);
  if (ch < 100) return defaultValue;
  return map(ch, 1000, 2000, minLimit, maxLimit);
}
 
// Read the switch channel and return a boolean value
bool readSwitch(byte channelInput, bool defaultValue){
  int intDefaultValue = (defaultValue)? 100: 0;
  int ch = readChannel(channelInput, 0, 100, intDefaultValue);
  return (ch > 50);
}
 
void setup(){
  // Set up serial monitor
  Serial.begin(9600);
  
  // Set all pins as inputs
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
}
 
void loop() {
  // Get values for each channel
  ch1Value = readChannel(CH1, -500, 500, 0);
  ch2Value = readChannel(CH2, -500, 500, 0);
  ch6Value = readSwitch(CH6, true);

  // I programmed the SWB switch on Channel 6 as a killswitch
  if(!ch6Value) {
    stop();
  }

  else {
    if(ch1Value > 150) {
      right();    
    }

    else if (ch1Value < -150) {
      left();
    }

    else if (ch2Value > 150) {
      forward();
    }

    else if (ch2Value < -150) {
      reverse();
    }

    else if (ch1Value > -100 && ch1Value < 100) {
      stop();
    }
  }

  // This outputs the radio channel values being transmitted
  // It is only information and will not affect the function
  Serial.print("CH1: ");
  Serial.print(ch1Value);
  Serial.print("| CH2: ");
  Serial.print(ch2Value);
  Serial.print("\n");
}

// Function to drive forward
void forward()
{
 motor1.setSpeed(255); //Define maximum velocity
 motor1.run(FORWARD); //rotate the motor clockwise
 motor2.setSpeed(255); //Define maximum velocity
 motor2.run(FORWARD); //rotate the motor counterclockwise

 motor3.setSpeed(255); //Define maximum velocity
 motor3.run(BACKWARD); //rotate the motor clockwise
 motor4.setSpeed(255); //Define maximum velocity
 motor4.run(BACKWARD); //rotate the motor counterclockwise
}

// Function to drive backward
void reverse()
{
 motor1.setSpeed(255); //Define maximum velocity
 motor1.run(BACKWARD); //rotate the motor clockwise
 motor2.setSpeed(255); //Define maximum velocity
 motor2.run(BACKWARD); //rotate the motor counterclockwise

 motor3.setSpeed(255); //Define maximum velocity
 motor3.run(FORWARD); //rotate the motor clockwise
 motor4.setSpeed(255); //Define maximum velocity
 motor4.run(FORWARD); //rotate the motor counterclockwise
}

// Function to turn right
void right()
{
  
 motor1.setSpeed(255); //Define maximum velocity
 motor1.run(FORWARD); //rotate the motor counterclockwise
 motor4.setSpeed(255); //Define maximum velocity
 motor4.run(BACKWARD); //rotate the motor clockwise

 motor3.setSpeed(255); //Define maximum velocity
 motor3.run(FORWARD); //turn motor1 off
 motor2.setSpeed(255); //Define maximum velocity
 motor2.run(BACKWARD); //rotate the motor clockwise
}

// Function to turn left
void left()
{
motor1.setSpeed(255); //Define maximum velocity
 motor1.run(BACKWARD); //rotate the motor counterclockwise
 motor4.setSpeed(255); //Define maximum velocity
 motor4.run(FORWARD); //rotate the motor clockwise

 motor3.setSpeed(255); //Define maximum velocity
 motor3.run(BACKWARD); //turn motor1 off
 motor2.setSpeed(255); //Define maximum velocity
 motor2.run(FORWARD); //rotate the motor clockwise
}

// Function to stop the motors
void stop()
{
 motor1.setSpeed(0);
 motor2.run(RELEASE); //turn motor1 off
 motor2.setSpeed(0);
 motor2.run(RELEASE); //turn motor2 off

 motor3.setSpeed(0);
 motor3.run(RELEASE); //turn motor3 off
 motor4.setSpeed(0);
 motor4.run(RELEASE); //turn motor4 off
}
