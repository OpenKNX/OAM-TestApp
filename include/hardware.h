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

    
    #ifdef BOARD_PIPICOW
        #define PROG_LED_PIN 32
        #define PROG_LED_PIN_ACTIVE_ON HIGH
    #endif
#endif

#ifdef ARDUINO_ARCH_SAMD
    #ifdef BOARD_KONNEKTING_MI
        #define PROG_LED_PIN A3
        #define PROG_LED_PIN_ACTIVE_ON HIGH
        #define PROG_BUTTON_PIN 38
        #define PROG_BUTTON_PIN_INTERRUPT_ON FALLING
        #define INFO_LED_PIN A5
        #define INFO_LED_PIN_ACTIVE_ON HIGH
        #define HARDWARE_NAME "KONNEKTING-MI"
        #define OPENKNX_NO_BOOT_PULSATING 1
    #endif
    #ifdef BOARD_WEMOS_MINI_D1
        #define PROG_LED_PIN 3
        #define PROG_LED_PIN_ACTIVE_ON HIGH
        #define PROG_BUTTON_PIN 5
        #define PROG_BUTTON_PIN_INTERRUPT_ON FALLING
        #define INFO_LED_PIN 4
        #define INFO_LED_PIN_ACTIVE_ON HIGH
        #define HARDWARE_NAME "WEMOS-MINI-D1"
    #endif
#endif

#ifdef ARDUINO_ARCH_ESP32
    #ifdef BOARD_ESP32_DEV
        #define PROG_LED_PIN 2
        #define PROG_LED_PIN_ACTIVE_ON HIGH
        // #define PROG_BUTTON_PIN 35
        // #define PROG_BUTTON_PIN_INTERRUPT_ON FALLING
        #define HARDWARE_NAME "ESP32_DEV"
    #endif
    #ifdef BOARD_ESP32_WT32_ETH01
        #define PROG_LED_PIN 2
        #define PROG_LED_PIN_ACTIVE_ON HIGH
        #define PROG_BUTTON_PIN 4
        #define PROG_BUTTON_PIN_INTERRUPT_ON FALLING

        #define ETH_PHY_TYPE        ETH_PHY_LAN8720
        #define ETH_PHY_ADDR        1
        #define ETH_PHY_MDC         23
        #define ETH_PHY_MDIO        18
        #define ETH_PHY_POWER       16
        #define ETH_CLK_MODE        ETH_CLOCK_GPIO0_IN

        #define HARDWARE_NAME "ESP32_WT32_ETH01"
    #endif
    #ifdef BOARD_REG1_ESP_DEVBOARD_V00_02
        #define HARDWARE_NAME "REG1_ESP_DEV"

        #define PROG_LED_PIN 4
        #define PROG_LED_PIN_ACTIVE_ON HIGH
        #define PROG_BUTTON_PIN 39
        #define PROG_BUTTON_PIN_INTERRUPT_ON FALLING

        #define SAVE_INTERRUPT_PIN 36
        #define KNX_UART_RX_PIN 37
        #define KNX_UART_TX_PIN 14

        //#define INFO1_LED_PIN 4
        //#define INFO1_LED_PIN_ACTIVE_ON HIGH
        //#define INFO2_LED_PIN 4
        //#define INFO2_LED_PIN_ACTIVE_ON HIGH
        //#define INFO3_LED_PIN 4
        //#define INFO3_LED_PIN_ACTIVE_ON HIGH

        #define FUNC1_BUTTON_PIN 38
        #define FUNC2_BUTTON_PIN 34
        #define FUNC3_BUTTON_PIN 35

        #define ETH_PHY_TYPE  ETH_PHY_LAN8720   // type of PHY used, needed for IDF
        #define ETH_PHY_ADDR  0                 // PHYs I2C address
        #define ETH_PHY_MDC   33                
        #define ETH_PHY_MDIO  32
        #define ETH_PHY_POWER 2                 // enable / disable the PHYs clock
        #define ETH_CLK_MODE  ETH_CLOCK_GPIO0_IN

        #define REG1_APP_PIN1 12
        #define REG1_APP_PIN2 15
        #define REG1_APP_PIN3 13
        #define REG1_APP_PIN4 5
        #define REG1_APP_PIN5 8
        #define REG1_APP_PIN6 7
        #define REG1_APP_PIN7 20

        // informative pin usage - Do not use for other purposes
        // RMII: 
        // ETH_PHY_CLK_INPUT_PIN 0
        // ETH_PHY_RXD0_PIN 25
        // ETH_PHY_RXD1_PIN 26
        // ETH_PHY_RX_DV_CRS_PIN 27
        // ETH_PHY_TX_EN_PIN 21
        // ETH_PHY_TXD0_PIN 19
        // ETH_PHY_TXD1_PIN 22
        //
        // USB:
        // USB_UART_TX_PIN 1
        // USB_UART_RX_PIN 3
    #endif
#endif
