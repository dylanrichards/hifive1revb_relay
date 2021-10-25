/**
 * Author: Dylan Richards
 * Description: Iterate through the relays on the Seeed Studio Relay Shield
 * 
 * HiFive1 Rev B01: https://www.sifive.com/boards/hifive1-rev-b
 * 
 * Freedom E310-G002 Manual:
 *   https://sifive.cdn.prismic.io/sifive/e36c0a2f-413f-49d4-85c1-51ee1ed243e5_fe310-g002-manual-v1p1.pdf
 * 
 * GPIO Freedom Metal Documentation:
 *   https://sifive.github.io/freedom-metal-docs/apiref/gpio.html
 */

#include <stdio.h>
#include <metal/gpio.h>
#include <metal/machine/platform.h>

#include "relayshield.h"

#define NUM_OF_RELAYS   4

int main(void)
{
    struct metal_gpio *gpio_device = metal_gpio_get_device(0);
    uint8_t relayArr[NUM_OF_RELAYS] = {RELAY1, RELAY2, RELAY3, RELAY4};

    setupRelays(gpio_device, relayArr);

    uint8_t relay;
    for (relay = 0;; relay++)
    {
        clearRelays(gpio_device, relayArr);
        metal_gpio_set_pin(gpio_device, relayArr[relay % NUM_OF_RELAYS], ON);
        printf("Relay %d ON\n", (relay % NUM_OF_RELAYS) + 1);
        delay(10);
    }

    return 0;
}

void setupRelays(struct metal_gpio *gpio_device, uint8_t *relayArr)
{
    uint8_t i;
    for (i = 0; i < NUM_OF_RELAYS; i++) {
        metal_gpio_enable_output(gpio_device, *(relayArr + i));
    }

    clearRelays(gpio_device, relayArr);
}

void clearRelays(struct metal_gpio *gpio_device, uint8_t *relayArr)
{
    uint8_t i;
    for (i = 0; i < NUM_OF_RELAYS; i++) {
        metal_gpio_set_pin(gpio_device, *(relayArr + i), OFF);
    }
}

/**
 * Core-Local Interruptor (CLINT) - page 44
 * METAL_RISCV_CLINT0_0_BASE_ADDRESS = 0x2000000
 * METAL_RISCV_CLINT0_MTIME = 0xbff8
 * mtime - timer register = 0x200bff8
 * number of cycles counted from rtcclk
 * 
 * Real-Time Clock (RTC) - page 73
 * 32.768 kHz
 */
void delay(int sec)
{
    volatile uint64_t *mtime = (uint64_t *)(METAL_RISCV_CLINT0_0_BASE_ADDRESS + METAL_RISCV_CLINT0_MTIME);
    uint64_t start = *mtime;

    uint64_t ticks = sec * METAL_SIFIVE_AON0_0_SIZE;

    while ((*mtime - start) < ticks);
}
