#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linked_list.h"

struct Address
{
    char name[30];
    char surname[30];
    char email[30];
    char phone[30];
    struct Address *next;
};

/// @brief Creates a node from provided attributes
/// @param name attribute 
/// @param surname 
/// @param email 
/// @param phone 
/// @return 
struct Address* create_node(char *name, char *surname, char *email, char *phone)
{
    struct Address *address = NULL;
    address = (struct Address*) malloc(sizeof(struct Address));
    
    strcpy(address->name, name);
    strcpy(address->surname, surname);
    strcpy(address->email, email);
    strcpy(address->phone, phone);
    address->next = NULL;

    return address;
}

/// @brief Displays all entries in the address book
/// @param pnt double pointer to the head of linked list
void get_all_nodes(struct Address **pnt)
{
    if (*pnt == NULL){
        printf("Address Book is empty, cannot print...\n");
        return;
    }
    struct Address *tmp = *pnt;
    int counter = 1;
    do {
        printf("%d. %s %s %s %s\n", counter, tmp->name, tmp->surname, tmp->email, tmp->phone);
        tmp = tmp->next;
        counter++;
    } while (tmp != NULL);
}


/// @brief Adds a node to the end of linked list
/// @param pnt double pointer to the head of linked list
/// @param address node to add
void add_node_to_list(struct Address **pnt, struct Address *address)
{
    if (*pnt == NULL){
        *pnt = address;
        return;
    }
    struct Address *tmp = *pnt;
    
    while (tmp->next != NULL){
        tmp = tmp->next;
    }
    tmp->next = address;
}


/// @brief Adds a node to the linked list in selected position
/// @param pnt double pointer to the head of linked list
/// @param address node to add
/// @param index position in the linked list
void add_node_to_position(struct Address **pnt, struct Address *address, int index)
{
    if (*pnt == NULL){
        *pnt = address;
        return;
    }
    else if(index == 1){
        address->next = *pnt;
        *pnt = address;
        return;
    }
    int counter = 2;
    struct Address *previous = *pnt;
    struct Address *preceding = (*(pnt))->next;
    
    while (preceding != NULL){
        if(counter == index){
            previous->next = address;
            address->next = preceding;
            return;
        }
        previous = previous->next;
        preceding = preceding->next;
        counter++;
    }
    previous->next = address;
}

/// @brief Removes a node from the linked list, selected by position
/// @param pnt double pointer to the head of linked list 
/// @param index position in the linked list
void remove_one_node(struct Address **pnt, int index)
{
    if (*pnt == NULL){
        return;
    }
    else if(index == 1){
        struct Address *tmp = *pnt;
        *pnt = (*(pnt))->next;
        free(tmp);
        return;
    }
    int counter = 2;
    struct Address *previous = *pnt;
    struct Address *preceding = (*(pnt))->next;
    
    while (preceding != NULL){
        previous = previous->next;
        preceding = preceding->next;
        if(counter == index){
            previous->next = preceding->next;
            free(preceding);
            return;
        }
        counter++;
    }
}

/// @brief Removes all the nodes from the linked list
/// @param pnt double pointer to the head of linked list
void remove_all_nodes(struct Address **pnt)
{
    if (*pnt == NULL){
        printf("Nothing to delete\n");
        return;
    }
    struct Address *to_delete = *pnt;
    while (*pnt != NULL){
        *pnt = (*(pnt))->next;
        free(to_delete);
        to_delete = *pnt;
    } 
}

/// @brief Finds a node in the linked list by position
/// @param pnt double pointer to the head of linked list
/// @param index position in the linked list
void find_node_by_position(struct Address **pnt, int index)
{
    if (*pnt == NULL){
        printf("Address Book is empty, cannot find\n");
        return;
    }
    struct Address *tmp = *pnt;
    int counter = 1;
    while (tmp != NULL) {
        if(counter == index){
            printf("%d. %s %s %s %s\n", counter, tmp->name, tmp->surname, tmp->email, tmp->phone);
            return;
        }
        tmp = tmp->next;
        counter++;
    } 
}


/// @brief Finds a node the linked list by an attribute
/// @param pnt double pointer to the head of linked list
/// @param attribute by which attribute to find node
/// @param value value of the attribute
void find_node_by_attribute(struct Address **pnt, char *attribute, char *value)
{
    int counter = 1;
    struct Address *tmp = *pnt;
    struct Address *result = NULL;
    while (tmp != NULL) {
        if(strcmp(attribute, "name") == 0 && strcmp(tmp->name, value) == 0){
            result = tmp;
            break;
        }
        if(strcmp(attribute, "surname") == 0 && strcmp(tmp->surname, value) == 0){
            result = tmp;
            break;
        }
        if(strcmp(attribute, "email") == 0 && strcmp(tmp->email, value) == 0){
            result = tmp;
            break;
        }
        if(strcmp(attribute, "phone") == 0 && strcmp(tmp->phone, value) == 0){
            result = tmp;
            break;
        }
        tmp = tmp->next;
        counter++;
    }
    
    if(result!=NULL)
        printf("%d. %s %s %s %s\n", counter, tmp->name, tmp->surname, tmp->email, tmp->phone);
    else
        printf("\nNo address found\n");
    
}




