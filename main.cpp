#include "./OOP_Dictionary/dict.h"

int main()
{
    std::string path = "./dict/words.txt";
    Dictionary MyDict(path);

    while (true)
    {
        MyDict.log("what word are you looking for?");
        std::string word;
        std::cin >> word;
        MyDict.toLowerCase(word);
        if (MyDict.checkForWord(word))
        {
            MyDict.log("word is in the dictionary");
        }
        else
        {
            MyDict.log("word is not in the dictionary");
        }
        if (word == "x")
        {
            MyDict.~Dictionary();
            break;
        }
    }
    std::cout << "dictionary deleted" << std::endl;
}

/*
#include "./dictionary/dictionary.h"
int main()
{
    initializeDict();
    log("Dict array initialized to nullptr");
    if (!loadDictionary(".\\dict\\words.txt"))
    {
        log("dict failed to load");
        return 1;
    }
    while (true)
    {
        std::string input;
        std::cin >> input;
        char *c_string = stringToChar(input);
        if (input == "X")
        {
            delete c_string;
            c_string = nullptr;
            break;
        }
        if (checkForWord(c_string))
        {
            std::cout << input << " foundd in the dictionary";
        }
        else
        {
            std::cout << input << " is not within the dictionary";
        }
        delete c_string;
        c_string = nullptr;
    }
}
    */