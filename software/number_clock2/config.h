/*
  file: config.h
  description: settings
  date: 14/03/2015
  author: Ismael Salvador
*/

#define VERSION_0_3


#ifdef VERSION_O_2
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

#ifdef VERSION_O_3
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

#ifdef VERSION_O_4

#define LDR     A2
#define DHT     A3
#define BUTTON_0 D2
#define BUTTON_1 D4
#define LED_R D3
#define LED_G D5
#define LED_G D6

//7219
#define DIN_7219 A0
#define LOAD_7219 D7
#define CLK_7219  D8

//nokia
#define RST_NK D7
#define CLK_NK D8
#define LIGHT_NK D9
#define CE_NK D10
#define DIN_NK D11
#define CE_NK D10

#define IR1838 D12

#endif

