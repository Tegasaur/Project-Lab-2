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
//58->Right Enable
//57->Left Enable
//72->Back Right
//66->Front Right
//59->Front Left
//63->Back Left
//74-button
int ENR=58;
int ENL=57;
int RF=66;
int LB=63;
int RB=72;
int LF=59;
int button=74;
Movementi mycar(ENR,ENL,RF,LF,RB,LB);
void setupNewMovement() {
Serial.begin(9600);
pinMode(button,INPUT_PULLUP);
}
int i = 0;
bool prevbutton = false;
void loopNewMovement() {
  if(!(digitalRead(button)==HIGH)&&!prevbutton){
    //change duty cycle
    i++;
    if(i==3){
      i=0;}
//    dutycycle = duty[ele];
    prevbutton = true;
  }
  else if (!(digitalRead(button)==HIGH)){
   prevbutton=prevbutton; 
  }
  else{
    // don't change duty cycle
    prevbutton = false;
  }
    movement(i);

}

void movement(int i) {
  if(i == 0){
    mycar.forward(50);}
  else if(i == 1){
    mycar.left(75,25);}
  else if(i == 2){
    mycar.right(75,25);}
  else{
    mycar.forward(0);}
}
