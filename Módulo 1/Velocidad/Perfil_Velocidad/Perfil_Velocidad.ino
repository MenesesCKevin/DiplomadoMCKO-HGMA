/************Diplomado IA con enfoque en robots de servicio****************/
/**************************************************************************/
/************Hernandez Gomez Mauricio Alejandro****************************/
/************Meneses Cornejo Kevin Osmar***********************************/
//Perfil de velocida lineal

const float Vmax = 1.5;

const int der = 7; //Pin hacia el control del motor derecho
const int der1 = 8; //Pin hacia el control del motor derecho
const int izq = 12; //Pin hacia el control del motor izquierdo
const int izq1 = 9; //Pin hacia el control del motor derecho

const float velDer = 10; //Pin hacia el habilitador del motor derecho
const float velIzq = 11; //Pin hacia el habilitaror del motor izquierdo


int direccion_izq; //Parametros iniciales de los motores
int velocidad_izq = 0;

int direccion_der;
int velocidad_der = 0;


/************************************************************************/
/***************************Bloque de funciones**************************/

void escritura_motores(){
    digitalWrite(izq,direccion_izq);
    digitalWrite(izq1,!direccion_izq);
    analogWrite(velIzq,velocidad_izq);
    
    digitalWrite(der,direccion_der);
    digitalWrite(der1,!direccion_der);
    analogWrite(velDer,velocidad_der);
}

float Velocidad_lineal(float Vmax,float tf, float t){
  if (t < (tf/3.0)){
    return (t*Vmax/(tf/3.0));
  }
  else if ((t >= (tf/3.0)) && (t < (2*tf/3.0))){
    return (Vmax);
  }
  else if ((t >= (2.0*tf/3.0)) && (t<tf)){
    return (Vmax - (Vmax*(t-2.0*tf/3.0))/(tf-(2.0*tf/3.0)));
  }
  else{
    return 0;
  }
}

void control_lineal(float di,bool direccion){
  float tf = (3.0/2.0)*(di/Vmax);
  for (float t=0; t<tf; t+=0.001)
  {
      direccion_izq = direccion;
      velocidad_izq = (Velocidad_lineal(Vmax,tf,t))*60.0/1.5;
      direccion_der = direccion;
      velocidad_der = (Velocidad_lineal(Vmax,tf,t))*60.0/1.5;
      escritura_motores(); 
      delay(1);
  }
 }


/************************************************************************/

void setup() {
  pinMode (der, OUTPUT);
  pinMode (izq, OUTPUT);
  pinMode (der1, OUTPUT);
  pinMode (izq1, OUTPUT);
  
  pinMode (velDer, OUTPUT);
  pinMode (velIzq, OUTPUT);

  Serial.begin(9600);
  control_lineal(1.0,false);
  /*for(int i=0;i<100;i++){
      direccion_izq = false;
      velocidad_izq = 60;
      direccion_der = false;
      velocidad_der = 56;
      escritura_motores(); 
      delay(1);
    }
   
  velocidad_izq = 0;
      direccion_der = false;
      velocidad_der = 0;
      escritura_motores();*/
}

void loop(){

  
} // end Main (loop)
