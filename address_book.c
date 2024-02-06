#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linked_list.h"
#include <signal.h>
#define DELIMETER ","
#define FILENAME "/addresses.csv"
#define MAX 30

struct Address *pnt = NULL;
char *filepath = NULL;

struct Address
{
    char name[MAX];
    char surname[MAX];
    char email[MAX];
    char phone[MAX];
    struct Address *next;
};

/// @brief Method to flush standard input
void flushInput()
{
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}

/// @brief Method to prompt user and receive input as int
/// @return int user entered
int receive_int_from_user()
{
    char *p, s[100]="";
    int selected_option;
    while (fgets(s, sizeof(s), stdin)) {
        selected_option = strtol(s, &p, 10);
        if (p == s || *p != '\n') {
            printf("Invalid input! \n");
        } else return selected_option;
    }
}

/// @brief Method to prompt user and receive input as a char array
/// @return string user entered
char* receive_string_from_user()
{
    char str[30]="";
    while(1==1){
        fgets(str, MAX, stdin);
        if( strlen(str) != 1){
            if(strlen(str) >= MAX-1){
                flushInput();
            }
            str[strcspn(str, "\n")] = 0;
            char *ptr = str;
            return ptr;
        }
        printf("Input cannot be empty\n");
    }
}

/// @brief Method to prompt user and receive input as a struct attribute
/// @return string user entered
char *receive_attribute_from_user()
{
    printf("\nBy which attribute you want to search the address book? (name, surname, email, phone)\n");
    while(1==1){
        char *attribute = receive_string_from_user();
        if(strcmp(attribute, "name") == 0 || strcmp(attribute, "surname") == 0 || 
           strcmp(attribute, "email") == 0 || strcmp(attribute, "phone") == 0){
            return attribute; 
        }
        printf("Wrong attribute (%s), try again", attribute);
    }
}

/// @brief Method to prompt user and receive input as char array
/// @return string user entered
char *receive_attribute_value_from_user(){
    printf("Attribute value: \n");
    char *attribute = receive_string_from_user();
}


/// @brief Method to add all the addresses from a csv file, create a node for each entry and add them to the linked list
///  @param csv_dir - file path to the csv file 
///  @param pnt - double pointer to the head of linked list

void populate_book(char csv_dir[], struct Address **pnt)
{
    FILE *file = NULL;
    file = fopen(csv_dir, "r");

    if (file == NULL){
        printf("Error while openning the csv file %s", csv_dir);
        return;
    }

    char line[150];
    while (fgets(line, sizeof(line), file)) {
        struct Address *address = NULL;
        if(strcmp(line, "\n") == 0) {
            continue;					
        }
        
        char *name = strtok(line, DELIMETER);
        char *surname = strtok(NULL, DELIMETER);
        char *email = strtok(NULL, DELIMETER);
        char *phone = strtok(NULL, DELIMETER);
        address = create_node(name, surname, email, phone);
	    if (address != NULL) {
            add_node_to_list(pnt, address);
        }
    }
    fclose(file);
}

/// @brief Method to display new address entry menu, check inputs and add to linked list 
/// @param pnt double pointer to the head of linked list
/// @param placement to determine where to put new entry
void menu_item_add_new_address(struct Address **pnt, char placement[])
{
    char name[MAX]="", surname[MAX]="", email[MAX]="", phone[MAX]="";
    char *name_p=NULL, *surname_p=NULL, *email_p=NULL, *phone_p = NULL;
    name_p = &name[0];
    surname_p = &surname[0];
    email_p = &email[0];
    phone_p = &phone[0];

    printf("\nType in the name: ");
    strcpy( name_p, receive_string_from_user());
    printf("\nType in the surname: ");
    strcpy(surname_p, receive_string_from_user());
    printf("\nType in the email: ");
    strcpy(email_p, receive_string_from_user());
    printf("\nType in the phone: ");
    strcpy(phone_p, receive_string_from_user());
    struct Address *new_address = create_node(name_p, surname_p, email_p, phone_p);

    if(strcmp(placement, "to_the_end") == 0){
        add_node_to_list(pnt, new_address);
    }
    else if(strcmp(placement, "by_position") == 0){
        printf("Enter a position where to insert new entry:");
        int index_to_insert = receive_int_from_user();
        add_node_to_position(pnt, new_address, index_to_insert);
    }

}

/// @brief Creates a menu and manages interactions from user
/// @param pnt double pointer to the head of linked list
void create_menu(struct Address **pnt)
{
    while(1==1){
        printf("\nSelect an option:\n");
        printf("1. View all addresses.\n");
        printf("2. Add new address.\n");
        printf("3. Add new address to position.\n");
        printf("4. Delete an address at position.\n");
        printf("5. Delete all addresses.\n");
        printf("6. Find address by position.\n");
        printf("7. Find address by attribute.\n");
        printf("8. Exit the program.\n");
        
        int selected_option = receive_int_from_user();
        switch(selected_option){
        case 1: //View all addresses
            get_all_nodes(pnt);
            break;
        case 2: //Add new address
            menu_item_add_new_address(pnt, "to_the_end");
            break;
        case 3: //Add new address to position
            menu_item_add_new_address(pnt, "by_position");
            break;
        case 4: //Delete an address at position
            printf("\nEnter index of an address you want to delete: ");
            int index_to_delete = receive_int_from_user();
            remove_one_node(pnt, index_to_delete);
            break;
        case 5: //Delete all addresses
            remove_all_nodes(pnt);
            printf("\nAll addresses removed succesfully.\n");
            break;
        case 6: //Find address by positon
            printf("\nEnter index of an address you want to find: ");
            int index_to_find = receive_int_from_user();
            find_node_by_position(pnt, index_to_find);
            break;
        case 7: //Find address by attribute
            char attribute[MAX], value[MAX];
            strcpy(&attribute[0], (receive_attribute_from_user()));
            strcpy(&value[0], (receive_attribute_value_from_user()));
            find_node_by_attribute(pnt, &attribute[0], &value[0]);
            break;
        case 8: //Exit the program
            return;
        default:
            printf("Invalid option selected\n");
            break;
        }
    }
}

void sigint_handler(int signum)
{
    if (pnt != NULL){
        remove_all_nodes(&pnt);
    }
    exit(0);
}


/// @brief Entry point of the program
int main(void)
{
    signal(SIGINT,sigint_handler);
    signal(SIGQUIT,sigint_handler);
    char *home_dir = getenv("HOME");
    filepath = malloc(strlen(home_dir) + strlen(FILENAME) + 1);
    strncpy(filepath, home_dir, strlen(home_dir) + 1);
    strncat(filepath, FILENAME, strlen(FILENAME) + 1);
    

    populate_book(filepath, &pnt);
    if( filepath != NULL) free(filepath);

    create_menu(&pnt);
    if(pnt != NULL) remove_all_nodes(&pnt);

    return 0;
}