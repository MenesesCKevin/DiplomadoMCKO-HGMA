/*************************La guayaba************************/
/***********************************************************/
/***********************************************************/
/***********************************************************/
/***********************************************************/
/***********************************************************/

int encoder_izqA = 3;
int encoder_izqB = 5;
int encoder_derA = 2;
int encoder_derB = 4;

volatile unsigned long leftCount = 0;
volatile unsigned long rightCount = 0;



const int der = 13; //Pin hacia el control del motor derecho
const int der1 = 8; //Pin hacia el control del motor derecho
const int izq = 12; //Pin hacia el control del motor izquierdo
const int izq1 = 9; //Pin hacia el control del motor derecho

const int velDer = 10; //Pin hacia el habilitador del motor derecho
const int velIzq = 11; //Pin hacia el habilitaror del motor izquierdo

int direccion_izq; //Parametros iniciales de los motores
int velocidad_izq = 0;

int direccion_der;
int velocidad_der = 0;

const int proxIzq = A0;
const int proxDer = A1;



/************************************************************************/
/***************************Bloque de funciones**************************/

void atras(){
  for (int i=0;i<900;i++){
  direccion_izq = true;
  velocidad_izq = 45;
  direccion_der = true;
  velocidad_der = 45;
  delay(1);
  digitalWrite(izq,direccion_izq);
  digitalWrite(izq1,!direccion_izq);
  analogWrite(velIzq,velocidad_izq);
    
  digitalWrite(der,direccion_der);
  digitalWrite(der1,!direccion_der);
  analogWrite(velDer,velocidad_der);
  }
}

void adelante(){
  direccion_izq = false;
  velocidad_izq = 45;
  direccion_der = false;
  velocidad_der = 45;
}

void giro_izq(){
  for (int i=0;i<250;i++){
    direccion_izq = true;
    velocidad_izq = 45;
    direccion_der = false;
    velocidad_der = 45;
    delay(1);
    digitalWrite(izq,direccion_izq);
    digitalWrite(izq1,!direccion_izq);
    analogWrite(velIzq,velocidad_izq);
    
    digitalWrite(der,direccion_der);
    digitalWrite(der1,!direccion_der);
    analogWrite(velDer,velocidad_der);
  }
}

void giro_der(){
  for (int i=0;i<250;i++){
    direccion_izq = false;
    velocidad_izq = 45;
    direccion_der = true;
    velocidad_der = 45;
    delay(1);
    digitalWrite(izq,direccion_izq);
    digitalWrite(izq1,!direccion_izq);
    analogWrite(velIzq,velocidad_izq);
    
    digitalWrite(der,direccion_der);
    digitalWrite(der1,!direccion_der);
    analogWrite(velDer,velocidad_der);
  }
}

void alto(){
  velocidad_der = 0;
  velocidad_izq = 0;
}

float muestreo(int muestras, int sensor){
  float suma = 0;
  for (int i = 0; i<muestras; i++){
    suma += analogRead(sensor);
    }
    suma /= muestras;
    return(suma);
  }

/************************************************************************/


void setup() {
  pinMode(encoder_izqA, INPUT);
  pinMode(encoder_izqB, INPUT);
  pinMode(encoder_derA, INPUT);
  pinMode(encoder_derB, INPUT);

  Serial.begin(9600);

  attachInterrupt(1, leftEncoderEvent, RISING);
  attachInterrupt(0, rightEncoderEvent, RISING);

}

void loop() {


   velocidad_izq = 45;
   direccion_izq =false;
   
   velocidad_der = 45;
   direccion_der = false;
   delay(1);

    Serial.print("Right Count: ");
    Serial.print(rightCount);
    Serial.print("\tLeft Count: ");
    Serial.println(leftCount);
    Serial.println();
    
   rightCount=0;
   leftCount=0;

 digitalWrite(izq,direccion_izq);
 digitalWrite(izq1,!direccion_izq);
 analogWrite(velIzq,velocidad_izq);
    
 digitalWrite(der,direccion_der);
 digitalWrite(der1,!direccion_der);
 analogWrite(velDer,velocidad_der);
}


// encoder event for the interrupt call
void leftEncoderEvent() {
   leftCount++;
}
 
// encoder event for the interrupt call
void rightEncoderEvent() {
  rightCount ++;
}
