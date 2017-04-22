const int stepGearboxPin = 3;
const int dirGearboxPin = 4;

const int stepAcmePin = 5;
const int dirAcmePin = 6;

const int stepEnginePin = 7;
const int dirEnginePin = 8;

void setup() {
  pinMode(stepGearboxPin, OUTPUT);
  pinMode(dirGearboxPin, OUTPUT);

  pinMode(stepAcmePin, OUTPUT);
  pinMode(dirAcmePin, OUTPUT);

  pinMode(stepEnginePin, OUTPUT);
  pinMode(dirEnginePin, OUTPUT);

  Serial.begin(9600);
}

void output(int dir, int stepPin, int dirPin, int multiplier) {
  digitalWrite(dirPin, dir);
  for (int x = 0; x < multiplier; x++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(1200);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(1200);
  }
}

void loop() {
  // read the sensor:
  if (Serial.available() > 0) {
    int inByte = Serial.read();
    switch (inByte) {
      case 'q':
        Serial.println("Rotating mass clockwise");
        output(1, stepGearboxPin, dirGearboxPin, 100);
        break;
      case 'a':
        Serial.println("Rotating mass anticlockwise");
        output(0, stepGearboxPin, dirGearboxPin, 100);
        break;
      case 'w':
        Serial.println("Mass forward");
        output(0, stepAcmePin, dirAcmePin, 500);
        break;
      case 's':
        Serial.println("Mass backward");
        output(1, stepAcmePin, dirAcmePin, 500);
        break;
      case 'e':
        Serial.println("Plunger forward");
        output(1, stepEnginePin, dirEnginePin, 2000);
        break;
      case 'd':
        Serial.println("Plunger backward");
        output(0, stepEnginePin, dirEnginePin, 2000);
        break;
      case 'z':
        Serial.println("Rotating mass slightly clockwise");
        output(1, stepGearboxPin, dirGearboxPin, 1);
        break;
      case 'x':
        Serial.println("Rotating mass slightly anticlockwise");
        output(0, stepGearboxPin, dirGearboxPin, 1);
        break;
      default:
        Serial.println("None");
    }
  }

}
