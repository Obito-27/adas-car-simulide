/*
  ADAS Car - SimulIDE (Arduino Uno)
  Forward Collision Warning, Auto Emergency Braking, adaptive speed control,
  Blind Spot Detection, Lane Departure Warning.

  D9  HC-SR04 TRIG   D10 HC-SR04 ECHO
  D6  Motor PWM -> MOSFET gate
  D11 Buzzer   D12 Warning LED   D13 Brake LED
  D2  Blind-spot LEFT switch   D3 Blind-spot RIGHT switch  (to GND, active LOW)
  D4  Lane LEFT switch         D5 Lane RIGHT switch        (to GND, active LOW)
  A1  BSD LED left   A2 BSD LED right   A3 Lane LED
  A0  Pot = driver throttle
*/
const int TRIG = 9, ECHO = 10, MOTOR = 6;
const int BUZZ = 11, LED_WARN = 12, LED_BRAKE = 13;
const int BSD_L = 2, BSD_R = 3, LANE_L = 4, LANE_R = 5;
const int LED_BSD_L = A1, LED_BSD_R = A2, LED_LANE = A3;

const int AEB_CM  = 30;   // full brake below this
const int WARN_CM = 80;   // warn + slow down below this

long readDistanceCm() {
  digitalWrite(TRIG, LOW);  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH); delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  long t = pulseIn(ECHO, HIGH, 30000UL);
  if (t == 0) return 400;            // no echo = clear road
  return t / 58;
}

void setup() {
  pinMode(TRIG, OUTPUT); pinMode(ECHO, INPUT);
  pinMode(MOTOR, OUTPUT);
  pinMode(BUZZ, OUTPUT); pinMode(LED_WARN, OUTPUT); pinMode(LED_BRAKE, OUTPUT);
  pinMode(LED_BSD_L, OUTPUT); pinMode(LED_BSD_R, OUTPUT); pinMode(LED_LANE, OUTPUT);
  pinMode(BSD_L, INPUT_PULLUP); pinMode(BSD_R, INPUT_PULLUP);
  pinMode(LANE_L, INPUT_PULLUP); pinMode(LANE_R, INPUT_PULLUP);
}

void loop() {
  int driverPwm = map(analogRead(A0), 0, 1023, 0, 255);
  long d = readDistanceCm();
  int pwm = driverPwm;
  bool warn = false, brake = false;

  if (d <= AEB_CM) {                 // Auto Emergency Braking
    pwm = 0; brake = true; warn = true;
  } else if (d <= WARN_CM) {         // Collision warning + adaptive speed
    int limit = map(d, AEB_CM, WARN_CM, 0, 255);
    pwm = min(driverPwm, limit);
    warn = true;
  }

  analogWrite(MOTOR, pwm);
  digitalWrite(LED_BRAKE, brake);
  digitalWrite(LED_WARN, warn);
  if (brake)      digitalWrite(BUZZ, HIGH);
  else if (warn)  digitalWrite(BUZZ, (millis() / 150) % 2);
  else            digitalWrite(BUZZ, LOW);

  digitalWrite(LED_BSD_L, !digitalRead(BSD_L));   // blind spot
  digitalWrite(LED_BSD_R, !digitalRead(BSD_R));
  digitalWrite(LED_LANE, !digitalRead(LANE_L) || !digitalRead(LANE_R)); // lane departure
  delay(50);
}
