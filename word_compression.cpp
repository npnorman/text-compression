#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class Token {

    private:
        std::string word;
        std::string type;
    
    public:
        
        Token(std::string word, std::string type) {
            //constructor
            this->word = word;
            this->setType(type);
        }

        void setWord(std::string word) {
            this->word = word;
        }

        void setType(std::string type) {
            if (type == "alpha") {
                this->type = "alpha";
            } else {
                this->type = "other";
            }
        }

        std::string getWord() {
            return this->word;
        }

        std::string getType() {
            return this->type;
        }

};

std::vector<Token> lexer(std::string line);
Token tokenizeAlpha(std::string line, int start, int end);

int main()
{
    //lines
    std::vector<std::string> lines;

    //tokens
    std::vector<Token> tokens;

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

        //tokenize them
        std::vector<Token> results = lexer(current);

        //add new line
        results.push_back(Token("\n", "other"));

        //for token in result
        for (int i=0; i < results.size(); i++) {
            //add to token list
            tokens.push_back(results[i]);

            std::cout << results[i].getWord();
        }
    }

    tokens.pop_back();

    file.close();

    return 0;
}

std::vector<Token> lexer(std::string line) {
    //goal: take some lines and produce tokens
    //input: a line of text
    //output: tokens

    //counter start and end
    int start = -1;
    int end = -1;

    //list of tokens
    std::vector<Token> tokens;

    //for character in line
    for (int i=0; i < line.length(); i++) {

        //if counter has not started,
        if (start == -1) {
            //if the character is alphabetic
            if (isalpha(line[i])) {
                //set counter
                start = i;
            } else {
                //not alpha

                std::string other = std::string(1, line[i]);
                Token token(other, "other");

                //push non-alpha to list
                tokens.push_back(token);
            }
        }
            
        //if the counter has started
        if (start != -1) {
            //if the character is alphabetic
            if (isalpha(line[i])) {
                //set end of counter
                end = i;
            //else
            } else {
                //not alpha

                //if counter is going
                if (start != -1) {
                    //tokenize
                    Token token = tokenizeAlpha(line, start, end);

                    //push token to list
                    tokens.push_back(token);

                    //reset counter and end
                    start = -1;
                    end = -1;
                }

                std::string other = std::string(1, line[i]);
                Token token(other, "other");

                //push non-alpha to list
                tokens.push_back(token);
            }
        }

        //reached the end
        if (i == line.length() - 1) {
            //if current has a token, push

            if (start != -1) {
                //tokenize
                Token token = tokenizeAlpha(line, start, end);

                //push token to list
                tokens.push_back(token);
            }
        }
    }

    //return a list of tokens
    return tokens;

}

Token tokenizeAlpha(std::string line, int start, int end) {

    //make a token from the substring of the line
    std::string word = line.substr(start, end - start + 1);

    Token token(word, "alpha");

    return token;
}