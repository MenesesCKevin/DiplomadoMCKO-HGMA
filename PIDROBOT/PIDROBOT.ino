//motor constants
#define PWM_MotorD 10 //Control de velocidad de los motores Derechos
#define PWM_MotorI 11 //Control de velocidad de los motores Izquierdos

#define MotorD_A 7 //Control de direccion de los motores Derechos A
#define MotorD_B 8 //Control de direccion de los motores Derechos B
#define MotorI_A 12 //Control de direccion de los motores Izquierdos A
#define MotorI_B 9 //Control de direccion de los motores Izquierdos B

//Enconders

//Motor 1 -- Derecha
#define Enc_M1A 2//Interrup0
#define Enc_M1B 4
//Motor 2 -- Izquierda
#define Enc_M2A 3//Interrup1
#define Enc_M2B 5

//Constantes del motor
// max and min values of RPMS
//Máximos y minimos valores de RPMs que puede conseguir el motor
#define maxPID 300
#define minPID 0
//Máximos y minimos valores de PWM que puede conseguir el motor
#define maxPWM 255
#define minPWM 0

double i;
//variables

int MD_A=0; //Valor de dirección del MotorD_A
int MD_B=0; //Valor de dirección del MotorD_B
int MI_A=0; //Valor de dirección del MotorI_A
int MI_B=0; //Valor de dirección del MotorI_B
int pwm_D = 0; //Valor de pwm del Motor_D
int pwm_I = 0; //Valor de pwm del Motor_I
float RPM_der = 0; //Revoluciones por minuto calculadas
float RPM_izq = 0; //Revoluciones por minuto calculadas
float velocidad_der = 0; //Velocidad en [m/s]
float velocidad_izq = 0; //Velocidad en [m/s]

int cambioderecha = 0;
float velocidadder = 0;
int cambioizquierda = 0;
float velocidadizq = 0;

//ENCODERS Y PID

//Alemacenaiento de pulsos de cada motor
volatile long ContM1=0;
volatile long ContM2=0;

//---------------------------------------------------------------------------------------------------
 //Variables para calcular la velocidad
unsigned long timeold = 0;       // Tiempo
unsigned int pulsesperturn = 310; // Número de pulsos por vuelta del motor
float wheel_diameter = 0.042;// Diámetro de la rueda
int ratio = 1;                  // Relación de transmisión 
//---------------------------------------------------------------------------------------------------

//Definición de las constanytes para el PID
float error_D = 0;
float errorAnterior_D = 0; 
float P_D = 0;//Acción Proporcional
float I_D = 0;//Acción integral
float D_D = 0;//Acción /DErivativa
float Kp_D = 0.70; //Constante proporcional
float Ki_D = 0.08; //Constante integral
float Kd_D = 23;//Constante derivativa


float error_I = 0;
float errorAnterior_I = 0; 
float P_I = 0;//Acción Proporcional
float I_I = 0;//Acción integral
float D_I = 0;//Acción /DErivativa
float Kp_I = 0.70; //Constante proporcional
float Ki_I = 0.08; //Constante integral
float Kd_I = 23;//Constante derivativa

//----------------------------------------------------------------------------------------
//Definición de las señales de error, control y la salida del sistema.
float r_t_D = 0 ; //[m/s]
float r_t_I = 0 ; //[m/s]
float r_tder = 0;//[m/s]
float r_tizq = 0;//[m/s]
volatile float y_t_D = 0;
volatile float y_t_I = 0;
float ut_D = 0;
float ut_I = 0;
//----------------------------------------------------------------------------------------

//Tiempo del ciclo del PID
float cycleTime = 100.0; //ms
///Tiempo del ciclo del PID en segundo
float cycleTimeSeconds = 0; //s  // Variable auxiliar del timepo del ciclo del PID
//----------------------------------------------------------------------------------------


//functions

