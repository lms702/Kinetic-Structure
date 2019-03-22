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
    if (flag) {
      noInterrupts();
      checkButton(lightOn);
      lastTime = millis();
      spikes = 0;
      flag = 0;
      interrupts();
    }
    if(millis()-lastTime > 100) {
      Serial.println(spikes);
      if(spikes > 10) {
        music = 1;
      }
      else {
        music = 0;
      }
      spikes = 0; 
      lastTime = millis();
    }
    else {
      if(analogRead(A0) > 15) {
        spikes++;
      }
    }
    if(lightOn && music) {
      digitalWrite(3, HIGH);
    }
    else {
      digitalWrite(3, LOW);
    }
  }
}
void bop() {
     flag = 1;
 }
void checkButton(bool &lightOn) {
      if(digitalRead(button) == 0) {
        delay(15);
        if(digitalRead(button) == 0){
          while(digitalRead(button) == 0){}
          if(lightOn) {
            digitalWrite(8, LOW);
            lightOn = 0;
            }
          else {
            digitalWrite(8, HIGH);
            lightOn = 1;
            }
          }
      flag = 0;
      }
      return;
}
