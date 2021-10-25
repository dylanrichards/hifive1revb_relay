/**
 * Seeed Studio - Relay Shield v2.1
 * https://wiki.seeedstudio.com/Relay_Shield_V2/#resources
 * 
 * Schematics:
 *   Seeed Studio:
 *     https://files.seeedstudio.com/wiki/Relay-Shield_V2.0/res/Relay%20shield%20sch.pdf
 *   Freedom E310:
 *     https://sifive.cdn.prismic.io/sifive/c34f4c7f-0d3a-493e-8a19-a0b18f8a4555_hifive1-b01-schematics.pdf
 * 
 */

#ifndef RELAYSHIELD_H_
#define RELAYSHIELD_H_

#define DIG4    20
#define DIG5    21
#define DIG6    22
#define DIG7    23

#define RELAY1  DIG7
#define RELAY2  DIG6
#define RELAY3  DIG5
#define RELAY4  DIG4

#define ON  1
#define OFF 0

void setupRelays(struct metal_gpio *gpio_device, uint8_t *relayArr);
void clearRelays(struct metal_gpio *gpio_device, uint8_t *relayArr);
void delay(int sec);

#endif