void speedsCallback(float data0, float data1){
/*  
  if(msg.data_length < 2){
     r_tizq=0;
     r_tder=0;
     return;
  }else
  {*/
    r_tizq=data0;
    r_tder=data1;
    
    if(r_tizq < - 0.60)
    r_tizq = -0.60;
    
    if(r_tizq > 0.60)
    r_tizq = 0.60;
    
    if(r_tder > 0.60)
    r_tder = 0.60;
    
    if(r_tder < - 0.60)
    r_tder = -0.60;

   

//  }

  velocidadder = fabs(r_tder);
  velocidadizq = fabs(r_tizq);

  
}

//--------------------------------------------------------------

void encoderM1aEvent(){
  if(digitalRead(Enc_M1A)==HIGH){
    if(digitalRead(Enc_M1B)==LOW){
      ContM1++;
      }
    else{ 
      ContM1--;
      }
    }
   else{
    if(digitalRead(Enc_M1B)==LOW){
      ContM1--;
      }
    else //if anidado A=0&B=1
      ContM1++;
      }
}

//--------------------------------------------------------------

void encoderM2aEvent(){ //MOTOR 2
  if(digitalRead(Enc_M2A)==HIGH)  {
    if(digitalRead(Enc_M2B)==LOW){
      ContM2--;                 }//Fin if anidado A=1&B=0
    else //if anidado A=1&B=1
      ContM2++;                    }//Fin primer if A=1
      
  else{
    if(digitalRead(Enc_M2B)==LOW)  {
      ContM2--;                 }//Fin if anidado A=0&B=0
      
    else //if anidado A=0&B=1
      ContM2++;                    }//Fin segundo if A=0
}//Fin encoderM2aEvent

//--------------------------------------------------------------

void calculoVelocidad()
{
  if (millis() - timeold >= 100)
  {   // Se actualiza cada segundo
      // Desconectamos la interrupción para que no actué en esta parte del programa.
      //***************************************************************************************
      RPM_der = 60 * abs(ContM1) / pulsesperturn * 1000 / (millis() - timeold) ;  // Calculamos las revoluciones por minuto
      //Ojo con la fórmula de arriba, la variable rpm tiene que ser tipo float porque salen decimales en medio de la operación.
      velocidad_der = RPM_der *3.1416 * wheel_diameter  / 60.0; // Cálculo de la velocidad de la rueda en [Km/h]
      ContM1 = 0;  // Inicializamos los pulsos.
      
      //***************************************************************************************
      RPM_izq = 60 * abs(ContM2) / pulsesperturn * 1000 / (millis() - timeold) ;  // Calculamos las revoluciones por minuto
      //Ojo con la fórmula de arriba, la variable rpm tiene que ser tipo float porque salen decimales en medio de la operación.
      velocidad_izq = RPM_izq *3.1416 * wheel_diameter  / 60.0; // Cálculo de la velocidad de la rueda en [Km/h]
      ContM2 = 0;  // Inicializamos los pulsos.
      timeold = millis(); // Almacenamos el tiempo actual.
      //interrupts(); // Restart the interrupt processing // Reiniciamos la interrupción
  }
}

//--------------------------------------------------------------

