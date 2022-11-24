#include "stdio.h"
#include "stdlib.h"

typedef struct node
{
    int val;
    struct node *next;
} node_t;

void print_list(node_t *head);
void push_end(node_t *head, int val);
void push_beginning(node_t **head, int val);
int pop(node_t **head);
int remove_last(node_t *head);

int 
main()
{
    node_t *head = NULL; // start of list
    head = (node_t*) malloc(sizeof(node_t));
    if (head == NULL) {return 1;}
    
    head->val = 1;
    head->next = (node_t*) malloc(sizeof(node_t));
    head->next->val = 2;
    head->next->next = (node_t*) malloc(sizeof(node_t));
    head->next->next->val = 3;
    head->next->next->next = NULL; // end of list
    
    print_list(head);
    push_end(head, 11);
    push_beginning(&head, 11);
    print_list(head);
    pop(&head);
    print_list(head);
    remove_last(head);
    print_list(head);
}

void 
print_list(node_t *head) 
{
    printf("printing list:\r\n");
    
    // Walking through in list to the end and print each list element's val.
    node_t *curr = head;
    while (curr != NULL) 
    {
        printf("%d\r\n", curr->val);
        curr = curr->next;
    }
}

// push_end operation adds new node to end of list.
void 
push_end(node_t *head, int val)
{
    // Find end of the list element
    node_t *curr = head;
    while(curr->next != NULL)   
    {
        curr = curr->next;
    }
    
    // After finding last element on the list create a new element and set val
    curr->next = (node_t*) malloc(sizeof(node_t));
    curr->next->val = val;
    
    // Set next element's addr to NULL to set end of list.
    curr->next->next = NULL;
}

// push_beginning operation adds new node to start of list.
// Creates new head
void
push_beginning(node_t **head, int val)
{
    // Create new node
    node_t *new_node;
    new_node = (node_t*) malloc(sizeof(node_t));
    
    // Set new node next to current head to make it new head.
    new_node->val = val;
    new_node->next = *head;
    
    // Set head's addr to added new node.   
    *head = new_node;
}

// Pop operation deletes one list element from beginning of list.
// Deletes head of list.
int
pop(node_t **head)
{
    int retval = -1;
    
    // create temp node.
    node_t *next_node = NULL;
    
    // check if head setted.
    if (*head == NULL){return -1;}
    
    // next_node is going to be new head.
    // hold current head's next and val to update later.
    next_node = (*head)->next;
    retval = (*head)->val;
    
    // free mem.
    free(*head);
    
    // update head's addr.
    // old head is deleted and mem. freed.
    // new head is setted as old head's next.
    *head = next_node;
    
    //printf("--%d--\r\n", (*head)->val);
    
    return retval;
}

int
remove_last(node_t *head)
{
    int retval = 0;
    
    // Check for len.
    // If there is only head.
    if (head->next == NULL) {
        retval = head->val;
        free(head);
        return retval;
    }
    
    // find end of the list
    node_t *curr = head;
    while (curr->next->next != NULL) {
        curr = curr->next;
    }
    
    // hold the value of end.
    retval = curr->next->val;
    
    // remove last element of list.
    free(curr->next);
    
    // set end.
    curr->next = NULL;
    return retval;
}