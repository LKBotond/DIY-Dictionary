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
    */
