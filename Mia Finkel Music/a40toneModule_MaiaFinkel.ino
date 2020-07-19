//toneModule_MaiaFinkel.ino
//4.14.2016
//George School Robotics Arr. 6



void playNoteLength(float freq, int duration) {

  float frequencyValue = (1.0 / (2.0 * freq)) * 1000000; //converts frequency to pulse width values

  int startTime = millis();
  int endTime = startTime + duration;

  while (millis() < endTime) {
    digitalWrite(audioPin, HIGH);
    delayMicroseconds(frequencyValue);
    digitalWrite(audioPin, LOW);
    delayMicroseconds(frequencyValue);
  }
  delay(20);

}

void playNoteForever(float freq) {
  float frequencyValue = (1.0 / (2.0 * freq)) * 1000000;
  digitalWrite(audioPin, HIGH);
  delayMicroseconds(frequencyValue);
  digitalWrite(audioPin, LOW);
  delayMicroseconds(frequencyValue);

}

void rest(int duration) {
  int startTime = millis();
  int endTime = startTime + duration;

  while (millis() < endTime) {
    digitalWrite(audioPin, LOW);
  }
  delay(20);
}
