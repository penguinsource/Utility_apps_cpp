#include "Opt.H"
#include <cstdlib>
#include <sstream>
using namespace std;

// abstract option base-class, every member function is virtual
// because we want to access them via base-class pointers.
// All members are common to all derived Option classes
class Opt::OptionBase
{
public:

  string name;   // name of option
  string descr;  // its description
  string type;

  virtual ~OptionBase(){};
};

// struct definitions
struct Opt::SwitchOption : public Opt::OptionBase
{

public:
	~SwitchOption(){}
	bool switch_value;
};

struct Opt::BoolOption : public Opt::OptionBase
{
public:
	~BoolOption(){}
  bool bool_value;
};

struct Opt::IntOption : public Opt::OptionBase
{
public:
	~IntOption(){}
  int int_value;
};

struct Opt::DoubleOption : public Opt::OptionBase
{
public:
	~DoubleOption(){}
  double double_value;
};

struct Opt::StringOption : public Opt::OptionBase
{
public:
	~StringOption(){}
  string string_value;
};

// class Opt destructor
Opt::~Opt(){
	for (unsigned int i = 0; i < options.size(); i++){
		delete options[i];
	}
}

// --------------
// add_x functions

// adding a switch option to the 'options' vector
void Opt::add_switch(string input1, string input2){
	if (checkAddMultiples(input1)){								
		SwitchOption *obj = new SwitchOption();		// create switch option
		obj->name = input1;							// save name, descr, value
		obj->descr = input2;						
		obj->switch_value = 0;						
		obj->type = "switch";						// set type
		options.push_back(obj);						// push object on vector 'options'
	}else {
		cerr << "duplicate option " << input1 << endl;	// option with name 'input1' already defined
		exit(20);
	}
}

// adding a bool option to the 'options' vector
void Opt::add_bool(string input1, string input2, bool input3){
	if (checkAddMultiples(input1)){		
		BoolOption *obj = new BoolOption();		// create bool option
		obj->name = input1;						// save name, descr, value
		obj->descr = input2;
		obj->bool_value = input3;
		obj->type = "bool";						// set type
		options.push_back(obj);					// push object on vector 'options'
	}else {
		cerr << "duplicate option " << input1 << endl;	// option with name 'input1' already defined
		exit(20);
	}
}

// adding an int option to the 'options' vector
void Opt::add_int(string input1, string input2, int input3){
	if (checkAddMultiples(input1)){	
		IntOption *obj = new IntOption();		// create int option
		obj->name = input1;						// save name, descr, value
		obj->descr = input2;
		obj->int_value = input3;
		obj->type = "int";						// set type
		options.push_back(obj);					// push object on vector 'options'
	}else {
		cerr << "duplicate option " << input1 << endl;	// option with name 'input1' already defined
		exit(20);
	}
}

// adding a double option to the 'options' vector
void Opt::add_double(string input1, string input2, double input3){
	if (checkAddMultiples(input1)){	
		DoubleOption *obj = new DoubleOption();		// create double option
		obj->name = input1;							// save name, descr, value
		obj->descr = input2;
		obj->double_value = input3;
		obj->type = "double";						// set type
		options.push_back(obj);						// push object on vector 'options'
	}else {
		cerr << "duplicate option " << input1 << endl;	// option with name 'input1' already defined
		exit(20);
	}
}

// adding a string option to the 'options' vector
void Opt::add_string(string input1, string input2, string input3){
	if (checkAddMultiples(input1)){	
		StringOption *obj = new StringOption();		// create string option
		obj->name = input1;							// save name, descr, value
		obj->descr = input2;
		obj->string_value = input3;
		obj->type = "string";						// set type
		options.push_back(obj);						// push object on vector 'options'
	}else {
		cerr << "duplicate option " << input1 << endl;	// option with name 'input1' already defined
		exit(20);
	}
}

