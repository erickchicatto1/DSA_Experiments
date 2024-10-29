//To do : Try to use this code in the stm32 logic

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

enum status {CONTINUE,WON,LOST};
int rollDice(void);

int main(void){

    int sum;
    int myPoint;

    enum Status gameStatus;

    /*randomize random number generator using current time*/
    srand(time(NULL));
    sum = rollDice();

    /*determine game status */
    switch(sum) {

        case 7:
        case 11:
          gameStatus = WON;
          break;
        case 2:
        case 3:
        case 12:
          gameStatus = LOST;
        default:
          gameStatus = CONTINUE;
          myPoint = sum;
          printf("Point is %d \n",myPoint);
          break;
    }

    while(gameStatus == CONTINUE){
        sum = rollDice(); 

        /* Determine game status */
        if(sum ==myPoint){
            gameStatus = WON;
        }else{
            if(sum==7){
                gameStatus = LOST;
            }
        }
    }

    /*Display won or lost message */
    if(gameStatus == WON){
        printf("Player wins \n");
    }
    else{
        printf("Player loses \n");
    }
    return 0;
}


int rollDice(void){

int die1;  // First die
int die2; //second die
int worksum; //sum of dice

die1 = 1 + ((rand()%6));
die2 = 1 + ((rand()%6));

worksum = die1 + die2;
printf("Player rolled %d + %d = %d \n",die1,die2,worksum);

return worksum;
}