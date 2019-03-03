const int der = 12;
const int izq = 13;
const int velDer = 10;
const int velIzq = 11;
String txtMsg = "";

int direccion_izq = false;
int velocidad_izq = 0;

int direccion_der = false;
int velocidad_der = 0;

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
  pinMode (der, OUTPUT);
  pinMode (izq, OUTPUT);
  pinMode (velDer, OUTPUT);
  pinMode (velIzq, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
   while (Serial.available()) {
    char inChar = Serial.read();
    if(inChar != '\n'){
      txtMsg.concat(inChar);
    }
    else{
      //Serial.println(txtMsg);
      txtMsg = "";
      }
    }
   if (txtMsg == "A1 on left"){
      izquierdo_left();
    }
   if (txtMsg == "A1 on right"){
      izquierdo_right();
    }
   if (txtMsg == "A1 off"){
      izquierdo_off();
    }
   if (txtMsg == "A2 on left"){
      derecho_left();
    }
   if (txtMsg == "A2 on right"){
      derecho_right();
    }
   if (txtMsg == "A2 off"){
      derecho_off();
    }

    digitalWrite(izq,direccion_izq);
    analogWrite(velIzq,velocidad_izq);
    digitalWrite(der,direccion_der);
    analogWrite(velDer,velocidad_der);
}
