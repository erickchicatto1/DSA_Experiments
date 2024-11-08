#include <stdio.h>
#include <stdlib.h>


int main(){

    int freq1=0;
    int freq2=0;
    int freq3=0;
    int freq4=0;
    int freq5=0;
    int freq6=0;

    int tiro; /*Contador de tiros , valores de 1 a 6000*/
    int cara; /*representa un tiro de un lado , valores de 1 a 6*/

    for(tiro = 1 ;tiro <=6000;tiro++){
        
        cara = 1 + rand()%6; /*Va a tener valores aleatorios*/

        switch(cara){
            /*Aqui se tienen todas las caras del dado*/
            case 1:
              ++freq1;
              break;
            case 2:
              ++freq2;
                break;
            case 3:
               ++freq3;
               break;
            case 4:
               ++freq4;
               break; 
            case 5:
               ++freq5;
               break;
            case 6:
               ++freq6;
               break;
        }

    }

    /* despliega los resultados en forma tabular */
 printf( "%s%13s\n", "Cara", "Frecuencia" );
 printf( "   1%13d\n", freq1 );
 printf( "   2%13d\n", freq2 );
 printf( "   3%13d\n", freq3 );
 printf( "   4%13d\n", freq4 );
 printf( "   5%13d\n", freq5 );
 printf( "   6%13d\n", freq6 );


    return 0;
}