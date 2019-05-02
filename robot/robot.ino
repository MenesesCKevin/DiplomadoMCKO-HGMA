#include<ros.h>
#include<std_msgs/Float32.h>
#include<std_msgs/Int64.h>
#include<std_msgs/Int16.h>
#include<std_msgs/Bool.h>
#include<std_msgs/Float32MultiArray.h>

#define PROX_IZQ  A0
#define PROX_DER  A1

//motor constants
#define PWM_MotorD 10 //Control de velocidad de los motores Derechos
#define PWM_MotorI 11 //Control de velocidad de los motores Izquierdos

#define MotorD_A 7 //Control de direccion de los motores Derechos A
#define MotorD_B 8 //Control de direccion de los motores Derechos B
#define MotorI_A 12 //Control de direccion de los motores Izquierdos A
#define MotorI_B 9 //Control de direccion de los motores Izquierdos B

#define PWM1 200
#define PWM2 200

//Motor 1 -- Derecha
#define Enc_M1A 2//Interrup0
#define Enc_M1B 4
//Motor 2 -- Izquierda
#define Enc_M2A 3//Interrup1
#define Enc_M2B 5

#define FOTO0 A4
#define FOTO1 A5
#define FOTO2 A2
#define FOTO3 A3

#define CONTACTO0 13
#define CONTACTO1 6

//Constantes del motor
// max and min values of RPMS
//Máximos y minimos valores de RPMs que puede conseguir el motor
#define maxPID 300
#define minPID 0
//Máximos y minimos valores de PWM que puede conseguir el motor
#define maxPWM 255
#define minPWM 0

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
volatile float Si,Sd;
volatile int luz0, luz1, luz2, luz3;

//functions

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




void lecturaPhoto(){
  for (int i=0; i<10; i++){
     int valor = analogRead(FOTO0);
     luz0 += valor;
    }
    luz0 /= 10;
  for (int i=0; i<10; i++){
     int valor1 = analogRead(FOTO1);
     luz1 += valor1;
    }
    luz1 /= 10;
  for (int i=0; i<10; i++){
     int valor2 = analogRead(FOTO2);
     luz2 += valor2;
    }
    luz2 /= 10;
  for (int i=0; i<10; i++){
     int valor3 = analogRead(FOTO3);
     luz3 += valor3;
    }
    luz3 /= 10;
}

ros::NodeHandle nh;

std_msgs::Int16 sharpSensor1;
std_msgs::Int16 sharpSensor2;
std_msgs::Bool contactSensor1;
std_msgs::Bool contactSensor2;
std_msgs::Int64 encoder1;
std_msgs::Int64 encoder2;
std_msgs::Int16 photo1;
std_msgs::Int16 photo2;
std_msgs::Int16 photo3;
std_msgs::Int16 photo4;

ros::Publisher sharpSensorPub1("/sharp_sensor_1", &sharpSensor1);
ros::Publisher sharpSensorPub2("/sharp_sensor_2", &sharpSensor2);
ros::Publisher contactSensorPub1("/contact_sensor_1", &contactSensor1);
ros::Publisher contactSensorPub2("/contact_sensor_2", &contactSensor2);
ros::Publisher encoderPub1("/encoder_1", &encoder1);
ros::Publisher encoderPub2("/encoder_2", &encoder2);
ros::Publisher photoPub1("/photo_0", &photo1);
ros::Publisher photoPub2("/photo_1", &photo2);
ros::Publisher photoPub3("/photo_2", &photo3);
ros::Publisher photoPub4("/photo_3", &photo4);

void speedMotor1Callback(const std_msgs::Float32& mess){
  r_tder=mess.data;
    
    if(r_tder > 0.60)
    r_tder = 0.60;
    
    if(r_tder < - 0.60)
    r_tder = -0.60;

  velocidadder = fabs(r_tder);
}

void speedMotor2Callback(const std_msgs::Float32& mess){
  r_tizq=mess.data;
    
  if(r_tizq < - 0.60)
  r_tizq = -0.60;
    
   if(r_tizq > 0.60)
   r_tizq = 0.60;
   velocidadizq = fabs(r_tizq);
    
}

float muestreo(int muestras, int sensor){
  float suma = 0;
  for (int i = 0; i<muestras; i++){
    suma += analogRead(sensor);
    }
    suma /= muestras;
    return(suma);
}

ros::Subscriber<std_msgs::Float32> subSpeedMotor1("/speed_motor_1", speedMotor1Callback);
ros::Subscriber<std_msgs::Float32> subSpeedMotor2("/speed_motor_2", speedMotor2Callback);


void setup() {
  nh.initNode();
  nh.advertise(sharpSensorPub1);
  nh.advertise(sharpSensorPub2);
  nh.advertise(contactSensorPub1);
  nh.advertise(contactSensorPub2);
  nh.advertise(encoderPub1);
  nh.advertise(encoderPub2);
  nh.advertise(photoPub1);
  nh.advertise(photoPub2);
  nh.advertise(photoPub3);
  nh.advertise(photoPub4);
  nh.subscribe(subSpeedMotor1);
  nh.subscribe(subSpeedMotor2);

  pinMode(PROX_IZQ, INPUT);
  pinMode(PROX_DER, INPUT);

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

  pinMode(CONTACTO0, INPUT);
  pinMode(CONTACTO1, INPUT);

  pinMode(FOTO0, INPUT);
  pinMode(FOTO1, INPUT);
  pinMode(FOTO2, INPUT);
  pinMode(FOTO3, INPUT);

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
}

void loop() {
  // put your main code here, to run repeatedly:
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

  //ROS
  float suma1 = muestreo(30,PROX_IZQ);
  Si = 2014.69323221936*pow(suma1,-0.941312417730894)-1.7;
  float suma2 = muestreo(30,PROX_DER);
  Sd = 2014.69323221936*pow(suma2,-0.941312417730894)-1.7;
  sharpSensor1.data = Si;
  sharpSensor2.data = Sd;
  contactSensor1.data = digitalRead(CONTACTO0);
  contactSensor2.data = digitalRead(CONTACTO1);
  encoder1.data = ContM1;
  encoder2.data = ContM2;
  lecturaPhoto();
  photo1.data = luz0;
  photo2.data = luz1;
  photo3.data = luz2;
  photo4.data = luz3;
  sharpSensorPub1.publish(&sharpSensor1);
  sharpSensorPub2.publish(&sharpSensor2);
  contactSensorPub1.publish(&contactSensor1);
  contactSensorPub2.publish(&contactSensor2);
  encoderPub1.publish(&encoder1);
  encoderPub2.publish(&encoder2);
  photoPub1.publish(&photo1);
  photoPub2.publish(&photo2);
  photoPub3.publish(&photo3);
  photoPub4.publish(&photo4);
  nh.spinOnce();
  delay(50);
}
