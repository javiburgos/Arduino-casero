#include <Arduino.h>

void setup() {
  Serial.begin(9600);
  pinMode(13,OUTPUT);

}
void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Hello from the other side");
  digitalWrite(13,HIGH);
  delay(2000);
  digitalWrite(13,LOW);
  delay(1000);
}
