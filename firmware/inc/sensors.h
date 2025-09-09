#ifndef SENSORS_H
#define SENSORS_H

void Sensors_Init(void);
void Trigger_Sensor1(void);
void Trigger_Sensor2(void);
void EXTI1_IRQHandler(void);
void EXTI9_5_IRQHandler(void);

#endif // SENSORS_H
