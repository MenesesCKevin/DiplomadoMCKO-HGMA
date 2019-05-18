const int izq1 = 5;
const int der1 = 9;
const int der2 = 2;
const int izq2 = 3;

String txtMsg = "";
String valor;

int direccion_izq = false;
int velocidad_izq = 60;

int direccion_der = false;
int velocidad_der = 60;

void setup() {
  // put your setup code here, to run once:
  pinMode (der1, OUTPUT);
  pinMode (der2, OUTPUT);
  pinMode (izq1, OUTPUT);
  pinMode (izq2, OUTPUT);
  
  Serial.begin(9600);
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

   String inicio = getValue(txtMsg, ' ', 0);
    
   if (inicio == "A1"){
      inicio = getValue(txtMsg, ' ',1);
      if (inicio == on) {
        valor = getValue(txtMsg, ' ',2);
        if (int)valor >= 127 {
          izquierdo_left((int)valor);
        }
        else{
          izquierdo_right((int)valor);
        }
      }
      else{
        izquierdo_off();
      }
    }


  if (inicio == "A2"){
      valor = getValue(txtMsg, ' ',2)
      if (int)valor >= 127 {
        derecho_left();
      }
      else{
        derecho_right();
      }
    }
 
    analogWrite(izq2,(int)valor);
    analogWrite(izq1,!(int)valor);

    digitalWrite(der1,!direccion_der);
    digitalWrite(der2,direccion_der);
    analogWrite(velDer,velocidad_der);
}
