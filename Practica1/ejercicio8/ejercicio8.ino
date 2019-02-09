//Ejercico 8

const int boton = 2;

void funcion(){
  for (int i=0;i<5;i++){
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)file:///home/kev/Documentos/Diplomado/Practica1/Ejercicio5/Ejercicio5.ino

    delay(250000);                       // wait for a second
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
    delay(250000);
  }
}
void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(boton, INPUT_PULLUP);
  Serial.begin(9600);
  attachInterrupt(0,funcion,RISING);

}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(boton)){
    Serial.println("Encendio");
  }
  delay(50);
  //digitalWrite(LED_BUILTIN, HIGH); 
}
