#include "dict.h"

void Dictionary::initializeFirstHalf()
{
    for (int i = 0; i < table_Size / 2; i++)
        hashTable[i] = nullptr;
}
void Dictionary::initializeSecondHalf()
{
    for (int i = table_Size / 2; i < table_Size; i++)
        hashTable[i] = nullptr;
}
void Dictionary::initializeDict()
{
    hashTable = new node *[table_Size]();
    /*
    std::thread worker1(&Dictionary::initializeFirstHalf,this);
    std::thread worker2(&Dictionary::initializeSecondHalf,this);
    worker1.join();
    worker2.join();
    */
}

void Dictionary::toLowerCase(std::string &input)
{
    std::transform(input.begin(), input.end(), input.begin(),
                   [](unsigned char c)
                   { return std::tolower(c); });
}

int Dictionary::getDepth(node *branch)
{
    if (branch == nullptr)
    {
        return 0;
    }
    int left_Depth = getDepth(branch->left);
    int right_Depth = getDepth(branch->right);
    return 1 + std::max(left_Depth, right_Depth);
}

bool Dictionary::searchTheWord(node *root, const std::string &word)
{
    if (root == nullptr)
    {
        return false;
    }
    if (root->word == word)
    {
        return true;
    }
    return searchTheWord(root->left, word) || searchTheWord(root->right, word);
}

bool Dictionary::checkForWord(const std::string &word)
{
    int hash = hashIt(word);

    return searchTheWord(hashTable[hash], word);
}

int Dictionary::hashIt(const std::string &str)
{
    unsigned long long hash = 5381;
    for (auto c : str)
    {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
        hash = hash % table_Size;
    }

    return hash;
}

node *Dictionary::createNewNode(std::string &word)
{
    node *new_node = new node;
    new_node->left = nullptr;
    new_node->right = nullptr;
    new_node->word = word;
    return new_node;
}

bool Dictionary::putNodeInDict(node *&current, node *new_Node)
{
    if (current == nullptr)
    {
        current = new_Node;
        return true;
    }

    int left = getDepth(current->left);
    int right = getDepth(current->right);

    if (left < right)
    {
        return putNodeInDict(current->left, new_Node);
    }
    else
    {
        return putNodeInDict(current->right, new_Node);
    }
}

/*
    std::future<int> left_Future = std::async(std::launch::async, &Dictionary::getDepth, this, current->left);
    std::future<int> right_Future = std::async(std::launch::async, &Dictionary::getDepth, this, current->right);
*/

void Dictionary::unloadDictionary()
{

    for (int i = 0; i < table_Size; i++)
    {
        if (hashTable[i] != nullptr)
        {
            removeNodeFromDict(hashTable[i]);
        }
    }
    delete[] hashTable;
    hashTable = nullptr;
}
void Dictionary::removeNodeFromDict(node *&current)
{
    if (current == nullptr)
    {
        return;
    }
    removeNodeFromDict(current->left);
    removeNodeFromDict(current->right);
    delete current;
    current = nullptr;
    total_Words--;
}

bool Dictionary::loadDictionary(std::string path)
{
    std::ifstream source(path);
    if (!source)
    {
        return false;
    }
    std::string line;
    while (std::getline(source, line))
    {
        toLowerCase(line);
        node *new_Word = createNewNode(line);
        int hash = hashIt(new_Word->word);
        if (putNodeInDict(hashTable[hash], new_Word))
        {
            total_Words++;
        }
        else
        {
            return false;
        }
    }
    if (total_Words > 0)
    {
        return true;
    }
    return false;
}
Dictionary::Dictionary(std::string path)
{
    initializeDict();
    if (!loadDictionary(path))
    {
        unloadDictionary();
    }
    log(total_Words);
}

Dictionary::~Dictionary()
{
    unloadDictionary();
    log(total_Words);
}