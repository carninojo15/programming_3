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

void insert(char* str){
    struct node_t* newNode = (struct node_t*)malloc(sizeof(struct node_t));
    newNode->str = (char*)malloc((strlen(str)+1)*sizeof(char));
    strcpy(newNode->str,str);
    newNode->next = NULL;
    
    // For first node in DLL
    if(head==NULL){
        head = newNode;
        tail = newNode;
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

void delete(char* str){
    struct node_t *temp = head;  
    // If DLL is empty.
    if (head == NULL){ 
        printf("Null list. Please insert elements.\n");
        return;
    }
    // Find the node that is to be deleted.
    while(strcmp(temp->str,str) != 0){
        if(temp == NULL){
            printf("This node does not exist.\n");
            return;
        }
        temp = temp->next;
    }
    // If there is only one element in DLL
    if(temp == head && head == tail){
        head = NULL;
        tail = NULL;
        printf("List is now empty\n");
        return;
    }
    // If we are deleting head node
    if(temp == head){
        head = temp->next;
        printf("Head node deleted.\n");
        return;
    }
    if(temp->next != NULL)
        temp->next->prev = temp->prev;
    if(temp->prev != NULL)
        temp->prev->next = temp->next; 
}

void list(int reverse_order){
    int node_num = 1;
    /*print from beginning to end*/
    if(reverse_order==0){
        struct node_t *temp = (struct node_t*)malloc(sizeof(struct node_t));
        if(head == NULL){
            printf("List is empty.");
        }
        else{
            temp = head;
            while(temp != NULL){
                printf("Contents of node %d = %s\n", node_num, temp->str);
                node_num++;
                // To next node
                temp = temp->next;
            }
        }
    }

    /*print from end to beginning*/
    else{
        struct node_t *temp = (struct node_t*)malloc(sizeof(struct node_t));
        if(tail == NULL){
            printf("List is empty.");
        }
        else{
            temp = tail;

            while(temp != NULL){
                printf("Contents of node -%d = %s\n", node_num, temp->str);
                node_num++;
                // To next node
                temp = temp->prev; 
            }
        }
    }
}
