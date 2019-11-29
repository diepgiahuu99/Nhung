#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#define OLED_RESET 4
LiquidCrystal_I2C  display(0x27, 16, 2);
#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>
SoftwareSerial mySerial(2, 3);
#include <Keypad.h>
const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'},
};

byte rowPins[ROWS] = {9, 8, 7, 6}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {5, 4, 3, 2}; //connect to the column pinouts of the keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
byte ledPin = 13; 

boolean blink = false;
boolean ledPin_state;
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);
int fingerprintID = 0;
void setup(){
    /*Serial.begin(9600);
    display.begin();
    pinMode(ledPin, OUTPUT);              // Sets the digital pin as output.
    digitalWrite(ledPin, HIGH);           // Turn the LED on.
    ledPin_state = digitalRead(ledPin);   // Store initial LED state. HIGH when LED is on.*/
    Serial.begin(9600);
  // set the data rate for the sensor serial port
  finger.begin(57600);
  
  if (finger.verifyPassword()) {
    Serial.println("Found fingerprint sensor!");
  } 
  else {
    Serial.println("Did not find fingerprint sensor :(");
    while (1) { delay(1); }
  }

  //OLED display setup
  Wire.begin();
  display.begin();
  //displays main screen
  displayMainScreen();
    keypad.addEventListener(keypadEvent); // Add an event listener for this keypad
}

void loop(){
  
    char key = keypad.getKey();

    if (key) {
        Serial.println(key);   
        if (key=='A')
        {
           
           display.clear();
          display.print("Dang tim");
          fingerprintID = getFingerprintIDez();
          delay(50);
          display.print("ID: ");
          display.print(fingerprintID);
        }
        if (key=='C') display.clear();
        else
        {    
          //displays main screen
          display.backlight(); 
          display.print(key);
        }
        
    }
    if (blink){
        digitalWrite(ledPin,!digitalRead(ledPin));    // Change the ledPin from Hi2Lo or Lo2Hi.
        delay(10);
    }
}

// Taking care of some special events.
void keypadEvent(KeypadEvent key){
    switch (keypad.getState()){
    case PRESSED:
        if (key == '#') {
            digitalWrite(ledPin,!digitalRead(ledPin));
            ledPin_state = digitalRead(ledPin);        // Remember LED state, lit or unlit.
        }
        break;

    case RELEASED:
        if (key == '*') {
            digitalWrite(ledPin,ledPin_state);    // Restore LED state from before it started blinking.
            blink = false;
        }
        break;

    case HOLD:
        if (key == '*') {
            blink = true;    // Blink the LED when holding the * key.
        }
        break;
    }
}
int getFingerprintIDez() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -1;
  
  // found a match!
  Serial.print("Found ID #"); 
  Serial.print(finger.fingerID); 
  Serial.print(" with confidence of "); 
  Serial.println(finger.confidence);
  return finger.fingerID; 
}
void displayMainScreen(){
  display.clear();
  display.backlight();
  display.print("Bam A de tim"); 
  delay(2000);
}
