#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>

#include "CruiseControl.h"


void OneStep(void);

int main(){
   

    //Init the model 
    CruiseControl_initialize();

    while(rtmGetErrorStatus(rtM)== (NULL) && !rtmGetStopRequested(rtM)){
        rt_OneStep();
    }



    return 0;
}


void OneStep(void){

    static bool OverrunFlag = false;

    if(OverrunFlag){
        rtmSetErrorStatus(rtM,"Overrun");
        return;
    }

    OverrunFlag = true;

    CruiseControl_step();

    OverrunFlag = false;

}