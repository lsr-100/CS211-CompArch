#include<stdlib.h>
#include<stdio.h>

struct node{
    struct node *right, *left; 
    int data; 
}; 

// A utility function to create a new BST node
//does not work in a createNode file
/*struct node *createNode(int num){
    struct node *x = (struct node *)malloc(sizeof(struct node));
    x->value = num;
    x->l = x->r = NULL;
    return x;
}*/

struct node* search(struct node* current, int data){
    
    //root is null or key is present at root
    if (current == NULL || current->data == data)
       return current;

    // Key is greater than root's key
    if (current->data < data)
       return search(current->right, data);

    // Key is smaller than root's key
    return search(current->left, data);

}

//Insert a new node, given key
struct node* insert(struct node* node, int key){

   if (node == NULL) {
        printf("inserted\n");
        struct node *new_node = (struct node *)malloc(sizeof(struct node));
        new_node->data = key;
        new_node->left = new_node->right = NULL;
        return new_node;
    }

   /* Otherwise, recur down the tree */
    if (key < node->data)
       node->left= insert(node->left, key);
    else if (key > node->data)
       node->right = insert(node->right, key);
    else {
       // free(node); 
        printf("not inserted\n");
    }

   //free(node); 
   return node;
}

struct node * minValueNode(struct node* node){

    struct node* current = node;
    while (current->left!= NULL)
        current = current->left;

    return current;
}

//Delete node given key
struct node* delete(struct node* root, int key){

    if (root == NULL) {
    return root;
    }

    if (key < root->data)
        root->left = delete(root->left, key);

    else if (key > root->data)
        root->right = delete(root->right, key);

    else
    {
        // node with only one child or no child
        if (root->left == NULL)
        {
            struct node *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            struct node *temp = root->left;
            free(root);
            return temp;
        }

        struct node* temp = minValueNode(root->right);
        root->data= temp->data;
        root->right = delete(root->right, temp->data);
        //free(temp); 

    }
    
    return root;
}

void freeStuff(struct node *root){
    if (root != NULL){
        freeStuff(root->left);
        freeStuff(root->right);
        free(root); 
    }
}

int check(char command){

    if(command=='i' || command == 'd' || command == 's' || command == 'p')
        return 1;
    else return 0;

}

//Inorder traversal
void in_order_traversal(struct node *begin){

    if(begin != NULL){
        printf("("); 
        in_order_traversal(begin->left); 
        printf("%d" , begin->data); 
        in_order_traversal(begin->right); 
        printf(")"); 
    }

}

int main(){

    char my_ch ='\0';
    int user_input;
    struct node *root = NULL;


    do {
        scanf("%c", &my_ch);

        if(feof(stdin)){
            freeStuff(root); 
            exit(0); 
        }

        else {

            // printf("ch was scanned\n");
            if(my_ch =='i'){
                scanf("%d",&user_input);
                root = insert(root,user_input);
                //printf("ch was inserted\n"); 
            }

           else if(my_ch =='d'){
                scanf("%d",&user_input);
                    if(search(root,user_input)){
                        root = delete(root,user_input);
                        printf("deleted\n");
                    } 
                    else printf("absent\n");
            
                //free(root); 
            }


           else if(my_ch =='s'){
                scanf("%d",&user_input);
                    if(search(root,user_input)){
                        printf("present\n");
                    }
                    else printf("absent\n");
            }

            else if(my_ch == 'p'){
                in_order_traversal(root);
                printf("\n");
            }


            else {
                return 0; 
            }

        }
       
           // free(root); 
           // printf("newline\n"); 
    } while((getchar()) != EOF); 
    
    free(root); 

    return 0;

    
} 
