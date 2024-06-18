/* WRITTEN BY: 	CEBALLOS, CRISTIENEIL J. (K-3L)
					MORGIA, MARON CHRISTOFER E. (K-3L)
					
	PROGRAMMING EXERCISE 02 - STACK IMPLEMENTATION
	A C PROGRAM WITH STACK IMPLEMENTATION AND STACK APPLICATION */
	
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <ctype.h>
	#define MAX_SIZE 20
	
	struct Node* create_node(char *data);
	struct Stack* create_stack();
	int isEMPTY(struct Stack* stack);
	int isFULL(struct Stack* stack);
	void PUSH(struct Stack* stack, char *data);
	char* POP(struct Stack* stack);
	char* TOP(struct Stack* stack);
	void MAKENULL(struct Stack* stack);
	void clear_input();
	void program_desc();
	void program_header();
	void add_dishes(struct Stack* stack);
	void continue_add(struct Stack* store_kitchenware);
	void wash_dishes(struct Stack* stack);
	void continue_wash(struct Stack* stack);
	void top_dish(struct Stack* stack);
	void wash_all(struct Stack* stack);
	void display_stack(struct Stack* stack);
	void exit_process();
	
	// struct for node to represent elements in the stack
	struct Node 
	{
	    char data[100];
	    struct Node* next;
	};
	
	// stack structure to manage the stack
	struct Stack 
	{
	    struct Node* top;
	};
	
	// function to create a new node
	struct Node* create_node(char *data) 
	{
	    struct Node* newNode = (struct Node*) malloc (sizeof(struct Node));
	    if (newNode == NULL) 
		{
	        printf("\n\t memory allocation failed...\n");
	        exit(1);
	    }
	    
	    strcpy(newNode -> data, data); // copy the string data to the new node
	    newNode -> next = NULL; // initialize next pointer to NULL
	    return newNode;
	}
	
	// function to create a new stack and initialize it
	struct Stack* create_stack() 
	{
	    struct Stack* stack = (struct Stack*) malloc (sizeof(struct Stack));
	    if (stack == NULL) 
		{
	        printf("\n\t memory allocation failed...\n");
	        exit(1);
	    }
	    
	    stack->top = NULL; // initialize the top pointer to NULL (empty stack)
	    return stack;
	}
	
	// function to check if the stack is EMPTY
	int isEMPTY(struct Stack* stack) 
	{
	    return !stack->top; // returns 1 if the stack is empty, otherwise returns 0
	}
	
	// function to check if the stack is FULL 
	int isFULL(struct Stack* stack) 
{
    int count = 0;
    struct Node* current = stack->top;
    
	while (current != NULL) 
	{
        count++;
        current = current->next;
    }
    
    if (count >= MAX_SIZE) 
	{
        return 1; // returns 1 if stack is full
    } 
	
	else 
	{
        return 0; // returns 0 if stack is not full
    }
}
	
	// function to push a string (kitchenware) onto the stack
	void PUSH(struct Stack* stack, char *data) 
	{
	    struct Node* dish_node = create_node(data); 
	    dish_node -> next = stack->top; 
	    stack -> top = dish_node; // update the top pointer to the new node (node for kitchenwares)
	}
	
	// function to remove a string (kitchenware) from the stack - means the dish is already washed
	char* POP(struct Stack* stack) 
	{
	    if (isEMPTY(stack)) // checks if stack is empty
	    {
	        return NULL; // Return NULL to indicate failure to pop from empty stack
	    }
	    
	    struct Node* temp = stack->top;
	    stack->top = temp->next; // move top pointer to the next node
	    char* dish_washed = strdup(temp->data); // copy the string to be popped from the top of the stack
	    free(temp); // free the memory of the popped node
	    return dish_washed; // return the popped string; dish washed - kitchenware that is washed (so it is then removed from the stack)
	}
	
	char* TOP(struct Stack* stack) 
	{
	    if (isEMPTY(stack)) // checks if stack is empty
	    {
	        return NULL;
	    }
	    
	    else 
	    {
	        // allocate memory for the copy of top element
	        char* top_data = (char*) malloc (sizeof(char) * 100);
	
	        // copy the top element data to the allocated memory
	        strcpy(top_data, stack->top->data);
	
	        return top_data; // return the copy of the top element
	    }   
	}
	
	// function to empty the stack / for the user to wash all the dishes
	void MAKENULL(struct Stack* stack) 
	{
    	while (!isEMPTY(stack)) 
		{
        	POP(stack);
    	}
	}

	// function to clear input buffer to enhance user interface
	void clear_input() 
	{
	    #ifdef _WIN32
	        system("cls");
	    #else
	        system("clear");
	    #endif
	}
	
	// MAIN MENU - KITCHENWARE WASHING MACHINE OPTIONS
	int main() 
	{
	    struct Stack* store_kitchenware = create_stack();
	    program_desc();
	
	    int user_choice;
	    do {
	    	program_header();
	        printf("\n\t Ready to delegate dish duty to your trusty dishwasher?");
	        printf("\n\t [1] Add kitchenware (ex. place, bowls, etc.)");
	        printf("\n\t [2] Wash kitchenware");
	        printf("\n\t [3] Top kitchenware");
	        printf("\n\t [4] Wash all");
	        printf("\n\t [5] Display stack of dishes");
	        printf("\n\t [0] Exit process");
	
	        printf("\n\n\t Enter Choice: ");
	        while (scanf("%d", &user_choice) != 1 || user_choice < 0 || user_choice > 5) 
	        {
	            printf("\n\t !! Invalid input. Please enter your choice: ");
	            while (getchar() != '\n'); // Clear input buffer
	        }
	
	        clear_input();
	
	        switch (user_choice) 
	        {
	            case 1:
	                add_dishes(store_kitchenware);
	                break;
	            case 2:
	                wash_dishes(store_kitchenware);
	                break;
	            case 3:
	                top_dish(store_kitchenware);
	                break;
	            case 4:
	                wash_all(store_kitchenware);
	                break;
	            case 5:
	                display_stack(store_kitchenware);
	                break;
	            case 0:
	                exit_process();
	                break;
	            default:
	                printf("\n\t !! Invalid input, please enter a valid option !!\n");
	                break;
	        }
	    } while (user_choice != 0);
	
	    return 0;
	}
	
	// function for program description
	void program_desc() 
	{
	    printf("..............................................................................\n");
	    printf("\n This program makes use of stack implementation and stack application. \n");
	}
	
	// function for program header - for aesthetic purposes
	void program_header()
	{
	    printf("\n==============================================================================\n");
	    printf("\n\t\t\t • KITCHENWARE WASHING MACHINE •\n");
	    printf("\n==============================================================================\n");
	}
	
	
	// function to add dishes to the stack
	void add_dishes(struct Stack* stack) 
	{
	    char user_dishes[100];
	    
	    int c;
	    while ((c = getchar()) != '\n' && c != EOF);
	
	    program_header();
	    printf("\n\t WANNA WASH? (Enter kitchenware you wanna wash)");
	    printf("\n\t Add kitchenware: ");
	    fgets(user_dishes, sizeof(user_dishes), stdin); // to get string from user-input including spaces
	    
	    // Convert each character to uppercase
	    for (int i = 0; user_dishes[i] != '\0'; i++) 
		{
	        user_dishes[i] = toupper(user_dishes[i]);
	    } 
	
	    // Remove the newline character, if present
	    char *newline = strchr(user_dishes, '\n');
	    if (newline != NULL)
	        *newline = '\0';
	
	    // check if user-input contains only alphabetic characters and spaces
	    int valid_input = 1; // assumes initially that user-input is valid
	    for (int i = 0; user_dishes[i] != '\0' && user_dishes[i] != '\n'; i++)
	    {
	        if (!isalpha(user_dishes[i]) && user_dishes[i] != ' ') // checks if user-input has only letters and space/s
	        { 
	            valid_input = 0; // mark input as invalid
	            break;
	        }
	    }
	
	    if (!valid_input) 
	    {
	        printf("\n\t !! Invalid input! Only alphabetic characters and spaces are allowed.\n");
	    } 
	    
	    else 
	    {
	        if (isFULL(stack)) 
	        {
	            printf("\n\t The STACK is FULL. Cannot add kitchenware.\n");
	        } 
	        
	        else 
	        {
	            // push the user-input kitchenware onto the stack
	            PUSH(stack, user_dishes);
	            printf("\n\t -- %s \n\t added to the stack of kitchenware to be washed.\n", user_dishes);
	        }
	    }
	    
	    continue_add(stack);
	}
	
	// function to when the user wants to add more dishes
	void continue_add(struct Stack* store_kitchenware)
	{
	    int choice;
	    do
	    {
	        // asks user if they want to continue adding dishes
	        printf("\n\t Do you want to continue adding kitchenware? \n");
	        printf("\t       [1] Yes\t   [0] No \n");
	        printf("\n\t Enter choice: ");
	        scanf("%d", &choice);
	
	        clear_input();
	
	        if (choice == 1)
	        {
	            add_dishes(store_kitchenware);
	            return; // Return after adding dishes to avoid repeating the continue_add question
	        }
	        
	        else if (choice != 0)
	        {
	            printf("\n\t !! Invalid input, please enter a valid option !!\n");
	        }
	    } while (choice != 0);
	}
	
	// function to wash the dish at the top of the stack
	void wash_dishes(struct Stack* stack)
	{  
	    if (isEMPTY(stack)) // checks if stack is empty
	    {
	    	program_header();
	        printf("\n\t The STACK is EMPTY. No more kitchenware to wash.\n");
	    }
	    
	    else 
	    {
	        // pop the top kitchenware from the stack
	        char* user_dishes = POP(stack);
	        
	        program_header();
		    printf("\n\t mother: hoy! panghugas na. isa nalang gani na imung gikaunan, \n\t\t di pa nimo mahugasan");
		    printf("\n\t son(dishwasher): ok pi\n");
		    
	        printf("\n\t -- %s is being washed.\n", user_dishes);
	        printf("\n\t < 1 minute later ... >");
	        printf("\n\t you're done washing %s! \n", user_dishes);
	        free(user_dishes);
	    }    
	    
	    continue_wash(stack); // call the continue_wash function passing the stack
	}
	
	// function to continue washing individual dishes or exit
	void continue_wash(struct Stack* stack)
	{
	    int choice;
	    do
	    {
	        // asks the user if they want to continue washing dishes
	        printf("\n\t Do you wish to continue washing the dishes? \n");
	        printf("\t       [1] Yes\t   [0] No \n");
	        printf("\n\t Enter choice: ");
	        scanf("%d", &choice);
	
	        clear_input();
	
	        if (choice == 1)
	        {
	            if (!isEMPTY(stack)) // checks if stack is empty
	            {
	                // pop the top kitchenware from the stack
	                char* user_dishes = POP(stack);
	                program_header();
	                printf("\n\t mother: nganong gi-isa isa mana nimo hugas?");
	                printf("\n\t son(dishwasher): sorry pi \n");
	                
	                printf("\n\t -- %s is being washed.\n", user_dishes);
	                printf("\n\t < 1 minute later ... >");
	                printf("\n\t you're done washing %s!\n", user_dishes);
	                free(user_dishes);
	            }
	            
	            else
	            {
	                printf("\n\t The STACK is EMPTY. No more kitchenware to wash.\n");
	                return; // return to avoid repeating the continue_wash question
	            }
	        }
	        
	        else if (choice != 0)
	        {
	            printf("\n\t !! Invalid input, please enter a valid option !!\n");
	        }
	    } while (choice != 0);
	}
			
	// function to know the top dish of the stack
	void top_dish(struct Stack* stack)
	{
	    int choice;
	    int invalid_input = 0; // to track invalid input
	    
	    do {
	        if (!invalid_input) 
			{
	            program_header();
	            
	            char* top_dish = TOP(stack);
	                
	            if (isEMPTY(stack)) // checks if stack is empty
	            {
	                printf("\n\t The STACK is EMPTY. No more kitchenware to wash.");
	            }
	                
	            else
	            {
	                printf("\n\t -- %s is next to be washed.\n", top_dish);
	                free(top_dish); // free the allocated memory
	            }
	        }
	        
	        printf("\n\t [0] Back to Main Menu");
	        
	        printf("\n\n\t Enter your choice: ");
	        scanf("%d", &choice);
	
	        if (choice != 0) 
	        {
	            invalid_input = 1; // if input is invalid
	            printf("\n\n\t Invalid input, please try again...\n");
	        } 
	        
	        else
	        {
	            invalid_input = 0; // reset if input is valid
	            clear_input();
	        }
	        
	    } while (choice != 0);
	}

	// function for washing all the kitchenware until the stack is empty
	void wash_all(struct Stack* stack) 
	{
		int choice;
		int invalid_input = 0; // to track invalid input
		
	    if (isEMPTY (stack)) 
		{
			program_header();
	        printf("\n\t The STACK is EMPTY. No kitchenware to wash.\n");
	    }
	    
	    else 
		{   
			program_header();
		    printf("\n\t mother: nak, panghugas na oh, ang mga hugason nagtambak ra");
		    printf("\n\t son(dishwasher): okay ma\n");
		    printf("\n\t-------------------------------------------------------------\n");
		    printf("\n\t Washing the dishes... \n");
		    
		    while (!isEMPTY(stack)) 
			{
		        char* dishes = POP(stack);
		        printf("\n\t --%s is being washed.\n", dishes);
		        printf("\n\t < 1 minute later ... >");
		        printf("\n\t you're done washing %s!\n", dishes);
		        free(dishes);
		    }
		    printf("\n\t ALL KITCHENWARE HAS BEEN WASHED!\n");
		    printf("\n\t-------------------------------------------------------------\n");
		}
	    
	    do {
	        printf("\n\n\t [0] Back to Main Menu");
	        printf("\n\n\t Enter your choice: ");
	        scanf("%d", &choice);
	        
	        if (choice != 0) 
			{
	            invalid_input = 1; // if input is invalid
	            printf("\n\n\t Invalid input, please try again...\n");
	        } 
			
			else 
			{
	            invalid_input = 0; // if input is valid
	            clear_input();
	        }
	    } while (choice != 0);
	}
	
	// function to when the user wants to display the stack of dishes
	void display_stack(struct Stack* stack)
	{
	    int choice;
	    int invalid_input = 0; // to track invalid input
	    
	    do {
	        if (!invalid_input) 
			{
	            program_header();
	            
	            if (isEMPTY(stack)) // checks if stack is empty
	            {
	                printf("\n\t The STACK is EMPTY. No kitchenware to display.\n");
	            }
	            
	            else 
	            {
	                struct Node* current = stack -> top;
	                printf("\n\t Kitchenware to be washed (Top to Bottom):\n");
	                while (current != NULL)
	                {
	                    printf("\t %s\n", current -> data);
	                    current = current->next;
	                }
	            }
	        }
	        
	        printf("\n\t [0] Back to Main Menu");
	        
	        printf("\n\n\t Enter your choice: ");
	        scanf("%d", &choice);
	
	        if (choice != 0) 
	        {
	            invalid_input = 1; // Set flag if input is invalid
	            printf("\n\n\t Invalid input, please try again...\n");
	        } 
	        
	        else
	        {
	            invalid_input = 0; // Reset flag if input is valid
	            clear_input();
	        }
	        
	    } while (choice != 0);
	}

	// function for when the user want to exit the program
	void exit_process()
	{
	    printf("\n\t You've chosen to exit. Unplugging your life...\n");
	}
