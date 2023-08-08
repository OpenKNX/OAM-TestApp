#pragma once
#include "OpenKNXHardware.h"

#ifdef ARDUINO_ARCH_RP2040
    #ifdef BOARD_MASIFI_SENSOR_BREAKOUT
        // #define OPENKNX_RECOVERY_ON LOW
        #define PROG_LED_PIN 1
        #define PROG_LED_PIN_ACTIVE_ON HIGH
        #define INFO_LED_PIN 3
        #define INFO_LED_PIN_ACTIVE_ON HIGH
        #define PROG_BUTTON_PIN 0
        #define PROG_BUTTON_PIN_INTERRUPT_ON FALLING
        #define SAVE_INTERRUPT_PIN 22
        #define KNX_UART_RX_PIN 17
        #define KNX_UART_TX_PIN 16
        #define HARDWARE_NAME "MASIFI-SENSOR-BREAKOUT"
    // #define SmartMF_HardwareVariant_PIN 26
    // #define SmartMF_HardwareRevision_PIN1 10
    // #define SmartMF_HardwareRevision_PIN2 11
    // #define SmartMF_HardwareRevision_PIN3 12
    #endif
#endif

#ifdef ARDUINO_ARCH_SAMD
    #ifdef BOARD_KONNEKTING_MI
        #define PROG_LED_PIN A3
        #define PROG_LED_PIN_ACTIVE_ON HIGH
        #define PROG_LED_SUPPORT_PWM
        #define PROG_BUTTON_PIN 38
        #define PROG_BUTTON_PIN_INTERRUPT_ON FALLING
        #define INFO_LED_PIN A5
        #define INFO_LED_PIN_ACTIVE_ON HIGH
        #define HARDWARE_NAME "KONNEKTING-MI"
        #define OPENKNX_NO_BOOT_PULSATING 1
    #endif
#endif

#ifdef ARDUINO_ARCH_ESP32
    #ifdef BOARD_ESP32_DEV
        #define PROG_LED_PIN 2
        #define PROG_LED_PIN_ACTIVE_ON HIGH
        #define PROG_BUTTON_PIN 35
        #define PROG_BUTTON_PIN_INTERRUPT_ON FALLING
        #define HARDWARE_NAME "ESP32_DEV"
    #endif
#endif
