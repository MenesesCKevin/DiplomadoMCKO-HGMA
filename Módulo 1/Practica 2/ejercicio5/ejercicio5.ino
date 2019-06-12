const int prox = A0;
const int led = 13;
void muestreo(int muestras){
  float suma = 0;
  for (int i = 0; i<muestras; i++){
    suma += analogRead(prox);
    delay(5);
    }
    suma /= muestras;
    Serial.println(suma);
    if(suma > 292){
      digitalWrite(led,HIGH);
      }
     else{
      digitalWrite(led, LOW);
      }
  }
void setup() {
  // put your setup code here, to run once:
  pinMode(prox, INPUT);
  Serial.begin(9600);
  pinMode(led, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  muestreo(30);
  
}
