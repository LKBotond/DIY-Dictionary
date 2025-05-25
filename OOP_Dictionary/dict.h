#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <future>
#include <algorithm>

typedef struct node
{
    std::string word;
    struct node *left;
    struct node *right;
} node;

class Dictionary
{
private:

    int total_Words = 0;

    int table_Size = 800023;
    node **hashTable;

    // methods
    void initializeFirstHalf();
    void initializeSecondHalf();
    void initializeDict();

public:
    // Utils
    template <typename Output>
    void log(Output value)
    {
        std::cout << value << std::endl;
    }

    void toLowerCase(std::string &input);

    // Search
    int getDepth(node *branch);
    bool searchTheWord(node *root, const std::string &word);
    bool checkForWord(const std::string &word);
    int hashIt(const std::string &str);

    // Load
    node *createNewNode(std::string &word);
    bool loadDictionary(std::string path);
    bool putNodeInDict(node *&current, node *new_Word);

    // Unload
    void removeNodeFromDict(node *&current);
    void unloadDictionary();

    Dictionary(std::string path);
    ~Dictionary();
};