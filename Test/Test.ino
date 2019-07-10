 /*  dummy */
      /*  1  - 3.3V */
      /*  2  - P6.0_A15 */
      /*  3  - P3.2_URXD */
      /*  4  - P3.3_UTXD */
      /*  5  - P4.1_IO_A12 */
      /*  6  - P4.3_A10 */
      /*  7  - P1.5_SPICLK */
      /*  8  - P4.6_IO_A7 */
      /*  9  - P6.5_I2CSCL */
      /*  10 - P6.4_I2CSDA */

      /*  11 - P3.6_IO */
      /*  12 - P5.2_IO */
      /*  13 - P5.0_IO */
      /*  14 - P1.7_SPIMISO */
      /*  15 - P1.6_SPIMOSI */
      /*  16 - RESET */
      /*  17 - P5.7_IO */
      /*  18 - P3.0_IO */
      /*  19 - P2.5_IO_PWM */
      /*  20 - GND */

      /*  21 - 5V */
      /*  22 - GND */
      /*  23 - P6.1_A14 */
      /*  24 - P4.0_A13 */
      /*  25 - P4.2_A11 */
      /*  26 - P4.4_A9 */
      /*  27 - P4.5_A8 */
      /*  28 - P4.7_A6 */
      /*  29 - P5.4_IO */
      /*  30 - P5.5_IO */

      /*  31 - P3.7_IO */
      /*  32 - P3.5_IO */
      /*  33 - P5.1_IO */
      /*  34 - P2.3_IO */
      /*  35 - P6.7_IO_CAPT */
      /*  36 - P6.6_IO_CAPT */
      /*  37 - P5.6_PWM */
      /*  38 - P2.4_PWM */
      /*  39 - P2.6_PWM */
      /*  40 - P2.7_PWM */

    /* pins 41-56 */
      /*  41 - P8.5 */
      /*  42 - P9.0 */
      /*  43 - P8.4 */
      /*  44 - P8.2 */
      /*  45 - P9.2 */
      /*  46 - P6.2 */
      /*  47 - P7.3 */
      /*  48 - P7.1 */
      /*  49 - P9.4 */
      /*  40 - P9.6 */
      /*  51 - P8.0 */
      /*  52 - P7.4 */
      /*  53 - P7.6 */
      /*  54 - P10.0 */
      /*  55 - P10_2 */
      /*  56 - P10.4 */

    /* pins 57-72 */
      /*  57 - P8.6 */
      /*  58 - P8.7 */
      /*  59 - P9.1 */
      /*  60 - P8.3 */
      /*  61 - P5.3 */
      /*  62 - P9.3 */
      /*  63 - P6.3 */
      /*  64 - P7.2 */
      /*  65 - P7.0 */
      /*  66 - P9.5 */
      /*  67 - P9.7 */
      /*  68 - P7.5 */
      /*  69 - P7.7 */
      /*  70 - P10.1 */
      /*  71 - P10.3 */
      /*  72 - P10.5 */

    /* virtual pins 73-78 */
      /*  73 - P1.1 SW1 */
      /*  74 - P1.4 SW2 */
      /*  75 - P2.0 RED_LED */
      /*  76 - P2.1 GREEN_LED */
      /*  77 - P2.2 BLUE_LED */
      /*  78 - P1.0 LED1 */

//IMPORTS------------------------------------------------------------------------------------
#if defined(ENERGIA) 
#include "Energia.h"
#else // error
#error Platform not defined
#endif

#include "SPI.h"
#define K35_SPI // HX8353E K35_SPI

#if defined(K35_SPI)
#include "Screen_K35_SPI.h"
Screen_K35_SPI myScreen;

#elif defined(HX8353E)
#include "Screen_HX8353E.h"
Screen_HX8353E myScreen;

#else
#error Unknown screen
#endif

#include "stdint.h"
//change these to any gpio
int SCLK = 59;// This for Serial Clock
int SDIO = 57;// Master Output
int NCS  = 58;// Slave select
//-------------------------------------------------------------------------------------------




//SETUP---------------------------------------------------------------------------------------
void setup() {
  Serial.begin(9600);
  pinMode(SCLK, OUTPUT);
  pinMode(SDIO, OUTPUT);
  pinMode(NCS, OUTPUT);
  mouse_reset();
  myScreen.begin();
  delay(10);

}
//---------------------------------------------------------------------------------------------



//LOOP---------------------------------------------------------------------------------------
void loop() {
  int img[15][15];
  for (int i=0;i<15;i++){
    for (int j=0;j<15;j++){
      img[i][j]=readLoc(0x0b);
      img[i][j] &= 0x7F; // msb = valid bit
      img[i][j]=(img[i][j]<<1);
      Serial.print(img[i][j]);
      Serial.print(",");
    }
    Serial.println();
  }
  Serial.println();
  LCD(img);
}
//-------------------------------------------------------------------------------------------



//LCD Code
void LCD(int a[15][15]){
  myScreen.setPenSolid(true);
  myScreen.setFontSolid(false);
  for(int i=0; i<15; i++){ // top right corner, x address
    for(int j=15; (int8_t)j>-1;j--){ // top right corner, y address
    int k=myScreen.calculateColour(a[i][j],a[i][j],a[i][j]);
    myScreen.dRectangle((16*i)+40,(16*j),16,16,k);  
    } // x resolution: 320 - 240 = 80 therefore 40 offset from both x axis limits (makes a 240x240)
}     // y resolution: 240p, 240/15 = 16
}
//





//MOUSE RESET--------------------------------------------------------------------------------
void mouse_reset(){
  // Initiate chip reset
  digitalWrite(NCS, LOW);
  pushbyte(0xba); // write address: MSB = 1 for write, address = 7-bit 0x3a
  pushbyte(0x5a); // write data, 8-bits
  digitalWrite(NCS, HIGH);
  delay(10);
  // Set 1000cpi resolution
  digitalWrite(NCS, LOW);
  pushbyte(0x0d);
  pushbyte(0x01);
  digitalWrite(NCS, HIGH);
}
//-------------------------------------------------------------------------------------------





//PUSH BYTE----------------------------------------------------------------------------------
void pushbyte(uint8_t c){
  pinMode(SDIO, OUTPUT);
  for(unsigned int i=0x80;i;i=i>>1){
    digitalWrite(SCLK, LOW);
    digitalWrite(SDIO, c & i);
    digitalWrite(SCLK, HIGH);
  }
}
//-------------------------------------------------------------------------------------------



//PULL BYTE----------------------------------------------------------------------------------
unsigned int pullbyte(){
  unsigned int ret=0;
  pinMode(SDIO, INPUT);
  for(unsigned int i=0x80; i>0; i>>=1) {
    digitalWrite(SCLK, LOW); //low
    ret |= i*digitalRead(SDIO);
    digitalWrite(SCLK, HIGH); // high
  }
  pinMode(SDIO, OUTPUT);
  return(ret);
}
//-------------------------------------------------------------------------------------------



//READ LOCATION------------------------------------------------------------------------------
unsigned int readLoc(uint8_t addr){
  unsigned int ret=0;
  digitalWrite(NCS, LOW);
  pushbyte(addr);
  ret=pullbyte();
  digitalWrite(NCS, HIGH);
  return(ret);
}
//-------------------------------------------------------------------------------------------
