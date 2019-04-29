/************Diplomado IA con enfoque en robots de servicio****************/
/**************************************************************************/
/************Hernandez Gomez Mauricio Alejandro****************************/
/************Meneses Cornejo Kevin Osmar***********************************/

const int der = 7; //Pin hacia el control del motor derecho
const int der1 = 8; //Pin hacia el control del motor derecho
const int izq = 12; //Pin hacia el control del motor izquierdo
const int izq1 = 9; //Pin hacia el control del motor derecho

const int foto1 = A3;
const int foto2 = A2;
const int foto3 = A4;
const int foto4 = A5;

const int velDer = 10; //Pin hacia el habilitador del motor derecho
const int velIzq = 11; //Pin hacia el habilitaror del motor izquierdo

String txtMsg = "";

int direccion_izq; //Parametros iniciales de los motores
int velocidad_izq = 0;

int direccion_der;
int velocidad_der = 0;

const int proxIzq = A0;
const int proxDer = A1;

int luz[4];
int vm;
int comp1,comp2;


/************************************************************************/
/***************************Bloque de funciones**************************/

void atras(){
  for (int i=0;i<900;i++){
  direccion_izq = true;
  velocidad_izq = 65;
  direccion_der = true;
  velocidad_der = 65;
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
  velocidad_izq = 65;
  direccion_der = false;
  velocidad_der = 65;
}

void giro_izq(){
  for (int i=0;i<250;i++){
    direccion_izq = true;
    velocidad_izq = 65;
    direccion_der = false;
    velocidad_der = 65;
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
    velocidad_izq = 65;
    direccion_der = true;
    velocidad_der = 65;
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
  digitalWrite(izq,direccion_izq);
  digitalWrite(izq1,!direccion_izq);
  analogWrite(velIzq,velocidad_izq);
    
  digitalWrite(der,direccion_der);
  digitalWrite(der1,!direccion_der);
  analogWrite(velDer,velocidad_der);
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
  // put your setup code here, to run once:
  pinMode (der, OUTPUT);
  pinMode (izq, OUTPUT);
  pinMode (der1, OUTPUT);
  pinMode (izq1, OUTPUT);

  pinMode(foto1, INPUT);
  pinMode(foto2, INPUT);
  pinMode(foto3, INPUT);
  pinMode(foto4, INPUT);
  
  pinMode (velDer, OUTPUT);
  pinMode (velIzq, OUTPUT);
  
  pinMode(proxIzq, INPUT);
  pinMode(proxDer, INPUT);

  Serial.begin(9600);

  
}
void lecturaPhoto(){
  for (int i=0; i<10; i++){
     int valor = analogRead(foto1);
     luz[0] += valor;
     delay(1);
    }
    luz[0] /= 10;
  for (int i=0; i<10; i++){
     int valor1 = analogRead(foto2);
     luz[1] += valor1;
     delay(1);
    }
    luz[1] /= 10;
  for (int i=0; i<10; i++){
     int valor2 = analogRead(foto3);
     luz[2] += valor2;
     delay(1);
    }
    luz[2] /= 10;
  for (int i=0; i<10; i++){
     int valor3 = analogRead(foto4);
     luz[3] += valor3;
     delay(1);
    }
    luz[3] /= 10;

    comp1 = min(luz[0],luz[1]); 
    comp2 = min(luz[2],luz[3]);
    vm = min(comp1,comp2); // Fotocelda con menor incidencia de luz;

    if(vm==luz[0]){
     delay(2);
    }
    if(vm==luz[1]){
     giro_der();
     giro_der();
    }
    if(vm==luz[2]){
      giro_izq();
      giro_izq();
      giro_izq();
      giro_izq();
    }
    if(vm==luz[3]){
      giro_izq();
      giro_izq();
    }
    alto();
 
}

void loop(){


int estado = 0;
float Si,Sd;  
// Estado inicial
estado = 0;
// Loop infinito
adelante();
while(1){
  // Se leen los sensores
  float suma1 = muestreo(30,proxIzq);
  Si = 2014.69323221936*pow(suma1,-0.941312417730894)-1.7;
  
  float suma2 = muestreo(30,proxDer);
  Sd = 2014.69323221936*pow(suma2,-0.941312417730894)-1.7;
  
  Serial.print("Estado Presente: ");
  Serial.println(estado);
  Serial.print("Si: ");
  Serial.println(Si);
  Serial.print("Sd: ");
  Serial.println(Sd);
  switch (estado){
    case 0:
    if (Si >=9.0){
      if (Sd >=9.0){
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
      if (Sd >=9.0){
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
      giro_izq();
      Serial.println("GIRO_IZQ");
      break;
    case 3: // est3
      estado = 4;
      atras();
      Serial.println("ATRAS");
      break;
    case 4: // est4
      estado = 0;
      giro_der();
      Serial.println("GIRO_DER");
      break;
    case 5: // est5
      estado = 6;
      atras();
      Serial.println("ATRAS");
      break;
    case 6: // est6
      estado = 7;
      giro_izq();
      Serial.println("GIRO_IZQ");
      break;
    case 7: // est7
      estado = 8;
      giro_izq();
      Serial.println("GIRO_IZQ");
      break;
    case 8: // est8
      estado = 9;
      adelante();
      Serial.println("ADELANTE");
      break;
    case 9: // est9
      estado = 10;
      for (int i=0; i<500; i++){
        adelante();
        delay(1);
        digitalWrite(izq,direccion_izq);
        digitalWrite(izq1,!direccion_izq);
        analogWrite(velIzq,velocidad_izq);
    
        digitalWrite(der,direccion_der);
        digitalWrite(der1,!direccion_der);
        analogWrite(velDer,velocidad_der);
      }
      Serial.println("ADELANTE");
      break;
    case 10: // est10
      estado = 11;
      giro_der();
      Serial.println("GIRO_DER");
      break;
    case 11: // est11
      estado = 0;
      giro_der();
      Serial.println("GIRO_DER");
      break;
    } // end case
    digitalWrite(izq,direccion_izq);
    digitalWrite(izq1,!direccion_izq);
    analogWrite(velIzq,velocidad_izq);
    
    digitalWrite(der,direccion_der);
    digitalWrite(der1,!direccion_der);
    analogWrite(velDer,velocidad_der);
  } // end while*/
} // end Main (loop)
