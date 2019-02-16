const int luz = 2;
void setup() {
  // put your setup code here, to run once:
  pinMode(luz, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int lectura = digitalRead(luz);
  Serial.println(lectura);
  delay(10);
  
}
