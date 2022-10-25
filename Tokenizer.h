#include <vector>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

class Tokenizer {
public:
    Tokenizer() = default;
    ~Tokenizer() = default;
    const vector<string> &tokens() {
        return _tokens;
    }
    void add_tokens(string word) {
        int last = 0;
        for(int i=0; i<word.size(); i++) {
            switch(word[i]) {
                case '(':
                case ')':
                case '[':
                case ']':
                case '{':
                case '}':
                case ':':
                case '\'':
                case '+':
                case '-':
                case '*':
                case '/':
                case '|':
                case '&':
                case '^':
                case '%': {
                    int size = i - last;
                    if (size) {
                        _tokens.push_back(word.substr(last, size));
                    }
                    _tokens.push_back(word.substr(i, 1));
                    last = i+1;
                    break;
                }
                case '=':
                case '!':
                case '>':
                case '<': {
                    int size = i - last;
                    if (size) {
                        _tokens.push_back(word.substr(last, size));
                    }
                    if(i<word.size()-1 && word[i+1] == '=') {
                        _tokens.push_back(word.substr(i, 2));
                        i++;
                        last = i+2;
                    } else {
                        _tokens.push_back(word.substr(i, 1));
                        last = i+1;
                    }
                }
                default:
                    break;
            }
        }
        int size = word.size()-last;
        if (size)
            _tokens.push_back(word.substr(last, size));
    }
    void tokenize(string file_path) {
        string line;
        ifstream program(file_path);
        if (program.is_open())
        {
            while (getline (program, line))
            {
                istringstream ss(line);
                string word;
                while(ss >> word) {
                    add_tokens(word);
                }
            }
            program.close();
        }
    }
private:
    vector<string> _tokens;
};