// -------------
// process function
void Opt::process(int argc, char * argv[]){
	int index = 1;	// use 'index' to keep track of argument pointer
	while(index < argc){

		// for each argument, save the type of arg and obj_name
		// when necessary in type_arg and obj_name respectively
		string argumentAtIndex = argv[index];
		string type_arg = "fail";
		string obj_name = "fail";
		for (unsigned int u = 0; u < options.size(); u++){
			if (options[u]->name == argv[index]){
				type_arg = options[u]->type;
				obj_name = options[u]->name;
			}
		}

		// go through each type and set the value of the option
		// according to the argument
		if (type_arg == "switch"){								// SWITCH ----------
			set_switch(obj_name);				// set value of switch option
			index = index + 1;
		}else if (type_arg == "bool"){							// BOOL ----------
			// check for missing value
			if (argv[index+1] == NULL){
				cerr << "missing value " << endl;
				exit(20);
			}

			/* Check if there's more than 1 digit */
			string checkDigit(argv[index+1]);
			if (checkDigit.size() > 1){
				cerr << "value syntax error for option " << argv[index] << " (" << 
					argv[index + 1] << ") " << endl;
				exit(20);
			}

			// convert to int
			istringstream in(argv[index+1]);
			int v; // or double or whatever
			in >> v;
			if (in.fail()){}	// if.. Conversion failed !
			if (in.good()){		// check if there is illegal syntax present after int was read
				cerr << "value syntax error for option " << argv[index] << " (" << 
					argv[index + 1] << ") " << endl;
				exit(20);
			}
			
			// check if v is 1 or 0.
			if ((v == 1) || (v == 0)) {
				set_bool(obj_name, v);				// set value of bool option
				index = index + 2;
			}else {
				cerr << "value syntax error for option " << argv[index] << " (" << 
					argv[index + 1] << ") " << endl;
				exit(20);
			}
		}else if (type_arg == "int"){							// INT ----------
			// check for missing value
			if (argv[index+1] == NULL){
				cerr << "missing value " << endl;
				exit(20);
			}

			// convert to int
			istringstream in(argv[index+1]);
			int v; // or double or whatever
			in >> v;
			if (in.fail()){
				
			}	// if.. Conversion failed !
			if (in.good()){		// check if there is illegal syntax present after int was read
				cerr << "value syntax error for option " << argv[index] << " (" << 
					argv[index + 1] << ") " << endl;
				exit(20);
			}

			set_int(obj_name, v);				// set value of int option
			index = index + 2;
		}else if (type_arg == "double"){							// DOUBLE ----------
			// check for missing value
			if (argv[index+1] == NULL){
				cerr << "missing value " << endl;
				exit(20);
			}

			// convert to int
			istringstream in(argv[index+1]);
			double v; // or double or whatever
			in >> v;
			if (in.fail()){}	// if.. Conversion failed !
			if (in.good()){		// check if there is illegal syntax present after double was read
				cerr << "value syntax error for option " << argv[index] << " (" << 
					argv[index + 1] << ") " << endl;
				exit(20);
			}

			// set value of double option
			set_double(obj_name, v);				
			index = index + 2;
		}else if (type_arg == "string"){							// STRING ----------
			// check for missing value
			if (argv[index+1] == NULL){
				cerr << "missing value " << endl;
				exit(20);
			}

			set_string(obj_name, argv[index+1]);	// set value of string option
			index = index + 2;
		}else if (type_arg == "fail"){								// NO MATCH ----------
			cerr << "unknown option " << argv[index] << endl;
			this->printChoices();									// print choices available and exit
			exit(20);
		}

	}
}

// -------------
// set_x functions

// set the value of a switch option
void Opt::set_switch(string &name_arg){
	for (unsigned int y = 0; y < options.size(); y++){
		if ((options[y]->type == "switch") && (options[y]->name == name_arg)){
			SwitchOption *o = dynamic_cast<SwitchOption*>(options[y]);	// cast OptionBase to SwitchOption
			assert(o !=0);				// check to see if cast was successful
			o->switch_value = 1;
		}
	}
}

// set the value of a bool option
void Opt::set_bool(string &name_arg, int value_arg){
	for (unsigned int y = 0; y < options.size(); y++){
		if ((options[y]->type == "bool") && (options[y]->name == name_arg)){
			BoolOption *o = dynamic_cast<BoolOption*>(options[y]);	// cast OptionBase to BoolOption
			assert(o !=0);				// check to see if cast was successful
			o->bool_value = value_arg;
		}
	}
}

// set the value of an int option
void Opt::set_int(string &name_arg, int value_arg){
	for (unsigned int y = 0; y < options.size(); y++){
		if ((options[y]->type == "int") && (options[y]->name == name_arg)){
			IntOption *o = dynamic_cast<IntOption*>(options[y]);	// cast OptionBase to IntOption
			assert(o !=0);				// check to see if cast was successful
			o->int_value = value_arg;
		}
	}
}

// set the value of a double option
void Opt::set_double(string &name_arg, double value_arg){
	for (unsigned int y = 0; y < options.size(); y++){
		if ((options[y]->type == "double") && (options[y]->name == name_arg)){
			DoubleOption *o = dynamic_cast<DoubleOption*>(options[y]);	// cast OptionBase to DoubleOption
			assert(o !=0);				// check to see if cast was successful
			o->double_value = value_arg;
		}
	}
}

// set the value of a string option
void Opt::set_string(string &name_arg, string value_arg){
	for (unsigned int y = 0; y < options.size(); y++){
		if ((options[y]->type == "string") && (options[y]->name == name_arg)){
			StringOption *o = dynamic_cast<StringOption*>(options[y]);	// cast OptionBase to StringOption
			assert(o !=0);				// check to see if cast was successful
			o->string_value = value_arg;
		}
	}
}

// -------------
// get_x functions

// get a switch option
bool Opt::get_switch(const std::string &name_arg) const
{
	int name_exists = 0;							// to check if the name exists in the list
	for (unsigned int p = 0; p < options.size(); p++){
		if ((options[p]->type == "switch") && (options[p]->name == name_arg) ){
			SwitchOption *obj_temp = dynamic_cast<SwitchOption*>(options[p]);	// cast to specific option
			assert(obj_temp != 0);							// assert that cast worked
			return obj_temp->switch_value;					// return value of switch
		}
		if (options[p]->name == name_arg)
			name_exists = 1;
	}

	if (name_exists == 1){							// an option with name 'name_arg exists'
		cerr << "in get_switch " << name_arg << " is not a switch option" << endl;
		exit(20);
	}
														// unknown option tried to be retrieved
	cerr << "tried to retrieve unknown option " << name_arg << endl;
	exit(20);
	return 0;
}

