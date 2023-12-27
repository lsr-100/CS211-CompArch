#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]){
   
    int count = 0;

    //count variable for the number of arguments in argv[1]; 
    for(int i = 0; argv[1][i]!='\0'; i++){
        count++;
    }

    //no inputs 
    if(argv[1]==NULL|| count == 0){
        EXIT_FAILURE; 
    }

    char* stack_array = malloc(count*sizeof(char));
    int head = 0;

    char* string = argv[1]; 

    for(int i = 0; i < count; i++){
        
        
        
        //add to array 
        if(string[i] =='(' || string[i] =='[' || string[i] =='{'){
            stack_array[head] = string[i];
            head++;
        }

        //check for )
        if(string[i]==')'){
            if(head == 0){
                printf("%d: %c\n",i,string[i]);
                exit(1);
            }
            
            else{
                if(stack_array[head-1]=='('){
                    head--;
                    continue;
                }
                else{
                    printf("%d: %c\n",i,string[i]);
                    exit(1);
                }
            }
        }
        
        //check for }
        if(string[i]=='}'){
            if(head == 0){
                printf("%d: %c\n", i, string[i]);
                exit(1);
            }
            else{
                if(stack_array[head-1]=='{'){
                    head--;
                    continue;
                }
                else{
                    printf("%d: %c\n",i, string[i]);
                    exit(1);
                }
            }
        }

        //check for ]
        if(string[i]==']'){
            if(head==0){
                printf("%d: %c\n", i, string[i]);
                exit(1);
            }
            else{
                if(stack_array[head-1]=='['){
                    head--;
                    continue;
                }
                else{
                    printf("%d: %c\n",i,string[i]);
                    exit(1);
                }
            }
        }

    }



    //cases where open is to be printed
    if(head != 0){
        //printf("loop entered"); 
        printf("open: ");
        for(int j = head -1 ; j >= 0 ;j--){

            //check each indiv case
            if(stack_array[j]=='{'){
                //printf("loop with { entered");
                printf("%c",'}');
            }

            if(stack_array[j]=='['){
                //printf("loop with [ entered");
                printf("%c",']');
            }

             if(stack_array[j]=='('){
                //printf("loop with ( entered");
                printf("%c",')');
            }
        }
        exit(1);

    }

    else{   
        exit(0);
    }

    //free malloc
    free(stack_array);

}
