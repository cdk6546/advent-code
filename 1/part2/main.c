#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// global variables

// array to hold the first column of the list
int col_num_one[1000];

// array to hold the second column of the list
int col_num_two[1000];

// array size which is the same for both columns
int array_size = 0;

/**
	comparator for qsort
	@return whether a is bigger than b
**/
int comp(const void* a, const void* b) {
      
    return (*(int*)a - *(int*)b);
}

/**
	reads in the input file, stores it into two column arrays (global)
	converts the strings from the input file into integers
	stores the array size in the global variable
**/
void read_file(){
	FILE* file;
	file = fopen("input", "r");
	char buffer[256];
	int list_index = 0;
	
	while (fgets(buffer, sizeof(buffer), file) != NULL){
	 	int i = 0;

		char first_num[32];
		char second_num[32];

		// gets the first number before the spaces
		while(buffer[i] != ' ' && buffer[i] != 0){
			first_num[i] = buffer[i];
			i+=1;
		}

		// filter out the spaces
		while(buffer[i] == ' '){
			i+=1;
		}
		
		int j = 0;

		// get the second number after the spaces
		while(buffer[i] != '\n' && buffer[i] != 0){
			second_num[j] = buffer[i];
			i+=1;
			j+=1;
		}

		// convert to integers
		col_num_one[list_index] = atoi(first_num);
		col_num_two[list_index] = atoi(second_num);	

		list_index ++;
	}
	
	// global storage of array size
	array_size = sizeof(col_num_one) / sizeof(col_num_one[0]);
}

/**
	finds the distance between each smallest elements in each column
**/
void find_distance(){

	// sort both lists so the smallest elements are first
	qsort(col_num_one, array_size, sizeof(int), comp);
	qsort(col_num_two, array_size, sizeof(int), comp);

	int total = 0;
	int sub = 0;

	// find the distance between the smallest elements in both columns
	for(int i = 0; i < array_size; i++){
		sub = abs(col_num_one[i] - col_num_two[i]);
		total += sub;
	}
	printf("total distance: %i\n", total);
}

/** 
	finds the similarity between the columns
	aka: element in column one * n occurences of column one element
	in column two 
**/
void find_similarity(){
	int similarity_score = 0;
		
	for(int j = 0; j < array_size; j++){
		int count = 0;
		for(int z = 0; z < array_size; z++){
		
		// for every element in column one, check if it is inside
		// column two
		
			if (col_num_one[j] == col_num_two[z]){
				count +=1;
			}
		}
		// score calculation, sum
		similarity_score += col_num_one[j] * count;
	}
	
	printf("similarity: %i\n", similarity_score);
	
}

int main(){
	read_file();
	find_distance();
	find_similarity();
}
		
