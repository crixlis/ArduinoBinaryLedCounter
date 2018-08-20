//  Button variables
const int switchPin = 12;
bool ledLightOn = false;

// global LED variable
int leds[8] = {11,10,9,8,7,6,5,4};

// Initializing
void setup() {
  //initialize the 8 led pins and 1 switch
  for(int i= 0; i < (sizeof(leds)/sizeof(int)) ; i++){
    pinMode(leds[i], OUTPUT);  
  }
  pinMode(switchPin, INPUT);
}

void loop() {
  // Switchbutton reading. The switchbutton is used as a button/toggle to power on the binary counter
  int switchState = digitalRead(switchPin);

  // On switchbutton click (when LED is off) lightup LED
  if (ledLightOn == false && switchState == HIGH){
    ledLightOn = true;

    // calculate binary number and show value as long as the delay (in milliseconds)
    for(int number = 1; number <= 255; number++){
      calculateBinaryLedValue(number);
      delay(500);
      ledsOff();
    }
    
    return;
  }
}

void ledsOff(){
    ledLightOn = false;
    for(int i; i < (sizeof(leds)/sizeof(int)); i++){
      digitalWrite(leds[i], LOW);   
    }
}

void calculateBinaryLedValue(int number){
  // power of 2 (2^0 <---> 2^7), values for all 8 LEDs
  int binaryNumbers[8] = {128,64,32,16,8,4,2,1};

  // determine which LED(s) to light on
  int decimal = number;
  int i = 0;
  while(i < (sizeof(binaryNumbers)/sizeof(int))){
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
}
