#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <stdint.h>

// create a struct to represent the node in linked list
typedef struct node{
    int data; 
    struct node *next; 
}Node; 


int check(Node *head, int key){
    Node *curr = head; 

    while(curr != NULL){
        if(curr-> data == key)
            return 1; 
        curr = curr->next; 
    }
    return 0; 
}


Node* insert(Node *head, int key){
    
    if(check(head,key) == 1) {
        return head;
    }

    //memory allocated remeber to free 
    Node *node = (Node*)malloc(sizeof(Node)); 

    if(node != NULL){  

        node->data = key;
        node->next = NULL;
        
        if(head == NULL)
            head = node;  

        else{
            Node *curr = head;
            Node *prev = NULL;

            while(curr != NULL){  // loop to insert n in correct position

                if(curr->data > node->data){  // if curr's data > n,insert it before curr

                    if(prev == NULL){
                        node->next = head;
                        head = node;
                    }

                    else{
                        node->next = curr;
                        prev->next = node;
                    }

                    //free(head);
                    return head;
                }

                prev = curr;
                curr = curr->next;
            }
                prev->next = node; // insert n at end
        }
    }
    
    return head;
    

}

// delete key from list
Node* delete(Node* head, int key){

    if(head != NULL){ 
                                        
        if(head->data == key){
            Node *temp = head;
            head = head->next;
            free(temp); 
        }

        else{
            Node *curr = head;
            Node *prev = NULL;
            while(curr != NULL){     
                if(curr->data == key){
                        prev->next = curr->next;
                        free(curr);
                        return head;
                }
                        prev = curr;
                        curr = curr->next;
            }
        }
    }

    return head;
}

//Count in list
int count_list(Node* head){
    int count = 0;
    Node *curr = head;
    
    while(curr != NULL){   
        count++;
        curr = curr->next;
        //free(curr); 
    }
    free(curr); 
    return count;
}

//Delete List
void deleteList(Node *head){
    Node *curr;

    while(head != NULL){
        curr = head;
        head = head->next;
        free(curr);
    }

}

//Print list
void print(Node *head){
    Node *curr = head;

    while(curr != NULL){     
        printf(" %d",curr->data);
        curr = curr->next;
    }

}

//function to perform specified commands on linked list
Node* do_stuff(Node *head, char command, int data) {
    
    if((tolower(command) != 'i') && (tolower(command) != 'd')) { // check if command is not valid, then exit from loop
        //printf("hey i entered"); 
        return NULL;
    }

    if(tolower(command) == 'i')  // insert data in linked list
    {
        return insert(head,data);
    }

    else // delete data from linked list
        return delete(head,data);
}

// function to print linked list after each update

void iterate(Node *head) {
    printf("%d :",count_list(head));
    print(head); 
    printf("\n");
}

int main(int argc, char** argv) {
            
     Node *head = NULL; 

    if(argc == 2) {
       char ch[INT16_MAX]; //i and d 
       char num[INT16_MAX]; //number that comes after I input i or d
       char a[INT16_MAX]; 
       int new_input;

        FILE *list1;
        list1 = fopen(argv[1], "r");
        
        while(scanf(a, "%s %s \n",ch, num) > 1)
        {
            //sscanf(line, "%s %s \n",command, data);
            new_input = atoi(num);
            head = do_stuff(head, ch[0], new_input);
            iterate(head);
        }
       
        fclose(list1); 
        
    }

   else 
    {
        int num;
        char ch;

        while(fscanf(stdin," %c %d",&ch,&num) != EOF){
            //printf("%c\n", command); 
            //scanf(" %c %d",&command,&data); 
            head = do_stuff(head, ch, num);
            iterate(head);
        }

        deleteList(head); 
    }
     
    return EXIT_SUCCESS;
}
