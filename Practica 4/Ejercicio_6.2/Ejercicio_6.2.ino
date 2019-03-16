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

const int sensorIzq = A0;
const int sensorDer = A1;

/************************************************************************/
/***************************Bloque de funciones**************************/

void adelante(){
  direccion_izq = false;
  velocidad_izq = 45;
  direccion_der = false;
  velocidad_der = 45;
}

void alto(){
  velocidad_izq = 0;
  velocidad_der = 0;
}

void atras(){
  for (int i=0; i<2000; i++){
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

void izquierda(){
  for (int i=0; i<2000; i++){
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

void derecha(){
  for (int i=0; i<2000; i++){
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


float muestreo(int muestras,int sensor){
  float suma = 0;
  for (int i = 0; i<muestras; i++){
    suma += analogRead(sensor);
    }
    suma /= muestras;
    return(suma);
  }

float sensor_lectura(int sensor){
  float lectura = muestreo(30,sensor);
  float distancia = 2014.69323221936*pow(lectura,-0.941312417730894)-1.7;
  return lectura;
}

/************************************************************************/


void setup() {
  // put your setup code here, to run once:
  pinMode (der, OUTPUT);
  pinMode (izq, OUTPUT);
  
  pinMode (velDer, OUTPUT);
  pinMode (velIzq, OUTPUT);

  pinMode (sensorIzq, INPUT);
  pinMode (sensorDer, INPUT);
  
  
  Serial.begin(9600);
}

void loop(){

  int estado = 0; //Estado inicial
  float Si,Sd;
   while(1){
     // Se leen los sensores
     Si = sensor_lectura(sensorIzq);
     Sd = sensor_lectura(sensorDer);
     Serial.print("Estado Presente: ");
     Serial.println(estado);
     Serial.print("Si: ");
     Serial.println(Si);
     Serial.print("Sd: ");
     Serial.println(Sd);
     switch (estado){
       case 0: // est0
      if (Si >= 6.0){
      if (Sd >= 6.0){
       estado = 0;
       adelante();
       Serial.println("ADELANTE");
      }
      else{
       estado = 1;
       alto();
       Serial.println("ALTO");
      }
      }
      else{
      if (Sd >= 6.0){
      estado = 3;
      alto();
       Serial.println("ALTO");
      }
      else{
      estado = 5;
      alto();
       Serial.println("ALTO");
      }
      }
       break;
       case 1: // est1
      estado = 2;
      atras();
      Serial.println("ATRAS");
      break;
       case 2: // est2
      estado = 0;
      izquierda();
      Serial.println("GIRO_IZQ");
      break;
       case 3: // est3
      estado = 4;
      atras();
      Serial.println("ATRAS");
      break;
       case 4: // est4
      estado = 0;
      derecha();
      Serial.println("GIRO_DER");
      break;
       case 5: // est5
      estado = 6;
      atras();
       Serial.println("ATRAS");
      break;
       case 6: // est6
      estado = 7;
      izquierda();
       Serial.println("GIRO_IZQ");
      break;
       case 7: // est7
      estado = 8;
      izquierda();
       Serial.println("GIRO_IZQ");
      break;
       case 8: // est8
      estado = 9;
      adelante();
      Serial.println("ADELANTE");
      break;
       case 9: // est9
      estado = 10;
      adelante();
      Serial.println("ADELANTE");
      break;
       case 10: // est10
      estado = 11;
      derecha();
      Serial.println("GIRO_DER");
      break;
       case 11: // est11
      estado = 0;
      derecha();
      Serial.println("GIRO_DER");
      break;
     } // end case
    digitalWrite(izq,direccion_izq);
    digitalWrite(izq1,!direccion_izq);
    analogWrite(velIzq,velocidad_izq);
    
    digitalWrite(der,direccion_der);
    digitalWrite(der1,!direccion_der);
    analogWrite(velDer,velocidad_der);
   } // end while
} // end loop
