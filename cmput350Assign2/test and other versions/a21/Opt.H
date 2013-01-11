#ifndef OPT_H
#define OPT_H

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

/////////////////////////////////////////////////////////////
// Class which manages command line options for a program. //
/////////////////////////////////////////////////////////////

class Opt
{
public:

	Opt(){};
    ~Opt();

  // add_x functions
	void add_switch(std::string input1, std::string input2);
	void add_bool(std::string input1, std::string input2, bool input3);
	void add_int(std::string input1, std::string input2, int input3);
	void add_double(std::string input1, std::string input2, double input3);
	void add_string(std::string input1, std::string input2, std::string input3);
  // get_x functions
	bool get_switch(const std::string &name_arg) const;
	bool get_bool(const std::string &name_arg) const;
	int get_int(const std::string &name_arg) const;
	double get_double(const std::string &name_arg) const;
	std::string get_string(const std::string &name_arg) const;
  // set_x functions
	void set_switch(std::string &name_arg);
	void set_bool(std::string &name_arg, int value_arg);
	void set_int(std::string &name_arg, int value_arg);
	void set_double(std::string &name_arg, double value_arg);
	void set_string(std::string &name_arg, std::string value_arg);
  // process
  void process(int argc, char * argv[]);

private:
  // copy constructor  
  Opt(const Opt &rhs);

  // assignment operator  
  Opt &operator=(const Opt &rhs); 
  
  // forward declaration of Option classes
  // define those classes in Opt.C
  class OptionBase;
  class BoolOption;
  class SwitchOption;
  class IntOption;
  class DoubleOption;
  class StringOption;
  
  // collection of added options
  // use option.push_back(p) to add new pointer
  // and options[i] to retrieve the i-th option
  // option.size() returns the current number of options
  std::vector<OptionBase*> options;

  // no other data members permitted

  // helper functions go here ...
    void printChoices();
	bool checkAddMultiples(std::string &name);
};

#endif
