const int proxIzq = A0;

float muestreo(int muestras,int sensor){
  float suma = 0;
  for (int i = 0; i<muestras; i++){
    suma += analogRead(sensor);
    delay(5);
    }
    suma /= muestras;
    return(suma);
  }

float sensor_lectura(int sensor){
  float lectura = muestreo(30,sensor);
  float distancia = 2014.69323221936*pow(lectura,-0.941312417730894)-1.7;
  return lectura;
}
  
void setup() {
  pinMode(proxIzq, INPUT);
  Serial.begin(9600);
}

void loop() {
  
  Serial.print(sensor_lectura(proxIzq));
 
}