void pid(){
  //****************PID DERECHO****************************
  y_t_D = RPM_der;
  r_t_D =velocidadder*60/(3.1416 * wheel_diameter);
  error_D = r_t_D - y_t_D;//Cálculo del error
  P_D = Kp_D * error_D;//Acción proporcional
  I_D += Ki_D * error_D * cycleTimeSeconds;// /Calculo acción integrativa
  D_D = Kd_D * (error_D - errorAnterior_D) / cycleTimeSeconds;//cálculo acción derivativa
  ut_D = P_D + I_D + D_D;//suma de las tres acciones para obtener la señal de control
  //Si las RPMs (ut) de salida, son mas grandes que el máximo al que puede girar el motor
  //entonces se asigna el máximo
  if (ut_D > maxPID) ut_D = maxPID;
  //Si las RPMs (ut) de salida, son mas pequeñas que el mínimo al que puede girar el motor (0 RPMs)
  //entonces se asigna el mínimo
  if (ut_D < minPID ||ut_D < 2 ) ut_D = minPID;
  errorAnterior_D = error_D;

    //****************PID IZQUIERDO****************************
  y_t_I = RPM_izq;
  r_t_I =velocidadizq*60/(3.1416 * wheel_diameter);
  error_I = r_t_I - y_t_I;//Cálculo del error
  P_I = Kp_I * error_I;//Acción proporcional
  I_I += Ki_I * error_I * cycleTimeSeconds;// /Calculo acción integrativa
  D_I = Kd_I * (error_I - errorAnterior_I) / cycleTimeSeconds;//cálculo acción derivativa
  ut_I = P_I + I_I + D_I;//suma de las tres acciones para obtener la señal de control
  //Si las RPMs (ut) de salida, son mas grandes que el máximo al que puede girar el motor
  //entonces se asigna el máximo
  if (ut_I > maxPID) ut_I = maxPID;
  //Si las RPMs (ut) de salida, son mas pequeñas que el mínimo al que puede girar el motor (0 RPMs)
  //entonces se asigna el mínimo
  if (ut_I < minPID || ut_I < 2 ) ut_I = minPID;
  errorAnterior_I = error_I;
}

//--------------------------------------------------------------

void elecciongiro(){
  if (r_tder < 0){ 
    MD_A = 1;
    MD_B = 0;
  }
  
  else{
    MD_A = 0;
    MD_B = 1;
  }
  
  if (r_tizq < 0){
    MI_A = 1;
    MI_B = 0;
  }
  else{
    MI_A = 0;
    MI_B = 1;
  }
}

//--------------------------------------------------------------

void rpmToPwm(){
  //Convertimos el valor de RPMs a PWM
  pwm_I = map(ut_I, minPID, maxPID, minPWM, maxPWM);
  pwm_D = map(ut_D, minPID, maxPID, minPWM, maxPWM);
}


//--------------------------------------------------------------


void setup() {
  //Serial.begin(9600);
   //Encoders
  pinMode(Enc_M1A,INPUT);
  pinMode(Enc_M1B,INPUT);
  pinMode(Enc_M2A,INPUT);
  pinMode(Enc_M2B,INPUT);
    
  //Motors
  pinMode(PWM_MotorD,OUTPUT);
  pinMode(PWM_MotorI,OUTPUT);
  pinMode(MotorD_A,OUTPUT);
  pinMode(MotorD_B,OUTPUT);
  pinMode(MotorI_A,OUTPUT);
  pinMode(MotorI_B,OUTPUT);
  
  //Interruptions
  attachInterrupt(0,encoderM1aEvent,RISING); //Int0 =Enc_M1A = pin2
  attachInterrupt(1,encoderM2aEvent,RISING); //Int1 =Enc_M2A = pin3

  //Set of values
  ContM1 = 0;
  ContM2 = 0;
  RPM_der = 0;  
  RPM_izq = 0;  
  timeold = 0;
  velocidadder = 0;
  velocidadizq = 0;
  r_tizq=0;
  r_tder=0; 
  cycleTimeSeconds = cycleTime / 1000.0;
  speedsCallback(0,0);
  
}



void loop() {
  //PID conttol 
  elecciongiro();
  calculoVelocidad();
  pid();
  rpmToPwm();
  //Serial.print("Velocidad_D\t");
  //Serial.println(RPM_der);
  //Serial.print("\t");
  //Serial.print("Velocidad_I\t");
  //Serial.println(velocidad_izq);
  //Direcciones y velocidad de lo motores*/
  digitalWrite(MotorD_A,MD_A); //Motores Derechos
  digitalWrite(MotorD_B,MD_B);
  digitalWrite(MotorI_A,MI_A);  //Motores Izquierda
  digitalWrite(MotorI_B,MI_B);
  
  analogWrite(PWM_MotorD, pwm_D);
  analogWrite(PWM_MotorI, pwm_I );
}
