//  Button variables
const byte switchPin = 10;
bool deviceOn = false;

// Global LED variable
int millisecondsPerNumber = 150;
byte leds[8] = {9,8,7,6,5,4,3,2};

// Initializing
void setup() {
  Serial.begin(9600);
  //initialize the 8 led pins and 1 switch
  for(byte i= 0; i < (sizeof(leds)/sizeof(byte)) ; i++){
    pinMode(leds[i], OUTPUT);  
  }
  pinMode(switchPin, INPUT);
}

void loop() {
  checkDeviceState();
  if (deviceOn == true){
    // calculate binary number and show value as long as the delay (in milliseconds)
    for(byte number = 1; number <= 255; number++){
      // React on pushbutton OFF when counting
      checkDeviceState();
      if (deviceOn == false) break;
      calculateBinaryLedValue(number);
    }
  }
}

void checkDeviceState(){
  // Switchbutton reading. The switchbutton is used as a button/toggle to power on the binary counter
  byte switchState = digitalRead(switchPin);

  // On switchbutton click (when LED is OFF) lightup LEDs
  if (deviceOn == false && switchState == HIGH){
    deviceOn = true;
    return;
  }

  // On switchbutton click (when LED is ON) turn off LEDs
  if (deviceOn == true && switchState == HIGH){
    deviceOn = false;
    return;
  }
}

void ledsOff(){
  byte i = 0;
  while(i < (sizeof(leds)/sizeof(byte))){
    digitalWrite(leds[i], LOW);   
    i++;
  }
}

void calculateBinaryLedValue(byte number){  
  // power of 2 (2^0 <---> 2^7), values for all 8 LEDs
  byte binaryNumbers[8] = {128,64,32,16,8,4,2,1};

  // determine which LED(s) to light on
  byte decimal = number;
  byte i = 0;
  while(i < (sizeof(binaryNumbers)/sizeof(byte))){
    checkDeviceState();
    if (deviceOn == false) break;
      
    int result = decimal - binaryNumbers[i];
    if(result >= 0){
      decimal = result;
      digitalWrite(leds[i], HIGH);

      // When result is 0 the binary value is known and the next number can be put in the loop
      if(result == 0){
        break;
      }
    }
      
    i++;  
  }
  
  delay(millisecondsPerNumber);
  ledsOff();
}