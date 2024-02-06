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
/// @param surname node attribute
/// @param email node attribute
/// @param phone node attribute
/// @return new node pointer
struct Address* create_node(char *name, char *surname, char *email, char *phone)
{
    struct Address *address = NULL;
    address = (struct Address*) malloc(sizeof(struct Address));
    if(address == NULL){
        printf("Failed to allocate memory!");
        return NULL;
    }
    
    strcpy(address->name, name);
    strcpy(address->surname, surname);
    strcpy(address->email, email);
    strcpy(address->phone, phone);
    address->next = NULL;

    return address;
}


void print_one_address(struct Address *address, int counter)
{
    printf("%d. %s %s %s %s\n", counter, address->name, address->surname, address->email, address->phone);
}


/// @brief Displays all entries in the address book
/// @param pnt double pointer to the head of linked list
void get_all_nodes(struct Address **pnt)
{
    if (*pnt == NULL){
        printf("\nAddress Book is empty, nothing to print\n");
        return;
    }
    struct Address *tmp = *pnt;
    int counter = 1;
    do {
        print_one_address(tmp, counter);
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
        if(counter == index){
            previous->next = preceding->next;
            free(preceding);
            return;
        }
        previous = previous->next;
        preceding = preceding->next;
        counter++;
    }
}

/// @brief Removes all the nodes from the linked list
/// @param pnt double pointer to the head of linked list
void remove_all_nodes(struct Address **pnt)
{
    if (*pnt == NULL){
        printf("\nNothing to delete\n");
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
        printf("\nAddress Book is empty, cannot find the address\n");
        return;
    }
    struct Address *tmp = *pnt;
    int counter = 1;
    while (tmp != NULL) {
        if(counter == index){
            print_one_address(tmp, counter);
            return;
        }
        tmp = tmp->next;
        counter++;
    } 
}

int check_if_attribute_value_same(struct Address *address, char *attribute, char *value)
{
    if(strcmp(attribute, "name") == 0 && strcmp(address->name, value) == 0){
        return 1;
    }
    if(strcmp(attribute, "surname") == 0 && strcmp(address->surname, value) == 0){
        return 1;
    }
    if(strcmp(attribute, "email") == 0 && strcmp(address->email, value) == 0){
        return 1;
    }
    if(strcmp(attribute, "phone") == 0 && strcmp(address->phone, value) == 0){
        return 1;
    }
    return 0;
}


/// @brief Finds a node the linked list by an attribute
/// @param pnt double pointer to the head of linked list
/// @param attribute by which attribute to find node
/// @param value value of the attribute
void find_node_by_attribute(struct Address **pnt, char *attribute, char *value)
{
    int counter = 1;
    struct Address *tmp = *pnt;
    int flag = 0;
    while (tmp != NULL) {
        if(check_if_attribute_value_same(tmp, attribute, value) == 1){
            if(flag == 0)
                printf("\nAddress found:\n ");
            print_one_address(tmp, counter);
            flag = 1;
        }
        tmp = tmp->next;
        counter++;
    }
    
    if(flag == 0)
        printf("No matches.");    
}




