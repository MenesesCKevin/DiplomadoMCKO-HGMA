const int proxIzq = A0;
const int proxDer = A1;
float muestreo(int muestras,int sensor){
  float suma = 0;
  for (int i = 0; i<muestras; i++){
    suma += analogRead(sensor);
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
  float suma1 = muestreo(30,proxIzq);
  float distanciaIzq = 2014.69323221936*pow(suma1,-0.941312417730894)-1.7;
  Serial.print("Izquierdo: ");
  Serial.print(distanciaIzq);
  float suma2 = muestreo(30,proxDer);
  float distanciaDer = -5.968611250*pow(10,-7)*pow(suma2,3)+0.000732269*pow(suma2,2)-0.30196775*suma2+49.11688515;
  Serial.print(" Derecho: ");
  Serial.println(distanciaDer);
  
  
}
