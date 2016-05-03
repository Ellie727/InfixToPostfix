#include <iostream>
#include <cctype>
#include <stack>
#include <map>

using namespace std; 

string infix_to_postfix(string);
void evaluate_postfix(string);


int main(){
	
	string expression; 
	
		cout << "Consider the rules..." << '\n' << '\n';
		cout << "< char > -> < letter > | < digit > | < operator > | < decpt > | < delimiter >" << '\n';
		cout << "< letter > -> A | B | C | ... | Z | a | b | ... | z" << '\n';
		cout << "< digit > -> 0 | 1 | 2 | ... | ... | 8 | 9" << '\n';
		cout << "< operator > ->  + | - | * | /" << '\n';
		cout << "< decpt > -> ." << '\n';
		cout << "< delimiter > -> _" << '\n';
		cout << "< < constant > -> < digit >< digit* > | < digit* > . < digit >< digit* >" << '\n';
		cout << "< variable > -> < letter >< letter* >" << '\n';
		cout << "< P > -> < constant > | < variable > | < P >< P >< operator >" << '\n' << '\n';
		
	
	do{
		
		cout << "Please enter an expression to evaluate or '0' to exit" << '\n';
	
		
		cin >> expression; 
		if(expression == "0"){
			return 0; 
		}
		
		cout << '\n' << '\n' << "The postfix of your expression is: " << infix_to_postfix(expression) << '\n' << '\n'; 
		evaluate_postfix(infix_to_postfix(expression));
		

		
	}while(expression != "0");
	
	return 0; 
}


//Converts infix expression into postfix expression
string infix_to_postfix(string expression){
	
	//Stack that keeps track of operation symbols in user entered expression
	stack<char> operator_stack;
	
	//String that stores  
	string postfix = ""; 
	
	//Map that stories the priorities of each symbol using PEMDAS
	map<char,int> priorities; 
	priorities['*'] = 1;
	priorities['/'] = 1;
	priorities['+'] = 2; 
	priorities['-'] = 2;
	
	
	//Goes through each character of user input to determine postfix string
	for(int x = 0; x < expression.length(); x++){
		
		//If the current character is a deliminator and it's the first or the character before it is not alphanumeric then add it to postfix string
		if(expression[x] == '-' &&  (x == 0 || !isalnum(expression[x-1]))){
			
				postfix += expression[x];
				x++;
				while(isdigit(expression[x]) || expression[x] == '.'){
				
					postfix += expression[x];
					x++; 
				}
				x--;
				postfix += "_";
		}
		
		//If any character encountered is an operation symbol the stack is examined 
		else if(expression[x] == '+' || expression[x] == '/' || expression[x] == '*' || expression[x] == '-'){
		
			//Checks to see if stack is empty
			if(operator_stack.empty()){
				 
				operator_stack.push(expression[x]);
			}
			else{
				
			
				//If the top of the stack is at a higher priority than the current operator being examined
				if(priorities[operator_stack.top()] < priorities[expression[x]]){
					
					
					
					while(!operator_stack.empty() && priorities[operator_stack.top()] < priorities[expression[x]]){
						
						//Adds top of stack to postfix string
						postfix += operator_stack.top();
						postfix += "_";
						
						//popping stack
						operator_stack.pop(); 
						
					}
					
					//Pushes lower priority symbol onto stack
					operator_stack.push(expression[x]);
			
					
				}
				//If the top of the stack is at a lower priority than the current operator being examined
				else if(priorities[operator_stack.top()] > priorities[expression[x]]){
					
								
					operator_stack.push(expression[x]);
					
				}
				//If current symbol being analyzed is equal to top of the stack
				else{
					
					//Adds top of stack to postfix string
					postfix += operator_stack.top();
					postfix += "_";
						
					//popping stack
					operator_stack.pop(); 	
					operator_stack.push(expression[x]);
					
				}
			}
		}
		//If current character is not an operator
		else if(isdigit(expression[x]) || expression[x] == '.'){
			
			while(isdigit(expression[x]) || expression[x] == '.'){
				
					postfix += expression[x];
					x++; 
			}
			x--;
			postfix += "_";
		}
		else if(expression[x] != '_'){
			postfix += expression[x];
			postfix += "_";
		}
		
		
		
			
		
	}
	
	//If after the entire expression has been read anything still in the stack is appended to the postfix expression
	if(!operator_stack.empty()){
		
		while(!operator_stack.empty()){
			
			postfix += operator_stack.top(); 
			postfix += "_";
			
			operator_stack.pop(); 
			
		}
		
		
	}
	
	return postfix; 
}


//Function that takes postfix string and evaluates and calculates a solution
void evaluate_postfix(string postfix_expression){
	
	//Stack that stories numeric values 
	stack<double> expression_stack; 
	
	//Map that stories variable values based on user input
	map<char,double> variables; 
	
	//Variable that stores mathamatical results
	double variable_value; 
	
	int position = 0; 
	
	//Uses deliminator to break up the string
	while((position = postfix_expression.find("_")) != std::string::npos){
		
		//Stores current value of string in op variable
		string op = postfix_expression.substr(0,position);
		
		//erases previous value from string to increment 
		postfix_expression.erase(0,position+1);
		
		//If value is a number then it is changed from a string to a double and pushed onto the stack
		if(isdigit(op[0]) || op[0] == '.' || (op[0] == '-' && op.length() != 1)){
			
			expression_stack.push(stod(op));
		}
		//If value is a letter the user gets the opportunity to enter the value of the letter
		else if(isalpha(op[0])){
			
			if(variables.count(op[0]) != 1){
				
				cout << "Please enter the value of your variable " << op[0] << '\n';
				cin >> variable_value; 
				
				variables[op[0]] = variable_value; 
			
			}
			
			
			expression_stack.push(variables[op[0]]);
			
		}
		//Otherwise if the value entered is an operation symbol it is used for calculation
		else{
			
			double result, num1, num2; 
			
			if(expression_stack.empty()){
				cout << "Invalid Expression!" << '\n' << '\n';
				return; 
			}
			num2 = expression_stack.top(); 
			expression_stack.pop();
			
			if(expression_stack.empty()){
				cout << "Invalid Expression!" << '\n' << '\n';
				return; 
			}
			num1 = expression_stack.top(); 
			expression_stack.pop(); 
			
			if(op == "+"){
				result = num1 + num2; 
			}
			else if(op == "-"){
				result = num1 - num2; 
			}
			else if(op == "*"){
				result = num1 * num2; 
			}
			else if(op == "/"){
				result = num1 / num2; 
			}
			
			expression_stack.push(result);
			
		}

		
	}
	
	//Outputs results of calculation
	cout << "The result of your expression is... " << expression_stack.top() << '\n' << '\n'; 
	
	return;

	
	
	
	
}