void funcion(){
   for (int i=0;i<3;i++){
    
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on 
    delay(1000);                       // wait for a second
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
    delay(2000);
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
