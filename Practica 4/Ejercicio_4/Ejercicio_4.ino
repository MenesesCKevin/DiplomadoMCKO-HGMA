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
  velocidad_izq = 90;
}

void izquierdo_right(){
  direccion_izq = false;
  velocidad_izq = 90;
}

void izquierdo_off(){
  velocidad_izq = 0;
}


void derecho_left(){
  direccion_der = true;
  velocidad_der = 90;
}

void derecho_right(){
  direccion_der = false;
  velocidad_der = 90;
}

void derecho_off(){
  velocidad_der = 0;
}

/************************************************************************/


void setup() {
  // put your setup code here, to run once:
  pinMode (der, OUTPUT);
  pinMode (izq, OUTPUT);
  
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
    
   if (txtMsg == "izq 1"){
      izquierdo_right();
    }
   if (txtMsg == "izq 0"){
      izquierdo_left();
    }
   if (txtMsg == "izq off"){
      izquierdo_off();
    }
   if (txtMsg == "der 1"){
      derecho_right();
    }
   if (txtMsg == "der 0"){
      derecho_left();
    }
   if (txtMsg == "der off"){
      derecho_off();
    }

    digitalWrite(izq,direccion_izq);
    digitalWrite(izq1,!direccion_izq);
    analogWrite(velIzq,velocidad_izq);
    
    digitalWrite(der,direccion_der);
    digitalWrite(der1,!direccion_der);
    analogWrite(velDer,velocidad_der);
}
