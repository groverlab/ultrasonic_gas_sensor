// measure_tubing_length.ino
// Fill tubing with air and run this to determine the tubing length in meters
// Use that value to set tubing_length in ultrasonic_gas_sensor.ino

const int trigPin = 10;
const int echoPin = 9;
float duration;
float length;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  length = (duration*.000343);
  Serial.print("Tubing length: ");
  Serial.print(length);
  Serial.println(" meters");
  delay(100);
}