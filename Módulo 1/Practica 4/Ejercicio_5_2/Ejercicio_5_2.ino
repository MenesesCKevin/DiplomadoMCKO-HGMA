/************Diplomado IA con enfoque en robots de servicio****************/
/**************************************************************************/
/************Hernandez Gomez Mauricio Alejandro****************************/
/************Meneses Cornejo Kevin Osmar***********************************/

const int der = 13; //Pin hacia el control del motor derecho
const int der1 = 8; //Pin hacia el control del motor derecho
const int izq = 12; //Pin hacia el control del motor izquierdo
const int izq1 = 9; //Pin hacia el control del motor derecho

const int velDer = 10; //Pin hacia el habilitador del motor derecho
const int velIzq = 11; //Pin hacia el habilitaror del motor izquierdo

String txtMsg = "";

int direccion_izq = false; //Parametros iniciales de los motores
int velocidad_izq = 0;

int direccion_der = false;
int velocidad_der = 0;


/************************************************************************/
/***************************Bloque de funciones**************************/

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

/************************************************************************/


void setup() {
  // put your setup code here, to run once:
  pinMode (der, OUTPUT);
  pinMode (izq, OUTPUT);
  pinMode (der1, OUTPUT);
  pinMode (izq1, OUTPUT);
  
  pinMode (velDer, OUTPUT);
  pinMode (velIzq, OUTPUT);
  
  Serial.begin(9600);
}

void loop(){
   while (Serial.available()) {
      char inChar = Serial.read();
      if(inChar != '\n'){
        txtMsg.concat(inChar);
      }
    else{
      txtMsg = "";
      }
    }
    
   if (txtMsg == "adelante"){
      izquierdo_right();
      derecho_right();
    }
   if (txtMsg == "atras"){
      izquierdo_left();
      derecho_left();
    }
   if (txtMsg == "giro izq"){
      izquierdo_right();
      derecho_left();
    }
   if (txtMsg == "giro der"){
      derecho_right();
      izquierdo_left();
    }
   if (txtMsg == "apagado"){
      derecho_off();
      izquierdo_off();
    }

    digitalWrite(izq,direccion_izq);
    digitalWrite(izq1,!direccion_izq);
    analogWrite(velIzq,velocidad_izq);
    
    digitalWrite(der,direccion_der);
    digitalWrite(der1,!direccion_der);
    analogWrite(velDer,velocidad_der);
}
