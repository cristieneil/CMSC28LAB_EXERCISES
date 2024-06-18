/* 	WRITTEN BY: CEBALLOS, CRISTIENEIL J. (K-3L)
					
	PROGRAMMING EXERCISE 05 - OOP 1
	A C++ PROGRAM WILL ASK THE USER TO INPUT VARIOUS NUMBERS (POSITIVE OR NEGATIVE 
	BUT NOT ZERO) AND PERFORM BASIC STATISTICS ON THESE NUMBERS. */
	
	#include <iostream>
	#include <cmath> 
	
	using namespace std;
	
	const int MAX_SIZE = 10; // max size of the array
	
	void program_desc();
	void user_input(int[], int&);
	int highestval(int[], int);
	int lowestval(int[], int);
	float average(int[], int);
	float standard_deviation(int[], int);
	float variance(int[], int);
	void print_result(int[], int, int, float, float, float);
	
	// MAIN PROGRAM
	int main()
	{
	    int numbers[MAX_SIZE]; // array to store user-input values
	    int count; // to keep track of the actual count of numbers entered
	
	    // function call for program description
	    program_desc();
	
	    // read the user's input
	    user_input(numbers, count);
	
	    // get the largest value
	    int largest = highestval(numbers, count);
	
	    // get the smallest value
	    int smallest = lowestval(numbers, count);
	
	    // get the average 
	    float ave = average(numbers, count);
	
	    // get the standard deviation
	    float standard_dev = standard_deviation(numbers, count);
	
	    // get the variance
	    float population_var = variance(numbers, count);
	
	    // display the result
	    print_result(numbers, largest, smallest, ave, standard_dev, population_var);
	
	    return 0;
	}
	
	// function about the program description
	void program_desc()
	{
	    cout << "\n\t This program will ask the user to input various numbers (positive or" << endl;
	    cout << "\t negative but not zero) and perform basic statistics on these numbers. \n" << endl;
	    cout << "............................................................................. \n" << endl;
	
	    // about the programmer: name, date done, subject number
	    cout << "\t CREATED BY: CRISTIENEIL CEBALLOS | DATE: MAY 11 2024 | SUBJ: CMSC 28 \n" << endl;
	    cout << "============================================================================= \n" << endl;
	}
	
	// function to let user input
	void user_input(int num[], int& count)
	{
	    count = 0;
	
	    do
	    {
	        cout << "\t Input an Integer: ";
	        cin >> num[count];
	
	        // if zero is inputted, end data entry of user
	        if (num[count] == 0)
	        {
	            break;
	        }
	
	        count++;
	
	    } while (count < MAX_SIZE); // continue accepting input until count reaches max size of array or 0 is entered
	
	    // adjust count if the last input was 0
	    if (num[count - 1] == 0)
	    {
	        count--;
	    }
	}
	
	// function to know the largest number among the user-input
	int highestval(int num[], int count)
	{
	    int largestnum = num[0]; // assumes the first element of the array as the largest number
	
	    // iterate through the array to find the largest element
	    for (int i = 1; i < count; ++i)
	    {
	        if (num[i] > largestnum)
	        {
	            largestnum = num[i];
	        }
	    }
	
	    return largestnum;
	}
	
	// function to know the smallest number among the user-input
	int lowestval(int num[], int count)
	{
	    int smallestnum = num[0]; // assumes the first element of the array as the smallest number
	
	    // iterate through the array to find the smallest element
	    for (int i = 1; i < count; ++i)
	    {
	        if (num[i] < smallestnum)
	        {
	            smallestnum = num[i];
	        }
	    }
	
	    return smallestnum;
	}
	
	// function to get the average of the user-input values
	float average(int num[], int count)
	{
	    int sum = 0; // initialize the value of sum to zero
	
	    // iterate through the array to get the sum of all its elements
	    for (int i = 0; i < count; ++i)
	    {
	        sum += num[i];
	    }
	
	    // convert the sum first to a floating-point number to ensure the correctness of the operation
	    // before dividing it with the array size
	    float averagenum = static_cast <float> (sum) / count; 
	
	    return averagenum;
	}
	
	// function to get the standard deviation of the values (formula used is for the stdev for population)
	float standard_deviation(int num[], int count)
	{
	    float avg = average(num, count); // get the mean of the values from the int average() function
	    float sum_squareddiff = 0;      // initialize the value of sum of the squared differences to zero
	
	    // calculate the sum of squared differences
	    for (int i = 0; i < count; ++i)
	    {
	        float difference = num[i] - avg; // subtract the mean from each number
	        sum_squareddiff += difference * difference; // add the squared differences to get their sum
	    }
	
	    // get the mean of the squared differences
	    float mean_squareddiff = sum_squareddiff / count;
	
	    // get the square root of the mean of the squared differences to get the standard deviation
	    float stddev = sqrt(mean_squareddiff);
	
	    return stddev;
	}
	
	float variance(int num[], int count)
	{
	    float stdev = standard_deviation(num, count);
	    float var = stdev * stdev;
	
	    return var;
	}
	
	// function to display all the values
	void print_result(int num[], int largest, int smallest, float ave, float standard_dev, float population_var)
	{
	    cout << "\n\t < THE VALUES > " << endl;
	    cout << "\n\t > Largest number: " << largest << endl;
	    cout << "\t > Smallest number: " << smallest << endl;
	    cout << "\t > Average: " << ave << endl;
	    cout << "\t > Standard Deviation: " << standard_dev << endl;
	    cout << "\t > Variance: " << population_var << endl;
	}
