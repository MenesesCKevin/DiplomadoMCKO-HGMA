const int prox = A0;
const int led = 13;
float muestreo(int muestras){
  float suma = 0;
  for (int i = 0; i<muestras; i++){
    suma += analogRead(prox);
    delay(5);
    }
    suma /= muestras;
    return(suma);
  }
void setup() {
  // put your setup code here, to run once:
  pinMode(prox, INPUT);
  Serial.begin(9600);
  pinMode(led, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  float suma = muestreo(30);
  float distancia1 = 2014.69323221936*pow(suma,-0.941312417730894)-1.7;
  Serial.println(distancia1);
  //float distancia2 = -5.968611250*pow(10,-7)*pow(suma,3)+0.000732269*pow(suma,2)-0.30196775*suma+49.11688515;
  //Serial.println(distancia2);
  
  
}
