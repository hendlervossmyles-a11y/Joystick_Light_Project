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
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(xPin, INPUT); // Sets Joystick X-axis as an analog input
  pinMode(yPin, INPUT); // Sets Joystick Y-axis as an analog input
  pinMode(buttonPin, INPUT_PULLUP); // Use internal pull-up resistor for button to distuinguish between pressed and unpressed
  // Set all LED pins as outputs so we can light them up
  pinMode(upLed, OUTPUT);
  pinMode(downLed, OUTPUT);
  pinMode(leftLed, OUTPUT);
  pinMode(rightLed, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
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