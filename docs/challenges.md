# Challenges and Solutions

## 1. Unreliable Distance Measurement Due to Noise
- **Problem**: Noise caused inconsistent distance readings.
- **Solution**: Use a threshold time instead of relying on absolute distance; simplified logic improves reliability.

## 2. Debouncing and False Triggering
- **Problem**: Consecutive interrupts sometimes caused false counts.
- **Solution**: Add a small delay in the main loop and handle interrupt flags carefully to ensure stable counting.

## 3. Accurate Counting with Multiple Entries/Exits
- **Problem**: Multiple people moving quickly caused miscounts.
- **Solution**: Use flags (`sensor1_flag`, `sensor2_flag`) to ensure sequential processing. Counters update only when thresholds are met.

## 4. Bluetooth Communication Stability
- **Problem**: Sometimes Bluetooth messages were lost.
- **Solution**: Proper UART baud rate settings and error checking in transmission ensured reliable message delivery.

---

## Limitations
- Sensor blind-spots if people walk too close to each other.
- HC-SR04 has limited accuracy for fast-moving multiple persons.
- System uses interrupts and a simple debounce; extreme crowding may still cause miscounts.

## Future Work / Improvements
- Add a small state machine to detect direction reliably (debounce + windowed sampling).
- Replace HC-SR04 with IR or time-of-flight (ToF) sensors for better accuracy.
- Add non-volatile storage (EEPROM/flash) to persist counts across power cycles.
- Create a mobile/web dashboard for live monitoring and historical analytics.
