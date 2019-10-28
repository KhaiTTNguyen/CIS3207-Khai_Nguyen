// Khai Nguyen
// Filename: function.cpp
// Usage: to build functions

#include "header.h"

    /*
    // Ask for dictionary
    // if none is provided - use DEFAULT_DICTIONARY 
    
    // Ask for port number
    // if none is provided - use DEFAULT_PORT
    */
set<string> load_dictionary(void){

    set<string> word_dict;
    set<string>::iterator it = word_dict.begin(); 

    // Ask for dictionary file
    // if none is provided - use DEFAULT_DICTIONARY     
    ifstream input;
    string filename;

    cout << "Specify a dictionary file : ";
    getline(std::cin, filename);

    if (filename == ""){
        filename = "dictionary.txt";
        input.open(filename.c_str());
    } else {
        input.open(filename.c_str());
        while(input.fail()){
            input.clear();
            cout<<"Incorrect filename, please enter again: ";
            cin>>filename;
            input.open(filename.c_str());
        }
    }

    for(string line; getline(input,line );){
        // add line to Set
        word_dict.insert(line); 
    }

    return word_dict;
}