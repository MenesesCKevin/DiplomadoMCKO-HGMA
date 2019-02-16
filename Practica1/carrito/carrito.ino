
const int der1 = 8;
const int der2 = 7;
const int izq1 = 13;
const int izq2 = 12;
const int velDer = 3;
const int velIzq = 5;

void adelante(){
  digitalWrite(izq1, LOW);
  digitalWrite(izq2, HIGH);
  digitalWrite(der1, HIGH);
  digitalWrite(der2, LOW);
  for(int i=0; i<475; i++){
    analogWrite(velIzq,75);
    analogWrite(velDer,72);
    delay(1);
  }
}

void Izq(){
  digitalWrite(izq1, LOW);
  digitalWrite(izq2, HIGH);
  digitalWrite(der1, HIGH);
  digitalWrite(der2, LOW);

  for(int i=0; i<650; i++){
    analogWrite(velIzq,20);
    analogWrite(velDer,36);
    delay(1);
  }
}
void Detener(){
  digitalWrite(izq1, LOW);
  digitalWrite(izq2, LOW);
  digitalWrite(der1, LOW);
  digitalWrite(der2, LOW);
  analogWrite(velIzq,0);
  analogWrite(velDer,0);
  delay(2000);
}
void setup() {
  // put your setup code here, to run once:
  pinMode (der1, OUTPUT);
  pinMode (der2, OUTPUT);
  pinMode (izq1, OUTPUT);
  pinMode (izq2, OUTPUT);
  pinMode (velDer, OUTPUT);
  pinMode (velIzq, OUTPUT);

  adelante();
  adelante();
  adelante();
  Izq();
  Izq();
  adelante();
  adelante();
  adelante();
  Izq();
  Detener();
}

void loop() {
  // put your main code here, to run repeatedly:

}
