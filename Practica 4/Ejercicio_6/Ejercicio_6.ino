/************Diplomado IA con enfoque en robots de servicio****************/
/**************************************************************************/
/************Hernandez Gomez Mauricio Alejandro****************************/
/************Meneses Cornejo Kevin Osmar***********************************/

const int der = 13; //Pin hacia el control del motor derecho
const int izq = 12; //Pin hacia el control del motor izquierdo

const int velDer = 10; //Pin hacia el habilitador del motor derecho
const int velIzq = 11; //Pin hacia el habilitaror del motor izquierdo


int direccion_izq = false; //Parametros iniciales de los motores
int velocidad_izq = 0;

int direccion_der = false;
int velocidad_der = 0;


const int proxIzq = A0;
const int proxDer = A1;

int obsIzq = 0;
int obsDer = 0;

/************************************************************************/
/***************************Bloque de funciones**************************/


//Cada una de las siguientes funciones corresponden a los movimientos del robot
//Cada una recibe de argumento el tiempo en milisegundos que ejecutara dicha funcion

void adelante(){
  direccion_izq = true;
  velocidad_izq = 60;
  direccion_der = true;
  velocidad_der = 60;

  digitalWrite(izq,direccion_izq);
  analogWrite(velIzq,velocidad_izq);
    
  digitalWrite(der,direccion_der);
  analogWrite(velDer,velocidad_der);
  
  delay(3000);
}

void atras(){
  direccion_izq = true;
  velocidad_izq = 60;
  direccion_der = true;
  velocidad_der = 60;

  digitalWrite(izq,direccion_izq);
  analogWrite(velIzq,velocidad_izq);
    
  digitalWrite(der,direccion_der);
  analogWrite(velDer,velocidad_der);

  delay(3000);
}


void apagado(){
  velocidad_izq = 0;
  velocidad_der = 0;

  digitalWrite(izq,direccion_izq);
  analogWrite(velIzq,velocidad_izq);
    
  digitalWrite(der,direccion_der);
  analogWrite(velDer,velocidad_der);
}

void giro_der(){
  direccion_der = false;
  direccion_izq = true;
  velocidad_izq = 50;
  velocidad_der = 50;
  
  digitalWrite(izq,direccion_izq);
  analogWrite(velIzq,velocidad_izq);
    
  digitalWrite(der,direccion_der);
  analogWrite(velDer,velocidad_der);
  
  delay(2000);

}

void giro_izq(){
  direccion_der = false;
  direccion_izq = true;
  velocidad_izq = 50;
  velocidad_der = 50;

  digitalWrite(izq,direccion_izq);
  analogWrite(velIzq,velocidad_izq);
    
  digitalWrite(der,direccion_der);
  analogWrite(velDer,velocidad_der);
  
  delay(2000);

}

//  Las siguientes funciones corresponden a los sensores de proximidad

float muestreo(int muestras,int sensor){
  float suma = 0;
  for (int i = 0; i<muestras; i++){
    suma += analogRead(sensor);
    delay(5);
    }
    suma /= muestras;
    return(suma);
  }

int sensor_lectura(int sensor){
  float lectura = muestreo(30,sensor);
  float distancia = 2014.69323221936*pow(lectura,-0.941312417730894)-1.7;
  if (distancia <= 5.0){
    return 1;
  }
  else{
    return 0;
  }
}

/************************************************************************/


void setup() {

  pinMode (der, OUTPUT);
  pinMode (izq, OUTPUT);
  
  pinMode (velDer, OUTPUT);
  pinMode (velIzq, OUTPUT);

  pinMode(proxIzq, INPUT);
  pinMode(proxDer, INPUT);
  
  Serial.begin(9600);
}

void loop(){

    if (sensor_lectura(proxIzq) == 1){
      if (sensor_lectura(proxDer) == 0){
        atras();
        giro_der();
      }
      else{
        atras();
        giro_izq();
        giro_izq();
        adelante();
        adelante();
        giro_der();
        giro_der();
      }
    }
    else{
      if (sensor_lectura(proxDer) == 0){
        adelante();
      }
      else{
        atras();
        giro_izq();
      }
    }
}
