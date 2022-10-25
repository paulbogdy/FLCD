#include <optional>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <assert.h>
#include <unordered_map>
#include <fstream>

using namespace std;

enum NodeStatus {
    EMPTY,
    OCCUPIED,
    DELETED,
};

template<class Key, class Value>
struct HashNode {
    Key key;
    Value value;
    NodeStatus status;
    HashNode(): status(NodeStatus::EMPTY) {}
    ~HashNode()=default;
    HashNode(Key key, Value value): key(key), value(value), status(NodeStatus::EMPTY) {}
    HashNode(Key key, Value value, NodeStatus status): key(key), value(value), status(status) {}
};

template<class Key, class Value, class Hash = hash<Key>>
class HashMap {

using Node = HashNode<Key, Value>;
using enum NodeStatus;

public:
    HashMap() {
        _cap = 17;
        _size = 0;
        _nodes = new Node[_cap];
    }
    ~HashMap() {
        delete[] _nodes; 
    }
    size_t size() {
        return _size;
    }
    void insert(Key key, Value value) {
        if (_cap >= 2*_size) {
            size_t hash = Hash{}(key);
            for(size_t i=0; ;i++) {
                size_t poz = (hash + i*i) % _cap;
                if(_nodes[poz].status == EMPTY || _nodes[poz].status == DELETED) {
                    _nodes[poz] = Node(key, value, OCCUPIED);
                    _size++;
                    return;
                }
            }
        }
        resize();
        insert(key, value);
    }
    optional<Value> search(Key key) {
        size_t hash = Hash{}(key);
        for(int i=0;;i++) {
            size_t poz = (hash + i*i) % _cap;
            Node *node = &_nodes[poz];
            switch (node->status) {
                case EMPTY:
                    return nullopt;
                case OCCUPIED:
                    if(node->key != key) break;
                    return make_optional(node->value);
                default:
                    break;
            }
        }
    }
    optional<Value> remove(Key key) {
        size_t hash = Hash{}(key);
        for(int i=0;;i++) {
            size_t poz = (hash + i*i) % _cap;
            Node *node = &_nodes[poz];
            switch (node->status) {
                case EMPTY:
                    return nullopt;
                case OCCUPIED:
                    if(node->key != key) break;
                    node->status = DELETED;
                    _size--;
                    return make_optional(node->value);
                default:
                    break;
            }
        }
    }
private:
    void resize() {
        size_t old_cap = _cap;
        _cap = next_prime(_cap*2);
        Node* old_nodes = _nodes;
        _nodes = new Node[_cap*2];
        _size = 0;
        for(size_t i=0; i<old_cap; i++) {
            if(old_nodes[i].status == OCCUPIED) {
                insert(old_nodes[i].key, old_nodes[i].value);
            }
        }
        delete[] old_nodes;
    }
    static size_t next_prime(size_t n) {
        for(size_t prime = n; ;++prime) {
            if(is_prime(prime)){
                return prime;
            }
        }
    }
    static bool is_prime(size_t n) {
        if (n <= 1) return false;
        if (n <= 3) return true;
        if (n%2 == 0 || n%3 == 0) return false;
        for (int i=5; i*i<=n; i+=6) {
            if(n%i == 0 || n%(i+2) == 0) {
                return false;
            }
        }
        return true;
    }
    size_t _cap;
    size_t _size;
    Node* _nodes;
};
