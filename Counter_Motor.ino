#define trigpin 7
#define echopin 6
int led1 = A0;
int led2 = A1;
int led3 = A2;
int led4 = A3;
int led5 = A4;
int Buzzer = A5;

int objectCount = 0;
bool objectDetected = false;

void setup() {
Serial.begin(9600);
pinMode(trigpin, OUTPUT);
pinMode(echopin, INPUT);
pinMode(led1, OUTPUT);
pinMode(led2, OUTPUT);
pinMode(led3, OUTPUT);
pinMode(led4, OUTPUT);
pinMode(led5, OUTPUT);
pinMode(Buzzer, OUTPUT);

digitalWrite(led1, LOW);
digitalWrite(led2, LOW);
digitalWrite(led3, LOW);
digitalWrite(led4, LOW);
digitalWrite(led5, LOW);
digitalWrite(Buzzer, LOW);
delay(1000);
}

void loop() {
  long duration, distance;
  digitalWrite(trigpin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigpin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigpin, LOW);

  duration = pulseIn(echopin, HIGH);
  distance = (duration / 2) / 29.1;
  
  if (distance < 20){
    if (!objectDetected){
      objectCount++;
      objectDetected = true;

      updateLEDs(objectCount);

      if(objectCount >= 5){
        digitalWrite(Buzzer, HIGH);
        delay(1000);
        digitalWrite(Buzzer, LOW);
      }
    }
  } else {
      objectDetected = false;
    }
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.print(" cm");
    Serial.print(" | Object Counted : ");
    Serial.print(objectCount);

    delay(500);
}

void updateLEDs(int count){
  digitalWrite(led1, count >= 1 ? HIGH : LOW);
  digitalWrite(led2, count >= 2 ? HIGH : LOW);
  digitalWrite(led3, count >= 3 ? HIGH : LOW);
  digitalWrite(led4, count >= 4 ? HIGH : LOW);
  digitalWrite(led5, count >= 5 ? HIGH : LOW);
}
