#define trigpin 8
#define echopin 9
#define trig2 10 // Trig pin Ultra 2
#define echo2 11
int led1 = 12; // Kuning
int led2 = 13; // Merah

int objectCount = 0;
bool objectDetected1 = false;
bool objectDetected2 = false;

void setup() {
Serial.begin(9600);
pinMode(trigpin, OUTPUT);
pinMode(trig2, OUTPUT);
pinMode(echo2, INPUT);
pinMode(echopin, INPUT);
pinMode(led1, OUTPUT);
pinMode(led2, OUTPUT);

digitalWrite(led1, LOW);
digitalWrite(led2, LOW);

delay(2000);
}

void loop() {
  long duration1, distance1;

  // Sensor 1
  digitalWrite(trigpin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigpin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigpin, LOW);

  duration1 = pulseIn(echopin, HIGH);
  distance1 = (duration1 / 2) / 29.1;

  // Sensor 2
  long duration2, distance2;
  digitalWrite(trig2, LOW);
  delayMicroseconds(2);
  digitalWrite(trig2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig2, LOW);

  duration2 = pulseIn(echo2, HIGH);
  distance2 = (duration2 / 2) / 29.1;

  bool currentDetected1 = (distance1 < 20);
  bool currentDetected2 = (distance2 , 20);

  if (!objectDetected1 or objectDetected2 && currentDetected1 && currentDetected2 && objectCount < 5) {
      objectCount++;
      objectDetected1 = true;
      objectDetected2 = true;
    }

  if (!currentDetection1 && !currentDetection2 && (objectDetected1 or objectDetected2)) {
    if (objectCount > 0) {
      objectCount--;
    }
    objectDetected1 = false;
    objectDetected2 = false;
  }
    updateLEDs(objectCount);

    if (objectCount >= 5) {
      digitalWrite(led2, HIGH);
    }
  }

  Serial.print("Distance1: ");
  Serial.print(distance1);
  Serial.print(" cm, Distance2: ");
  Serial.print(distance2);
  Serial.print(" cm | Object Counted: ");
  Serial.println(objectCount);

  delay(2000);
}

void updateLEDs(int count) {
  if (count >= 5) {
    digitalWrite(led2, HIGH); // Nyalakan LED2
    digitalWrite(led1, LOW);  // Matikan LED1
  } else if (count == 4) {
    digitalWrite(led1, HIGH); // Nyalakan LED1 jika count >= 4
    digitalWrite(led2, LOW);  // Matikan LED2
  } else {
    digitalWrite(led1, LOW);  // Matikan LED1 jika count kurang dari 4
    digitalWrite(led2, LOW);  // Matikan LED2 jika count kurang dari 4
  }
}