#include <stdlib.h>
#include <memory>
#include <string>
#include <vector>

/*	I need to refactor this. Leaf and expression should inherit 
 *	from a shared abstract base class (interface). I'll do that
 *	later; I want to get some output on the screen first.
 */

enum Op { add, sub, mult, divi, exp };

class expression 
{
  protected:
    expression(expression* parentPtr);
    expression* parent; 		//this pointer is safe because this
    std::unique_ptr<expression> left;   //object will be deleted if the 
    std::unique_ptr<expression> right;  //parent is deleted
    Op kind;


  public:
    expression(std::string start, expression* parentPtr);
    virtual const std::string toString();    
};

class leaf : public expression
{
  protected:
    std::string val;
  public:
    leaf(std::string val, expression* parent);

    const std::string toString();
    
};


