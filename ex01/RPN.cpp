#include "RPN.hpp"

/* Orthodox Canonical Form */
RPN::RPN()
{
	std::cout << "(RPN) Default Constructor called" << std::endl;
}

RPN::RPN(const RPN& rhs) : _stk(rhs._stk)
{
	std::cout << "(RPN) Copy Constructor called"  << std::endl;
}

RPN::~RPN()
{
	std::cout << "(RPN) Destructor called" << std::endl;
}

RPN& RPN::operator=(const RPN& rhs)
{
	std::cout << "(RPN) Copy assignment operator called" << std::endl;
	if (this == &rhs)
		return *this;
	_stk = rhs._stk;
	return *this;
}

/* Function */
int	RPN::calcRPN(const std::string& strRPN)
{
	std::istringstream iss(strRPN);
	std::string token;

	while (iss >> token)
	{
		if (token == "+" || token == "-" || token == "*" || token == "/")
			processCharOperation(token);
		else
			processNum(token);
	}
	if (_stk.size() != 1)
	{
		std::cerr << "Error: invalid argv[1]" << std::endl;
		exit(1);
	}

	return _stk.top();
}

void	RPN::processCharOperation(const std::string& token)
{
	if (_stk.size() < 2)
	{
		std::cerr << "Error: insufficient operands for " << token << std::endl;
		exit(1);
	}
	int operand2 = _stk.top(); _stk.pop();
	int operand1 = _stk.top(); _stk.pop();

	if (token == "+") _stk.push(operand1 + operand2);
	else if (token == "-") _stk.push(operand1 - operand2);
	else if (token == "*") _stk.push(operand1 * operand2);
	else if (token == "/")
	{
		if (operand2 == 0)
		{
			std::cerr << "Error: division by zero" << std::endl;
			exit(1);
		}
		_stk.push(operand1 / operand2);
	}
}

void	RPN::processNum(const std::string& token)
{
	std::istringstream issToken(token);
	int num;
	if (issToken >> num)
		_stk.push(num);
	else
	{
		std::cerr << "Error: invalid token " << token << std::endl;
		exit(1);
	}
}
