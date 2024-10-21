#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main()
{
    std::vector<std::string> lines;

    //create a file stream
    std::ifstream file;

    //open file
    file.open("sample.txt");

    //current contents
    std::string current;

    //get next line
    while(std::getline(file, current)) {

        //collect lines
        lines.push_back(current);
    }

    file.close();

    return 0;
}