// Mihai Oprescu
// -------------
// Options class..

#include "Opt.H"
#include <cstdlib>
#include <sstream>
using namespace std;

// class Opt destructor
Opt::~Opt(){
	for ( it=omap.begin() ; it != omap.end(); it++ ){
		delete (*it).second;
	}
}

// process function
void Opt::process(int argc, char * argv[]){
	int index = 1;	// use 'index' to keep track of argument pointer
	while(index < argc){

		// for each argument, save the type of arg and obj_name
		// when necessary in type_arg and obj_name respectively
		string argumentAtIndex = argv[index];
		string type_arg = "fail";
		string obj_name = "fail";
		for ( it=omap.begin() ; it != omap.end(); it++ ){		// iterate through the map
			if ( (*it).first == argv[index] ){							
				type_arg = (*it).second->type;
				obj_name = (*it).first;
			}
		}

		// go through each type and set the value of the option	according to the argument
		if (type_arg == "switch"){								// SWITCH ----------
			//set_switch(obj_name);				// set value of switch option
			bool boo = 1;
			set(obj_name, boo);
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
				bool boo = v;
				set(obj_name, boo);				// set value of bool option
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
				cerr << "value syntax error for option " << argv[index] << " (" << 
					argv[index + 1] << ") " << endl;
				exit(20);
			}	// if.. Conversion failed !
			if (in.good()){		// check if there is illegal syntax present after int was read
				cerr << "value syntax error for option " << argv[index] << " (" << 
					argv[index + 1] << ") " << endl;
				exit(20);
			}

			set(obj_name, v);				// set value of int option
			index = index + 2;
		}else if (type_arg == "double"){	// DOUBLE ----------
			// check for missing value
			if (argv[index+1] == NULL){
				cerr << "missing value " << endl;
				exit(20);
			}
			
			// convert to int
			istringstream in(argv[index+1]);
			double v; // or double or whatever
			in >> v;
			if (in.fail()){
				cerr << "value syntax error for option " << argv[index] << " (" << 
				argv[index + 1] << ") " << endl;
				exit(20);
			}	// if.. Conversion failed !
			if (in.good()){		// check if there is illegal syntax present after double was read
				cerr << "value syntax error for option " << argv[index] << " (" << 
				argv[index + 1] << ") " << endl;
				exit(20);
			}

			// set value of double option
			set(obj_name, v);				
			index = index + 2;
		}else if (type_arg == "string"){							// STRING ----------
			// check for missing value
			if (argv[index+1] == NULL){
				cerr << "missing value " << endl;
				exit(20);
			}
			string str = argv[index+1];
			set(obj_name, str);	// set value of string option
			index = index + 2;
		}else if (type_arg == "fail"){								// NO MATCH ----------
			cerr << "unknown option " << argv[index] << endl;
			this->printChoices();									// print choices available and exit
			exit(20);
		}

	}
}

bool Opt::checkMultiples(string &name_arg){
	for ( it=omap.begin() ; it != omap.end(); it++ ){		// iterate through the map
		if ( (*it).first == name_arg ){							// duplicate name found ..
			return false;
		}
	}
	return true;									// return true otherwise
}

void Opt::printChoices(){	// print all the choices available to the user if an unknown option is passed to the program
	cerr << "choices are:" << endl;
	for ( it=omap.begin() ; it != omap.end(); it++ ){		// iterate through the map
		cerr << (*it).first << " : " << (*it).second->descr <<
			" [" << (*it).second->type << "] ";
		if ( (*it).second->type == "switch"){
			cerr << endl;
		}else if (( (*it).second->type == "bool")){
			cerr << get<bool>((*it).first) << endl;
		}else if (( (*it).second->type == "int")){
			cerr << get<int>((*it).first) << endl;
		}else if (( (*it).second->type == "double")){
			cerr << get<double>((*it).first) << endl;
		}else if (( (*it).second->type == "string")){
			cerr << get<string>((*it).first) << endl;
		}
	}
}
