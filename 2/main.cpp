#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

//part 1: 1 incorrect submit
// part 2: 6 incorrect submits

vector<vector<int>> nums;
vector<vector<int>> invalid_levels;

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

void print_levels(vector<int> levels){
	// for each level in the levels array, iterate by reference not by copy
	for (const auto& level : levels) {
		cout << to_string(level) << ',';
	}
	cout << '\n';
}

int dampen(){
	cout << "---------------------------\n";
	int valid_reports = 0;
	
	for(vector<int> row : invalid_levels){
	   for (size_t i = 0; i < row.size(); i++) {
	        vector<int> row_copy(row.begin(), row.end());
	        row_copy.erase(row_copy.begin() + i);
	        
			vector<int> levels;
			for (size_t z = 0; z < row_copy.size(); z++) {
				if(z > 0 && z < row_copy.size() - 1){
					// int left_center = row[z] - row[z-1];
					int right_center = row_copy[z+1] - row_copy[z];
					// levels.push_back(left_center);
					levels.push_back(right_center);
				}
				else if(z == 0){
					int right_center = row_copy[z+1] - row_copy[z];
					levels.push_back(right_center);
				}
				else if(z == row_copy.size() - 1){
					int left_center = row_copy[z] - row_copy[z-1];
					levels.push_back(left_center);
				}
			}
					
			bool all_pos = true;
			bool all_neg = true;
			bool distance_valid = true;
			print_levels(levels);
			
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

			cout << "\n" << "all_pos: " << all_pos << " all_neg: " << all_neg << " distance_valid: " << distance_valid << "\n";
					
			if((all_pos || all_neg) && distance_valid){
				valid_reports +=1;
				break;
			}
					
		}
	}
	return valid_reports;
}

int analyze_reports(){
	int valid_reports = 0;

	// for each row in the nums array, iterate by reference not by copy
	for (const auto& row : nums) {
	// loop until the row's size
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
		
		bool all_pos = true;
		bool all_neg = true;
		bool distance_valid = true;

		for (const auto& level : levels){
			cout << to_string(level) << ',';
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
		// cout << "\n" << "all_pos: " << all_pos << " all_neg: " << all_neg << " distance_valid: " << distance_valid << "\n";
		if((all_pos || all_neg) && distance_valid){
			valid_reports +=1;
		}
		else{
			invalid_levels.push_back(row);
		}
	}
	cout << "valid reports without dampener: " << valid_reports << '\n';
	return valid_reports;
}

int main(){
	read_file();
	int undamp = analyze_reports();
	int damp = dampen();
	cout << damp + undamp << '\n';
}
