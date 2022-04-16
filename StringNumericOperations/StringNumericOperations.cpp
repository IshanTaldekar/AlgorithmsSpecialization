#include <string>
#include <iostream>
#include <vector>

class StringNumericOperations {

public:

	std::string add(std::string num1, std::string num2) {

		make_equal_length(num1, num2);

		num1 = reverse_string(num1);
		num2 = reverse_string(num2);

		int carry = 0;
		std::string result = "";

		for (int i = 0; i < num1.length(); ++i) {

			int sum = (int)(num1.at(i) - '0') + (int)(num2.at(i) - '0') + carry;
			result.push_back((sum % 10) + '0');
			carry = sum / 10;

		}

		if (carry > 0) result += std::to_string(carry);

		return reverse_string(result);

	}

	std::string multiply(std::string num1, std::string num2) {

		if (num1.length() < num2.length()) {

			swap_strings(num1, num2);

		}

		std::vector<std::string> multiplications;

		for (int i = num2.size() - 1; i >= 0; --i) {

			multiplications.push_back(multiply(num1, num2.at(i) - '0'));

		}

		return add(multiplications);


	}

private:

	void multiply_by_10_raised_n(std::string& num, int n) {

		for (int i = 0; i < n; ++i) {

			num.push_back('0');

		}

	}

	std::string add(const std::vector<std::string>& multiplications) {

		std::string sum = multiplications.at(0);
		int add_zeros_count = 1;

		for (int i = 1; i < multiplications.size(); ++i) {

			std::string num = multiplications.at(i);

			for (int j = 0; j < add_zeros_count; ++j) {

				num.push_back('0');

			}

			sum = add(num, sum);
			++add_zeros_count;

		}

		return sum;

	}

	std::string multiply(std::string num1, int val) {

		num1 = reverse_string(num1);
		std::string result = "";
		int carry = 0;

		for (int i = 0; i < num1.length(); ++i) {

			int multiplication = ((int)(num1.at(i) - '0') * val) + carry;
			result.push_back((multiplication % 10) + '0');
			carry = multiplication / 10;

		}

		if (carry > 0) result += std::to_string(carry);

		return reverse_string(result);

	}

	std::string reverse_string(const std::string& str) {

		return std::string{ str.rbegin(), str.rend() };

	}

	void swap_strings(std::string& string1, std::string& string2) {

		std::string temp = string1;

		string1 = string2;
		string2 = temp;

	}

	void make_equal_length(std::string& string1, std::string& string2) {

		bool swap = false;

		if (string1.length() < string2.length()) {

			swap = true;
			swap_strings(string1, string2);

		}

		std::string zero_padding(string1.length() - string2.length(), '0');
		string2 = zero_padding + string2;

		if (swap) {

			swap_strings(string1, string2);

		}

	}


};

int main() {

	StringNumericOperations operations_module;

	std::string s1;
	std::cout << "Enter first number to multiply: ";
	std::cin >> s1;
	std::cout << std::endl;

	std::string s2;
	std::cout << "Enter second number to multiply: ";
	std::cin >> s2;
	std::cout << std::endl;

	std::cout << "Result: " << operations_module.multiply(s1, s2);

}