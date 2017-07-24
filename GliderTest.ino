const int stepRollPin = 4;
const int dirRollPin = 5;
const int endStopRollPin = 14;

const int stepPitchPin = 12;
const int dirPitchPin = 3;
const int endStopPitchPin = 16;

const int stepEnginePin = 6;
const int dirEnginePin = 7;
const int endStopEnginePin = 15;

int rollPos;
int rollMax = 1000;
int pitchPos;
int pitchMax = 3500;
int enginePos;
int engineMax = 22000;

void setup() {
  pinMode(stepRollPin, OUTPUT);
  pinMode(dirRollPin, OUTPUT);

  pinMode(stepPitchPin, OUTPUT);
  pinMode(dirPitchPin, OUTPUT);

  pinMode(stepEnginePin, OUTPUT);
  pinMode(dirEnginePin, OUTPUT);

  homeAll();
  
  Serial.begin(115200);

}

boolean reachedEndStop(int endStop) {
  return(digitalRead(endStop) == 0);
}

boolean dirForward(int dir) {
  return(dir == 0);
}

int runMotor(int dir, int stepPin, int dirPin, int endStop, int amountToMove, int currentPos, int maxPos) {
  digitalWrite(dirPin, dir);
  for (int x = 0; x < amountToMove; x++) {
    if (dirForward(dir) && reachedEndStop(endStop) ) {
      return 0;
    } 
    if (!dirForward(dir) && (currentPos + 1 > maxPos)) {
      break;
    } 
    
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(1200);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(1200);
    
    if (dirForward(dir)) {
      currentPos += -1;
    } else {
      currentPos += 1;
    }
  }
  return currentPos;
}

void diagnosticOutput () {
  Serial.print("Roll end stop: ");
  Serial.print(digitalRead(endStopRollPin));
  Serial.print(", pitch end stop: ");
  Serial.print(digitalRead(endStopPitchPin));
  Serial.print(", engine end stop: ");
  Serial.print(digitalRead(endStopEnginePin));
  Serial.println();
  Serial.print("Roll pos: ");
  Serial.print(rollPos);
  Serial.print(", Pitch pos: ");
  Serial.print(pitchPos);
  Serial.print(", Engine pos: ");
  Serial.print(enginePos);
  Serial.println();
  
}

void homeAll () {
//  rollPos = runMotor(0, stepRollPin, dirRollPin, endStopRollPin, rollMax, rollPos, rollMax);
//  rollPos = runMotor(1, stepRollPin, dirRollPin, endStopRollPin, rollMax * .1, rollPos, rollMax);
  pitchPos = runMotor(0, stepPitchPin, dirPitchPin, endStopPitchPin, pitchMax, pitchPos, pitchMax);
  pitchPos = runMotor(1, stepPitchPin, dirPitchPin, endStopPitchPin, pitchMax * 0.5, pitchPos, pitchMax);
  enginePos = runMotor(0, stepEnginePin, dirEnginePin, endStopEnginePin, engineMax, enginePos, engineMax);
  enginePos = runMotor(1, stepEnginePin, dirEnginePin, endStopEnginePin, engineMax * 1.0, enginePos, engineMax);
  
}

void loop() {

  if (Serial.available() > 0) {
    
    int inByte = Serial.read();
    Serial.println(inByte);
    switch (inByte){
      case 1:
        Serial.println("Disabled Rotating mass clockwise");
        //rollPos = runMotor(1, stepRollPin, dirRollPin, endStopRollPin, 100, rollPos, rollMax);
        break;
      case 2:
        Serial.println("Disabled Rotating mass anticlockwise");
        //rollPos = runMotor(0, stepRollPin, dirRollPin, endStopRollPin, 100, rollPos, rollMax);
        break;
      case 3:
        Serial.println("Mass forward");
        pitchPos = runMotor(0, stepPitchPin, dirPitchPin, endStopPitchPin, 50, pitchPos, pitchMax);
        break;
      case 4:
        Serial.println("Mass backward");
        pitchPos = runMotor(1, stepPitchPin, dirPitchPin, endStopPitchPin, 50, pitchPos, pitchMax);
        break;
      case 5:
        Serial.println("Plunger forward");
        enginePos = runMotor(1, stepEnginePin, dirEnginePin, endStopEnginePin, 100, enginePos, engineMax);
        break;
      case 6:
        Serial.println("Plunger backward");
        enginePos = runMotor(0, stepEnginePin, dirEnginePin, endStopEnginePin, 100, enginePos, engineMax);
        break;
      default:
        Serial.println("None");
        
    }
    diagnosticOutput();
  }
}
