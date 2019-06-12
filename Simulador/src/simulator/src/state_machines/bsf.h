/***********************************************
*                                              *
*      bfs.h			                             *
*      Mauricio Hernandez                      *
*      Kevin Meneses                           *
*                                              *
*              Bio-Robotics Laboratory         *
*              UNAM, 2019                      *
*                                              *
*                                              *
************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ros/package.h>


int contador=0;

int queue[250];
int qp=0;
void encolar(int v){queue[qp++] = v;}
void print_queue(){
	printf("\nqueue: ");
    for(int i=0; i < qp; i++)
    {
    	printf(" %d ",queue[i]);
    }
    printf("\n");
}

void bfs_algorithm(int D ,int L)
{
	
  qp=0;
	int menor,flagOnce;
	
	int node_actual = D;
  	encolar(node_actual);
	int flagencolar;
	nodes[node_actual].flag='Y';
	while(node_actual != L)
	{	
		//print_queue();
    contador++;
		//printf("aa  %d \n",nodes[node_actual].num_conections );
		for( int j = 0; j < nodes[node_actual].num_conections; j++)
   		{
   			//printf("** %c** \n",nodes[nodes[node_actual].conections[j].node].flag );
   			if(nodes[nodes[node_actual].conections[j].node].flag == 'N')
   			{
   				//printf("Node actual %d \n",node_actual);
   				nodes[nodes[node_actual].conections[j].node].flag = 'Y';
   				nodes[nodes[node_actual].conections[j].node].parent = nodes[node_actual].num_node;
   				encolar(nodes[node_actual].conections[j].node);
   				nodes[node_actual].flag='Y';
   				//printf("Node actual %d \n",node_actual);
   			}
   		}
      node_actual = queue[contador];
	}
	push(node_actual);
	while(node_actual != -1){
		push(nodes[node_actual].parent);
		node_actual=nodes[node_actual].parent;
	}
	print_stack();
}




int bfs(float rx ,float ry ,float lx ,float ly, char *world_name,step *steps )
{
   //char archivo[]="../data/obstacles/obstacles.top";
    char archivo[150];
   int i;
     int start = 0;
   int goal = 0;
   //"../data/obstacles/obstacles.top";
   std::string paths = ros::package::getPath("simulator");
   strcpy(archivo,paths.c_str());
   strcat(archivo,"/src/data/");
   strcat(archivo,world_name);
   strcat(archivo,"/");
   strcat(archivo,world_name);
   strcat(archivo,".top");


   for(int i=0; i<200; i++)
   {
   		nodes[i].flag='N';
   		nodes[i].num_conections = 0;
   		nodes[i].parent = -1;
   		nodes[i].acumulado = 0;
   }
   num_nodes=read_nodes(archivo);
   //printf("NUmero de nodos #: %d \n",num_nodes);
   for(i = 1; i < num_nodes; i++)
   {
   		if ( sqrt(pow( nodes[i].x - rx ,2) + pow( nodes[i].y - ry ,2)) < sqrt( pow( nodes[start].x - rx ,2) + pow( nodes[start].y - ry ,2)) )
   		{	//	printf("r-n : %d Distancia %f  Node x %f  node y %f   rx %f  ry%f \n",i,sqrt(pow( nodes[i].x - rx ,2) + pow( nodes[i].y - ry ,2)),nodes[i].x,nodes[i].y,rx,ry  );
   			start = i;
   		}
   		if (sqrt(pow( nodes[i].x - lx ,2) + pow( nodes[i].y - ly ,2)) < sqrt(pow( nodes[goal].x - lx ,2) + pow( nodes[goal].y - ly ,2) ) )
   			goal = i;
   }
   //for(int i=0; i<num_nodes; i++)
   //	printNode(i);
  
   //printf("%d %d \n",atoi(argv[1]),atoi(argv[2]) );

   bfs_algorithm(start,goal);

   //printf("Final queue\n");
   //print_queue();

   printf("%d\n", sp);
   int k=0;
    for(int i = sp-2; i >= 0; i--)
    {
    	//printf("%d\n", i);
    	printf(" %d ",stack[i]);
    	steps[k].node = nodes[stack[i]].num_node;
	   	steps[k].x = nodes[stack[i]].x;
	   	steps[k].y = nodes[stack[i]].y;
	   	k++;
    }
    //printf("\n");


	return 0;
} 
