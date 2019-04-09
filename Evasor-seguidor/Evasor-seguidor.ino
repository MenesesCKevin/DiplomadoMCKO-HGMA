/************Diplomado IA con enfoque en robots de servicio****************/
/**************************************************************************/
/************Hernandez Gomez Mauricio Alejandro****************************/
/************Meneses Cornejo Kevin Osmar***********************************/

const int der = 7; //Pin hacia el control del motor derecho
const int der1 = 8; //Pin hacia el control del motor derecho
const int izq = 12; //Pin hacia el control del motor izquierdo
const int izq1 = 9; //Pin hacia el control del motor derecho

const int foto2 = A5; //Pines para las fotoresistencias
const int foto3 = A2; 
const int foto4 = A3; 
const int foto1 = A4; 

const int velDer = 10; //Pin hacia el habilitador del motor derecho
const int velIzq = 11; //Pin hacia el habilitaror del motor izquierdo


int direccion_izq; //Parametros iniciales de los motores
int velocidad_izq = 0;

int direccion_der;
int velocidad_der = 0;

const int proxIzq = A0; //Pines para los sensores de proximidad
const int proxDer = A1;

int luz[4];             //Vector para almacenar los valores de las fotoresistencias
int vm;                 //Variable para almacenar el valor de la fotoresistencia con menor valor
int comp1,comp2;        //Variables auxiliares para realizar las comparaciones entre las fotoresistencias

const int VMI = 60;     //Velocidad del Motor Izquierdo
const int VMD = 50;     //Velocidad del Motor Derecho

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

void atras(){
  for (int i=0;i<300;i++){
  direccion_izq = true;
  velocidad_izq = VMI;
  direccion_der = true;
  velocidad_der = VMD;
  delay(1);
  escritura_motores();
  }
}

void adelante(){
    direccion_izq = false;
    velocidad_izq = VMI;
    direccion_der = false;
    velocidad_der = VMD;
    escritura_motores();
}

void giro_izq(){
  for (int i=0;i<250;i++){
    direccion_izq = true;
    velocidad_izq = VMI;
    direccion_der = false;
    velocidad_der = VMD;
    delay(1);
    escritura_motores();
  }
}

void giro_der(){
  for (int i=0;i<250;i++){
    direccion_izq = false;
    velocidad_izq = VMI;
    direccion_der = true;
    velocidad_der = VMD;
    delay(1);
    escritura_motores();
  }
}

void alto(){
  for (int i=0;i<200;i++){
    velocidad_der = 0;
    velocidad_izq = 0;
    delay(1);
    escritura_motores();
  }
}

float muestreo(int muestras, int sensor){
  float suma = 0;
  for (int i = 0; i<muestras; i++){
    suma += analogRead(sensor);
    }
    suma /= muestras;
    return(suma);
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
}


/************************************************************************/

void setup() {
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

void loop(){
  int estado = 0;
  float Si,Sd;  
  estado = 0;
  while(1){

    float suma1 = muestreo(30,proxIzq);                         //Lectura de los sensores
    Si = 2014.69323221936*pow(suma1,-0.941312417730894)-1.7;
    
    float suma2 = muestreo(30,proxDer);
    Sd = 2014.69323221936*pow(suma2,-0.941312417730894)-1.7;
    Serial.print("Estado Presente: ");
    Serial.println(estado);
 
    switch (estado){    
      case 0:
      lecturaPhoto();
      Serial.print(luz[0]);
      Serial.print("\t");
      Serial.print(luz[1]);
      Serial.print("\t");
      Serial.print(luz[2]);
      Serial.print("\t");
      Serial.print(luz[3]);
      Serial.println();
      if(luz[0]<=120 || luz[1]<=120 || luz[2]<=120 || luz[3]<=120){
        estado=0;
        alto();
        Serial.println("ya llegue :v");
      }
      else{
        adelante();
        estado=1;
      }
      break;
      case 1:
      if (Si >=4.5){
        if (Sd >=4.5){
        estado = 13;
        adelante();
        Serial.println("ADELANTE");
        }
      else{
        estado = 2;
        alto();
        Serial.println("ALTO");
        }
      }
      else{
        if (Sd >=4.5){
          estado = 4;
          alto();
          Serial.println("ALTO");
          }
        else{
          estado = 6;
          alto();
          Serial.println("ALTO");
          }
      }
      break;
      case 2:
        estado = 3;
        atras();
        Serial.println("ATRAS");
        break;
      case 3:
        estado = 0;
        giro_izq();
        Serial.println("GIRO_IZQ");
        break;
      case 4:
        estado = 5;
        atras();
        Serial.println("ATRAS");
        break;
      case 5:
        estado = 0;
        giro_der();
        Serial.println("GIRO_DER");
        break;
      case 6:
        estado = 7;
        atras();
        Serial.println("ATRAS");
        break;
      case 7:
        estado = 8;
        giro_izq();
        Serial.println("GIRO_IZQ");
        break;
      case 8: 
        estado = 9;
        giro_izq();
        Serial.println("GIRO_IZQ");
        break;
      case 9:
        estado = 10;
        adelante();
        Serial.println("ADELANTE");
        break;
      case 10:
        estado = 11;
        for(int i=0;i<250;i++){
        adelante();
        delay(1);
        Serial.println("ADELANTE");
        }
        break;
      case 11:
        estado = 12;
        giro_der();
        Serial.println("GIRO_DER");
        break;
      case 12:
        estado = 0;
        giro_der();
        Serial.println("GIRO_DER");
        break;
      case 13:
        lecturaPhoto();
        comp1 = min(luz[0],luz[1]); 
        comp2 = min(luz[2],luz[3]);
        vm = min(comp1,comp2); // Fotocelda con menor incidencia de luz;
        if(vm==luz[0]){
          estado=0;
          giro_der();
          Serial.println("GIRO_DER");
        }
        if(vm==luz[1]){
          estado=0;
          giro_izq();
          Serial.println("GIRO_IZQ");
        }
        if(vm==luz[2]){
          estado=0;
          adelante();
          Serial.println("ADELANTE");
        }
        if(vm==luz[3]){
          estado=0;
          adelante();
           Serial.println("ADELANTE");
        }
      break;
      }//end switch case
    escritura_motores();
  } // end while*/
} // end Main (loop)
