#define RH_ENCODER_A 2
#define RH_ENCODER_B 4

#define LF_ENCODER_A 3
#define LF_ENCODER_B 5

#define D00 7
#define D01 8
#define E1 10
#define PWM1 200

#define I00 12
#define I01 9
#define E2 11
#define PWM2 200

int direccion_izq; //Parametros iniciales de los motores
int velocidad_izq = 0;
int direccion_der;
int velocidad_der = 0;

volatile long rightCount = 0;
volatile long leftCount = 0;

void rightEncoderEvent(){
  if(digitalRead(RH_ENCODER_A == HIGH)){
    if(digitalRead(RH_ENCODER_B) == LOW){
      rightCount++;
    }else{
      rightCount--;
    }
  }
  else{
    if(digitalRead(RH_ENCODER_B == LOW)){
      rightCount--;
    }else{
      rightCount++;
    }
  }
}
void leftEncoderEvent(){
  if(digitalRead(LF_ENCODER_A == HIGH)){
    if(digitalRead(LF_ENCODER_B) == LOW){
      leftCount++;
    }else{
      leftCount--;
    }
  }
  else{
    if(digitalRead(LF_ENCODER_B == LOW)){
      leftCount--;
    }else{
      leftCount++;
    }
  }
}
void escritura_motores(){
    digitalWrite(I00,direccion_izq);
    digitalWrite(I01,!direccion_izq);
    analogWrite(E2,velocidad_izq);
    
    digitalWrite(D00,direccion_der);
    digitalWrite(D01,!direccion_der);
    analogWrite(E1,velocidad_der);
}

void setup() {
  pinMode(D00, OUTPUT);
  pinMode(D01, OUTPUT);
  pinMode(E1, OUTPUT);
  pinMode(RH_ENCODER_A, INPUT);
  pinMode(RH_ENCODER_B, INPUT);

  
  pinMode(I00, OUTPUT);
  pinMode(I01, OUTPUT);
  pinMode(E2, OUTPUT);
  pinMode(LF_ENCODER_A, INPUT);
  pinMode(LF_ENCODER_B, INPUT);

  attachInterrupt(0, rightEncoderEvent, CHANGE);
  attachInterrupt(1, leftEncoderEvent, CHANGE);
  Serial.begin(9600);

}


void loop() {
  /*for(int i=0;i<1000;i++){
      direccion_izq = true;
      velocidad_izq = 60;
      direccion_der = true;
      velocidad_der = 56;
      escritura_motores(); 
      delay(1);
      Serial.println(leftCount);
    }
   while(1){
    Serial.println(rightCount);
    velocidad_izq = 0;
      direccion_der = false;
      velocidad_der = 0;
      escritura_motores();
   }*/
   Serial.println(rightCount);

}
