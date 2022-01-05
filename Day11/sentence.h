#include <iostream>
#include <string>
#include <vector>

class Sentence {
    private:
        char *sentence;
        std::vector<int> vsentence; // stores the word offsets
        int size;
    public:
        Sentence(char* sent, int size); // regular constructor
        Sentence(const Sentence &copy); // insert a deep copy  constructor here
        Sentence &operator = (const Sentence &copy);// insert a deep copy assignment operator here
        char *data(); // returns the data for sentence
        int num_words() const; // fetches the number of words 
        std::string get_word(int n); // get nth word in sentence 
        void replace(char* sent, int size); // replace existing sentence
        ~Sentence(); // destroy any memory allocated

        Sentence(Sentence &&move); // move constructor
        Sentence& operator = (Sentence &&move); // move assignment operator
};