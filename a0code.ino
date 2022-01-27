#define NUM_LEDS 5
#define MAX_ANALOG 1023 //max analog reading
#define MAX_BRIGHT 255  //max brightness setting
#define NUM_MODES 3   //3 modes: mode 0 = off, mode 1 = on, mode 2 = on with leds order reversed


// constants won't change. They're used here to set pin numbers:
const int buttonPin = 2;     // the number of the pushbutton pin
const int orderLedPins[] = {3, 5, 6, 9, 10};  //order of LED pins
const int orderLedPinsR[] = {10, 9, 6, 5, 3}; //above but in reverse

// variables will change:
int mode = 0;                 //3 modes: mode 0 = off, mode 1 = on, mode 2 = on with leds order reversed
int buttonState = 0;          // variable for reading the pushbutton status
int lastButtonState = 0;     

void setup() {
  // initialize the LED pin as an output:
  const int* ledPins = orderLedPins;  //pointer to led pins array
  
  for (int i = 0; i < NUM_LEDS; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);
  if (buttonState != lastButtonState) {
    if (buttonState == HIGH) {
      mode = (mode + 1) % NUM_MODES;  //change to correct mode
    }
  }
  lastButtonState = buttonState;

  const int* ledPins = orderLedPins;
  if (mode == 2) {  //reverse leds mode
    ledPins = orderLedPinsR;  
  }
  
  if (mode != 0) {
    //read brightness
    int value = analogRead(A0);  
    Serial.println("Analog Value :");
    Serial.println(value);  

    float brightness = ((float) (value)/MAX_ANALOG) * (MAX_BRIGHT * NUM_LEDS);  //calculate brightness for 5 leds
    Serial.println("Brightness Value :");
    Serial.println(brightness); 

    int numLedsFull = (int) brightness/MAX_BRIGHT;
    int lastLedBrightness = (int) brightness % MAX_BRIGHT;
    Serial.println("NUMLEDS FULL:");
    Serial.println(numLedsFull); 
    Serial.println("lastLed:");
    Serial.println(lastLedBrightness); 
    
    for (int i = 0; i < numLedsFull; i++) { //set however many LEDs to full brightness
      analogWrite(ledPins[i], 255);
    }
    
    analogWrite(ledPins[numLedsFull], lastLedBrightness); //set brightness of final led

    for (int i = numLedsFull + 1; i < NUM_LEDS; i++) {
      analogWrite(ledPins[i], 0);
    }
  } else {
    // turn LEDs off:
    for (int i = 0; i < NUM_LEDS; i++) {
      analogWrite(ledPins[i], 0);
    }
  }
  delay(30);
}
