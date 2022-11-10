#include <optional>
#include <regex>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <assert.h>
#include <unordered_map>
#include <fstream>
#include "SymTable.h"
#include "Tokenizer.h"
#include "PIForm.h"

using namespace std;

class Scanner {
public:
    Scanner(string file_path){
        string staticToken;
        ifstream program(file_path);
        int nr = 1;
        if (program.is_open())
        {
            while (getline (program, staticToken))
            {
                _staticTokens.insert(staticToken, ++nr);
            }
        }
    }
    optional<pair<int, string>> create_pif(string file_path) {
        _tokenizer.tokenize(file_path);
        for(const pair<string, int> &token: _tokenizer.tokens()) {
            try {
                auto elem = add_token(token.first);
                _pif.insert(elem);
            } catch (runtime_error &e) {
                return make_pair(token.second, e.what());
            }
        }
        return {};
    }
    const PIForm &get_pif() {
        return _pif;
    }
    SymTable &constants() {
        return _constants;
    }
    SymTable &identifiers() {
        return _identifiers;
    }
private:
    pair<int, int> add_token(const string &token) {
        auto fromTokens = _staticTokens.search(token);
        if (fromTokens.has_value()) {
            return {fromTokens.value(), -1};
        }

        if (is_constant(token)) {
            int code = _constants.insert(token);
            return {0, code};
        }

        if (is_identifier(token)) {
            int code = _identifiers.insert(token);
            return {1, code};
        }
        
        throw runtime_error("Lexical Error at token: " + token);
    }
    bool is_constant(const string &token) {
        if (PIForm::char_fa.matches(token)) return true; // Char
        if (PIForm::number_fa.matches(token)) return true; // Number

        return false;
    }
    bool is_identifier(const string &token) {
        return PIForm::identifier_fa.matches(token);
    }
    HashMap<string, int> _staticTokens;
    Tokenizer _tokenizer;
    SymTable _constants;
    SymTable _identifiers;
    PIForm _pif;
};

int main() {
    Scanner scanner("Tokens.txt");
    auto error = scanner.create_pif("programs/p3.jpb");
    if(error.has_value()) {
        cout << "Issue at line " << error.value().first << " | " << error.value().second << '\n';
    } else {
        cout << "No Lexical Errors\n";
        ofstream symtablefile;
        symtablefile.open("ST.out");
        
        symtablefile << "Constants\n";
        for(auto elem: scanner.constants().elems()) {
            symtablefile << elem.first << '|' << elem.second << '\n';
        }

        symtablefile << "Identifiers\n";
        for(auto elem: scanner.identifiers().elems()) {
            symtablefile << elem.first << '|' << elem.second << '\n';
        }

        symtablefile.close();


        ofstream piffile;
        piffile.open("PIF.out");

        auto pif = scanner.get_pif();
        for (auto elem: pif) {
            piffile << elem.first << ' ' << elem.second << '\n';
        }

        piffile.close();

    }
}
