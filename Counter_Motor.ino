#define trigpin 8
#define echopin 9
#define trig2 10 // Trig pin Ultra 2
#define echo2 11
int led1 = 12; // Kuning
int led2 = 13; // Merah
int led3 = 7; // Hijau

int objectCount = 0;
bool objectDetected1 = false;
bool objectDetected2 = false;
bool currentDetection1 = false;
bool currentDetection2 = false;


void updateLEDs(int count) {
  if (count >= 2) {
    digitalWrite(led2, HIGH); // Nyalakan LED2
    digitalWrite(led1, LOW);  // Matikan LED1
    digitalWrite(led3, LOW);
  } else if (count == 1) {
    digitalWrite(led1, HIGH); // Nyalakan LED1 jika count == 4
    digitalWrite(led2, LOW);  // Matikan LED2
    digitalWrite(led3,LOW);
  } else {
    digitalWrite(led1, LOW);  // Matikan LED1 jika count kurang dari 4
    digitalWrite(led2, LOW);  // Matikan LED2 jika count kurang dari 4
    digitalWrite(led3, HIGH);
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(trigpin, OUTPUT);
  pinMode(trig2, OUTPUT);
  pinMode(echo2, INPUT);
  pinMode(echopin, INPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);

  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);

  delay(1000);
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

  bool currentDetected1 = (distance1 < 10);//Diganti nantinya dengan tinggi sesungguhnya
  bool currentDetected2 = (distance2 < 10);

// Penambahan objectCount ketika objek terdeteksi oleh sensor 1
  if (currentDetected1 && !objectDetected1) {
    objectCount++;
    objectDetected1 = true;
  }
  
  // Penambahan objectCount ketika objek terdeteksi oleh sensor 2
  if (currentDetected2 && !objectDetected2) {
    objectCount++;
    objectDetected2 = true;
  }

  // Pengurangan objectCount ketika objek tidak lagi terdeteksi oleh sensor 1
  if (!currentDetected1 && objectDetected1) {
    if (objectCount > 0) {
      objectCount--;
    }
    objectDetected1 = false;
  }

  // Pengurangan objectCount ketika objek tidak lagi terdeteksi oleh sensor 2
  if (!currentDetected2 && objectDetected2) {
    if (objectCount > 0) {
      objectCount--;
    }
    objectDetected2 = false;
  }

  updateLEDs(objectCount);


  Serial.print("Distance1: ");
  Serial.print(distance1);
  Serial.print(" cm, Distance2: ");
  Serial.print(distance2);
  Serial.print(" cm | Object Counted: ");
  Serial.println(objectCount);

  delay(1000);
}
