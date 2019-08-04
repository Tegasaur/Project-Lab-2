#include <Movementi.h>



    
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
//64->Right Enable->ENA
//65->Left Enable->ENB
//66->Front Left->IN2
//59->Front Right->IN4
//63->Back Right ->IN3
//72->Back Left->IN1
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
int SCLK = 60;// This for Serial Clock
int SDIO = 61;// Master Output
int NCS  = 62;// Slave select
int SCLK1 =41;// Serial Clock
int SDIO1= 42;// Master Output
int NCS1=43; //Slave select
int img[15][15];
int img2[15][15];
int ENR=68;
int ENL=69;
int RF=44;
int LB=59;
int RB=66;
int LF=63;
int speedr=110;
int speedl=110;
int speedt=90;
char t;
void setup() {
  Serial.begin(9600);
  pinMode(ENR,OUTPUT);
  pinMode(ENL,OUTPUT);
  pinMode(59,OUTPUT);
  pinMode(63,OUTPUT);
  pinMode(66,OUTPUT);
  pinMode(72,OUTPUT);
  pinMode(SCLK, OUTPUT);
  pinMode(SDIO, OUTPUT);
  pinMode(NCS, OUTPUT);
  pinMode(SCLK1, OUTPUT);
  pinMode(SDIO1, OUTPUT);
  pinMode(NCS1, OUTPUT);
  myScreen.begin();
  int color5=myScreen.calculateColour(255,255,255);
  wordPrinter(120,30,"SPI Mouse",color5);
}
int f = 0;
bool prevbutton = false;
void loop() {
 for (int i=0;i<15;i++){
    for (int j=14;j>=0;j--){
      
      img[i][j]=readLoc(0x0b,NCS,SDIO,SCLK);
      img[i][j] &= 0x7F; // msb = valid bit
      img[i][j]=(img[i][j]<<1);
      
      img2[i][j]=readLoc(0x0b,NCS1,SDIO1,SCLK1);
      img2[i][j] &= 0x7F; // msb = valid bit
      img2[i][j]=(img2[i][j]<<1);
      
       myScreen.setPenSolid(true);
       myScreen.setFontSolid(false);
       int k=myScreen.calculateColour(img[i][j],img[i][j],img[i][j]);
       myScreen.dRectangle((10*i),(10*j)+90,10,10,k);  
       int p=myScreen.calculateColour(img2[i][j],img2[i][j],img2[i][j]);
       myScreen.dRectangle((10*i)+170,(10*j)+90,10,10,p); 
       
        if(Serial.available()>0){
        t=Serial.read();
        int mover=readLoc(0x09,NCS,SDIO,SCLK);
        int mover2=readLoc(0x09,NCS1,SDIO1,SCLK1);
        
        if(t=='a'){
         move(t);
        }
        
        
        else if(t=='b'){
        if((mover>60)&&(mover2>60)){
          f=0;
        }
        else if((mover<=60)&&(mover2>60)){
          f=1;
        }
        else if((mover2<=60)&&(mover>60)){
          f=2;
        }
        else if((mover2<=60)&&(mover<=60)){
          f=3;
        }
        movement(f);
        }


        else if(t=='c'){
          
        }
        }
      }

  
}
void wordPrinter(int a,int b ,String c,int d){
  myScreen.setPenSolid(true);
  myScreen.setFontSolid(false);
  myScreen.setFontSize(20);
  myScreen.gText(a,b,c,d);
}
void move(char t){
if(t=='l'){
analogWrite(ENR,speedt);
analogWrite(ENL,speedt);
digitalWrite(RB,LOW);
digitalWrite(RF,HIGH);
digitalWrite(LB,HIGH);
digitalWrite(LF,LOW);
}
else if(t=='r'){
analogWrite(ENR,speedt);
analogWrite(ENL,speedt);
digitalWrite(RB,HIGH);
digitalWrite(RF,LOW);
digitalWrite(LB,LOW);
digitalWrite(LF,HIGH);
}
else if(t=='f'){
analogWrite(ENR,speedr);
analogWrite(ENL,speedl);
digitalWrite(RB,LOW);
digitalWrite(RF,HIGH);
digitalWrite(LB,LOW);
digitalWrite(LF,HIGH);
}
else if(t=='s'){
digitalWrite(RB,LOW);
digitalWrite(RF,LOW);
digitalWrite(LB,LOW);
digitalWrite(LF,LOW);
}
}
void movement(int t) {
if(t==1){
analogWrite(ENR,speedt);
analogWrite(ENL,speedt);
digitalWrite(RB,LOW);
digitalWrite(RF,HIGH);
digitalWrite(LB,HIGH);
digitalWrite(LF,LOW);
}
else if(t==2){
analogWrite(ENR,speedt);
analogWrite(ENL,speedt);
digitalWrite(RB,HIGH);
digitalWrite(RF,LOW);
digitalWrite(LB,LOW);
digitalWrite(LF,HIGH);
}
else if(t==0){
analogWrite(ENR,speedr);
analogWrite(ENL,speedl);
digitalWrite(RB,LOW);
digitalWrite(RF,HIGH);
digitalWrite(LB,LOW);
digitalWrite(LF,HIGH);
}
else if(t==3){
digitalWrite(RB,LOW);
digitalWrite(RF,LOW);
digitalWrite(LB,LOW);
digitalWrite(LF,LOW);
}
}

//MOUSE RESET--------------------------------------------------------------------------------
//void mouse_reset(){
//  // Initiate chip reset
//  digitalWrite(NCS, LOW);
//  pushbyte(0xba); // write address: MSB = 1 for write, address = 7-bit 0x3a
//  pushbyte(0x5a); // write data, 8-bits
//  digitalWrite(NCS, HIGH);
//  delay(10);
//  // Set 1000cpi resolution
//  digitalWrite(NCS, LOW);
//  pushbyte(0x0d);
//  pushbyte(0x01);
//  digitalWrite(NCS, HIGH);
//}
//-------------------------------------------------------------------------------------------



//HYPOTHESIS FUNCTION------------------------------------------------------------------------


//PUSH BYTE----------------------------------------------------------------------------------
void pushbyte(uint8_t c,int SDIO,int SCLK){
  pinMode(SDIO, OUTPUT);
  for(unsigned int i=0x80;i;i=i>>1){
    digitalWrite(SCLK, LOW);
    digitalWrite(SDIO, c & i);
    digitalWrite(SCLK, HIGH);
  }
}
//-------------------------------------------------------------------------------------------



//PULL BYTE----------------------------------------------------------------------------------
unsigned int pullbyte(int SDIO, int SCLK){
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
unsigned int readLoc(uint8_t addr,int NCS,int SDIO, int SCLK){
  unsigned int ret=0;
  digitalWrite(NCS, LOW);
  pushbyte(addr,SDIO,SCLK);
  ret=pullbyte(SDIO,SCLK);
  digitalWrite(NCS, HIGH);
  return(ret);
}
//-------------------------------------------------------------------------------------------
   
