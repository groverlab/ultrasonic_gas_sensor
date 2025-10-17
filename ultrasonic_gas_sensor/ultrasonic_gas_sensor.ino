// ultrasonic_gas_sensor.ino

#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int trig_pin = 10;
const int echo_pin = 9;
const float tubing_length = 3.0;  // meters; measure using 'measure_tubing_length.ino'
float duration;
float speed;
String gases[5] = {
  "Air        ",
  "Carbon diox",
  "Nitrogen   ",
  "Nitrous ox ",
  "Oxygen     "
};
float speeds[5] = {
  343.0,  // air
  260.0,  // carbon dioxide
  354.0,  // nitrogen
  268.0,  // nitrous oxide
  330.0   // oxygen
};
float diff = 0;
float closest_diff = 0;
int closest_i = 0;

void setup() {
  lcd.begin(16, 2);
  pinMode(trig_pin, OUTPUT);
  pinMode(echo_pin, INPUT);
}

void loop() {
  digitalWrite(trig_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(trig_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_pin, LOW);
  duration = pulseIn(echo_pin, HIGH);  // microseconds
  speed = tubing_length / (duration * 1e-6);
  closest_diff = 9999;
  for (int i = 0; i < 5; i++) {
    diff = abs(speeds[i] - speed);
    if (diff < closest_diff) {
      closest_diff = diff;
      closest_i = i;
    }
  }

  lcd.setCursor(0, 0);
  lcd.print("Speed: ");
  lcd.print(speed, 0);
  lcd.print(" m/s");
  lcd.setCursor(0, 1);
  lcd.print("Gas: ");
  lcd.print(gases[closest_i]);
  delay(500);
}