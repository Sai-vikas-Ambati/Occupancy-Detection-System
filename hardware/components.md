# Hardware Components

The following hardware components were used in the **Occupancy Detection System**:

| Component                  | Quantity | Description / Role |
|-----------------------------|----------|--------------------|
| **STM32 Microcontroller**  | 1        | Main processing unit for sensor control and Bluetooth communication |
| **Ultrasonic Sensor (HC-SR04)** | 2    | Detect entry and exit events by measuring distance/proximity |
| **Bluetooth Module (HC-05)** | 1      | Enables wireless communication with external devices (e.g., mobile app, PC) |
| **Power Supply**            | 1        | Provides stable voltage and current to STM32 and sensors |
| **Breadboard / PCB**        | 1        | Mounting and wiring of components for prototyping |

---

## Notes
- Sensors are positioned at the entrance for entry/exit detection.
- Bluetooth module transmits real-time occupancy count.
- A regulated **5V/3.3V supply** is required for stable operation.
