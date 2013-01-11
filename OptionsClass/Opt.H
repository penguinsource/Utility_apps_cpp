// Mihai Oprescu
// -------------
// Options class..

#ifndef OPT_H
#define OPT_H

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <typeinfo>
#include <map>
#include <cstring>

// Class which manages command line options for a program. //

class Opt
{
public:

	Opt(){};
    ~Opt();

	template <class T>						// template class for function that inits an option
	void add(std::string input1, T input2, std::string input3){
		if (checkMultiples(input1)){
				OptT<T> *newObj = new OptT<T>(input1,input2,input3);	// create pointer to an option of type T
				omap[input1] = newObj;											// add object to map
		}else {
			std::cerr << "duplicate option " << input1 << std::endl;			// option with name 'input1' already defined
			exit(20);
		}
	}
	
	//template <class T>
	void add(std::string input1, std::string input2){								// this add is specific for switch options 
		if (checkMultiples(input1)){											// (only 2 arguments)
			OptT<bool> *newObj = new OptT<bool>(input1,input2);	// create pointer to an option of type T
			omap[input1] = newObj;
		}else {
			std::cerr << "duplicate option " << input1 << std::endl;			// option with name 'input1' already defined
			exit(20);
		}
	}

	template <class T>							// template class for function that gets the value of an option
	T get(std::string input1){
		for ( it=omap.begin() ; it != omap.end(); it++ ){		// iterate through the map
			if ( (*it).first == input1 ){							// duplicate name found ..
				OptT<T> *obj_temp = dynamic_cast< OptT<T> *>( (*it).second );	// cast to specific option
				if (obj_temp == 0){							// assert that cast worked
					std::cerr << "incorrect option type at 'get<option>'. option with name " << input1 << " is of type '" << (*it).second->type << "'" << std::endl;
					exit(20);					// exit program !
				}
				return obj_temp->get();
			}

		}
		std::cerr << "no option found with name " << input1 << std::endl; 
		exit(20);								// exit program !

		return 0;
	}
	
	template <class T>
	void set(std::string input1, T value_arg){
		for ( it=omap.begin() ; it != omap.end(); it++ ){			// iterate through the map
			if ( (*it).first == input1 ){							// duplicate name found ..
				OptT<T> *obj_temp = dynamic_cast< OptT<T> *>( (*it).second );	// cast to specific option
				assert(obj_temp != 0);							// assert that cast worked		// if this fails, that means the name input1 is matching a different type of option ****
				obj_temp->set(value_arg);
				break;
			}
		}
	}
	
  // process
  void process(int argc, char * argv[]);

private:
  Opt(const Opt &rhs);  // copy constructor  
  Opt &operator=(const Opt &rhs); 	  // assignment operator  
	class OptionBase
	{
		public:

		std::string name;   // name of option
		std::string descr;  // its description
		std::string type;	// its type

		virtual ~OptionBase(){};
	};

  std::map<std::string, OptionBase*>::iterator it;			// iterator for the map
  std::map<std::string, OptionBase*> omap;					// map holds all the options and their names
  
	template <class T> 
	class OptT : public OptionBase
	{
		T value;
	public:
		// constructor for all options except the switch option(s)
		OptT(std::string input1, T input2, std::string input3){
			name = input1;
			value = input2;
			descr = input3;
		
			if (strcmp(typeid(input2).name(),"b") == 0){
				type = "bool";
			}else if (strcmp(typeid(input2).name(),"i") == 0){
				type = "int";
			}else if (strcmp(typeid(input2).name(),"d") == 0){
				type = "double";
			}else if (strcmp(typeid(input2).name(),"Ss") == 0){
				type = "string";
			}
		}
		
		OptT(std::string input1, std::string input2){		// constructor for switch option(s)
			name = input1;
			descr = input2;
			value = 0;
			type = "switch";
		}
		// getter for value of type T
		T get(){
			return value;
		}
		// setter for value of type T
		void set(T value_arg){
			value = value_arg;
		}
		// setter for the switch option
		void set(){
			value = 1;
		}
	
	};

  // helper functions=
  void printChoices();
  bool checkMultiples(std::string &name);
};

#endif
