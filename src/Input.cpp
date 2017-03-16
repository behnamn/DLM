/*
 *
 *	Input.cpp
 * 	Author: Behnam
 *
 */

#include "Input.h"

input_file::input_file() {
	true_values.insert("true");
	true_values.insert("1");
	true_values.insert("yes");
	true_values.insert("yup");
	true_values.insert("of course");

	false_values.insert("false");
	false_values.insert("0");
	false_values.insert("no");
	false_values.insert("nope");
	false_values.insert("are you crazy?");
}

Inputs::Inputs (int argc, char * argv[]) { 
	if (argc != 2){
		cout << "Usage: ./DLM input_file" << endl;
		exit (EXIT_FAILURE);	
	}
	else{
		file_name = argv[1];
	}
	loadInputFile();
	loadOptions();
	//print_params();
}

void Inputs::print_map(){
	cout << "\n______________________________Printing Input Map_____________________________\n";
	for(auto it = input.keys.cbegin(); it != input.keys.cend(); ++it){
    std::cout << it->first << " " << it->second.value << "\n";
	}
	cout << "_______________________________________________________________________________\n";
	cout << "\n";
}
void Inputs::print_params(){
	cout << "\n___________________________Printing Input Parameters_________________________\n";
	cout << "seed: " << seed << "\n";
	cout << "gamma: " << gamma << "\n";
	cout << "n_param: " << n_param << "\n";
	cout << "concentration: " << concentration << "\n";
	cout << "anneal: " << anneal << "\n";
	cout << "melt: : " << melt << "\n";
	cout << "cool_rate: " << cool_rate << "\n";
	cout << "n_cycles: " << n_cycles << "\n";
	cout << "max_temp: " << max_temp << "\n";
	cout << "min_temp: " << min_temp << "\n";
	cout << "const_T_interval: " << const_T_interval << "\n";
	cout << "seq_dependence: " << seq_dependence << "\n"; 
	cout << "trajectory_file: " << trajectory_file_name << "\n"; 
	cout << "occupancy_file: " << occupancy_file_name << "\n"; 
	cout << "scaffold_file: " << scaffold_file_name << "\n"; 
	cout << "staple_file: " << staple_file_name << "\n"; 
	cout << "domain_file: " << domain_file_name << "\n"; 
	cout << "print_state_interval: " << print_state_interval << "\n";
	cout << "staple_species: ";
	for (vector<int>::iterator it = staple_species.begin(); it!=staple_species.end(); ++it){
		cout << *it << "\t";
	}
	cout << "\n";
	cout << "_______________________________________________________________________________\n";
	cout << "\n";
}
void Inputs::loadInputFile() {
	FILE *inp_file = fopen(file_name, "r");
	if(inp_file == NULL) {
		fprintf(stderr, "Input file '%s' not found\n", file_name);
			input.state = -2;
			return;
	}
	loadInput(inp_file);
	fclose(inp_file);
	return;
}
void Inputs::loadInput(FILE *inp_file) {
	input.state = UNPARSED;
	addInput(inp_file);
	input.state = PARSED;
}
void Inputs::addInput(FILE *inp_file) {
	size_t alloc_size;
	char *c_option = NULL;
	string file_contents("");

	int count = 0;
	while(count != -1) {
		count = getline(&c_option, &alloc_size, inp_file);
		if(count != -1) file_contents += string(c_option);
		free(c_option);
		c_option = NULL;
	}

	addInput(file_contents);
}
void Inputs::addInput(std::string s_inp) {
	vector<string> tot_lines;
	boost::split(tot_lines, s_inp, boost::is_any_of("\n"));
	vector<string> lines;

	for(vector<string>::iterator it = tot_lines.begin(); it != tot_lines.end(); it++) {
		// remove in-line comments
		size_t comment_start = it->find('#');
		if(comment_start != string::npos) it->erase (comment_start, it->size() - comment_start);

		// split the string using ; as a delimiter
		std::vector<string> to_add;
		boost::split(to_add, *it, boost::is_any_of(";"));

		lines.insert(lines.end(), to_add.begin(), to_add.end());
	}

	std::vector<string>::iterator l_end = lines.end();
	for(std::vector<string>::iterator it = lines.begin(); it != lines.end(); it++) {
		//cout << *it << endl;
		string key, value;
		int res = readLine(it, l_end, key, value);

		if(res == KEY_READ){
			input_value new_value(value);

			input_map::iterator old_val = input.keys.find(key);
			input.keys[key] = value;
		}
	}
}
int readLine(std::vector<string>::iterator &it, std::vector<string>::iterator &end, string &key, string &value) {
	string option(*it);
	option = trim(option);

	if (option.size() > 0) {
		std::vector<string> words;
		boost::split(words, option, boost::is_any_of("="));;
		
		if (words.size() == 1) {
			return NOTHING_READ;
		}

		if (words.size() > 2) {
			for (unsigned int i = 2; i < words.size(); i ++) words[1] += string("=") + words[i];
		}

		string my_key = trim(words[0]);
		string my_value = trim(words[1]);

		if(my_value[0] == '{') {
			// counts the number of open and closed curly brackets 
			size_t open = std::count (my_value.begin(), my_value.end(), '{');
			size_t close = std::count (my_value.begin(), my_value.end(), '}');

			int sum = (int)open - (int)close; 

			if (sum < 0) {
				return NOTHING_READ;
			}

			if (sum > 0) my_value += string("\n");

			while (sum > 0) {
				it++;
				
				string new_line = string(*it);
				new_line = trim(new_line);
			
				sum += std::count (new_line.begin(), new_line.end(), '{');
				sum -= std::count (new_line.begin(), new_line.end(), '}');

				my_value += new_line;
				if(sum != 0) my_value += string("\n");
			}
		}

		key = my_key;
		value = my_value;
	}
	else return NOTHING_READ;

	return KEY_READ;
}

