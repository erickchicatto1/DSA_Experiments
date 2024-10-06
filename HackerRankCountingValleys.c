#include <stdio.h>


int CountingValley(int steps,char *path);

int main(){

    int steps = 8;
    char path[]="UDDDUDUU";

    int valleys = CountingValley(steps, path);
    
    printf("Number of valleys : %d \n",valleys);

return 0;
}



int CountingValley(int steps,char *path){

    int valleys = 0;
    int altitude = 0;

    for(int i=0;path[i] != '\0';i++){

        char step = path[i]; // To access to the element

        if(step == 'U'){
            altitude++;

            if(altitude==0){
                valleys++;
            }

        }

        else if(step=='D'){
            altitude--;
        }


    }


    return valleys;

}