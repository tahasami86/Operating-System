//#include "util.h"

void memory_copy(char *source, char *dest, int nbytes){

    for (int i=0;i < nbytes; i++){
        *(dest + i) = *(source + i);
    }
}

void int_to_ascii(int n, char str[]) {
    int i,sign;
    if((sign = n) < 0) n= -n;
    
    i=0;
    while(n > 0){
        str[i++] = (n %10) + '0';
        n /=10 ;
    }

    if(sign < 0) str[i++] = '-';
    str[i] = '\0';

    char tmp;
    int j=0;
    while(i > j){
        tmp = str[--i];
        str[i] = str[j];
        str[j] = tmp;
        j++;
    }
}
