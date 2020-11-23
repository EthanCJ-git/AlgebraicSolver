#include <string>
#include <memory>
#include <iostream>
#include "expression.h"
#include <math.h>

expressable::expressable(expressable* parentPtr): parent(parentPtr) {}

std::string expression::toString()
{
    std::string which;
    std::string output;
    switch(this->kind)
    {
	case(add):
	    which = "+";
	    break;
	case(sub):
	    which = "-";
	    break;
	case(mult):
	    which = "*";
	    break;
	case(divi):
	    which = "/";
	    break;
	case(expo):
	    which = "^";
	    break;
    }

    output = which;
    output.append("{" + left->toString() + ", " + right->toString() + "}");
    return output;
}

//need to add exceptions for malformed input
expression::expression(std::string start, expressable* parentPtr):
expressable(parentPtr)
{
    //assigns expression if operator is present in string, else assign leaf
    auto assign = [&](const std::string &check)
    {
	bool condition = false;
	condition = condition || check.find("+") != std::string::npos;
	condition = condition || check.find("-") != std::string::npos;
	condition = condition || check.find("*") != std::string::npos;
	condition = condition || check.find("/") != std::string::npos;
	condition = condition || check.find("^") != std::string::npos;
	if(condition)
	    return std::unique_ptr<expressable>(new expression(check, this));
	else 
	    return std::unique_ptr<expressable>(new leaf(check, this));
    };

    //looks for next operator to split on, and assigns left and right
    auto check = [&](const std::string &toCheck, const Op &operation)
    {
	int level = 0;
	char which;
	switch(operation)
    	{
	    case(add):
	        which = '+';
		break;
	    case(sub):
	        which = '-';
		break;
	    case(mult):
	    	which = '*';
		break;
	    case(divi):
	    	which = '/';
		break;
	    case(expo):
	    	which = '^';
		break;
    	}
	
	int i = 0;
	for(char letter : toCheck)
	{
	    if(letter == '(') ++level;
	    if(letter == ')') --level;
	    if(level == 0 && letter == which)
	    {
		this->kind = operation;
		this->left = assign(start.substr(0, i));
		this->right = assign(start.substr(i+1));
		return true;
	    }

	    ++i;
	}//end for
	return false;
    };//check

    if(start.at(0) == '(' && start.at(start.length()-1) == ')')
    {
	start = start.substr(1, std::string::npos);
	start.pop_back();
    }

    std::vector<Op> vals{ add, sub, mult, divi, expo };
    for(auto &val : vals)
    {
	if(check(start, val)) break;
    }
    
    

}

std::string expression::getValue()
{
    std::string leftStr = left->getValue();
    std::string rightStr = right->getValue();
    std::string output;
    double leftVal = atof(leftStr.data());
    double rightVal = atof(rightStr.data());
    if(leftVal != 0.0 && rightVal != 0.0)
    {
	switch(kind)
    	{
	    case(add):
	        output = std::to_string(leftVal+rightVal);
		break;
	    case(sub):
	        output = std::to_string(leftVal-rightVal);
		break;
	    case(mult):
	    	output = std::to_string(leftVal*rightVal);
		break;
	    case(divi):
	    	output = std::to_string(leftVal/rightVal);
		break;
	    case(expo):
	    	output = std::to_string(pow(leftVal, rightVal));
		break;
    	}
    }
    
    else
    {
	char which;
	switch(kind)
    	{
            case(add):
            	which = '+';
	    	break;
	    case(sub):
	    	which = '-';
	    	break;
	    case(mult):
            	which = '*';
	    	break;
	    case(divi):
	    	which = '/';
	    	break;
	    case(expo):
	    	which = '^';
	    	break;
    	}
	output.append(leftStr);
    	output.append(std::string(1, which));
    	output.append(rightStr);
    }
    while(output.find('.') != std::string::npos && output.back() == '0')
	output.pop_back();
    if(output.back() == '.')
	output.pop_back();
    return output;
}

leaf::leaf(std::string val, expressable* parentPtr): 
expressable(parentPtr),
val(val)
{}

std::string leaf::toString()
{
    std::string out(val);
    return out;
}
std::string leaf::getValue()
{
    std::string out(val);
    return out;
}
