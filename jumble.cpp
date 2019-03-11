
#include "jumble.h"

using namespace std;

void ssort(string &s) {

  /*
     strings are "iterable" objects and so have the begin()
     and end() functions.  These functions (in a pretty
     abstract way) return "iterators" which specify the
     "beginning" and "end" of the associated object).

     Thus, this call is asking the sort function to sort
     the entire string s.
  */
  sort(s.begin(), s.end());
}

int main(int argc, char *argv[]){
    /*
    the variable jumble is an unordered_map
    from strings to strings.
    */
    unordered_map<string, vector<string>> jumble;
    ifstream file;
    string word;
    string userInput;

    if(argc != 2) {
        cout << "usage:  ./freq <filename>\n";
        cout << "goodbye\n";
        return 1;
    }

    //attempt to open file on command line
    file.open(argv[1], ios::in);

    if(!file.is_open()){
        cout << "Error: could not open file '" <<
        argv[1] << "'\n";
        cout << "goodbye\n";
        return 1;
    }

    cout << "reading input file...\n";

    int num_words = 0;
    int num_classes = 0;
    string largest_class;
    int largest_class_size = 0;
    string newKey;

    while(file >> word) { 
        // file >> word; 

        newKey = word;
        ssort(newKey); //new key = equivalence class
        
        if(jumble.count(newKey) == 0){ //if class DNE, create class and insert word into equivalence class vector
            jumble[newKey] = vector<string>();
            jumble[newKey].push_back(word);
            num_classes++; //update num_classes
            num_words++; //update num_words
        }
        else { //class exists, insert new word into equivalence class vector
            jumble[newKey].push_back(word);
            num_words++; //update num_words
        }
        /*if size of current equivalence class is greater than largest_class_size, then update largest_class and largest_class_size*/
        if(jumble[newKey].size() > largest_class_size){ 
            largest_class = newKey;
            largest_class_size = jumble[newKey].size();
        }
    }

    //close file
    file.close();

    cout << "start entering jumbled words (ctrl-d to terminate)\n\n";
    cout << ">  ";

    while(cin >> userInput){
        newKey = userInput;
        ssort(newKey); //new key = equivalence class
        if(jumble.count(newKey) == 0){
            cout << "no anagrams found...try again" << endl;
            cout << endl << "> ";
        }
        else{
            cout << "English Anagrams Found: " << endl;
            for(int i = 0; i < jumble[newKey].size(); i++){
                cout << right;
                cout << setw(10) << jumble[newKey][i] << endl;
            }
            cout << endl << ">  ";
        }
    }

    //user has quit, generate report:
    cout << "REPORT:\n\n";
    cout << left;
    cout << setw(25) << "num_words" << ":" << num_words << endl;
    cout << setw(25) << "num_classes" << ":" << num_classes << endl;
    cout << setw(25) << "size-of-largest-class" << ":" << largest_class_size << endl;
    cout << setw(25) << "largest-class key" << ":" << largest_class << endl;
    cout << setw(25) << "members of largest class" << ":" << endl << endl;


    for(int i = 0; i < largest_class_size; i++){
        cout << right;
        cout << setw(10) << jumble[largest_class][i] << endl;
    }

    return 0;
}

