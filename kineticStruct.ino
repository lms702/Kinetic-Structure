#define button 2
void checkButton(bool &lightOn);
bool sample();
void setup() {
  // put your setup code here, to run once:
  pinMode(button, INPUT);
  digitalWrite(button, HIGH);
  pinMode(8, OUTPUT);
  pinMode(3, OUTPUT);
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(button), bop, CHANGE);
}
volatile bool flag = 0;
void loop() {
  // put your main code here, to run repeatedly:
  bool lightOn = 0;
  unsigned int timeSince = 0;
  bool moving = 0;
  bool music = 0;
  int spikes = 0;
  unsigned int elapsed = 1001;
  unsigned long int lastTime = 0;
  while (true) {
    //Serial.println(analogRead(A0));
    if (flag) {
      checkButton(lightOn);
    }
    if(millis()-lastTime > 1000) {
      Serial.println(millis() - lastTime);
      if(spikes > 10) {
        digitalWrite(8, HIGH);
        music = 1;
      }
      else {
        music = 0;
        digitalWrite(8, LOW);
      }
      spikes = 0; 
      lastTime = millis();
    }
    else {
      if(analogRead(A0) > 15) {
        spikes++;
      }
    }
  }
}
void bop() {
     flag = 1;
 }
void checkButton(bool &lightOn) {
      noInterrupts();
      if(digitalRead(button) == 0) {
        delay(15);
        if(digitalRead(button) == 0){
          while(digitalRead(button) == 0){}
          if(lightOn) {
            digitalWrite(8, LOW);
            digitalWrite(3, LOW);
            lightOn = 0;
            }
          else {
            digitalWrite(8, HIGH);
            digitalWrite(3, HIGH);
            lightOn = 1;
            }
          }
      interrupts();
      flag = 0;
      }
      return;
}
