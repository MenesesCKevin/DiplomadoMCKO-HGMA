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
void user_obs(float rx ,float ry, float intensity, float *light_values, float *observations, int size, float laser_value, int  dest, int obs ,
					movement *movements  ,int *next_state ,float Mag_Advance ,float max_twist)
{

 int state = *next_state;
 int i;
 int obstaculo=0;
 float rx_inicial = rx , ry_inicial = ry ;

 printf("intensity %f\n",intensity);
 printf("quantized destination %d\n",dest);
 printf("quantized obs %d\n",obs);

/* for(int i = 0; i < 8; i++)
        printf("light_values[%d] %f\n",i,light_values[i]);
 for (int i = 0; i < size ; i++ ) 
         printf("laser observations[%d] %f\n",i,observations[i]);
*/

 switch ( state ) {

		case 0: //Estado inicial
				*movements=generate_output(FORWARD,Mag_Advance,max_twist);
				if (obs == 0){
					*next_state = 0;
				}
				else{
					*next_state = 1;
				}
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
 				break;

 		case 5: //Se encontró un pinshi obstaculo
 				*movements = generate_output(FORWARD,Mag_Advance,max_twist);
 				if (obs == 1){
 					*next_state = 5 ;
 				}
 				else{
 					*next_state = 6 ;
 				}
 				break;

 		case 3: //Encontre el obstaculo pero necesito pocisionarme
 				*movements=generate_output(LEFT,Mag_Advance,max_twist);
 				if (obs == 1){
 					*next_state = 5 ;
 				}
 				else if (obs==3){
 					*next_state = 1;
 				}
 				break;

 		case 4: //Estoy posicionado
 				*movements = generate_output(LEFT,Mag_Advance,max_twist);
 				*next_state = 3;
 				break;

 		case 6: //Estoy posicionado
 				*movements = generate_output(RIGHT,Mag_Advance,max_twist);
 				*next_state = 7;
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
 				break;



         /*case 0:
                // there is not obstacle
                *movements=generate_output(FORWARD,Mag_Advance,max_twist);
                //printf("Present State: %d FORWARD\n", state);
                *next_state = 0;

                break;

        case 1: // Backward, obstacle in the right
                if(obs == 0 && obstaculo ==0){
                	*next_state = 0;
        		}
        		else{
        			*movements=generate_output(BACKWARD,Mag_Advance,max_twist);
        			if(rx_inicial == rx){
        				 *movements=generate_output(LEFT,Mag_Advance,max_twist);
        				 *movements=generate_output(LEFT,Mag_Advance,max_twist);
        				 *next_state = 0;
        				 obstaculo = 0;
                	}
                	else{
                		*next_state = 2;
                		obstaculo = 1;
                	}
                	 
            	}
                break;

        case 2: // left turn
        				if (obs == 1){
                                // obtacle in the right
                                *next_state = 3;
                        }
                        else if (obs == 2){
                                // obstacle in the left
                                *next_state = 4;
                        }
                        else if (obs == 3){
                                // obstacle in the front
                                *next_state = 1;
                        }
        		
                break;

        case 3: // Backward, obstacle in the left
                *movements=generate_output(LEFT,Mag_Advance,max_twist);
                //printf("Present State: %d BACKWARD, obstacle LEFT\n", state);
                *next_state = 1;
                break;

        case 4: // right turn
                *movements=generate_output(FORWARD,Mag_Advance,max_twist);
                //printf("Present State: %d TURN RIGHT\n", state);
                *next_state = 1;
                break;
        case 5: // Backward, obstacle in front

                *movements=generate_output(LEFT,Mag_Advance,max_twist);
                //printf("Present State: %d BACKWARD, obstacle FRONT\n", state);
                *next_state = 6;
                break;

        case 6: /// Left turn
                *movements=generate_output(LEFT,Mag_Advance,max_twist);
                //printf("Present State: %d TURN 1 LEFT\n", state);
                *next_state = 1;
                break;

        case 7:// Left turn
                *movements=generate_output(LEFT,Mag_Advance,max_twist);
                //printf("Present State: %d TURN 2 LEFT\n", state);
                *next_state = 8;
                break;

        case 8: // Forward
                *movements=generate_output(FORWARD,Mag_Advance,max_twist);
                //printf("Present State: %d 1 FORWARD\n", state);
                *next_state = 9;
                break;

        case 9: // Forward
                *movements=generate_output(FORWARD,Mag_Advance,max_twist);
                //printf("Present State: %d 2 FORWARD\n", state);
                *next_state = 10;
                break;

        case 10: // Right turn
                *movements=generate_output(RIGHT,Mag_Advance,max_twist);
                //printf("Present State: %d TURN 1 RIGHT\n", state);
                *next_state = 11;
                break;

        case 11: // Right turn
                *movements=generate_output(RIGHT,Mag_Advance,max_twist);
                //printf("Present State: %d TURN 2 RIGHT\n", state);
                *next_state = 0;
                break;

        */
                
 }

 printf("Next State: %d\n", *next_state);


}



                 
