# Occupancy Detection System for Closed Spaces

## 📌 Overview
This project is an **embedded system** that detects and counts the number of people inside a closed space (e.g., room, office, hallway).  
It uses **two ultrasonic sensors** for entry/exit detection, an **STM32 microcontroller** for processing, and an **HC-05 Bluetooth module** for real-time occupancy updates.

👉 Full design details: [docs/design_overview.md](docs/design_overview.md)

---

## ⚡ Features
- Real-time entry and exit detection using dual ultrasonic sensors  
- Accurate occupancy tracking with **interrupt-based processing**  
- Wireless Bluetooth communication for monitoring  
- Low-cost, non-intrusive, and scalable  

---

## 🛠️ Hardware Components
- STM32 Microcontroller  
- Ultrasonic Sensors (HC-SR04) ×2  
- Bluetooth Module (HC-05)  
- Power Supply (regulated 5V/3.3V)  
- Breadboard / PCB  

📜 Full list here: [hardware/components.md](hardware/components.md)

---

## 🔧 Firmware
Firmware is written in **C for STM32F4** using register-level configuration.

👉 Source code: [firmware/src/main.c](firmware/src/main.c)


---

## 🚀 Applications
- **Smart Buildings** → Room occupancy monitoring  
- **Energy Optimization** → Control HVAC and lighting  
- **Security** → Detect unauthorized access  
- **Conference Rooms / Offices** → Ensure occupancy compliance  

📜 More details: [docs/applications.md](docs/applications.md)

---




## Repository Structure

Occupancy-Detection-System/
│── README.md
│── LICENSE
│── docs/
│ ├── design_overview.md
│ ├── challenges.md
│ └── applications.md
│── hardware/
│ ├── components.md
│ └── schematic.png (optional)
│── firmware/
│ ├── src/
│ │ └── main.c
│ └── inc/
│── simulations/
└── .gitignore

