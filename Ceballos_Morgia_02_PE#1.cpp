	/* WRITTEN BY: 	CEBALLOS, CRISTIENEIL J. (K-3L)
					MORGIA, MARON CHRISTOFER E. (K-3L)
					
	PROGRAMMING EXERCISE 01 - LINKED LIST IMPLEMENTATION
	A C PROGRAM IMPLEMENTING THE LIST ADT USING LINKED LIST */
	
	// THIS PROGRAM WILL ONLY ACCEPT INTEGER-TYPE DATA
	
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	
	void program_desc();
	void program_header();
	void list_menu(struct node** head);
	void clear_input();
	void continue_add(struct node** head); 
	void continue_delete(struct node** head);
	void exit_program();
	void add_item(struct node** head);
	void delete_item(struct node** head);
	void display_list(struct node* head);
	void delete_list(struct node** head);
	
	// define structure of a node in linked list
	struct node 
	{
	    int data;
	    struct node* next;
	};
	
	// clears input buffer to enhance user interface
	void clear_input() 
	{
	    #ifdef _WIN32
	        system("cls");
	    #else
	        system("clear");
	    #endif
	}
	
	int main()
	{
	    program_desc();
	    
	    // initialized empty linked list
	    struct node* head = NULL;
	
	    // list menu - serves as the main menu of the program
	    list_menu(&head);
	    
	    return 0;
	}
	
	void program_desc() 
	{
	    printf("..............................................................................\n");
	    printf("\n This program implements the Abstract Data Type (ADT) List using linked list.\n");
	    printf("\n This program will only accept integer-type data.\n");
	}
	
	void program_header()
	{
	    printf("\n==============================================================================\n");
	    printf("\n\t\t\t INTEGER LIST MANAGER\n");
	    printf("\n==============================================================================\n");
	}
	
	// function for the program's main menu / list menu
	
	void list_menu(struct node** head) 
	{
	    int user_choice;
	
	    do {
	        program_header();
	        
	        printf("\n\t LIST MENU");
	        printf("\n\t [1] Add Item");
	        printf("\n\t [2] Delete Item");
	        printf("\n\t [3] Display List");
	        printf("\n\t [4] Delete List");
	        printf("\n\t [0] Exit Program");
	
	        printf("\n\n\t Enter Choice: ");
	        while (scanf("%d", &user_choice) != 1 || user_choice < 0 || user_choice > 4) 
			{
	            printf("\n\t !! Invalid input. Please enter your choice: ");
	            while (getchar() != '\n'); // Clear input buffer
        	}
	
	        clear_input();
	
	        switch (user_choice) 
	        {
	            case 1:
	                add_item(head); 
	                break;
	            case 2:
	                delete_item(head);
	                break;
	            case 3:
	                display_list(*head);
	                break;
	            case 4:
	                delete_list(head);
	                break;
	            case 0:
	                exit_program();
	                break;
	            default:
	                printf("\n\t !! Invalid input, please enter a valid option !!\n");
	                break;
	        }
	    } while (user_choice < 0 || user_choice > 4);
	}
	
	// function for the add item feature 
	void add_item(struct node** head) 
{
    int item, position = 0, node_cnt = 0;
    struct node* newnode = (struct node*) malloc(sizeof(struct node)); // allocates memory for new node in a linked list
    int user_choice; // added for input validation

    do {
        program_header();

        printf("\n\t Please enter the item to be added: ");

        // input validation for integer data
        while (scanf("%d", &item) != 1 || user_choice < 0 || user_choice > 3) 
		{
            printf("\n\t !! Invalid input. Please enter an integer value: ");
            while (getchar() != '\n'); // Clear input buffer
        }

        clear_input();
		program_header();
        printf("\n\t WHERE TO ADD THE ITEM?");
        printf("\n\t [1] Start of the list");
        printf("\n\t [2] End of the list");
        printf("\n\t [3] Specific position");
        printf("\n\t [0] Cancel\n");
        printf("\n\t Enter choice: ");
        scanf("%d", &position);

        clear_input();

        // add item based on the user's choice
        switch (position) 
        {
            case 0:
                printf("\n\t Adding number cancelled, going back to list menu...\n");
                list_menu(head);
                return; 
            case 1: 
                newnode->data = item;
                newnode->next = *head;
                *head = newnode;
                printf("\n\t Number %d was added to the start of the list.\n", item);
                break;
            case 2: 
                newnode->data = item;
                newnode->next = NULL;
                
                if (*head == NULL) 
                {
                    *head = newnode;
                } 
                
                else 
                {
                    struct node* current = *head;
                    while (current->next != NULL) 
                    {
                        current = current->next;
                    }
                    current->next = newnode;
                }
                printf("\n\t Number %d was added to the end of the list.\n", item);
                break;
            case 3: 
                {
                    program_header();
                    int specific_pstn;
                    printf("\n\t Enter position to add the number: ");
                    scanf("%d", &specific_pstn);
                    
                    if (*head == NULL) 
                    {
                        // if item added is the first nuber to be added, add in the beginning of list
                        printf("\n\t The list is empty. Adding the number at the beginning.\n");
                        clear_input();
                        
                        newnode->data = item;
                        newnode->next = NULL;
                        *head = newnode;
                        
                        break;
                    }
                    
                    struct node* temp = *head;
                    struct node* prev = NULL;
                    int node_cnt = 1; 
                    
                    while (temp != NULL && node_cnt < specific_pstn) 
                    {
                        prev = temp;
                        temp = temp->next;
                        node_cnt++;
                    }
                    
                    if (node_cnt == specific_pstn) 
                    { 
                        newnode->data = item;
                        newnode->next = temp;
                        
                        if (prev == NULL)
                        {
                            *head = newnode;
                        }
                        else 
                        {
                            prev->next = newnode;
                        }
                        
                        printf("\n\t Number %d was added to position %d.\n", item, specific_pstn);
                    } 
                    
                    else 
                    { 
                        // if position does not exist, add number at the end of list
                        printf("\n\t Position %d does not exist, adding number at the end.\n", specific_pstn);
                        
                        // Traverse the list to the last node
                        struct node* current = *head;
                        while (current->next != NULL) 
                        {
                            current = current->next;
                        }
                
                        current->next = newnode;
                        newnode->data = item;
                        newnode->next = NULL;
                    }
                    
                    break; 
                }

            default:
                printf("\n\t !! Invalid input, please enter a valid option !!\n");
                break;
        }
    } while (position != 1 && position != 2 && position != 3 && position != 0); // Loop until the user chooses to stop adding items

    continue_add(head);
}

	
	void continue_add(struct node** head) 
	{
	    int answer;
	    
	    do
	    {    
	    	program_header();
	    	
	        // ask the user if they want to add more items
	        printf("\n\t Would you like to add more items? \n");
	        printf("\t       [1] Yes\t   [0] No \n");
	        printf("\n\t Enter choice: ");
	        scanf("%d", &answer);
	        
	        clear_input();
	    } while (answer != 0 && answer != 1); // loops until the user chooses to stop adding items
	    
	    if (answer == 1)
	    {
	        add_item(head);
	    }
	    else if (answer == 0)
	    {
	        list_menu(head);
	    }
	}
	
	// funtion in order for the user to delete a specific item in their list
	void delete_item(struct node** head) 
{
    program_header();
    
    struct node* current = *head;
    int node_cnt = 1; 

    // display the current list with the specific item and their positions
    while (current != NULL) 
    {
        printf("\n\t Item position #%d: %d", node_cnt, current->data);
        current = current->next;
        node_cnt++;
    }
    
    // if list is empty
    if (*head == NULL) 
    {
        printf("\n\t Current list is empty, no data available...");
        list_menu(head);
    }

    int item;
    printf("\n\n\t Please enter the number to be deleted: ");
    scanf("%d", &item);

    current = *head;
    struct node* previous = NULL;

    // Traverse the list to find the item
    while (current != NULL && current->data != item) 
    {
        previous = current;
        current = current->next;
        node_cnt++;
    }

    if (current == NULL) 
    {
        printf("\n\t !! Number not found in the list !!\n");
        list_menu(head);
        return;
    }

    // delete the inputted item
    if (previous == NULL) 
    {
        *head = current->next;
    } 
    else 
    {
        previous->next = current->next;
    }

    free(current);

    // displays the updated list with their specific items and their positions after item deletion
    printf("\n\n\t Updated List:\n");
    current = *head;
    node_cnt = 1;
    
    while (current != NULL) 
    {
        printf("\n\t Position %d: %d", node_cnt, current->data);
        current = current->next;
        node_cnt++;
    }

    printf("\n\n\t Number %d has been deleted.\n", item);
    
    continue_delete(head);
}

	void continue_delete(struct node** head) 
	{
    	int choice;
    	do
		{
			// asks user if they want to continue deleting items
		    printf("\n\t Do you want to continue deleting? \n");
	        printf("\t       [1] Yes\t   [0] No \n");
	        printf("\n\t Enter choice: ");
		    scanf("%d", &choice);
		    
		    clear_input();
    
	    if (choice == 1) 
		{
	        delete_item(head);
		} 
		
		else if (choice == 0) 
		{
	        list_menu(head);
		} 
		
		else if (choice != 0 && choice != 1 )
		{
			printf("\n\t !! Invalid input, please enter a valid option !!\n");
		}
	} while (choice != 0 && choice != 1 );
}
	// function in order to display the list
	void display_list(struct node* head) 
	{
    program_header();
    
    struct node* current = head;
    int node_cnt = 0;
    
    while (current != NULL) {
        printf("\n\t Item position #%d: %d", node_cnt + 1, current->data);
        current = current->next;
        node_cnt++;
    }

    if (node_cnt == 0) 
	{
        printf("\n\t The list is empty, no data found...\n");
        list_menu(&head);
    } 
	
	else {
        printf("\n\n\t [0] Back to Main Menu");
        
        int choice;
        
        printf("\n\n\t Enter your choice: ");
        scanf("%d", &choice);
        
        clear_input();

        if (choice == 0) 
		{
            list_menu(&head);
        } 
		
		else 
		{
        	printf("\n\t Invalid input, returning to List Menu...\n");
            clear_input();
            list_menu(&head);
        }
    }
}

	// function in order for the user to delete the entire list
	void delete_list(struct node** head) 
	{
	    program_header();
	    
	    struct node* current = *head;
	    struct node* next;
	
	    // Traverse the list and delete each node
	    while (current != NULL) 
		{
	        next = current->next;
	        free(current);
	        current = next;
	    }
	
	    *head = NULL;
	    printf("\n\t The entire list was deleted.\n");
	    list_menu(head);
	}
	
	// function for when the user want to exit the program
	void exit_program()
	{
	    printf("\n\t You've chosen to exit. Terminating program...\n");
	}

