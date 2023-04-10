const int controlPin1 = 2; //Control pins for direction of motor
const int controlPin2 = 3;
const int enablePin = 9; //Determines if the motor will be spinning 
const int directionSwitchPin = 4; //Used for changing motor direction
const int switchStatePin = 5; //Used for tuning the motor on/off 
const int potPin = A0;
int switchState = 0;
int prevSwitchState = 0;
int directionSwitchState = 0;
int prevDirectionSwitchState = 0;
int motorEnabled = 0;
int motorSpeed = 0;
int motorDirection = 1; 

void setup() {
  pinMode(directionSwitchPin, INPUT);
  pinMode(switchStatePin, INPUT);
  pinMode(controlPin1, OUTPUT);
  pinMode(controlPin2, OUTPUT);
  pinMode(enablePin, OUTPUT);
  digitalWrite(enablePin, LOW); //Starts the motor off
}

void loop() {
  switchState = digitalRead(switchStatePin);
  delay(1);
  directionSwitchState = digitalRead(directionSwitchPin);
  motorSpeed = analogRead(potPin)/4; //potPin gets 1024 values, divide by 4 to make it 256 values 

  //If the switch state has changed from the previous, check if the switch is currently set to HIGH 
  //If so, negate the on/off status of the motor if the on/off switch is pressed 
  if (switchState != prevSwitchState) {
    if (switchState == HIGH) {
      motorEnabled = !motorEnabled; 
    }
  }

  //If direction switch is in a different position than previously, negate the motorDirection
  if (directionSwitchState != prevDirectionSwitchState) { 
    if (directionSwitchState == HIGH) { 
      motorDirection = !motorDirection;
    }
  }

  //If both control pins are different values (LOW,HIGH or HIGH,LOW), the motor will spin in one direction
  if (motorDirection == 1) { 
    digitalWrite(controlPin1, HIGH); 
    digitalWrite(controlPin2, LOW);
  } else {
    digitalWrite(controlPin1, LOW);
    digitalWrite(controlPin2, HIGH);
  }

  //Turn on the motor at the calculated motorSpeed value or turn it off
  if (motorEnabled == 1) {
    analogWrite(enablePin, motorSpeed);
  } else {
    analogWrite(enablePin, 0);
  }

  //Set prevDirectionSwitchState and prevSwitchState to the current values for the next loop.
  prevDirectionSwitchState = directionSwitchState;
  prevSwitchState = switchState;
}
