#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

//part 1: 1 incorrect submit
// part 2: 3 incorrect submits

vector<vector<int>> nums;

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

void analyze_reports(){
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
		// print_levels(levels);		
		// cout << '\n';
		
		bool all_pos = true;
		bool all_neg = true;
		bool distance_valid = true;
		int distance_mistakes = 0;

		print_levels(levels);
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
				distance_mistakes +=1;
			}	
		}
		cout << "\n" << "all_pos: " << all_pos << " all_neg: " << all_neg << " distance_valid: " << distance_valid << "\n";
		if((all_pos || all_neg) && distance_valid){
			valid_reports +=1;
		}
		else {
			if(distance_mistakes == 1){
				valid_reports +=1;
			}
		}
	}
	cout << valid_reports << '\n';
}

int main(){
	read_file();
	analyze_reports();

}
