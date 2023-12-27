#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct gate
{
    char cat[17];
    int *in;
    int *out;
    int *s;
    int numin;
    int numout;

} truthtable;

void Multiplexer(int *values, int numSelectors, int* inputs, int* selectors, int outputIndex){
    int x = 0;
    for (int i = 0; i < numSelectors; i++){
        x += values[selectors[i]] << (numSelectors - i - 1);
    } 
    values[outputIndex] = values[inputs[x]];
}


int increase(int n, int *k){
    for (int i = n + 1; i >= 2; i--)
    {
        k[i] = !k[i];
        if (k[i] == 1) return 1;
    }
    return 0;
}

int get(char *rana, int param, char **a)
{
    for (int i = 0; i < param; i++)
    {
        if (strcmp(a[i], rana) == 0){
            return i;
        }
    }
    return -1;
}

int main(int argc, char** argv) {
    
    FILE *truthfile = fopen(argv[1], "r");
    
    //number of inputs
    int numin = 0;
    //number of outputs
    int numout = 0;
    //size of 
    int size = 2;

    char* my_string = malloc(17 * sizeof(char));

    //mystring = INPUT
    fscanf(truthfile, " %16s", my_string);
    //mystring = number of inputs
    fscanf(truthfile, " %d", &numin);

    //size = number of inputs
    size += numin;

    //for variables in input
    char** variables = malloc(size * sizeof(char *));
    for(int i = 0; i < size; i++) {
        variables[i] = (char*) malloc(17 *sizeof(char)); 
    }

    //creating truthtable rows, the 0 and 1
    //variables[0] = "0"; 
    //variables[1] = "1"; 
    
    strcpy(variables[0], "0\0");
    strcpy(variables[1], "1\0");

    //store the variables in inputvariables
    for (int i = 0; i < numin; i++)
    {
        fscanf(truthfile, " %16s", my_string);
        //variables[i+2] = my_string;
        strcpy(variables[i + 2], my_string);
    }

    //mystring = output
    fscanf(truthfile, " %16s", my_string);
    //numout = size of output
    fscanf(truthfile, "%d", &numout);

    //size = number of inputs + outputs
    size += numout; 

    //reallocte the memory of variables to show new size with inputs and outputs. 
    variables = realloc(variables, size * sizeof(char*));
    for (int i = 0; i < numout; i++) {
        variables[i + 2 + numin] = (char*)malloc(17 * sizeof(char)); 
    }

    //varibles of output
    for (int i = 0; i < numout; i++){
        fscanf(truthfile, " %16s", my_string);
        strcpy(variables[i + 2 + numin], my_string);
    }

    //create a list/arr
    truthtable* list = NULL;
    int count = 0;
    int temp = 0;


    while (feof(truthfile) != 1) {

        truthtable my_gate;
        my_gate.numin = 0;
        my_gate.numout = 0;
        count++;

        fscanf(truthfile, " %16s", my_string); //first gate
        strcpy(my_gate.cat, my_string); //move gate name to my gate

        int a = 2;
        int numout = 1;

        if ((strcmp(my_string, "NOT") == 0) || (strcmp(my_string, "PASS") == 0)){
           a = 1; 
        } 
        else if (strcmp(my_string, "DECODER") == 0)
        {
            fscanf(truthfile, "%d", &a);
            //printf("%d", inC); 
            my_gate.numin = a;
            numout = (int) (pow(2, a) + .5); 
        }
        else if (strcmp(my_string, "MULTIPLEXER") == 0)
        {
            fscanf(truthfile, "%d", &a);
            my_gate.numout = a;
            a = (int)(pow(2,a) + .5); 
        }

        my_gate.in = malloc(a * sizeof(int));
        my_gate.out = malloc(numout * sizeof(int));
        my_gate.s = malloc(my_gate.numout * sizeof(int));

        for (int i = 0; i < a; i++){
            fscanf(truthfile, " %16s", my_string);
            my_gate.in[i] = get(my_string, size, variables);
        }

        for (int i = 0; i < my_gate.numout; i++){
            fscanf(truthfile, " %16s", my_string);
            my_gate.s[i] = get(my_string, size, variables);
        } 

        int i = 0;  

        //indexxing
        while(i < numout){
            fscanf(truthfile, " %16s", my_string);
            int j = get(my_string, size, variables);
            
            if (j != -1){
                my_gate.out[i] = j;
            } 
            else if (j == -1){
                size++;
                temp++;

                variables = realloc(variables, size * sizeof(char *));

                int newsize = size - 1; 
                variables[newsize] = malloc(17 * sizeof(char));
                strcpy(variables[newsize], my_string);
                my_gate.out[i] = newsize;
            }
            i++; 
        }
        i = 0; 
        
        if (!list) {
            list = malloc(sizeof(truthtable));
        }
        else list = realloc(list, count * sizeof(truthtable));        
        list[count - 1] = my_gate;
    }


    int* result = malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        result[i] = 0;
    }
    result[1] = 1;


    while(result[1]){

        for (int i = 0; i < numin; i++){
            printf("%d ", result[i + 2]);  
        }      
        printf("|");

        for (int i = 0; i < count; i++) {
            truthtable g = list[i];
            //switch ?
            //method ?
            //gateoperation(g, values,numin, numout); 

            if (strcmp(g.cat, "NOT") == 0) {
                int o = g.out[0]; 
                int n = g.in[0]; 
                result[o] = !result[n];
            }           
            if (strcmp(g.cat, "AND") == 0) {
                int o = g.out[0]; 
                int n = g.in[0]; 
                int n1 = g.in[1]; 
                result[o] = result[n] && result[n1];
            }
            if (strcmp(g.cat, "OR") == 0){
                int o = g.out[0]; 
                int n = g.in[0]; 
                int n1 = g.in[1]; 
                result[o] = result[n] || result[n1];
            }
            if (strcmp(g.cat, "NAND") == 0){
                int o = g.out[0]; 
                int n = g.in[0]; 
                int n1 = g.in[1]; 
                result[o] = !(result[n] && result[n1]);
            }            
            if (strcmp(g.cat, "NOR") == 0){
                int o = g.out[0]; 
                int n = g.in[0]; 
                int n1 = g.in[1]; 
                result[o] = !(result[n] || result[n1]);
            }            
            if (strcmp(g.cat, "XOR") == 0){
                int o = g.out[0]; 
                int n = g.in[0]; 
                int n1 = g.in[1]; 
                result[o] = result[n] ^ result[n1];
            }
            if (strcmp(g.cat, "PASS") == 0){
                int o = g.out[0]; 
                int n = g.in[0]; 
                result[o] = result[n];
            }
            if (strcmp(g.cat, "DECODER") == 0){
                int x = 0;
                int term = (int)(pow(2,g.numin) + .5); 
                for (int i = 0; i < term; i++){
                    result[g.out[i]] = 0;
                }
                for (int i = 0; i < g.numin; i++){
                    int t = g.numin - i - 1; 
                    x += result[g.in[i]] << t;
                } 
                result[g.out[x]] = 1;
            }
            if (strcmp(g.cat, "MULTIPLEXER") == 0){
                Multiplexer(result, g.numout, g.in, g.s, g.out[0]);
            }
        }

        for (int i = 0; i < numout; i++){
             printf(" %d", result[numin + i + 2]); 
        }       
        printf("\n");
        
        if (!increase(numin,result)){
            break;       
        } 

    }

    free(result);
    free(my_string);

    for (int i = 0; i < count; i++)
    {
        free(list[i].out);
        free(list[i].s);
        free(list[i].in);
    }
    free(list);

    for (int i = 0; i < size; i++)
    {
        free(variables[i]);
    }
    free(variables);
    

    return EXIT_SUCCESS;
}
