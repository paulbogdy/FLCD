#include "HashMap.h"
#include "PIForm.h"

void TestCommonHashMap(int testsize) {
    // Testing our Use Case HashMap<string, int>
    cout << "Test for " << testsize << " started...\n";
    vector<string> keys;
    vector<int> values;
    HashMap<string, int> hashmap;
    for(int value=0; value<testsize; value++) {
        string key;
        int aux = value+69;
        while(aux) {
            key.push_back(aux%26 + 'a');
            aux/=26;
        }
        keys.push_back(key);
        values.push_back(value);
    }
    assert(hashmap.size() == 0);
    for(int i=0; i<testsize; i++) {
        hashmap.insert(keys[i], values[i]);
        cout << "Inserted " << i+1 << "/" << testsize << '\r';
    }
    cout << "Insert done -------------\n";
    assert(hashmap.size() == testsize);
    for(int i=0; i<testsize; i++) {
        auto found = hashmap.search(keys[i]);
        assert(found.has_value());
        assert(found.value() == values[i]);
        cout << "Searched " << i+1 << "/" << testsize << '\r';
    }
    cout << "Search done -------------\n";
    for(int i=0; i<testsize; i++) {
        assert(hashmap.size() == testsize - i);
        auto removed = hashmap.remove(keys[i]);
        assert(removed.has_value());
        assert(removed.value() == values[i]);
        assert(!hashmap.search(keys[i]).has_value());
        assert(!hashmap.remove(keys[i]).has_value());
        cout << "Deleted " << i+1 << "/" << testsize << '\r';
    }
    cout << "Delete Done -------------\n";
    assert(hashmap.size() == 0);
    cout << "Test Passed\n";
}

void TestRegex() {
    cout << "Testing char regex...";
    assert(regex_match("'a'", PIForm::char_regex));
    assert(!regex_match("'a", PIForm::char_regex));
    cout << " Passed\n";
    
    cout << "Testing number regex...";
    assert(regex_match("15", PIForm::number_regex));
    assert(regex_match("+15", PIForm::number_regex));
    assert(regex_match("0", PIForm::number_regex));
    assert(!regex_match("+0", PIForm::number_regex));
    assert(!regex_match("-0", PIForm::number_regex));
    assert(!regex_match("10.0", PIForm::number_regex));
    assert(regex_match("+9", PIForm::number_regex));
    assert(regex_match("-1885647", PIForm::number_regex));
    assert(!regex_match("03", PIForm::number_regex));
    assert(!regex_match("++3", PIForm::number_regex));
    cout << " Passed\n";

    cout << "Testing identifier regex...";
    assert(regex_match("number", PIForm::identifier_regex));
    assert(regex_match("a", PIForm::identifier_regex));
    assert(regex_match("number25", PIForm::identifier_regex));
    assert(regex_match("s3x", PIForm::identifier_regex));
    assert(!regex_match("5ex", PIForm::identifier_regex));
    assert(!regex_match("", PIForm::identifier_regex));
    cout << " Passed\n";
}


void TestFiniteAutomata() {

    cout << "Testing char automata...";

    assert(PIForm::char_fa.matches("'a'"));
    assert(!PIForm::char_fa.matches("'a"));

    cout << "Pased\n";
    
    cout << "Testing number automata...";

    assert(PIForm::number_fa.matches("15"));
    assert(PIForm::number_fa.matches("+15"));
    assert(PIForm::number_fa.matches("0"));
    assert(!PIForm::number_fa.matches("+0"));
    assert(!PIForm::number_fa.matches("-0"));
    assert(!PIForm::number_fa.matches("10.0"));
    assert(PIForm::number_fa.matches("+9"));
    assert(PIForm::number_fa.matches("-1885647"));
    assert(!PIForm::number_fa.matches("03"));
    assert(!PIForm::number_fa.matches("++3"));

    cout << " Passed\n";

    cout << "Testing identifier automata...";

    assert(PIForm::identifier_fa.matches("number"));
    assert(PIForm::identifier_fa.matches("a"));
    assert(PIForm::identifier_fa.matches("number25"));
    assert(PIForm::identifier_fa.matches("s3x"));
    assert(!PIForm::identifier_fa.matches("5ex"));
    assert(!PIForm::identifier_fa.matches(""));

    cout << "Passed\n";
}

int main() {
    TestCommonHashMap(4);
    TestCommonHashMap(69);
    TestCommonHashMap(42069);
    TestCommonHashMap(69420);
    TestRegex();
    TestFiniteAutomata();
}
