// FSM Mode Selector using Arduino 
// States: IDLE -> BLINK -> RUN -> ON -> back to IDLE 
// Define states 
typedef enum {S0_IDLE, S1_BLINK, S2_RUN, S3_ON} State; 
State current_state = S0_IDLE; 
// Pin configuration 
const int ledPins[3] = {3, 4, 5}; 
const int buttonPin = 2; 
// Variables 
unsigned long lastUpdate = 0; 
bool lastButtonState = HIGH; 
int idx = 0;   // index for chasing LEDs 
// Function: turn all LEDs OFF 
void allOff() { 
for (int i = 0; i < 3; i++) digitalWrite(ledPins[i], LOW); 
} 
void setup() { 
for (int i = 0; i < 3; i++) pinMode(ledPins[i], OUTPUT); 
pinMode(buttonPin, INPUT_PULLUP); // button with internal pull-up 
Serial.begin(9600); 
} 
void loop() { 
// Check button press with debounce 
bool buttonState = digitalRead(buttonPin); 
if (lastButtonState == HIGH && buttonState == LOW) { 
// Button pressed -> change state 
current_state = (State)((current_state + 1) % 4); 
Serial.print("State Changed to: "); 
Serial.println(current_state); 
    delay(200); // debounce delay 
  } 
  lastButtonState = buttonState; 
 
  // FSM State Actions 
  switch (current_state) { 
    case S0_IDLE: 
      allOff(); 
      break; 
 
    case S1_BLINK: 
      if (millis() - lastUpdate > 500) { 
        digitalWrite(ledPins[0], !digitalRead(ledPins[0])); 
        lastUpdate = millis(); 
      } 
      break; 
 
    case S2_RUN: 
      if (millis() - lastUpdate > 300) { 
        allOff(); 
        digitalWrite(ledPins[idx], HIGH); 
        idx = (idx + 1) % 3; 
        lastUpdate = millis(); 
      } 
      break; 
 
    case S3_ON: 
      for (int i = 0; i < 3; i++) digitalWrite(ledPins[i], HIGH); 
      break; 
  } 
} 