#include <Arduino.h>

void setup() {
  Serial.begin(9600);

}
void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Hello from the other side");
  delay(1000);
}
