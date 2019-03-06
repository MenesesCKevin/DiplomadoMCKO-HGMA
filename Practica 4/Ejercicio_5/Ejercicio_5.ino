/************Diplomado IA con enfoque en robots de servicio****************/
/**************************************************************************/
/************Hernandez Gomez Mauricio Alejandro****************************/
/************Meneses Cornejo Kevin Osmar***********************************/

const int der = 13; //Pin hacia el control del motor derecho
const int izq = 12; //Pin hacia el control del motor izquierdo

const int velDer = 10; //Pin hacia el habilitador del motor derecho
const int velIzq = 11; //Pin hacia el habilitaror del motor izquierdo

String txtMsg = "";

int direccion_izq = false; //Parametros iniciales de los motores
int velocidad_izq = 0;

int direccion_der = false;
int velocidad_der = 0;


/************************************************************************/
/***************************Bloque de funciones**************************/


//Cada una de las siguientes funciones corresponden a los movimientos del robot
//Cada una recibe de argumento el tiempo en milisegundos que ejecutara dicha funcion

void adelante(){
  direccion_izq = true;
  velocidad_izq = 60;
  direccion_der = true;
  velocidad_der = 60;
}

void atras(){
  direccion_izq = true;
  velocidad_izq = 60;
  direccion_der = true;
  velocidad_der = 60;
}


void apagado(){
  velocidad_izq = 0;
  velocidad_der = 0;
}

void giro_der(){
  direccion_der = false;
  direccion_izq = true;
  velocidad_izq = 50;
  velocidad_der = 50;

}

void giro_izq(){
  direccion_der = false;
  direccion_izq = true;
  velocidad_izq = 50;
  velocidad_der = 50;

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

  velocidad_izq = 0;
  velocidad_der = 0;
  
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
      adelante();
    }
   if (txtMsg == "atras"){
      atras();
    }
   if (txtMsg == "apagado"){
      apagado();
    }
   if (txtMsg == "izquierda"){
      giro_izq();
    }
   if (txtMsg == "derecha"){
      giro_der();
    }

    digitalWrite(izq,direccion_izq);
    analogWrite(velIzq,velocidad_izq);
    
    digitalWrite(der,direccion_der);
    analogWrite(velDer,velocidad_der);

    delay(2000);  //tiempo que ejecuta las instrucciones
}
