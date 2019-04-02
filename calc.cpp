#include <iostream>
#include <cmath>
#include <stack>
#include <string>

const char sep = '|';
const std::string operators = "-+/*^",
	brackets = "()",
	symbols = "0123456789,.";

short priority(const char op){
	switch(op){
		case '+':	return 1;
		case '-':	return 1;
		case '/':	return 2;
		case '*':	return 2;
		case '^':	return 3;
		default:	
			std::string err = std::string("unknown operator:");
			err += op;
			throw std::runtime_error(err);
	}
}

double calc(const char op, double val1, double val2){
	switch(op){
		case '+':	return val1 + val2;
		case '-':	return val1 - val2;
		case '/':	return val1 / val2;
		case '*':	return val1 * val2;
		case '^':	return std::pow(val1, val2);
		default:	
			std::string err = std::string("unknown operator:");
			err += op;
			throw std::runtime_error(err);
	}
}

bool contains(const std::string &str, const char c){
	return str.find(c) != std::string::npos;
}

std::string to_poland(const std::string &input){
	std::string output = "";
	std::stack<char> st;
	bool sym_met = false;
	for(const char &c : input){
		if(contains(symbols, c)){
			output += c;
			sym_met = true;
		}else if(contains(operators, c)){
			if(sym_met){
				output += sep;
				sym_met = false;
			}
			while(st.size() != 0 &&
				(contains(operators, st.top())) &&
				(priority(st.top()) >= priority(c)))
			{
				output += st.top();
				st.pop();
			}
			st.push(c);
		}else if(contains(brackets, c)){
			if(sym_met){
				output += sep;
				sym_met = false;
			}
			if(c == '('){
				st.push(c);
			}else if(c == ')'){
				while(st.top() != '('){
					output += st.top();
					st.pop();
				}
				st.pop();
			}
		}
	}
	if(sym_met){
		output += sep;
	}
	while(st.size() != 0){
		output += st.top();
		st.pop();
	}
	return output;
}

double calculate(const std::string &input){
	std::string temp = "";
	std::stack<std::string> st;
	for(const char &c : input){
		if(c == sep){
			st.push(temp);
			temp = "";
		}else if(contains(symbols, c)){
			temp += c;
		}else if(contains(operators, c)){
			double op2 = std::stod(st.top());
			st.pop();
			double op1 = std::stod(st.top());
			st.pop();
			double res = calc(c, op1, op2);
			st.push(std::to_string(res));
		}
	}
	return std::stod(st.top());
}

std::string check(const std::string &str){
	std::string temp = "";
	bool minus_met = false;
	for(const char &c : str){
		if(c == '-'){
			if(temp == "" || !contains(symbols, temp.back())){
				temp += "(0-";
				minus_met = true;
			}
		}else if(!contains(symbols, c)){
			if(minus_met){
				temp += ")";
				minus_met = false;
			}
			temp += c;
		}else{
			temp += c;
		}
	}
	if(minus_met){
		temp += ")";
	}
	return temp;
}

int main(){
	std::string input = "";
	while(1){
		std::cin >> input;
		if(input == "q"){
			break;
		}
		const std::string chck = check(input);
		std::cout<<chck<<'\n';
		const std::string pol = to_poland(chck);
		std::cout << pol << '\n';
		std::cout << calculate(pol) << '\n';
	}
}
