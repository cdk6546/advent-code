#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

// part 1: 1 incorrect submit
// part 2: 6 incorrect submits

// holds the original read-in values
vector<vector<int>> nums;

// holds the reports that have incorrect levels
vector<vector<int>> invalid_levels;


/** 
	reads the input file and feeds the data
	into the global nums variable
**/
void read_file(){
	ifstream File("input");
	
	string line_str;
	while(getline(File, line_str)){		
		istringstream line(line_str);
		
		string s;
		vector<int> num;
		while (getline(line, s, ' ')){
			num.push_back(stoi(s));
		}

		nums.push_back(num);
	}

	File.close();
}

/**
	helper function that prints the nums array
	for testing
**/
void print_rows(){
	// for each row in the nums array, iterate by reference not by copy
	for (const auto& row : nums) {
	// loop until the row's size
	      for (size_t z = 0; z < row.size(); z++) {
	          cout << row[z];
	          if (z < row.size() - 1)
	              cout << ',';
	      }
	      cout << '\n';
	  }
}

/**
	helper function that prints the levels array
	for testing
**/
void print_levels(vector<int> levels){
	// for each level in the levels array, iterate by reference not by copy
	for (const auto& level : levels) {
		cout << to_string(level) << ',';
	}
	cout << '\n';
}

/**
	do the calculations between levels
	@return a vector of integers holding the calculations per row
**/
vector<int> initialize_levels(vector<int> row){
	vector<int> levels;
	for (size_t z = 0; z < row.size(); z++) {
			if(z > 0 && z < row.size() - 1){
				// int left_center = row[z] - row[z-1];
				int right_center = row[z+1] - row[z];
				// levels.push_back(left_center);
				levels.push_back(right_center);
			}
			else if(z == 0){
				int right_center = row[z+1] - row[z];
				levels.push_back(right_center);
			}
			else if(z == row.size() - 1){
				int left_center = row[z] - row[z-1];
				levels.push_back(left_center);
			}
		}
	return levels;
}

/**
	checks if level calulations are valid
	@return whether the set of level calculations are valid
**/
bool check_validity(vector<int> levels){
	bool all_pos = true;
	bool all_neg = true;
	bool distance_valid = true;
	
	for (const auto& level : levels){
		if(level > 0){
			all_neg = false;
		}
		if(level < 0){
			all_pos = false;
		}
		if (abs(level) < 1 || abs(level) > 3){
			distance_valid = false;
		}	
	}
			
	if((all_pos || all_neg) && distance_valid){
		return true;
	}
	return false;

}

/**
	allows for ONE element to be removed to make a report valid
	@return the number of incorrect reports corrected by this rule
**/
int dampen(){
	int valid_reports = 0;	
	for(vector<int> row : invalid_levels){
	   for (size_t i = 0; i < row.size(); i++) {
	        vector<int> row_copy(row.begin(), row.end());
	        row_copy.erase(row_copy.begin() + i);
	        
			vector<int> levels = initialize_levels(row_copy);
					
			if(check_validity(levels) == true){
				valid_reports +=1;
				break;
			}
		}
	}
	return valid_reports;
}

/**
	checks the original set of calculations for validity
	invalid reports get appended to the invalid_levels
	global variable
	@return the number of valid reports without dampening
**/
int analyze_reports(){
	int valid_reports = 0;

	// for each row in the nums array, iterate by reference not by copy
	for (const vector<int>& row : nums) {
	// loop until the row's size
		vector<int> levels = initialize_levels(row);
		
		if(check_validity(levels) == true){
			valid_reports +=1;
		}
		else{
			invalid_levels.push_back(row);
		}
	}
	return valid_reports;
}

int main(){
	read_file();
	int undamp = analyze_reports();
	int damp = dampen();
	cout << damp + undamp << '\n';
}
