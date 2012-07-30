int pushButton = 2;

void setup(){
   Serial.begin(9600);
   pinMode(pushButton, INPUT);
}

boolean on = false;
void loop() {
  int buttonState = digitalRead(pushButton);
  
  if(buttonState == 1 && !on){
    Serial.println("SIGNAL ON");
    on = true;
  } else if(buttonState == 0 && on){
    Serial.println("SIGNAL OFF");
    on = false;
  }
  
  delay(1);
}
