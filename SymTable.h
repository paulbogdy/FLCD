#include "HashMap.h"

class SymTable {
public:
    SymTable(): _next_code(0), _map() {}
    size_t insert(string id) {
        auto current = _map.search(id);
        if (current.has_value()) return current.value();
        _map.insert(id, ++_next_code);
        return _next_code;
    }
    optional<size_t> search(const string &id) {
        return _map.search(id); 
    }
private:
    size_t _next_code;
    HashMap<string, size_t> _map;
};
