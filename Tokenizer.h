#include <vector>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

class Tokenizer {
public:
    Tokenizer() = default;
    ~Tokenizer() = default;
    const vector<pair<string, int>> &tokens() {
        return _tokens;
    }
    void tokenize(string file_path) {
        string line;
        ifstream program(file_path);
        if (program.is_open())
        {
            int nr=0;
            while (getline (program, line))
            {
                nr++;
                istringstream ss(line);
                string word;
                while(ss >> word) {
                    add_tokens(word, nr);
                }
            }
            program.close();
        }
    }
private:
    void add_tokens(string word, int lineNr) {
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
                case '+':
                case '-':
                case ',':
                case '*':
                case '/':
                case '|':
                case '&':
                case '^':
                case '%': {
                    int size = i - last;
                    if (size) {
                        _tokens.push_back({word.substr(last, size), lineNr});
                    }
                    _tokens.push_back({word.substr(i, 1), lineNr});
                    last = i+1;
                    break;
                }
                case '=':
                case '!':
                case '>':
                case '<': {
                    int size = i - last;
                    if (size) {
                        _tokens.push_back({word.substr(last, size), lineNr});
                    }
                    if(i<word.size()-1 && word[i+1] == '=') {
                        _tokens.push_back({word.substr(i, 2), lineNr});
                        last = i+2;
                        i++;
                    } else {
                        _tokens.push_back({word.substr(i, 1), lineNr});
                        last = i+1;
                    }
                }
                default:
                    break;
            }
        }
        int size = word.size()-last;
        if (size)
            _tokens.push_back({word.substr(last, size), lineNr});
    }
    vector<pair<string, int>> _tokens;
};
