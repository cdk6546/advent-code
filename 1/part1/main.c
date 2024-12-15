#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int comp(const void* a, const void* b) {
      
    return (*(int*)a - *(int*)b);
}

int main(){
	FILE* file;
	file = fopen("input", "r");
	char buffer[256];

	int col_num_one[1000];
	int col_num_two[1000];
	
	
	int list_index = 0;
	
	while (fgets(buffer, sizeof(buffer), file) != NULL){
	 	int i = 0;

		char first_num[32];
		char second_num[32];
		
		while(buffer[i] != ' ' && buffer[i] != 0){
			first_num[i] = buffer[i];
			i+=1;
		}
		
		while(buffer[i] == ' '){
			i+=1;
		}
		int j = 0;
		while(buffer[i] != '\n' && buffer[i] != 0){
			second_num[j] = buffer[i];
			i+=1;
			j+=1;
		}

		col_num_one[list_index] = atoi(first_num);
		col_num_two[list_index] = atoi(second_num);	

		list_index ++;
	}

	int array_size = sizeof(col_num_one) / sizeof(col_num_one[0]);

	
	qsort(col_num_one, array_size, sizeof(int), comp);
	qsort(col_num_two, array_size, sizeof(int), comp);

	int total = 0;
	int sub = 0;
	
	for(int i = 0; i < array_size; i++){
		sub = abs(col_num_one[i] - col_num_two[i]);
		total += sub;
	}

	printf("total distance: %i\n", total);
		
}
		
