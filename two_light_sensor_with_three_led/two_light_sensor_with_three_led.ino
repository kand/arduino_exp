const int MAX_OUT = 255;

const int LED_R = 11;
const int LED_G = 10;
const int LED_B = 9;

const int PHOTO_IN_R = 0;
const int PHOTO_IN_L = 1;

const int PHOTO_POWER_R = 5;
const int PHOTO_POWER_L = 6;

void setup(){
  Serial.begin(9600);
  
  // set up leds
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);
  
  // power photo resistors
  analogWrite(PHOTO_POWER_R, MAX_OUT);
  analogWrite(PHOTO_POWER_L, MAX_OUT);
}

int ledPower (int light, int lMin, int lMax){
  return ((light - lMin) * 1.0 / (lMax - lMin)) * MAX_OUT;
};

// store min and max readings from photo resistors
int rMax = -1;
int lMax = -1;
int dMax = -1; // max delta between r and l
int rMin = -1;
int lMin = -1; 
int dMin = -1; // min delta between r and l

// begin main loop
void loop(){
  // read input from photo resistors
  int rLight = analogRead(PHOTO_IN_R);
  int lLight = analogRead(PHOTO_IN_L);
  
  // calculate delta
  int dLight;
  if(rLight > lLight) dLight = rLight - lLight;
  else dLight = lLight - rLight;
  
  // figure out min and max readings
  if (rMax == -1 || rLight > rMax) rMax = rLight;
  if (lMax == -1 || lLight > lMax) lMax = lLight;
  if (dMax == -1 || dLight > dMax) dMax = dLight;
  if (rMin == -1 || rLight < rMin) rMin = rLight;
  if (lMin == -1 || lLight < lMin) lMin = lLight;
  if (dMin == -1 || dLight < dMin) dMin = dLight;
  
  // calculate led power
  int rPow = 0;
  int gPow = 0;
  int bPow = 0;
  
  // as r + light, + light of red led
  rPow = ledPower(rLight, rMin, rMax);
  
  // as delta r and l decreases, + light of green led
  gPow = MAX_OUT - ledPower(dLight, dMin, dMax);
  
  // as l + light, + light of blue led
  bPow = ledPower(lLight, lMin, lMax);

  // write out led power
  analogWrite(LED_R, rPow);
  analogWrite(LED_G, gPow);
  analogWrite(LED_B, bPow);
 
  // print some info
  Serial.print(rMin);
  Serial.print("<");
  Serial.print(rLight);
  Serial.print("<");
  Serial.print(rMax);
  Serial.print(",");
  Serial.print(lMin);
  Serial.print("<");
  Serial.print(lLight);
  Serial.print("<");
  Serial.print(lMax);
  Serial.print(",");
  Serial.print(rPow);
  Serial.print("|");
  Serial.print(gPow);
  Serial.print("|");
  Serial.print(bPow);
  Serial.println();
  
  delay(100);
}
