const int led = 3;
const int pot =A0;
void setup() {
  // put your setup code here, to run once:
  pinMode(led, OUTPUT);
  pinMode(pot, INPUT);
}

void loop() {
  int valor = analogRead(pot);
  int val = map(valor,0,1024, 2000,4000);
  // put your main code here, to run repeatedly:
  for(int i=0;i<256;i++){
      analogWrite(led, i);
      delay(10);
    }
    delay(val);
   for(int i=255;i>=0;i--){
      analogWrite(led, i);
      delay(10);
    }
    delay(val);

}
