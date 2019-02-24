const int temp = A0;
String txtMsg = "";
const int prox = A1;
const int luz = A3;

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
  pinMode(temp, INPUT);
  Serial.begin(9600);
  pinMode(prox, INPUT);
  pinMode(luz, INPUT);
}
 void temperatura(){
  float lectura = analogRead(temp);
  float v = (lectura*5)/1024;
  float temperaturaC = (v - 0.5) * 100 ; 
  Serial.print("temp ");
  Serial.print(temperaturaC); Serial.println("°C");
  Serial.print(temperaturaC+273);Serial.println("°K");
  float temperaturaF = (temperaturaC * 9.0 / 5.0) + 32.0;
  Serial.print(temperaturaF); Serial.println("°F");
  Serial.println();
  }
void infrarojo(){
  float suma = muestreo(30);
  float distancia1 = 2077.15573625364*pow(suma,-0.953001973271067);
  Serial.println(distancia1);
  }

void fotoresistencia(){
  int lectura = analogRead(luz);
  Serial.println(lectura);
  delay(10);
}

void loop() {
  // put your main code here, to run repeatedly:
  while (Serial.available()) {
    char inChar = Serial.read();
    if(inChar != '\n'){
      txtMsg.concat(inChar);
    }
    else{
      //Serial.println(txtMsg);
      txtMsg = "";
      }
  }
 if (txtMsg == "shs temp"){
    temperatura();
  }
 if (txtMsg == "shs infrared"){
  infrarojo();
  }
 if (txtMsg == "shs fotores"){
  fotoresistencia();
  }
}
