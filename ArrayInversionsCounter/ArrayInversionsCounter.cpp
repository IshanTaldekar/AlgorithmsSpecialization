#include <vector>
#include <fstream>
#include <string>
#include <iostream>

std::vector<int> read_input_file(const std::string & input_file_location) {

	std::ifstream ifs(input_file_location, std::ios_base::in);
	std::string line;
	std::vector<int> result;

	if (ifs.is_open()) {

		while (getline(ifs, line)) {

			result.push_back(std::stoi(line));

		}

		ifs.close();

	}

	return result;

}

class ArrayInversionsCounter {

public:

	long long get_array_inversion_count(const std::vector<int> & input_arr) {

		long long count = 0L;
		divide(input_arr, count);
		return count;

	}

	long long brute_force_array_inversion_count(const std::vector<int>& input_arr) {

		long long count = 0;

		for (int i = 0; i < input_arr.size(); ++i) {

			for (int j = i + 1; j < input_arr.size(); ++j) {

				if (input_arr.at(i) > input_arr.at(j)) ++count;

			}

		}

		return count;

	}

private:


	std::vector<int> divide(const std::vector<int>& arr, long long & count) {

		if (arr.size() <= 1) return arr;

		int mid = arr.size() / 2;

		std::vector<int> left{ arr.begin(), arr.begin() + mid };
		std::vector<int> right{ arr.begin() + mid, arr.end() };

		left = divide(left, count);
		right = divide(right, count);

		return merge(left, right, count);


	}

	std::vector<int> merge(const std::vector<int>& left, const std::vector<int>& right, long long & count) {

		int left_ptr = 0, right_ptr = 0;
		std::vector<int> result;

		while (left_ptr < left.size() || right_ptr < right.size()) {

			if (left_ptr >= left.size()) {

				result.push_back(right.at(right_ptr++));

			} else if (right_ptr >= right.size()) {

				result.push_back(left.at(left_ptr++));

			}
			else {

				if (left.at(left_ptr) <= right.at(right_ptr)) {

					result.push_back(left.at(left_ptr++));

				}
				else {

					count += left.size() - left_ptr;
					result.push_back(right.at(right_ptr++));

				}

			}

		}

		return result;

	}

};

int main() {

	std::vector<int> input_arr = read_input_file("Input_Arr.txt");
	
	ArrayInversionsCounter obj;
	std::cout << "Divide and conquer algorithm result: " << obj.get_array_inversion_count(input_arr) << std::endl;
	std::cout << "Brute force algorithm result: " << obj.brute_force_array_inversion_count(input_arr) << std::endl;

}
