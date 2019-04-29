#include<ros.h>
#include<std_msgs/Float32.h>
#include<std_msgs/Int64.h>
#include<std_msgs/Int16.h>
#include<std_msgs/Bool.h>
#include<std_msgs/Float32MultiArray.h>

#define PROX_IZQ  A0
#define PROX_DER  A1

#define D00 7
#define D01 8
#define E1 10
#define PWM1 200

#define I00 12
#define I01 9
#define E2 11
#define PWM2 200

#define RH_ENCODER_A 2
#define RH_ENCODER_B 4

#define LF_ENCODER_A 3
#define LF_ENCODER_B 5

#define FOTO0 A4
#define FOTO1 A5
#define FOTO2 A2
#define FOTO3 A3

#define CONTACTO0 13
#define CONTACTO1 6

volatile float Si,Sd;
volatile long rightCount = 0;
volatile long leftCount = 0;
volatile int luz0, luz1, luz2, luz3;

void rightEncoderEvent(){
  if(digitalRead(RH_ENCODER_A == HIGH)){
    if(digitalRead(RH_ENCODER_B) == LOW){
      rightCount++;
    }else{
      rightCount--;
    }
  }
  else{
    if(digitalRead(RH_ENCODER_B == LOW)){
      rightCount--;
    }else{
      rightCount++;
    }
  }
}
void leftEncoderEvent(){
  if(digitalRead(LF_ENCODER_A == HIGH)){
    if(digitalRead(LF_ENCODER_B) == LOW){
      leftCount++;
    }else{
      leftCount--;
    }
  }
  else{
    if(digitalRead(LF_ENCODER_B == LOW)){
      leftCount--;
    }else{
      leftCount++;
    }
  }
}

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
  if(mess.data >=0){
    digitalWrite(D00,HIGH);
    digitalWrite(D01,LOW);
    analogWrite(E1, mess.data);
  }
  else{
    digitalWrite(D00,LOW);
    digitalWrite(D01,HIGH);
    analogWrite(E1, fabs(mess.data));
  }
}

void speedMotor2Callback(const std_msgs::Float32& mess){
  if(mess.data >=0){
    digitalWrite(I00,HIGH);
    digitalWrite(I01,LOW);
    analogWrite(E2, mess.data);
  }
  else{
    digitalWrite(I00,LOW);
    digitalWrite(I01,HIGH);
    analogWrite(E2, fabs(mess.data));
  }
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

  pinMode(D00, OUTPUT);
  pinMode(D01, OUTPUT);
  pinMode(E1, OUTPUT);
  pinMode(RH_ENCODER_A, INPUT);
  pinMode(RH_ENCODER_B, INPUT);

  
  pinMode(I00, OUTPUT);
  pinMode(I01, OUTPUT);
  pinMode(E2, OUTPUT);
  pinMode(LF_ENCODER_A, INPUT);
  pinMode(LF_ENCODER_B, INPUT);

  pinMode(CONTACTO0, INPUT);
  pinMode(CONTACTO1, INPUT);

  pinMode(FOTO0, INPUT);
  pinMode(FOTO1, INPUT);
  pinMode(FOTO2, INPUT);
  pinMode(FOTO3, INPUT);

  attachInterrupt(0, rightEncoderEvent, CHANGE);
  attachInterrupt(1, leftEncoderEvent, CHANGE);
}

void loop() {
  // put your main code here, to run repeatedly:
  float suma1 = muestreo(30,PROX_IZQ);
  Si = 2014.69323221936*pow(suma1,-0.941312417730894)-1.7;
  float suma2 = muestreo(30,PROX_DER);
  Sd = 2014.69323221936*pow(suma2,-0.941312417730894)-1.7;
  sharpSensor1.data = Si;
  sharpSensor2.data = Sd;
  contactSensor1.data = digitalRead(CONTACTO0);
  contactSensor2.data = digitalRead(CONTACTO1);
  encoder1.data = rightCount;
  encoder2.data = leftCount;
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
