#include <stdio.h>
#include <string.h>

void reverseString(char *str);

int main(){

    char TestStr[] = "ERICK";
    reverseString(TestStr);

    return 0;
}



void reverseString(char *str) {

    char *start = str;
    char *end = start + strlen(str)-1; //
    char temp;

    //Reverse
    while(end>start){
        temp = *start;
        *start = *end;
        *end = temp;

        ++start;
        --end;
    }

}