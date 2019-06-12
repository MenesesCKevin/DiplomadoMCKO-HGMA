const int temp = A0;
void setup() {
  // put your setup code here, to run once:
  pinMode(temp, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  float lectura = analogRead(temp);
  float v = (lectura*5)/1024;
  float temperaturaC = (v - 0.5) * 100 ; 
  Serial.print(temperaturaC); Serial.println("°C");
  Serial.print(temperaturaC+273);Serial.println("°K");
  float temperaturaF = (temperaturaC * 9.0 / 5.0) + 32.0;
  Serial.print(temperaturaF); Serial.println("°F");
  delay(2000);
  Serial.println();
  
}
