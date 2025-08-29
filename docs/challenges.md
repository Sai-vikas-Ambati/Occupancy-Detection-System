# Challenges and Solutions

## 1. Unreliable Distance Measurement Due to Noise
- **Problem**: Noise caused inconsistent distance readings.
- **Solution**: Instead of calculating exact distance, a threshold time was used to check if a person is within 10 cm. This simplified logic and improved reliability.

## 2. Debouncing and False Triggering
- **Problem**: Consecutive interrupts sometimes caused false counts.
- **Solution**: Added a small delay in the main loop and handled interrupt flags carefully to ensure stable counting.

## 3. Accurate Counting with Multiple Entries/Exits
- **Problem**: Multiple people moving quickly caused miscounts.
- **Solution**: Used flags (`sensor1_flag`, `sensor2_flag`) to ensure sequential processing. Counters update only when thresholds are met.

## 4. Bluetooth Communication Stability
- **Problem**: Sometimes Bluetooth messages were lost.
- **Solution**: Proper UART baud rate settings and error checking in transmission ensured reliable message delivery.
