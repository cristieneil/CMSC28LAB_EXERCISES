/* WRITTEN BY: 	CEBALLOS, CRISTIENEIL J. (K-3L)
					
	PROGRAMMING EXERCISE 03 - QUEUE IMPLEMENTATION
	A C PROGRAM WITH QUEUE IMPLEMENTATION AND QUEUE APPLICATION */
	
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <stdbool.h>
	#include <ctype.h>
	
	#define MAX_NAME_LENGTH 50
	struct node* create_node(char *name, float amount);
	struct queue *INIT();
	bool isEMPTY(queue *Queue);
	struct node* FRONT(struct queue *Queue);
	void ENQUEUE (struct queue *Queue, char *name, float amount);
	void DEQUEUE(struct queue *Queue);
	void clear_input();
	void program_desc();
	void program_header();
	void continue_add(struct queue *cashier_queue);
	void continue_serve(struct queue *cashier_queue);
	void add_customer(struct queue *cashier_queue);
	void serve_customer(struct queue *cashier_queue);
	void next_customer(struct queue *cashier_queue);
	void closing_time(struct queue *cashier_queue);
	void exit_system();
	
	struct node 
	{
	    char name[MAX_NAME_LENGTH];
	    float amount;
	    struct node *next;
	};
	
	struct queue 
	{
	    struct node *front;
	    struct node *rear;
	};
	
	// function to create new node
	struct node* create_node(char *name, float amount) 
	{
	    struct node* newnode = (struct node*) malloc (sizeof(struct node));
	    if (newnode == NULL) 
		{
	        printf("\n\t memory allocation failed...\n");
	        exit(1);
	    }
	    
	    strcpy(newnode -> name, name);	// copy the string data to the new node
	    newnode -> amount = amount;		// assign the float value to the new node
	    newnode -> next = NULL;			// initialize the next pointer to NULL
	    return newnode;
	}
	
	// function to create and return the queue
	struct queue *INIT() 
	{
	    struct queue *Queue = (struct queue *) malloc (sizeof(struct queue));
	    if (Queue == NULL) 
		{
	        printf("\n\t memory allocation failed...\n");
	        exit(1);
	    }
	    
	    Queue -> front = NULL;
	    Queue -> rear = NULL;
	    return Queue;
	}
	
	// function to check whether queue is EMPTY
	bool isEMPTY(queue *Queue)
	{
		if (Queue -> rear == NULL && Queue -> front == NULL)
		{
			return true;	// queue is empty
		}
		
		return false;		// queue is not empty
	}
	
	// function to return a copy of the front/top element/item of the queue
	struct node* FRONT(struct queue *Queue)
	{
		if (isEMPTY(Queue))
		{
			return NULL;
		}
		
		else 
		{
        	return Queue -> front; // return a copy of the front item of the queue
    	}
	}
	
	// function to insert an item to the queue (enqueue)
	void ENQUEUE (struct queue *Queue, char *name, float amount)
	{
		struct node *newcustomer = (struct node*) malloc (sizeof(struct node));
		if (newcustomer == NULL)
		{
	        printf("\n\t memory allocation failed...\n");
	        exit(1);
	    }
	    
		strcpy(newcustomer -> name, name);	// copy the string data to the new node
	    newcustomer -> amount = amount;		// assign the float value to the new node
	    newcustomer -> next = NULL;			// initialize new ptr to NULL
		
		// if it is the first node of the queue
		if (Queue -> front == NULL && Queue -> rear == NULL)
		{
			Queue -> front = Queue -> rear = newcustomer; // both the front and rear pointers initialized as the new node
		}
		
		else 
		{
			Queue -> rear -> next = newcustomer;	// add new node after the current rear node
			Queue -> rear = newcustomer;			// update the new rear node
		}
	}
	
	
	void DEQUEUE(struct queue *Queue) 
	{
	    if (isEMPTY(Queue)) 
		{
	        return; // if queue is empty, nothing to dequeue; return nothing
	    } 
		
		else 
		{
	        struct node *temp = Queue->front; 			// store the previous front node
	        Queue -> front = Queue -> front -> next;	// move front one node ahead
	        
	        if (Queue -> front == NULL) 
			{
	            Queue -> rear = NULL; // if front becomes NULL, change rear also to NULL
	        }
	        
	        free(temp); // free the memory of the dequeued node
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

	// MAIN APPLICATION - SHOP CASHIER CHECKOUT SYSTEM
	int main() 
	{
	    struct queue* cashier_queue = INIT();
	    program_desc();
	
	    int user_choice;
	    do {
	        program_header();
	        printf("\n\t |    WEVERSE SHOP    |    COUNTER 0    > \n");
	        printf("\n\t [1] Fall in line");
	        printf("\n\t [2] Serve Customer");
	        printf("\n\t [3] Next Customer");
	        printf("\n\t [4] Closing Time");
	        printf("\n\t [0] Exit process");
	
	        printf("\n\n\t Enter Choice: ");
	        while (scanf("%d", &user_choice) != 1 || user_choice < 0 || user_choice > 4) 
			{
	            printf("\n\t < Invalid input. Please enter your choice: ");
	            while (getchar() != '\n'); // clear input buffer
	        }
	
			clear_input();
			
	        switch (user_choice) 
			{
	            case 1:
	                add_customer(cashier_queue);
	                break;
	            case 2:
	                serve_customer(cashier_queue);
	                break;
	            case 3:
	                next_customer(cashier_queue);
	                break;
	            case 4:
	                closing_time(cashier_queue);
	                break;
	            case 0:
	                exit_system();
	                break;
	            default:
	                printf("\n\t < Invalid input, please enter a valid option! >\n");
	                break;
	        }
	    } while (user_choice != 0);
	
	    return 0;
	}

	// funxtion for program description
	void program_desc() 
	{
	    printf("..............................................................................\n");
	    printf("\n This program makes use of queue implementation and queue application. \n");
	}
	
	// function for program header - for aesthetic purposes
	void program_header()
	{
	    printf("\n==============================================================================\n");
	    printf("\n\t\t • WEVERSE SHOP - All Things for Fans! •\n");
	    printf("\n==============================================================================\n");
	}
	
	// function to add costumer's info that is falling in line in the cashier queue
	void add_customer(struct queue *cashier_queue) 
	{
	    char last_name[MAX_NAME_LENGTH + 1]; // +1 for null terminator
	    float total_amount;
	
	    program_header();
	    printf("\n\t Welcome ^__^ | Kindly provide the following information to facilitate \n\t\t\tyour transaction smoothly: \n");
	
	    int c;
	    while ((c = getchar()) != '\n' && c != EOF); // clear input buffer
	    
	    while (1) 
		{
	        printf("\n\t Enter your Last Name (ex. Ceballos): ");
	
	        fgets(last_name, sizeof(last_name), stdin); // read last name from user input
	
	        last_name[strcspn(last_name, "\n")] = '\0'; // remove trailing newline character
	        
	        // Transform last name to UUPERCASE
			for (int i = 0; last_name[i] != '\0'; i++) 
			{
			    last_name[i] = toupper(last_name[i]);
			}
	
	        // remove leading / unnecessary spaces
	        char *trimmed_last_name = last_name;
	        while (isspace(*trimmed_last_name)) 
			{
	            trimmed_last_name++;
	        }
	
	        // checks if user-input's last name is empty
	        if (strlen(trimmed_last_name) == 0) 
			{
	            printf("\n\t < ERROR: Last name cannot be empty. Please try again. >");
	            continue; // Loop again for input
	        }
	
	        // validate last name
	        int valid_input = 1; // initially assumes true
	        for (int i = 0; trimmed_last_name[i] != '\0'; i++) 
			{
	            if (!isalpha(trimmed_last_name[i]) && trimmed_last_name[i] != '-' && !isspace(trimmed_last_name[i])) 
				{
	                valid_input = 0; // false
	                break;
	            }
	        }
	
	        if (!valid_input) 
			{
	            printf("\n\t < ERROR: Invalid input. Only alphabetic characters, spaces, and '-' \n\t   symbol are allowed. Please try again. > \n");
	            continue; // loop again for input
	        }
	
	        // input total amount payable
		    do {
			    printf("\n\t Total Amount Payable: PHP ");
			    int input_amount = scanf("%f", &total_amount);
			    
			    // check if the input is a valid floating-point number and non-negative
			    if (input_amount != 1 || total_amount < 0 || getchar() != '\n') 
				{
			        printf("\n\t < ERROR: Invalid input. Please enter a valid non-negative amount. >\n");
			        
			        // clear input buffer
			        while ((c = getchar()) != '\n' && c != EOF);
			        
			        // reset total_amount
			        total_amount = -1;
			    }
			} while (total_amount < 0);

	
	        // enqueue  / insert customer's information to cashier queue
	        ENQUEUE(cashier_queue, trimmed_last_name, total_amount);
	        printf("\n\t -- Customer '%s' with total amount payable of PHP %.4f added to the queue.\n", trimmed_last_name, total_amount);
	
	        break; // break out of the loop after successful entry
	    }
	    
	    continue_add(cashier_queue);
	}
	
	// function to when there are more customers who would like to queue in this counter
	void continue_add(struct queue *cashier_queue)
	{
		int choice;
		do
		{
		    // asks if the customer/s want to fall in line in the cashier counter
		    printf("\n\t Do you want to fall in line in this counter? \n");
		    printf("\t       [1] Yes\t   [0] No \n");
		    printf("\n\t Enter choice: ");
		    scanf("%d", &choice);
		
		    clear_input();
		
		    if (choice == 1)
		    {
		        add_customer(cashier_queue);
		        return; // return after adding customers to avoid repeating the continue_add question
		    }
		        
		    else if (choice != 0)
		    {
		            printf("\n\t < Invalid input, please enter a valid option! > \n");
		    }
		} while (choice != 0);
	}

	// function to serve the customer who is first in line by checking out their order | DEQUEUE customer from the queue
	void serve_customer(struct queue *cashier_queue) 
	{
	    if (isEMPTY(cashier_queue)) 
		{
	        printf("\n\t The QUEUE is EMPTY. No orders to serve.\n");
	        return;
	    } 
		
		else 
		{
	        struct node *served_customer = FRONT(cashier_queue);
	        program_header();
	        printf("\n\t cashier lady: may WEVERSE card available po ba sila?");
	        printf("\n\t customer: wala pi\n");
	        printf("\n\t -- Now serving %s with total amount payable of PHP %.4f.\n", served_customer -> name, served_customer -> amount);
	        printf("\n\t < %s is done paying ... > \n", served_customer -> name);
	        DEQUEUE(cashier_queue);
	    }
	    
	    continue_serve(cashier_queue);
	}
	
	// function for the next customer who wants to check out
	void continue_serve(struct queue *cashier_queue)
	{
	    int choice;
	    do
	    {
	        // asks the next customer if they want to be served
	        printf("\n\t Do you want to check out your order? \n");
	        printf("\t       [1] Yes\t   [0] No \n");
	        printf("\n\t Enter choice: ");
	        scanf("%d", &choice);
	
	        clear_input();
	
	        if (choice == 1)
	        {
	            serve_customer(cashier_queue); // proceed to serve the next customer
	            return; // return after serving the customer to avoid repeating the continue_serve question
	        }
	        else if (choice != 0)
	        {
	            printf("\n\t < Invalid input, please enter a valid option! >\n");
	        }
	    } while (choice != 0);
	}

	// function to display the next customer in the queue
	void next_customer(struct queue *cashier_queue)
	{
	    int choice;
	    int invalid_input = 0; // to track invalid input
	    
	    do {
	        if (!invalid_input) 
	        {
	            if (isEMPTY(cashier_queue))
	            {
	                printf("\n\t The QUEUE is EMPTY. No orders to serve.\n");
	                return;
	            }
	            
	            else
	            {
	                struct node *next_customer = FRONT(cashier_queue);
	                program_header();
	                printf("\n\t Next order: For %s with total amount payable of PHP %.4f.\n", next_customer -> name, next_customer -> amount);
	            }
	        }
	        
	        printf("\n\t Enter [0] Back to Main Menu: ");
	        scanf("%d", &choice);
	
	        if (choice != 0) 
	        {
	            invalid_input = 1; // if input is invalid
	            printf("\n\n\t < Invalid input, please enter a valid option! >\n");
	        } 
	        
	        else
	        {
	            invalid_input = 0; // reset if input is valid
	            clear_input();
	        }
	        
	    } while (choice != 0);
	}
	
	// function to serve all the remaining customers in the queue before closing time
	void closing_time(struct queue *cashier_queue)
	{
	    int choice;
	    int invalid_input = 0; // to track invalid input
	    
	    if (isEMPTY(cashier_queue)) 
	    {
	        printf("\n\t The QUEUE is EMPTY. No customer/s to serve.\n");
	        return;
	    }
	    
	    else 
	    {   
	        program_header();
	        printf("\n\tAttention all shoppers! Our store will be closing in 15 minutes.");
	        printf("\n\tPlease bring your final purchases to the checkout stand at this time. \n");
	        printf("\n\t---------------------------------------------------------------\n");
	        printf("\n\t Closing Time... \n");
	        
	        while (!isEMPTY(cashier_queue)) 
	        {
	            struct node *customer = FRONT(cashier_queue);
	            printf("\n\t -- Now serving %s with total amount payable of PHP %.4f.\n", customer->name, customer->amount);
	            DEQUEUE(cashier_queue);
	        }
	        
	        printf("\n\t ALL CUSTOMERS HAVE BEEN SERVED!\n");
	        printf("\n\t---------------------------------------------------------------\n");
	    }
	    
	    do {
	        printf("\n\n\t [0] Back to Main Menu");
	        printf("\n\n\t Enter your choice: ");
	        scanf("%d", &choice);
	        
	        if (choice != 0) 
	        {
	            invalid_input = 1; // if input is invalid
	            printf("\n\n\t < Invalid input, please enter a valid option! >\n");
	        } 
	        
	        else 
	        {
	            invalid_input = 0; // if input is valid
	            clear_input();
	        }
	    } while (choice != 0);
	}

	
	// function for when the user want to exit the checkout system
	void exit_system()
	{
		clear_input();
		printf("\n\t < You've chosen to exit. Done checking out...\n");
	}

	
	
	
	
