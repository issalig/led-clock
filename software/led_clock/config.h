/*
  file: config.h
  description: settings
  date: 14/03/2015
  author: Ismael Salvador
*/

//pinout version
#define VERSION_0_4

#if defined(VERSION_0_2)
#define DHT      D6
#define BUTTON_0 A1
#define BUTTON_1 A2
#define BUTTON_2 A3
#define BUTTON_3 A4
//7219
#define LOAD_7219 D10
#define CLK_7219  D11
#define DIN_7219  D12
#endif

///////////////////////////
#if defined(VERSION_0_3)
#define DHT      D6
#define BUTTON_0 D2
#define BUTTON_1 D3
#define BUTTON_2 D4
#define BUTTON_3 D5
//7219
#define LOAD_7219 D7
#define CLK_7219  D8
#define DIN_7219  D9
#endif

///////////////////////////
#if defined(VERSION_0_4)
#define LDR     A2

#define BUTTON_0 2
#define BUTTON_1 4
#define BUTTON_MODE BUTTON_1
#define BUTTON_SET BUTTON_0

#define LED_R D3
#define LED_G D5
#define LED_B D6
//7219
#define DIN_7219 A0
#define LOAD_7219 7
#define CLK_7219  8
//dht
#define DHT_PIN 6
//nokia
#define RST_NK 7
#define CLK_NK 8
#define LIGHT_NKD9
#define CE_NK 10
#define DIN_NK 11
#define CE_NK 10
//ir
#define IR1838 12

//dht
#define DHT_TYPE         DHT11 
#define DHT_PIN 6

//ws2812b data pin
#define DATA_WS2812B 3
#endif