void Inputs::loadOptions(){
	getInputDouble("gamma", &gamma);
	getInputDouble("n_param", &n_param);
	getInputDouble("concentration", &concentration);

	getInputBool("seq_dependence", &seq_dependence);

	getInputDouble("max_temp", &max_temp);
	getInputDouble("min_temp", &min_temp);
	getInputDouble("cool_rate", &cool_rate);
	getInputInt("const_T_interval", &const_T_interval);
	getInputBool("anneal", &anneal);
	getInputBool("melt", &melt);
	getInputInt("n_cycles", &n_cycles);
	
	getInputInt("seed", &seed);
	getInputVectorInt("staple_species", &staple_species);

	getInputString("scaffold_file", scaffold_file_name);
	getInputString("domain_file", domain_file_name);
	getInputString("staple_file", staple_file_name);

	getInputString("trajectory_file", trajectory_file_name);
	getInputInt("print_state_interval", &print_state_interval);
	getInputString("occupancy_file", occupancy_file_name);
}

input_map::iterator Inputs::getInputValue(const char *skey)  {
	std::map<string, input_value>::iterator it = input.keys.find(string(skey));
	if(it != input.keys.end()) it->second.read++;
	return it;
}

int Inputs::getInputString(const char *skey, std::string &dest) {
	input_map::iterator it = getInputValue(skey);
	if(it == input.keys.end()) return KEY_NOT_FOUND;
		
	dest = it->second.value;

	return KEY_FOUND;
}

int Inputs::getInputString(const char *skey, char *dest) {
	string s_dest;
	int res = getInputString(skey, s_dest);
	if(res != KEY_FOUND) return res;
	strncpy(dest, s_dest.c_str(), sizeof(char) * (s_dest.size()+1));

	return KEY_FOUND;
}

int Inputs::getInputInt(const char *skey, int *dest) {
	input_map::iterator it = getInputValue(skey);
	if(it == input.keys.end()) return KEY_NOT_FOUND;

	*dest = (int) floor(atof(it->second.value.c_str())+0.1);

	return KEY_FOUND;
}

int Inputs::getInputBool(const char *skey, bool *dest) {
	input_map::iterator it = getInputValue(skey);
	if(it == input.keys.end()) return KEY_NOT_FOUND;

	// make it lower case
	string val = it->second.value;
	std::transform(val.begin(), val.end(), val.begin(), ::tolower);

	set<string>::iterator res = input.true_values.find(val);
	if(res != input.true_values.end()) *dest = true;
	else {
		res = input.false_values.find(val);
		if(res != input.false_values.end()) *dest = false;
	}

	return KEY_FOUND;
}

int Inputs::getInputDouble(const char *skey, double *dest) {
	input_map::iterator it = getInputValue(skey);
	if(it == input.keys.end()) return KEY_NOT_FOUND;

	*dest = atof(it->second.value.c_str());

	return KEY_FOUND;
}

int Inputs::getInputChar(const char *skey, char *dest) {
	input_map::iterator it = getInputValue(skey);
	if(it == input.keys.end()) return KEY_NOT_FOUND;

	*dest = it->second.value[0];

	return KEY_FOUND;
}
int Inputs::getInputVectorInt(const char *skey, vector<int> *dest) {
	input_map::iterator it = getInputValue(skey);
	if(it == input.keys.end()) return KEY_NOT_FOUND;

	int dummy;
	vector<string> str_vec;
	boost::split(str_vec, it->second.value, boost::is_any_of(" "));
	for (vector<string>::iterator nit = str_vec.begin(); nit!=str_vec.end(); ++nit){
		//cout << *nit << endl;
		dummy = (int) floor(atof(nit->c_str())+0.1);
		dest->push_back(dummy);
	}

	return KEY_FOUND;
}
