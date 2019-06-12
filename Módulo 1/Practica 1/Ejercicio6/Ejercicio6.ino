void funcion(){
   for (int i=0;i<5;i++){
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)file:///home/kev/Documentos/Diplomado/Practica1/Ejercicio5/Ejercicio5.ino
    delay(2500);                       // wait for a second
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
    delay(2500);
  }
}


void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  funcion();
}



// the loop function runs over and over again forever
void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
}
