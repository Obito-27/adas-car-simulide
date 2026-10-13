# ADAS Car System: Arduino + SimulIDE

A simulated Advanced Driver Assistance System (ADAS) for a car, built on an Arduino Uno (ATmega328P) and simulated in [SimulIDE](https://simulide.com). An ultrasonic sensor measures the distance to an obstacle, and the firmware warns the driver, slows the car and brakes automatically.

**Authors:** Salil Sampat (B.Tech IT, A255), Lokesh Patil (B.Tech IT, A240)
NMIMS Mukesh Patel School of Technology Management & Engineering, Shirpur

## Features

| Feature | Behaviour |
|---|---|
| Forward Collision Warning | Warning LED on and buzzer beeps when the obstacle is 80 cm or closer |
| Adaptive speed reduction | Motor speed falls in proportion to the gap between 80 cm and 30 cm |
| Automatic Emergency Braking (AEB) | Motor stops, brake LED on, continuous buzzer at 30 cm or closer |
| Blind Spot Detection | Left and right switches light two orange LEDs |
| Lane Departure Warning | Left or right lane switch lights a blue LED |
| Driver throttle | Potentiometer sets speed; ADAS overrides it in danger zones |

## Files

| File | Description |
|---|---|
| `adas_car.sim1` | SimulIDE circuit (open this) |
| `adas_car.hex` | Compiled firmware, loaded automatically by the circuit |
| `adas_car.ino` | Arduino source code |

## How to run

1. Install SimulIDE (version 1.1 or later).
2. Download all three files into the **same folder**.
3. Open `adas_car.sim1` in SimulIDE (File, then Open).
4. Press the red power button.
5. Turn the **obstacle distance dial** (1 V = 1 m) and watch the response:
   - Above 80 cm: normal driving
   - 30 to 80 cm: warning and slowing
   - 30 cm or less: emergency braking
6. Turn the **throttle pot** (A0) to change the driver's speed request, and click the switches to test blind spot and lane alerts.

If the Uno shows no program, right-click it, choose Load firmware and select `adas_car.hex`.

## Pin map

| Component | Arduino pin |
|---|---|
| HC-SR04 Trig / Echo | D9 / D10 |
| Motor (via MOSFET, PWM) | D6 |
| Buzzer | D11 |
| Warning LED / Brake LED | D12 / D13 |
| Blind-spot switches (left / right) | D2 / D3 |
| Lane switches (left / right) | D4 / D5 |
| Blind-spot LEDs (left / right) | A1 / A2 |
| Lane LED | A3 |
| Throttle potentiometer | A0 |

## Test results

19 test cases (collision zones, throttle interaction, blind spot, lane departure) were run in SimulIDE and all passed. Details are in the project report.

## Limitations

- Simulation only. The car is a small DC motor, so vehicle mass and braking distance are not modelled.
- Decisions use distance only, not relative speed or time-to-collision.
- Blind spot and lane sensors are represented by switches.
- Ultrasonic sensing has a short range and suits low speeds only.

## Future scope

Time-to-collision braking, real IR and radar sensors, an LCD dashboard, servo lane-keep steering, and a hardware build with a flyback diode and motor driver IC.

## Tools

SimulIDE, Arduino C/C++, avr-gcc.
