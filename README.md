# Arduino Joystick LED Directional Controller

An interactive hardware project that maps the 2-axis directional movement of an analog joystick module to dynamically fade an array of 4 directional LEDs. Pushing the joystick further in a given direction increases the brightness of the corresponding LED using Pulse Width Modulation (PWM). Pressing the joystick button triggers a "panic/override" mode that illuminates all LEDs simultaneously.

---

## Features
* **Proportional LED Fading:** Maps the raw 10-bit analog joystick values ($0$ to $1023$) to an 8-bit PWM duty cycle ($0$ to $255$) for smooth, reactive brightness changes.
* **Deadzone Handling:** Calibrated centered reference bounds ($\approx 489$ for Y-axis, $\approx 511$ for X-axis) ensure LEDs remain fully off when the stick is resting.
* **Tactile Switch Interrupt:** Utilizes an internal pull-up resistor connection to detect joystick clicks, immediately lighting up the entire board.

---

## Hardware Configuration

### Components Required
* **Elegoo / Arduino Uno R3** Microcontroller
* **2-Axis Analog Joystick Module** (with select button pin)
* **4 LEDs** (Red, Yellow, Green, Blue)
* **4 Resistors** (for LED current limiting protection)
* **Solderless Breadboard & Jumper Wires**

### Pin Connection Layout
Based on the project firmware configuration, connect your hardware components directly to the microcontroller using the following pin map:

| Component | Pin Function | Connected / Arduino Pin |
| :--- | :--- | :--- |
| **Joystick Module** | X-Axis Analog Output (`VRx`) | **Analog Pin A1** |
| | Y-Axis Analog Output (`VRy`) | **Analog Pin A2** |
| | Tactile Switch Button (`SW`) | **Digital Pin 2** |
| **Directional LEDs** | UP LED (Green) | **Digital Pin 10 (PWM)** |
| | DOWN LED (Red) | **Digital Pin 9 (PWM)** |
| | LEFT LED (Yellow) | **Digital Pin 11 (PWM)** |
| | RIGHT LED (Blue) | **Digital Pin 6 (PWM)** |

---

## Project Visuals & Hardware Setup

### Wiring & Assembly Showcase
Below are the assembly views of the real-world build detailing the layout of the resistors, common power rails, and wiring paths back to the Elegoo Uno R3:

| Top-Down Wiring Profile | Breadboard Profile Detail |
| :---: | :---: |
| ![Full System Layout](<media/IMG_2232.jpg>) | ![Resistor and LED Matrix](<media/IMG_2228.jpg>) |


### Working Project Demo
> 🎥 **Watch the demonstration video here:** (https://www.youtube.com/watch?v=bKtfi2IBZck)

---

## Firmware Configuration (`JoystickControl.ino`)

Upload the following sketch directly to your hardware environment via the Arduino IDE. 

```cpp
// Credits: Project and Code inspiration from Rachel De Barros
// Debugging Help from Chat-GPT

int xPin = A1; // Joystick X-axis connected to analog pin A1
int yPin = A2; // Joystick Y-axis connected to analog pin A2
int buttonPin = 2; // Joystick button connected to digital pin 2

int xVal; // Holds the X-axis reading
int yVal; // Holds the Y-axis reading
int buttonState; // Holds the button state (Pressed or Not Pressed)

int upLed = 10; // LED that represents UP direction
int downLed = 9; // LED for DOWN direction
int leftLed = 11; // LED for LEFT direction
int rightLed = 6; // LED for RIGHT direction
int upBrightness = 0;
int downBrightness = 0;
int leftBrightness = 0;
int rightBrightness = 0;

void setup() {
  Serial.begin(9600);
  pinMode(xPin, INPUT); // Sets Joystick X-axis as an analog input
  pinMode(yPin, INPUT); // Sets Joystick Y-axis as an analog input
  pinMode(buttonPin, INPUT_PULLUP); // Use internal pull-up resistor for button to distinguish between pressed and unpressed
  
  // Set all LED pins as outputs so we can light them up
  pinMode(upLed, OUTPUT);
  pinMode(downLed, OUTPUT);
  pinMode(leftLed, OUTPUT);
  pinMode(rightLed, OUTPUT);
}

void loop() {
  xVal = analogRead(xPin); // Read X position (0 = left, 1023 = right)
  yVal = analogRead(yPin); // Read Y position (0 = up, 1023 = down)
  buttonState = digitalRead(buttonPin); // Read button

  upBrightness = map(yVal, 489, 0, 0, 255); // Map Y-axis to UP brightness: pushed up = high brightness
  downBrightness = map(yVal, 489, 1023, 0, 255); // Map Y-axis to DOWN brightness: pushed down = high brightness
  leftBrightness = map(xVal, 511, 0, 0, 255);
  rightBrightness = map(xVal, 511, 1023, 0, 255);

  if (yVal <= 489) { // LED brightness depends on how far it's pushed
    analogWrite(upLed, upBrightness);
  }
  if (yVal >= 489) {
    analogWrite(downLed, downBrightness);
  }
  if (xVal <= 511) {
    analogWrite(leftLed, leftBrightness);
  }
  if (xVal >= 511) {
    analogWrite(rightLed, rightBrightness);
  }
  
  if (buttonState == LOW) { // LOW means button is pressed.
    // If Low then turn on all the lights
    digitalWrite(upLed, HIGH);
    digitalWrite(downLed, HIGH);
    digitalWrite(leftLed, HIGH);
    digitalWrite(rightLed, HIGH);
  }
}




