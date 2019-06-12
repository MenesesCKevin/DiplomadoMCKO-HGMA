/********************************************************
 *                                                      *
 *                                                      *
 *      user_sm.h			          	*
 *                                                      *
 *							*
 *		FI-UNAM					*
 *		17-2-2019                               *
 *                                                      *
 ********************************************************/
// State Machine 
#define PI 3.14159265
#define THRESHOLD_FOLLOWER 30
int CPotenciales(float intensity, float *light_values, float *observations, int size, float laser_value, int  dest, int obs ,
					movement *movements  ,int *next_state ,float Mag_Advance ,float max_twist)
{

 float xobs, yobs, frepulx, frepuly, FtotalX, FtotalY,q_qobsX, q_qobsY;
 float ang,angObs,angLuz, alpha,xdes,ydes,fqX =0,fqY=0,qnX,qnY;
 float AtraccionX,AtraccionY;
 float qn;
 float e1 = 0.05;
 float heta = 0.000001;
 int sensor;
 int sensorLuz = 0;
 float maxLuz =0.8264;
 printf("%f\n",intensity );
 
 if(intensity > THRESHOLD_FOLLOWER){
  movements->twist = 0.0;
  movements->advance = 0.0;
  printf("\n **************** Reached light source ******************************\n");
  return 1;
}
else{

    for(int i = 0; i < 8; i++ )
    {
        if( light_values[i] > light_values[sensorLuz] )
            sensorLuz = i;
    }
      
    angLuz = (sensorLuz*2*PI)/8;
    xdes = cos(angLuz)*(THRESHOLD_FOLLOWER-intensity);
    ydes = sin(angLuz)*(THRESHOLD_FOLLOWER-intensity);

    printf("xdes: %f\n",xdes );
    printf("ydes: %f\n",ydes );

    AtraccionX = e1 * (-xdes);
    AtraccionY = e1 * (-ydes);
    printf("AtraccionX: %f\n", AtraccionX);
    printf("AtraccionX: %f\n", AtraccionY);
    fqX= AtraccionX/(sqrt(pow(AtraccionX,2)+pow(AtraccionY,2)));
    fqY= AtraccionY/(sqrt(pow(AtraccionX,2)+pow(AtraccionY,2)));
    printf("fqX: %f\n", fqX);
    printf("fqX: %f\n", fqY);

    if(obs != 0){

      for (int i = 0; i < size ; i++ ) //derecha
        {
            if( observations[i] < observations[sensor]  )
            {
                sensor = i;
            }
        }
      printf("sensor: %d\n", sensor);
      angObs = PI*sensor/size;
      printf("angObs: %f\n",angObs );
      if (angObs >= 1.571){
          alpha = angObs -1.57;
      }
      else{
          alpha = 1.571- angObs;
      }
      printf("alfa %f\n",alpha);
      xobs = observations[sensor] * cos(alpha);
      yobs = observations[sensor] * sin(alpha);
      printf("xobs %f\n",xobs);
      printf("yobs %f\n", yobs );
      q_qobsX = -xobs;
      q_qobsY = -yobs;
      frepulx = -heta*((1/q_qobsX)-(1/laser_value))*(1/pow(q_qobsX,2))*(q_qobsX/(sqrt(pow(q_qobsX,2)+pow(q_qobsY,2))));
      frepuly = -heta*((1/q_qobsY)-(1/laser_value))*(1/pow(q_qobsY,2))*(q_qobsY/(sqrt(pow(q_qobsX,2)+pow(q_qobsY,2))));    
    }
    else{
        frepulx = 0.0001;
        frepuly = 0.0001;
    }

    printf("frepulx: %f\n",frepulx );
    printf("frepuly: %f\n", frepuly );
      

    FtotalX = fqX + frepulx;
    FtotalY = fqY + frepuly;

    printf("FtotalX; %f\n",FtotalX );
    printf("FtotalY; %f\n",FtotalY );

    qnX= -Mag_Advance*FtotalX;
    qnY= -Mag_Advance*FtotalY;

    printf("qnX: %f\n", qnX );
    printf("qnY: %f\n", qnY);

    ang= atan2(qnY,qnX);
    qn = qnY/sin(ang);

    movements->twist = ang;
    movements->advance = qn;

    printf("Ang %f\n",ang);
    printf("Qn %f\n",qn);

    return 0;
  }

}

