//                      +-\/-+
//               VCC   1|    |20  GND
//         (A0)  P1.0  2|    |19  XIN
//         (A1)  P1.1  3|    |18  XOUT
//         (A2)  P1.2  4|    |17  TEST
//         (A3)  P1.3  5|    |16  RST#
//         (A4)  P1.4  6|    |15  P1.7  (A7) (SCL) (MISO) depends on chip
//         (A5)  P1.5  7|    |14  P1.6  (A6) (SDA) (MOSI)
//               P2.0  8|    |13  P2.5
//               P2.1  9|    |12  P2.4
//               P2.2 10|    |11  P2.3
//                      +----+
//
int ENA=2;
int ENB=3;
int IN1=8;
int IN2=9;
int IN3=10;
int IN4=11;
int Button=5;
bool prevbutton=false;
const int period=1000;
int dutycycle;
int duty[4]={250,500,750,0};
int ele=0;

void setup() {   
  pinMode(ENA, OUTPUT);   
  pinMode(ENB, OUTPUT); 
  pinMode(IN1, OUTPUT); 
  pinMode(IN2, OUTPUT); 
  pinMode(IN3, OUTPUT); 
  pinMode(IN4, OUTPUT);
  pinMode(Button, INPUT_PULLUP);
}



//Functions
void pwm(int dutycycle,int period, int ENA, int ENB){
    for(int i = 0; i < dutycycle; i++) {
      digitalWrite(ENA,HIGH);
      digitalWrite(ENB, HIGH);   
      }
    for(int i = 0; i < period-dutycycle; i++) {
      digitalWrite(ENA,LOW);
      digitalWrite(ENB, LOW);
      }   
}
  


// the loop routine runs over and over again forever:
void loop() {
  if((digitalRead(Button)==HIGH)&&!prevbutton){
    //change duty cycle
    ele++;
    if(ele==4){
      ele=0;}
    dutycycle = duty[ele];
    prevbutton = true;
  }
  else if ((digitalRead(Button)==HIGH)){
   prevbutton=prevbutton; 
  }
  else{
    // don't change duty cycle
    prevbutton = false;
  }
digitalWrite(IN1, HIGH);  
digitalWrite(IN2, LOW);  
digitalWrite(IN3, LOW);  
digitalWrite(IN4, HIGH);
pwm(dutycycle, period,ENA, ENB);
  
}
