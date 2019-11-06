#include "mylist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* all yours to code! */

struct node_t {
    char* str;
    struct node_t* prev; 
    struct node_t* next; 
}

void insert(char* str){
    char* str, data;
    struct node_t *newNode;
    /* find where to insert new node
    use strcmp() to determine increasing order*/
    while(strcomp(str,temp))

    if(n >= 1)
    {
        head = (struct node *)malloc(sizeof(struct node));

        if(head != NULL)
        {
            printf("Enter data of 1 node: ");
            scanf("%d", &data);

            head->data = data;
            head->prev = NULL;
            head->next = NULL;

            last = head;

            /*
             * Create rest of the n-1 nodes
             */
            for(i=2; i<=n; i++)
            {
                newNode = (struct node *)malloc(sizeof(struct node));

                if(newNode != NULL)
                {
                    printf("Enter data of %d node: ", i);
                    scanf("%d", &data);

                    newNode->data = data;
                    newNode->prev = last; // Link new node with the previous node
                    newNode->next = NULL;

                    last->next = newNode; // Link previous node with the new node
                    last = newNode;          // Make new node as last/previous node
                }
                else
                {
                    printf("Unable to allocate memory.");
                    break;
                }
            }

            printf("\nDOUBLY LINKED LIST CREATED SUCCESSFULLY\n");
        }
        else
        {
            printf("Unable to allocate memory");
        }
    }
}

void delete(char* str)
{

}

void list(int reverse_order){
    /*print from beginning to end*/
    if(reverse_order==0){
        struct node * temp;
        int n = 1;

        if(head == NULL){
            printf("List is empty.");
        }
        else{
            temp = head;
            printf("\n\nDATA IN THE LIST:\n");

            while(temp != NULL){
                printf("DATA of %d node = %d\n", n, temp->data);
                n++;
                /* Move the current pointer to next node */
                temp = temp->next;
            }
        }
    }

    /*print from end to beginning*/
    else{
        struct node * temp;
        int n = 0;

        if(last == NULL){
            printf("List is empty.");
        }
        else{
            temp = last;
            printf("\n\nDATA IN THE LIST:\n");

            while(temp != NULL){
                printf("DATA of last-%d node = %d\n", n, temp->data);
                n++;
                /* Move the current pointer to previous node */
                temp = temp->prev; 
            }
        }
    }
}
