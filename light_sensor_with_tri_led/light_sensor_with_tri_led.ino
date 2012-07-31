int PIN_PHOTO_RESISTOR = 0;
int LED_R = 11;
int LED_G = 10;
int LED_B = 9;

int MAX_LED_BRIGHTNESS = 255; // for one led
int MAX_TRI_BRIGHTNESS = MAX_LED_BRIGHTNESS * 3; // R * G * B total
int DIV_BRIGHTNESS = MAX_TRI_BRIGHTNESS / 4; // partitions for brightness values
int MIN_G_BRIGHTNESS = MAX_TRI_BRIGHTNESS - (DIV_BRIGHTNESS * 3);
int MIN_B_BRIGHTNESS = MAX_TRI_BRIGHTNESS - (DIV_BRIGHTNESS * 2);
int MAX_G_BRIGHTNESS = MAX_TRI_BRIGHTNESS - (DIV_BRIGHTNESS);

void setup() {
  Serial.begin(9600);
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);
}

int oldLightRead = 0;
int maxRead = 0;
int minRead = -1;
void loop(){
  int currLightRead = analogRead(PIN_PHOTO_RESISTOR);
  
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
    int ledBrightness = (deltaCurrAndMin * 1.0 / deltaMaxAndMin) * MAX_TRI_BRIGHTNESS;
    
    // get color spectrum (R brigther, G is medium, B is darker)
    int ledBrightnessR = 0;
    if(0 <= ledBrightness && ledBrightness <= MIN_B_BRIGHTNESS){
      ledBrightnessR = (ledBrightness * 1.0 / MIN_B_BRIGHTNESS) * MAX_LED_BRIGHTNESS;
    }
    
    int ledBrightnessG = 0;
    if(MIN_G_BRIGHTNESS <= ledBrightness && ledBrightness <= MAX_G_BRIGHTNESS){
      ledBrightnessG = ((ledBrightness * 1.0 - MIN_G_BRIGHTNESS) / MAX_G_BRIGHTNESS) * MAX_LED_BRIGHTNESS;
    }
    
    int ledBrightnessB = 0;
    if(MIN_B_BRIGHTNESS <= ledBrightness && ledBrightness <= MAX_TRI_BRIGHTNESS){
      ledBrightnessB = ((ledBrightness * 1.0 - MIN_B_BRIGHTNESS) / MAX_TRI_BRIGHTNESS) * MAX_LED_BRIGHTNESS;
    }
    
    analogWrite(LED_R, ledBrightnessR);
    analogWrite(LED_G, ledBrightnessG);
    analogWrite(LED_B, ledBrightnessB);
    
    Serial.print(" R: ");
    Serial.print(ledBrightnessR);
    Serial.print(" G: ");
    Serial.print(ledBrightnessG);
    Serial.print(" B: ");
    Serial.print(ledBrightnessB);

    // end line
    Serial.println();
  }
  
  delay(100);
}
