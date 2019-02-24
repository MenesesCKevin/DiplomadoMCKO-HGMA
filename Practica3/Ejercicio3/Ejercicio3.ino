const int der1 = 5;
const int der2 = 6;
const int izq1 = 2;
const int izq2 = 3;
const int velDer = 10;
const int velIzq = 11;
String txtMsg = "";
int lectura;
int global;

int direccion_izq = false;
int velocidad_izq = 60;

int direccion_der = false;
int velocidad_der = 60;

void izquierdo_left(){
  direccion_izq = true;
  velocidad_izq = 60;
}

void izquierdo_right(){
  direccion_izq = false;
  velocidad_izq = 60;
}

void izquierdo_off(){
  velocidad_izq = 0;
}


void derecho_left(){
  direccion_der = true;
  velocidad_der = 60;
}

void derecho_right(){
  direccion_der = false;
  velocidad_der = 60;
}

void derecho_off(){
  velocidad_der = 0;
}
void setup() {
  // put your setup code here, to run once:
  pinMode (der1, OUTPUT);
  pinMode (der2, OUTPUT);
  pinMode (izq1, OUTPUT);
  pinMode (izq2, OUTPUT);
  pinMode (velDer, OUTPUT);
  pinMode (velIzq, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
   if (Serial.available()) {
    lectura = Serial.parseInt();
    if(lectura==0){
      lectura = global;
    }
    }
   if (lectura == 127){
      izquierdo_off();
      derecho_off();
   }
   if (lectura < 127){
      izquierdo_left();
      derecho_left();
    }
   if (lectura > 127){
      derecho_right();
      izquierdo_right();
    }
   
   Serial.println(lectura);

    digitalWrite(izq1,direccion_izq);
    digitalWrite(izq2,!direccion_izq);
    analogWrite(velIzq,lectura);

    digitalWrite(der1,!direccion_der);
    digitalWrite(der2,direccion_der);
    analogWrite(velDer,lectura);
    global=lectura;
}
