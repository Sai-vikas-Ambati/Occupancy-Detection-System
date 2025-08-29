# System Design Overview

## Sensors
- Two ultrasonic sensors are placed at the entry/exit point of the room, with one dedicated to detecting entry and the other to detecting exit.
- Each sensor sends an ultrasonic pulse and measures the echo time to determine if a person is within a defined proximity range (e.g., 10 cm).

## Processing Logic
- The STM32 microcontroller initializes the sensors and monitors interrupt signals from the echo pins.
- A `people_inside` counter is updated whenever a person enters or exits.
- Bluetooth communication sends real-time updates after every count change.

## Code Structure
- **GPIO Configuration**: Sets up pins for triggers, echoes, and UART.
- **UART Configuration**: Enables Bluetooth communication through UART2.
- **Timer Configuration**: TIM2 measures the duration of ultrasonic pulses.
- **Interrupt Handlers**: Handle rising/falling edges of the echo signal.
- **Main Loop**: Triggers sensors, checks for entry/exit, updates occupancy, and sends messages via Bluetooth.
