#include <Servo.h>

#define TP 6
#define EP 7
#define SWITCH_PIN 2 // Assuming the switch is connected to digital pin 2

Servo myservo;
bool open;
const int servoOpenAngle = 0;   // Adjust as needed
const int servoCloseAngle = 90; // Adjust as needed
unsigned long currentTime, previousTime, delayTime = 5000;

int distance() {
  digitalWrite(TP, LOW);
  delayMicroseconds(2);
  digitalWrite(TP, HIGH);
  delayMicroseconds(10);
  digitalWrite(TP, LOW);
  long duration = pulseIn(EP, HIGH);
  int distance = duration * 0.034 / 2;
  //Serial.print("Distance: ");
  //Serial.println(distance);
  return distance;
}

void setup() {
  myservo.attach(9);  // Attach servo to pin 9
  pinMode(TP, OUTPUT);
  pinMode(EP, INPUT);
  pinMode(SWITCH_PIN, INPUT_PULLUP); // Assuming the switch is normally open
  Serial.begin(9600);
}

void loop() {
  currentTime = millis();
  int D = distance();
  bool switchState = digitalRead(SWITCH_PIN); // Read the state of the switch
  
  if (switchState == LOW) { // If the switch is closed
    if (D != 0) {
      if (D <= 10 && !open) {
        open = true;
        myservo.write(servoOpenAngle);
        Serial.println("Open");
        previousTime = currentTime;
      }
      else if (D > 10 && currentTime - previousTime >= delayTime && open) {
        open = false;
        myservo.write(servoCloseAngle);
        Serial.println("Close");
      }
    }
  }
  else { // If the switch is open
    // Reset the system
    open = false;
  }
  delay(10);
}
