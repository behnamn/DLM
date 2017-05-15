/*
 *
 *	Input.h
 * 	Author: Behnam
 *
 */

#ifndef INPUT_H_
#define INPUT_H_

#include "Common.h"
//#include "Common.h"
//#include "Constants.h"

#define UNPARSED 0
#define PARSED 1
#define ERROR 2
#define KEY_NOT_FOUND -1
#define KEY_FOUND 0
#define KEY_INVALID 1

#define INP_EOF -1
#define KEY_READ 0
#define NOTHING_READ 1

int readLine(std::vector<string>::iterator &it, std::vector<string>::iterator &end, string &key, string &value);

static inline std::string &ltrim(std::string &s) {
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
	return s;
}
static inline std::string &rtrim(std::string &s) {
	s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
	return s;
}
static inline std::string &trim(std::string &s) {
	return ltrim(rtrim(s));
}

struct input_value {
	std::string value;
	int read;
	input_value() : value(""), read(0) {}
	input_value(std::string v) : value(v), read(0) {}
};

typedef std::map<std::string, input_value> input_map;
struct input_file {
    input_map keys;
    std::vector<std::string> unread_keys;
    int state;
    std::set<std::string> true_values;
    std::set<std::string> false_values;
    input_file();
};

class Inputs{
public:
    Inputs(int argc, char * argv[]);
    Inputs();
    virtual ~Inputs(){}

    const char * file_name;
    input_file input;

    void print_map();
    void print_params();
    
    void loadInputFile();
    void loadInput(FILE *);
    void addInput(string);
    void addInput(FILE *);
    
    void loadOptions();
    input_map::iterator getInputValue(const char *skey);
    int getInputString(const char *skey, std::string &dest);
    int getInputString(const char *skey, char *dest);
    int getInputBool(const char *skey, bool *dest);
    int getInputDouble(const char *skey, double *dest);
    int getInputInt(const char *skey, int *dest);
    int getInputVectorInt(const char *skey, vector<int> *dest);
    int getInputChar(const char *skey, char *dest); 
    
    double gamma;
    double n_param;
    double concentration;
    
    bool seq_dependence;
    
    double max_temp;
    double min_temp;
    double cool_rate;
    int const_T_interval;
    bool anneal;
    bool melt;
    int n_cycles;
    
    int seed;
    
    vector<int> staple_species;
    
    string scaffold_file_name;
    string domain_file_name;
    string staple_file_name;

    string statistics_file_name;

    int write_transition_every;
    string transition_file_name;
    
    int write_state_every;
    string trajectory_file_name;
    
    bool make_movie;
    
    //string occupancy_file_name;
};

#endif
