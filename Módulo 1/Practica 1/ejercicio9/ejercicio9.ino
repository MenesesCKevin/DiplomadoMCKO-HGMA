const int led = 3;
void setup() {
  // put your setup code here, to run once:
  pinMode(led, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i=0;i<256;i++){
      analogWrite(led, i);
      delay(10);
    }
    delay(2000);
   for(int i=255;i>=0;i--){
      analogWrite(led, i);
      delay(10);
    }
    delay(3000);

}
