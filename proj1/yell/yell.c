#include <stdio.h>
#include <ctype.h>


int main(int argc, char *argv[]){
  
    int count = 0; 

    for (int a= 1; a < argc; a++) {
       
        char *string = argv[a];
        for (int i = 0; i < string[i]; i++) {
            string[i] = toupper(string[i]);
            count++; 
            printf("%c", string[i]);
        }
    }

    if (count < 1){
        return 0; 
    }

    if(argc > 1){
        printf("!!");
        printf("\n");  
    }
    
    return 0;

}

