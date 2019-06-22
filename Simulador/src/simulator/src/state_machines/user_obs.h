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


int condicion_grados(int grd){
    if (grd >= 360 || grd <= -360){
        return 1;
    }
    else{
        return 0;
    }
}



// State Machine 
void user_obs(float rx ,float ry, float intensity, float *light_values, float *observations, int size, float laser_value, int  dest, int obs ,
					movement *movements  ,int *next_state ,float Mag_Advance ,float max_twist, int *grados)
{

 int state = *next_state;
 int i;
 int obstaculo=0;
 float rx_inicial = rx , ry_inicial = ry ;

 printf("intensity %f\n",intensity);
 printf("quantized destination %d\n",dest);
 printf("quantized obs %d\n",obs);

 max_twist=0.628;
 Mag_Advance=0.008;
 printf("intensity %f\n",max_twist);
 switch ( state ) {

		case 0: //Estado inicial
				*movements=generate_output(FORWARD,Mag_Advance,max_twist);
				if (obs == 0){
					*next_state = 0;
				}
				else{
					*next_state = 1;
				}
                if(condicion_grados(*grados)==1)
                    *next_state = 8;
				break;

 		case 1://Estado iniciol
 				*movements = generate_output(STOP,Mag_Advance,max_twist);
 				if(obs == 1){
 					*next_state = 5;
 				}
 				else if(obs == 2) {
 					*next_state = 4;
 				}
 				else{
 					*next_state = 3;
 				}
                if(condicion_grados(*grados)==1)
                    *next_state = 8;
 				break;

 		case 5: //Se encontró un pinshi obstaculo
 				*movements = generate_output(FORWARD,Mag_Advance,max_twist);
 				if (obs == 1){
 					*next_state = 5 ;
 				}
 				else{
                    *movements=generate_output(FORWARD,Mag_Advance*2,max_twist);
 					*next_state = 6 ;
 				}
                if(condicion_grados(*grados)==1)
                    *next_state = 8;
 				break;

 		case 3: //Encontre el obstaculo pero necesito pocisionarme
 				*movements=generate_output(LEFT,Mag_Advance,max_twist);
                *grados=*grados-40;
 				if (obs == 1){
 					*next_state = 5 ;
 				}
 				else if (obs>=3){
 					*next_state = 1;
 				}
                if(condicion_grados(*grados)==1)
                    *next_state = 8;
 				break;

 		case 4: //Estoy posicionado
 				*movements = generate_output(LEFT,Mag_Advance,max_twist);
                //*grados=*grados-36;
 				*next_state = 3;
                if(condicion_grados(*grados)==1)
                    *next_state = 8;
 				break;

 		case 6: //Estoy posicionado
 				*movements = generate_output(RIGHT,Mag_Advance,max_twist*1.5);
                *grados = *grados + 54;
 				*next_state = 7;
                if(condicion_grados(*grados)==1)
                    *next_state = 8;
 				break;

 		case 7: //Estoy posicionado
 				*movements=generate_output(FORWARD,Mag_Advance,max_twist);
 				if ( obs == 0){
 					*next_state = 6;
 				}
 				else if (obs == 1){
 					*next_state = 5;
 				}
 				else{
 					*next_state = 1;
 				}
                if(condicion_grados(*grados)==1)
                    *next_state = 8;
 				break;

        case 8:
               *movements = generate_output(STOP,Mag_Advance,max_twist);
               *next_state = 9;
               *grados = 45;
               break;

        case 9:
               *movements = generate_output(LEFT,Mag_Advance,max_twist);
               if (obs != 0){
                *next_state = 9;
               }
               else{
                *next_state = 0;
               }
               break;
                
 }

 printf("Next State: %d\n", *next_state);
 printf("Grados %d\n",*grados);

}



                 
