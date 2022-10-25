#include <optional>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <assert.h>
#include <unordered_map>
#include <fstream>
#include "SymTable.h"
#include "Tokenizer.h"

using namespace std;


int main() {
    Tokenizer tokenizer;
    tokenizer.tokenize("programs/p1.jpb");
    for(auto elem: tokenizer.tokens()) cout << elem << '\n';
    SymTable identifiers, constants;
}
