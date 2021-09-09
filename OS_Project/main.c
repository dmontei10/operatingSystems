
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <math.h>

// Variavel Global para as opcoes
 int opcaoPonto=0;
 int opcaoThreas=0;
 // Variavel Global para que vai servir de parametro para divisao,guarda o numero depontos
 int quantidadesPontos=0;
 double pi=0;
 
//ponto x
double coordenada_x=0.0;
//ponto y
double coordenada_y=0.0;
double soma=0.0;	
int count=0;
//variavel que ira acumular o nr de pontos gerados dentro do circulo  
double circulo=0.0;
//variavel que ira acumular o nr de pontos gerados dentro do quadrado
double quadrado=0.0;


// o menu para as threads
int menuThreads(){
    
    
    printf("\t\tEscolhe o numero de Threads\n");
    printf("\t 2-Threads\n");
    printf("\t 4-Threads\n");
    printf("\t 6-Threads\n");
    printf("\t 8-Threads\n");
    
    
     printf("\tEscolheThreads:");
   
    scanf("%d",&opcaoThreas);
    
    printf("\n");
    
    
    
     switch(opcaoThreas){
        case 2:
            
            
            return opcaoThreas=2;
            
            
        case 4:
            
           
             return opcaoThreas=4;
             
        case 6:
           
            
            return opcaoThreas=6;
            
        case 8:
          
           
            return opcaoThreas=8;
            
        default:
            return 0;
            
    }
     
    
}
///menu que recebe os arrays de pontos
  int menu( int pontos[]){
     
    
       printf("\n");
     
 
    printf("\t\tEscolhe o numero de ponros\n");
    printf("\tse deseja 20000 pontos escolhe a opcao 2\n");
    printf("\tse deseja 100000 pontos escolhe a opcao 4\n");
    printf("\tse deseja 1000000 pontos escolhe a opcao 6\n");
    printf("\tse deseja 10000000 pontos escolhe a opcao 8\n");
     
    
    printf("\tEscolhe:");
   
    scanf("%d",&opcaoPonto);
    
    printf("\n");
    
    
    
    switch(opcaoPonto){
        case 2:
            quantidadesPontos=pontos[0];
            
            return pontos[0];
            
            
        case 4:
            quantidadesPontos=pontos[1];
           
             return pontos[1];
             
        case 6:
            quantidadesPontos=pontos[2];
            
            return pontos[2];
            
        case 8:
            quantidadesPontos=pontos[3];
           
            return pontos[3];
            
        default:
            return 0;
            
    }
    
    
			
   }
  
  
  
  //====================================================================================================================
  double coordenadas( double x,double y){
       double coordenada=sqrt(( x * x ) + (y * y));
       return coordenada;
       
       
      
      
  }
 
  
  void *algoritmoMonteCarlo(void *ponto){
      
   //bibliografia http://www.davidrobles.net/blog/2014/06/22/estimating-pi-using-monte-carlo-simulations/   
      //https://www.thegeekstuff.com/2012/04/create-threads-in-linux/
      
    

	// nr de pontos a gerar pela thread
	int numPontos=*((int*) ponto);

	//escreve no ecra o id da thread que esta a executar
	

	//ciclo que ira gerar o nr de pontos 
	for(;count<numPontos;count++){
		
		//gera coordenadas aleatorias para os pontos x e y entre -1 e 1 
		coordenada_x =(rand()/(double)RAND_MAX);
                
		coordenada_y =(rand()/(double)RAND_MAX);

                
                //distancia varial que recebe os valores da funcao coordenadas com os argumentos x e y
               
               double distancia= coordenadas (coordenada_x,coordenada_y);
                

		//contabiliza sempre o nr de pontos no quadrado por cada passagem 
		quadrado ++;
		
		// funcao contabiliza o nr de pontos gerados dentro do circulo quando satisfaz a equacao x^2+y^2<=1
		if (distancia <=1){
			
		circulo++;
                //calcaular o valor de pi conforme a formula
                pi=4*(circulo)/quadrado;
			
			
		
		} 
                //actualiza o valor de pi de acordo com a formula

	
	}
	
	//imprime para o ecra o nr de pontos gerado por cada thread
         printf("ID da thread em  execucao :[%d],\fpontos gerados:[%d]\n",pthread_self(),count);
       

	//termina a execucao da thread
	pthread_exit(NULL);
	
}
  
  
 
  //========================================================================================================================

  //divide as tarefas de gerar pontos pelo nr de threads que o utilizador escolher
  
  int divPontos(int pontos,int opcao){
      pontos=(pontos/opcao);
      return pontos;
      
  }
  
  void threads(){
      //tarefa  recebe os dados retornados pela a funacao Menu
      int tarefa=menuThreads();
      
      
       int  p=divPontos(quantidadesPontos,tarefa);
       
       
       
       

		//id para a primeira possicao da thread
		pthread_t id[tarefa];
               
		//for que percorre o numero de tarefas threads
		for (int i =1;i<=tarefa;i++){

			//cria a thread que vai executar a funcao monte_carlo em que passa para esta o argumento nr_pontos
			pthread_create(&id[i],NULL,&algoritmoMonteCarlo,&p);
		

		}
		
		
		
                for (int i =1;i<=tarefa;i++){

			
			pthread_join(id[i],NULL);//retorna 0 se tiver sucesso
		}

                
		
                
                 //imprime o valor final do PI para o ecra
	          printf("O valor de Ip:%f \n",pi);
            
  
  }
  
 
  void tempo(){
       clock_t timer;//criar uma variavel do tipo clock_t
       timer=clock();//atribuindo a funcao clock() a variavel timer
       
       threads();
       timer=clock()-timer;
       
       printf("\n");
       printf("\t-------------------Tempo------------------------");
     
       
        printf("\n\t\t{%f} segundo(s) de execucao\n\n",((float)timer)/CLOCKS_PER_SEC);
      
  }
  
  

int main() {
   
    //araray com os pontos
    int pontos[4] ={20000,100000,1000000,10000000};
   
  
         int escolhas=menu(pontos);
         
         tempo();
              
    return 0;
}
//David Monteiro
//Zaissov Adao
