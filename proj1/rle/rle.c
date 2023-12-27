#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <ctype.h>

//ADD TEST CASES
char* run_length_encoding(int string_length,char* my_string,char* string){

  char *check_string = my_string;
  
  for(int i=0; i < string_length; i++) {   
      int counter = 1;   

      while (i < string_length - 1 && string[i] == string[i+1]) {
        counter++;
        i++;
      } 

    char temp2 = string[i];
    check_string += sprintf(check_string, "%c%d", temp2, counter);
    
  }


  return my_string;
}

    int main(int argc, char* argv[]){

      char *string = argv[1]; 
    
      //edge case -- argument less than 1
      if(strlen(argv[1]) < 1){
        return 0; 
      }

      //edge cases -- check for digits
      for(int b = 0; b < string[b]; b++){
        if(isdigit(string[b])){
          printf("error\n"); 
          return 0; 
        }
      }

      int string_length = strlen(argv[1]); 

      //memory allocated remeber to free
      char *my_string = (char*)malloc(sizeof(char)*(string_length*2+1));

      my_string = run_length_encoding(string_length,my_string,string);

      //edge case -- which string is bigger
      if(strlen(my_string) > strlen(string)){
        my_string = string;
        printf("%s\n", my_string); 
        return 0; 
      }

      printf("%s\n", my_string); 

      //free memory
      free(my_string);
      
      return 0;

    }




