#include <stdlib.h>
#include <memory>
#include <string>
#include <vector>


enum Op { add, sub, mult, divi, expo };

class expressable 
{
  protected:
    expressable* parent;		//this pointer is safe because the whole
    expressable(expressable* parentPtr);//object will be deleted if the parent
					//is deleted -- no leak possible
  public:				
    virtual std::string toString() = 0;
    virtual std::string getValue() = 0;
};

class expression : public expressable
{
  protected:	
    std::unique_ptr<expressable> left;   
    std::unique_ptr<expressable> right; 
    Op kind;


  public:
    expression(std::string start, expressable* parentPtr);
    std::string toString();
    std::string getValue(); 
};

class leaf : public expressable
{
  protected:
    std::string val;
  public:
    leaf(std::string val, expressable* parent);

    std::string toString();
    std::string getValue();
};


