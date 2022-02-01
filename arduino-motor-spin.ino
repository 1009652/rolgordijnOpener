/*Example sketch to control a stepper motor with A4988/DRV8825 stepper motor driver and Arduino without a library. More info: https://www.makerguides.com */

// Define stepper motor connections and steps per revolution:
#define dirPin 2
#define stepPin 3
#define stepsPerRevolution 200*5
#define upButton 6
#define downButton 5
#define upLight 10
#define downLight 7 
#define downButtonESP 12
#define upButtonESP 11

bool isUp = false;

void setup() {
  // Declare pins as output:
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);

  pinMode(upButton, INPUT);
  pinMode(downButton, INPUT);

  pinMode(upLight, OUTPUT);
  pinMode(downLight, OUTPUT);

  pinMode(upButtonESP, INPUT);
  Serial.begin(9600);
}

void loop() {
  if((digitalRead(upButton) || digitalRead(upButtonESP)) && !isUp){
    Serial.println("Up ");
    digitalWrite(upLight, HIGH);
    spin(true);
    isUp = true;
    digitalWrite(upLight, LOW);
  } else if ((digitalRead(downButton) || digitalRead(downButtonESP)) && isUp){
    Serial.println("Down ");
    digitalWrite(downLight, HIGH);
    spin(false);
    isUp = false;
    digitalWrite(downLight, LOW);
  }
  
  
}

void spin(bool clockWise){
  if(clockWise){
    digitalWrite(dirPin, HIGH);
  } else {
    digitalWrite(dirPin, LOW);
  }
  
  
  for (int i = 0; i < 5 * stepsPerRevolution; i++) {
    // These four lines result in 1 step:
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(500);
  }
}
