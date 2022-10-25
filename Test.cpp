#include "HashMap.h"


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

int main() {
    TestCommonHashMap(4);
    TestCommonHashMap(69);
    TestCommonHashMap(42069);
    TestCommonHashMap(69420);
}