// get a bool option
bool Opt::get_bool(const std::string &name_arg) const
{
	int name_exists = 0;							// to check if the name exists in the list
	for (unsigned int p = 0; p < options.size(); p++){
		if ((options[p]->type == "bool") && (options[p]->name == name_arg) ){
			BoolOption *obj_temp = dynamic_cast<BoolOption*>(options[p]);	// cast to specific option
			assert(obj_temp != 0);							// assert that cast worked
			return obj_temp->bool_value;					// return value of bool
		}
		if (options[p]->name == name_arg)
			name_exists = 1;
	}

	if (name_exists == 1){							// an option with name 'name_arg exists'
		cerr << "in get_bool " << name_arg << " is not a bool option" << endl;
		exit(20);
	}
														// unknown option tried to be retrieved
	cerr << "tried to retrieve unknown option " << name_arg << endl;
	exit(20);
	return 1;
}

// get an int option
int Opt::get_int(const std::string &name_arg) const
{
	int name_exists = 0;							// to check if the name exists in the list
	for (unsigned int p = 0; p < options.size(); p++){
		if ((options[p]->type == "int") && (options[p]->name == name_arg) ){
			IntOption *obj_temp = dynamic_cast<IntOption*>(options[p]);	// cast to specific option
			assert(obj_temp != 0);							// assert that cast worked
			return obj_temp->int_value;						// return value of int
		}
		if (options[p]->name == name_arg)
			name_exists = 1;
	}

	if (name_exists == 1){							// an option with name 'name_arg exists'
		cerr << "in get_int " << name_arg << " is not an int option" << endl;
		exit(20);
	}
														// unknown option tried to be retrieved
	cerr << "tried to retrieve unknown option " << name_arg << endl;
	exit(20);
	return 0;
}

// get a double option
double Opt::get_double(const std::string &name_arg) const
{
	int name_exists = 0;							// to check if the name exists in the list
	for (unsigned int p = 0; p < options.size(); p++){
		if ((options[p]->type == "double") && (options[p]->name == name_arg) ){
			DoubleOption *obj_temp = dynamic_cast<DoubleOption*>(options[p]);	// cast to specific option
			assert(obj_temp != 0);							// assert that cast worked
			return obj_temp->double_value;					// return value of double
		}
		if (options[p]->name == name_arg)
			name_exists = 1;
	}

	if (name_exists == 1){							// an option with name 'name_arg exists'
		cerr << "in get_double " << name_arg << " is not a double option" << endl;
		exit(20);
	}
														// unknown option tried to be retrieved
	cerr << "tried to retrieve unknown option " << name_arg << endl;
	exit(20);
	return 0;
}

// get a string option
string Opt::get_string(const std::string &name_arg) const
{
	int name_exists = 0;							// to check if the name exists in the list
	for (unsigned int p = 0; p < options.size(); p++){
		if ((options[p]->type == "string") && (options[p]->name == name_arg) ){
			StringOption *obj_temp = dynamic_cast<StringOption*>(options[p]);	// cast to specific option
			assert(obj_temp != 0);							// assert that cast worked
			return obj_temp->string_value;					// return value of string
		}
		if (options[p]->name == name_arg)
			name_exists = 1;
	}

	if (name_exists == 1){							// an option with name 'name_arg exists'
		cerr << "in get_string " << name_arg << " is not a string option" << endl;
		exit(20);
	}
													// unknown option tried to be retrieved
	cerr << "tried to retrieve unknown option " << name_arg << endl;
	exit(20);
	return 0;
}

bool Opt::checkAddMultiples(string &name_arg){
	unsigned int n;
	for (n = 0; n < options.size(); n++){			// go through each option
			if (options[n]->name == name_arg){		// if it has the name.. it's a replicate
				return false;
			}
	}
	return true;									// return true otherwise
}

// print all the choices available to the user if an unknown option is passed to the program
void Opt::printChoices(){
	cerr << "choices are:" << endl;
	for (unsigned int i = 0; i < options.size(); i++){
		cerr << options[i]->name << " : " << 
			options[i]->descr << "  [" << options[i]->type << "] ";
		if (options[i]->type == "switch"){					// print value of switch
			cerr << endl;
		}else if (options[i]->type == "bool"){				// print value of bool
			cerr << get_bool(options[i]->name) << endl;
		}else if (options[i]->type == "int"){				// print value of int
			cerr << get_int(options[i]->name) << endl;
		}else if (options[i]->type == "double"){			// print value of double
			cerr << get_double(options[i]->name) << endl;
		}else if (options[i]->type == "string"){			// print value of string
			cerr << get_string(options[i]->name) << endl;
		}
	}
}
