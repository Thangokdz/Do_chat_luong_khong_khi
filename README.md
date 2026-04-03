# Air Quality Monitoring and Control System (IoT)

## Description
This project is an advanced air quality monitoring system that detects gas and dust levels in the environment and automatically controls a ventilation system. The system also allows manual control via buttons and provides visual feedback through LEDs and LCD.

## Features
- Detect gas concentration using MQ135 sensor
- Measure dust level using dust sensor
- Automatic air quality evaluation (clean / polluted)
- Control ventilation fan via relay
- Servo motor to open/close air vent
- LED indicators for gas and dust status
- LCD display for real-time system status
- Manual control using buttons (power & fan)

## Hardware Components
- Arduino Uno
- MQ135 Gas Sensor
- Dust Sensor
- Relay Module
- DC Fan
- Servo Motor
- LCD (I2C)
- LEDs (status indicators)
- Push buttons
- Breadboard & jumper wires

## Working Principle
- The system reads gas and dust values periodically
- If values exceed threshold:
  - Air is considered polluted
  - LEDs turn RED
- If air is clean:
  - LEDs turn GREEN

- User can:
  - Turn system ON/OFF using button
  - Control fan manually

- When fan is ON:
  - Relay activates the fan
  - Servo opens air vent

- LCD displays:
  - Air quality status (clean / polluted)
  - System state

## Demo
(Add your video link here)

## Images
<img width="769" height="609" alt="Screenshot 2026-04-03 171544" src="https://github.com/user-attachments/assets/feb75793-3390-4ca2-9c9b-3250ece45574" />

![z7687872055510_69d87c82fbf9a985d9410d9fc3eedff9](https://github.com/user-attachments/assets/00f38876-65ad-4f15-9224-952eea22d761)

