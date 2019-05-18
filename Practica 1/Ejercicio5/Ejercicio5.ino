//Ejercico 5

const int boton = 2;

void funcion(){
  digitalWrite(LED_BUILTIN, HIGH);
  delay(100000);
  digitalWrite(LED_BUILTIN, LOW);
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
  
}
