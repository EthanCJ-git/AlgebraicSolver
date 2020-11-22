#include <string>
#include <memory>
#include "expression.h"

const std::string expression::toString()
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
	case(exp):
	    which = "^";
	    break;
    }

    output = which;
    output.append("{" + left->toString() + ", " + right->toString() + "}");
    return output;
}

//need to add exceptions for malformed input
expression::expression(std::string start, expression* parentPtr):
parent(parentPtr)
{
    //assigns expression if operator is present in string, else assign leaf
    auto assign = [&](const std::string &toCheck)
    {
	bool condition = false;
	condition = condition || toCheck.find("+");
	condition = condition || toCheck.find("-");
	condition = condition || toCheck.find("*");
	condition = condition || toCheck.find("/");
	condition = condition || toCheck.find("^");
	if(condition)
	    return std::make_unique<expression>(toCheck, this);
	else 
	    return std::unique_ptr<expression>(new leaf(toCheck, this));
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
	    case(exp):
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

    std::vector<Op> vals{ add, sub, mult, divi, exp };
    for(auto &val : vals)
    {
	check(start, val);
    }
    
    

}

expression::expression(expression* parentPtr):
parent(parentPtr),
left(),
right()
{}

leaf::leaf(std::string val, expression* parentPtr):
expression(parentPtr),
val(val)
{}

const std::string leaf::toString()
{
    std::string out(val);
    return out;
}
