#include <ros.h>
#include <std_msgs/Float32.h>
#include <std_msgs/Int64.h>
#include <std_msgs/Int16.h>
#include <std_msgs/Bool.h>
#define D00 7
#define D01 8
#define D10 9
#define D11 12
#define E1 10
#define E2 11
#define PWM1 200
#define RH_ENCODER_A 2
#define RH_ENCODER_B 4
#define LH_ENCODER_A 3
#define LH_ENCODER_B 5
//Máximos y minimos valores de RPMs que puede conseguir el motor
#define maxPID 50
#define maxI 1000
#define minPID 0
#define maxPWM 255
#define minPWM 0
#define BAUD 200000
volatile long rightCount = 0;
volatile int relRightCount = 0;
volatile long leftCount = 0;
volatile int relLeftCount = 0;
//Variables para calcular la velocidad
unsigned long timeold = 0; // Tiempo
unsigned int pulsesperturn = 600; // Número de pulsos por vuelta del motor, por canal = 600.
float wheel_diameter = (43.38)/1000;// Diámetro de la rueda pequeña[mm]
int ratio = 1; // Relación de transmisión ]
int pwmR = 0;
int pwmL = 0;
float RPMRight = 0.0;
float RPMLeft = 0.0;
float speedRight = 0;
float speedLeft = 0;
//Definición de las constanytes para el PID
float error_R = 0;
float lastError_R = 0;
float P_R = 0;//Acción Proporcional
float I_R = 0;//Acción integral
float D_R = 0;//Acción /DErivativa
float Kp_R = 0.332; //Constante proporcional
//float Ki_R = 0.08; //Constante integral
//float Kd_R = 0.01;//Constante derivativa
float Ki_R = 0.075; //Constante integral
float Kd_R = 0.25;//Constante derivativa
float error_L = 0;
float lastError_L = 0;
float P_L = 0;//Acción Proporcional
float I_L = 0;//Acción integral
float D_L = 0;//Acción /DErivativa
float Kp_L = 0.332; //Constante proporcional
//float Ki_L = 0.08; //Constante integral
//float Kd_L = 0.01;//Constante derivativa
float Ki_L = 0.075; //Constante integral
float Kd_L = 0.25;//Constante derivativa
float r_t_R = 0;
volatile float y_t_R = 0;
float r_tR = 0;
float ut_R = 0;
float r_t_L = 0;
volatile float y_t_L = 0;
float r_tL = 0;
float ut_L = 0;
float goalSpeedRight = 0.0;
float goalSpeedLeft = 0.0;
float cycleTime = 40;
float cycleTimeSeconds = 0;
void rightEncoderEvent(){
 if(digitalRead(RH_ENCODER_A) == HIGH){
   if(digitalRead(RH_ENCODER_B) == LOW){
    rightCount++;
    relRightCount++;
 }else{
  rightCount--;
  relRightCount--;
  }
 }
 else{
  if(digitalRead(RH_ENCODER_B) == LOW){
  rightCount--;
  relRightCount--;
 }else{
  rightCount++;
  relRightCount++;
 }
 }
}
void leftEncoderEvent(){
 if(digitalRead(LH_ENCODER_A) == HIGH){
   if(digitalRead(LH_ENCODER_B) == LOW){
   leftCount++;
   relLeftCount++;
   }else{
   leftCount--;
   relLeftCount--;
   }
   }
   else{
   if(digitalRead(LH_ENCODER_B) == LOW){
   leftCount--;
   relLeftCount--;
   }else{
   leftCount++;
   relLeftCount++;
   }
   }
}
void computeSpeeds()
{
 if (millis() - timeold >= cycleTime)
 {
   RPMRight = 60.0 * fabs(relRightCount) / pulsesperturn * 1000.0 / (millis() - timeold);
   speedRight = RPMRight *3.1416 * wheel_diameter / 60.0;
   relRightCount = 0;

   RPMLeft = 60.0 * fabs(relLeftCount) / pulsesperturn * 1000.0 / (millis() - timeold);
   speedLeft = RPMLeft *3.1416 * wheel_diameter / 60.0;
   relLeftCount = 0;
   timeold = millis();
 }
}
void pid(){
 //****************PID DERECHO****************************
 y_t_R = RPMRight;
 r_t_R = goalSpeedRight * 60.0 / (3.1416 * wheel_diameter);

 error_R = r_t_R - y_t_R;//Cálculo del error
 P_R = Kp_R * error_R;//Acción proporcional
 I_R += Ki_R * error_R * cycleTimeSeconds;// /Calculo acción integrativa
 D_R = Kd_R * (error_R - lastError_R) / cycleTimeSeconds / 60.0;//cálculo acción derivativa
 ut_R = P_R + I_R + D_R;//suma de las tres acciones para obtener la señal de control
 if(I_R > maxI) I_R = maxI;
 //Si las RPMs (ut) de salida, son mas grandes que el máximo al que puede girar el motor
 //entonces se asigna el máximo
 if (ut_R > maxPID) ut_R = maxPID;
 //Si las RPMs (ut) de salida, son mas pequeñas que el mínimo al que puede girar el motor (0 RPMs)
 //entonces se asigna el mínimo
 if (ut_R < minPID ||ut_R < 7 ) ut_R = minPID;
 lastError_R = error_R;
 //****************PID IZQUIERDO****************************
 y_t_L = RPMLeft;
 r_t_L =goalSpeedLeft * 60.0 / (3.1416 * wheel_diameter);
 error_L = r_t_L - y_t_L;//Cálculo del error
 P_L = Kp_L * error_L;//Acción proporcional
 I_L += Ki_L * error_L * cycleTimeSeconds;// /Calculo acción integrativa
 D_L = Kd_L * (error_L - lastError_L) / cycleTimeSeconds / 60.0;//cálculo acción derivativa
 ut_L = P_L + I_L + D_L;//suma de las tres acciones para obtener la señal de control
 if(I_L > maxI) I_L = maxI;
 //Si las RPMs (ut) de salida, son mas grandes que el máximo al que puede girar el motor
 //entonces se asigna el máximo
 if (ut_L > maxPID) ut_L = maxPID;
 //Si las RPMs (ut) de salida, son mas pequeñas que el mínimo al que puede girar el motor (0 RPMs)
 //entonces se asigna el mínimo
 if (ut_L < minPID ||ut_L < 7 ) ut_L = minPID;
 lastError_L = error_L;
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
//ros::Publisher contactSensorPub1("/contact_sensor_1", &contactSensor1);
//ros::Publisher contactSensorPub2("/contact_sensor_2", &contactSensor2);
ros::Publisher encoderPub1("/encoder_1", &encoder1);
ros::Publisher encoderPub2("/encoder_2", &encoder2);
ros::Publisher photoPub1("/photo_1", &photo1);
ros::Publisher photoPub2("/photo_2", &photo2);
ros::Publisher photoPub3("/photo_3", &photo3);
ros::Publisher photoPub4("/photo_4", &photo4);
void speedMotor1Callback(const std_msgs::Float32& mess){
 if(mess.data > 0){
 digitalWrite(D00, LOW);
 digitalWrite(D01, HIGH);
 //analogWrite(E1, mess.data);
 }
 else{
 digitalWrite(D00, HIGH);
 digitalWrite(D01, LOW);
 //analogWrite(E1, fabs(mess.data));
 }
 I_R = 0;
 goalSpeedRight = fabs(mess.data);
}
void speedMotor2Callback(const std_msgs::Float32& mess){
 if(mess.data > 0){
 digitalWrite(D10, LOW);
 digitalWrite(D11, HIGH);
 }
 else{
 digitalWrite(D10, HIGH);
 digitalWrite(D11, LOW);
 }
 I_L = 0;
 goalSpeedLeft = fabs(mess.data);
}
void rpmToPwm(){
 //Convertimos el valor de RPMs a PWM
 pwmL = map(ut_L, minPID, maxPID, minPWM, maxPWM);
 pwmR = map(ut_R, minPID, maxPID, minPWM, maxPWM);
 if(pwmR > 255)
 pwmR = 255;
 if(pwmL > 255)
 pwmL = 255;
 if(pwmR < 0)
 pwmR = 0;
 if(pwmL < 0)
 pwmL = 0;
}
ros::Subscriber<std_msgs::Float32> subSpeedMotor1("/speed_motor_1", speedMotor1Callback);
ros::Subscriber<std_msgs::Float32> subSpeedMotor2("/speed_motor_2", speedMotor2Callback);
void setup() {
 // put your setup code here, to run once:
 nh.getHardware()->setBaud(BAUD);
 nh.initNode();
 nh.advertise(sharpSensorPub1);
 nh.advertise(sharpSensorPub2);
 /*nh.advertise(contactSensorPub1);
 nh.advertise(contactSensorPub2);*/
 nh.advertise(encoderPub1);
 nh.advertise(encoderPub2);
 nh.advertise(photoPub1);
 nh.advertise(photoPub2);
 nh.advertise(photoPub3);
 nh.advertise(photoPub4);
 nh.subscribe(subSpeedMotor1);
 nh.subscribe(subSpeedMotor2);

 pinMode(D00, OUTPUT);
 pinMode(D01, OUTPUT);
 pinMode(E1, OUTPUT);
 pinMode(RH_ENCODER_A, INPUT);
 pinMode(RH_ENCODER_B, INPUT);
 pinMode(D10, OUTPUT);
 pinMode(D11, OUTPUT);
 pinMode(E2, OUTPUT);
 pinMode(LH_ENCODER_A, INPUT);
 pinMode(LH_ENCODER_B, INPUT);
 attachInterrupt(0, rightEncoderEvent, CHANGE);
 attachInterrupt(1, leftEncoderEvent, CHANGE);
 cycleTimeSeconds = cycleTime / 1000.0;
}
void loop() {
 // put your main code here, to run repeatedly:
 /*sharpSensor1.data = 0.5;
 sharpSensor2.data = 0.7;
 contactSensor1.data = true;
 contactSensor2.data = false;*/
 encoder1.data = rightCount;
 encoder2.data = leftCount;
 /*photo1.data = 1;
 photo2.data = 1;
 photo3.data = 1;
 photo4.data = 1;
 sharpSensorPub1.publish(&sharpSensor1);
 sharpSensorPub2.publish(&sharpSensor2);*/
 /*contactSensorPub1.publish(&contactSensor1);
 contactSensorPub2.publish(&contactSensor2);*/
 encoderPub1.publish(&encoder1);
 encoderPub2.publish(&encoder2);
 /*photoPub1.publish(&photo1);
 photoPub2.publish(&photo2);
 photoPub3.publish(&photo3);
 photoPub4.publish(&photo4);*/
 computeSpeeds();
 pid();
 rpmToPwm();
 analogWrite(E1, pwmR);
 analogWrite(E2, pwmL);

 nh.spinOnce();
 delay(20);
}
