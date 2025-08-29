#include "stm32f4xx.h"
#include <stdio.h>

void GPIO_Config(void);
void UART2_Config(void);
void TIM2_Config(void);
void delay_us(unsigned int us);
void trigger_sensor1(void);
void trigger_sensor2(void);
void send_message_via_bluetooth(const char *message);
void EXTI1_IRQHandler(void);
void EXTI9_5_IRQHandler(void);

int people_inside = 0;
int distance_sensor1_cm = 0;
int distance_sensor2_cm = 0;
unsigned int start_time_sensor1 = 0;
unsigned int end_time_sensor1 = 0;
unsigned int start_time_sensor2 = 0;
unsigned int end_time_sensor2 = 0;

int sensor1_flag = 0;
int sensor2_flag = 0;

int main(void) {
    GPIO_Config();
    UART2_Config();
    TIM2_Config();

    while (1) {
        // Trigger both sensors
        trigger_sensor1();
        trigger_sensor2();

        // Check if Sensor 1 detected entry
        if (sensor1_flag) {
            people_inside++;
            char message[50];
            sprintf(message, "Person entered, Inside Count: %d", people_inside);
            send_message_via_bluetooth(message);
            sensor1_flag = 0; // Reset the flag after processing
        }

        // Check if Sensor 2 detected exit
        if (sensor2_flag) {
            if (people_inside > 0) {
                people_inside--;
                char message[50];
                sprintf(message, "Person exited, Inside Count: %d", people_inside);
                send_message_via_bluetooth(message);
            }
            sensor2_flag = 0; // Reset the flag after processing
        }

        // Small delay for debouncing
        for (int i = 0; i < 10000; i++);
    }
}

// Configuration functions and interrupt handlers remain the same

void GPIO_Config(void) {
    // GPIO setup code remains the same
	 RCC->AHB1ENR |= (1 << 0);

    // Set PA0 and PA4 as output for Trigger (Sensor1 and Sensor2)
    GPIOA->MODER |= (1 << 0) | (1 << 8);
    GPIOA->OTYPER &= ~((1 << 0) | (1 << 4));
    GPIOA->OSPEEDR |= (3 << 0) | (3 << 8);

    // Set PA1 and PA5 as input for Echo (Sensor1 and Sensor2)
    GPIOA->MODER &= ~((3 << 2) | (3 << 10));

    // Configure PA2 and PA3 as TX and RX for UART2
    GPIOA->MODER |= (2 << 4) | (2 << 6);
    GPIOA->AFR[0] |= (7 << 8) | (7 << 12);

    // Enable SYSCFG clock and configure EXTI
    RCC->APB2ENR |= (1 << 14);
    SYSCFG->EXTICR[0] &= ~(0xF << 4); // PA1 for EXTI1 (Sensor1 Echo)
    EXTI->IMR |= (1 << 1);
    EXTI->FTSR |= (1 << 1);
    EXTI->RTSR |= (1 << 1);

    SYSCFG->EXTICR[1] &= ~(0xF << 4); // PA5 for EXTI5 (Sensor2 Echo)
    EXTI->IMR |= (1 << 5);
    EXTI->FTSR |= (1 << 5);
    EXTI->RTSR |= (1 << 5);

    NVIC_EnableIRQ(EXTI1_IRQn);
    NVIC_EnableIRQ(EXTI9_5_IRQn);
}

void UART2_Config(void) {
    RCC->APB1ENR |= (1 << 17);
    USART2->BRR = 0x0683;
    USART2->CR1 |= (1 << 3) | (1 << 2) | (1 << 13);
}

void TIM2_Config(void) {
    // TIM2 setup code remains the same
	 RCC->APB1ENR |= (1 << 0);
    TIM2->PSC = 84 - 1;
    TIM2->ARR = 0xFFFFFFFF;
    TIM2->CNT = 0;
    TIM2->CR1 |= (1 << 2);
}

void delay_us(unsigned int us) {
    unsigned int count = 84 * us;
    while (count--) {
        __NOP();
    }
}

void trigger_sensor1(void) {
    GPIOA->ODR |= (1 << 0);
    delay_us(10);
    GPIOA->ODR &= ~(1 << 0);
}

void trigger_sensor2(void) {
    GPIOA->ODR |= (1 << 4);
    delay_us(10);
    GPIOA->ODR &= ~(1 << 4);
}

void EXTI1_IRQHandler(void) {
    if (EXTI->PR & (1U << 1)) {
        EXTI->PR |= (1U << 1); // Clear interrupt flag

        if (GPIOA->IDR & (1 << 1)) { // Rising edge
            TIM2->CNT = 0;
            TIM2->CR1 |= (1 << 0); // Start counting
        } else { // Falling edge
            TIM2->CR1 &= ~(1 << 0); // Stop counting
            end_time_sensor1 = TIM2->CNT;
            distance_sensor1_cm = (end_time_sensor1 * 0.0343) / 2;
            if (distance_sensor1_cm < 10) { // Check 10 cm range
                sensor1_flag = 1;
            }
        }
    }
}

void EXTI9_5_IRQHandler(void) {
    if (EXTI->PR & (1U << 5)) {
        EXTI->PR |= (1U << 5); // Clear interrupt flag

        if (GPIOA->IDR & (1 << 5)) { // Rising edge
            TIM2->CNT = 0;
            TIM2->CR1 |= (1 << 0); // Start counting
        } else { // Falling edge
            TIM2->CR1 &= ~(1 << 0); // Stop counting
            end_time_sensor2 = TIM2->CNT;
            distance_sensor2_cm = (end_time_sensor2 * 0.0343) / 2;
            if (distance_sensor2_cm < 10) { // Check 10 cm range
                sensor2_flag = 1;
            }
        }
    }
}

void send_message_via_bluetooth(const char *message) {
    for (const char *p = message; *p != '\0'; p++) {
        while (!(USART2->SR & (1 << 7)));
        USART2->DR = *p;
    }
    while (!(USART2->SR & (1 << 7)));
    USART2->DR = '\n';
}



+1 -1
