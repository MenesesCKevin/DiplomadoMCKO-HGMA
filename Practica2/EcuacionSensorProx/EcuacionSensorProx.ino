const int proxIzq = A0;
const int proxDer = A1;
float muestreo1(int muestras){
  float suma = 0;
  for (int i = 0; i<muestras; i++){
    suma += analogRead(proxIzq);
    delay(5);
    }
    suma /= muestras;
    return(suma);
  }
float muestreo2(int muestras){
  float suma = 0;
  for (int i = 0; i<muestras; i++){
    suma += analogRead(proxDer);
    delay(5);
    }
    suma /= muestras;
    return(suma);
  }
void setup() {
  // put your setup code here, to run once:
  pinMode(proxIzq, INPUT);
  pinMode(proxDer, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  float suma1 = muestreo1(30);
  float distanciaIzq = 2014.69323221936*pow(suma1,-0.941312417730894)-1.7;
  Serial.print("Izquierdo: ");
  Serial.print(distanciaIzq);
  
  float suma2 = muestreo2(30);
  float distanciaDer = 2014.69323221936*pow(suma2,-0.941312417730894)-1.7;
  Serial.print("   Derecho: ");
  Serial.println(distanciaDer);
  
  
}
