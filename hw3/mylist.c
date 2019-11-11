#include "mylist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* all yours to code! */

struct node_t {
    char* str;
    struct node_t* prev; 
    struct node_t* next; 
} *head, *tail;

//struct node_t (*head) = NULL; 
//struct node_t (*tail) = NULL; 

void insert(char* str){
    struct node_t* newNode = (struct node_t*)malloc(sizeof(struct node_t));
    newNode->str = str;
    newNode->next = NULL;
    
    // For first node in DLL
    if(head==NULL){
        head = str;
        tail = str;
        head->prev = NULL;
        return;
    }

    // If node has less value than head
    if(strcmp(newNode->str,head->str) < 0){ 
        newNode->prev = NULL; 
        head->prev = newNode; 
        newNode->next = head; 
        head = newNode; 
        return; 
    } 

    // If node has more value than tail
    if(strcmp(newNode->str,tail->str) > 0){
        newNode->prev = tail; 
        tail->next = newNode; 
        tail = newNode; 
        return; 
    }

    // Find the node before which we need to insert newNode. 
    struct node_t *temp = head->next; 
    while(strcmp(temp->str,newNode->str) < 0)
        temp = temp->next; 
  
    // Insert new node before temp 
    (temp->prev)->next = newNode; 
    newNode->prev = temp->prev; 
    temp->prev = newNode; 
    newNode->next = temp; 
}

void delete(char* str)
{
    struct node_t *temp = head;

    if (head == NULL) 
        return;

    while (temp->next != NULL){
        if (strcmp(temp->str, str) == 0){
            if (temp->prev != NULL){
                temp->prev->next = temp->next;
            }
            if (temp->next != NULL){
                temp->next->prev = temp->prev;
            }
            if (head == temp){
                head = temp->next;
            }
            free(temp);
            return;
        }
        temp = temp->next;
    }
}

void list(int reverse_order){
    /*print from beginning to end*/
    if(reverse_order==0){
        struct node_t *temp = (struct node_t*)malloc(sizeof(struct node_t));
        int n = 1;

        if(head == NULL){
            printf("List is empty.");
        }
        else{
            temp = head;
            printf("\n\nDATA IN THE LIST:\n");

            while(temp != NULL){
                printf("DATA of %d node = %d\n", n, temp->str);
                n++;
                /* Move the current pointer to next node */
                temp = temp->next;
            }
        }
    }

    /*print from end to beginning*/
    else{
        struct node_t *temp = (struct node_t*)malloc(sizeof(struct node_t));
        int n = 0;

        if(tail == NULL){
            printf("List is empty.");
        }
        else{
            temp = tail;
            printf("\n\nDATA IN THE LIST:\n");

            while(temp != NULL){
                printf("DATA of last-%d node = %d\n", n, temp->str);
                n++;
                /* Move the current pointer to previous node */
                temp = temp->prev; 
            }
        }
    }
}
