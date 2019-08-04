int ENR=68;
int ENL=69;
int LB=59;
int RF=44;
int RB=66;
int LF=63;
char t;


void setupSPI(){
  Serial.begin(9600);
  pinMode(ENR,OUTPUT);
  pinMode(ENL,OUTPUT);
  pinMode(RF,OUTPUT);
  pinMode(RB,OUTPUT);
  pinMode(LF,OUTPUT);
  pinMode(LB,OUTPUT);
  
}


void loopSPI(){
 analogWrite(ENR,100);
 analogWrite(ENL,100);
 digitalWrite(RF,LOW);
 digitalWrite(RB,HIGH);
 digitalWrite(LF,LOW);
 digitalWrite(LB,HIGH);
}


//void move(char t){
//if(t=='l'){
//analogWrite(ENR,250);
//analogWrite(ENL,250);
//digitalWrite(63,LOW);
//digitalWrite(72,HIGH);
//digitalWrite(59,HIGH);
//digitalWrite(66,LOW);
//}
//else if(t=='r'){
//analogWrite(ENR,250);
//analogWrite(ENL,250);
//digitalWrite(63,HIGH);
//digitalWrite(72,LOW);
//digitalWrite(59,LOW);
//digitalWrite(66,HIGH);
//}
//else if(t=='f'){
//analogWrite(ENR,250);
//analogWrite(ENL,250);
//digitalWrite(63,LOW);
//digitalWrite(72,LOW);
//digitalWrite(59,HIGH);
//digitalWrite(66,HIGH);
//}
//else if(t=='s'){
//digitalWrite(63,LOW);
//digitalWrite(72,LOW);
//digitalWrite(59,LOW);
//digitalWrite(66,LOW);
//}
//}
