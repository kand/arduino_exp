int photoResistor = 0;
int led = 9;
int maxBrightness = 255;

void setup(){
  Serial.begin(9600);
  pinMode(led, OUTPUT);
}

int oldLightRead = 0;
int maxRead = 0;
int minRead = -1;
void loop(){
  int currLightRead = analogRead(photoResistor);
  
  // print value if changed, gather some data,
  //  change brightness of led based on value
  if(oldLightRead != currLightRead){  
    Serial.print("LIGHT: ");
    Serial.print(currLightRead);
    oldLightRead = currLightRead;
    
    // get max read
    if(maxRead < currLightRead){
      maxRead = currLightRead;
      Serial.print(" (NEW MAX)");
    }
    
    // get min read
    if(minRead == -1 || minRead > currLightRead){
      minRead = currLightRead;
      Serial.print(" (NEW MIN)");
    }

    // set led brightness as a percentage of max
    int deltaCurrAndMin = (currLightRead - minRead);
    int deltaMaxAndMin = (maxRead - minRead);
    int ledBrightness = (deltaCurrAndMin * 1.0 / deltaMaxAndMin) * maxBrightness;
    analogWrite(led, ledBrightness);
    Serial.print(" LED: ");
    Serial.print(ledBrightness);

    // end line
    Serial.println();
  }
  
  delay(100);
}
