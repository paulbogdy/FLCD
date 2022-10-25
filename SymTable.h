#include "HashMap.h"

class SymTable {
public:
    void insert(string id) {
        if (_map.search(id).has_value()) return;
        _map.insert(id, ++_next_code);
    }
    optional<size_t> search(const string &id) {
        return _map.search(id); 
    }
private:
    size_t _next_code;
    HashMap<string, size_t> _map;
};
