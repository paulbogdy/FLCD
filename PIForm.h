#include <regex>
#include <iostream>
#include "FiniteAutomata.h"

using namespace std;

template<class T>
struct ListNode {
    T value;
    ListNode<T> *next;
    ListNode(): next(nullptr) {}
};

static void delete_list(ListNode<pair<int, int>> *list) {
    if (list == nullptr) return;
    delete_list(list->next);
    delete list;
}
static void print(ListNode<pair<int, int>> *list) {
    if (list == nullptr) return;
    cout << list->value.first << ' ' << list->value.second << '\n';
    print(list->next);
}

class PIForm {
public:
    inline static const regex char_regex { "'.'" };
    inline static const regex number_regex { "0|([+-]?[1-9][0-9]*)" };
    inline static const regex identifier_regex { "[a-zA-Z][a-zA-Z0-9]*" };
    inline static FiniteAutomata char_fa { "automatas/char.fa" };
    inline static FiniteAutomata number_fa { "automatas/number.fa" };
    inline static FiniteAutomata identifier_fa { "automatas/identifier.fa" };
    PIForm(): _list(nullptr), _tail(nullptr){}
    void insert(pair<int, int> &elem) {
        if(_tail == nullptr) {
            _list = new ListNode<pair<int, int>>;
            _list->value = elem;
            _tail = _list;
        } else {
            _tail->next = new ListNode<pair<int ,int>>;
            _tail->next->value = elem;
            _tail = _tail->next;
        }
    }
    void print() {
        ::print(_list);
    }
    class Iterator{
    public:
        Iterator() noexcept : m_pCurrentNode(nullptr) { }
        Iterator(const ListNode<pair<int, int>>* pNode) noexcept : m_pCurrentNode (pNode) { }

        Iterator& operator=(ListNode<pair<int, int>>* pNode){
            this->m_pCurrentNode = pNode;
            return *this;
        }
 
        // Prefix ++ overload
        Iterator& operator++()
        {
            if (m_pCurrentNode)
                m_pCurrentNode = m_pCurrentNode->next;
            return *this;
        }
 
        // Postfix ++ overload
        Iterator operator++(int)
        {
            Iterator iterator = *this;
            ++*this;
            return iterator;
        }
 
        bool operator!=(const Iterator& iterator)
        {
            return m_pCurrentNode != iterator.m_pCurrentNode;
        }
 
        pair<int, int> operator*()
        {
            return m_pCurrentNode->value;
        }
 
    private:
        const ListNode<pair<int, int>>* m_pCurrentNode;
    };

    Iterator begin() {
        return Iterator(_list);
    }
    Iterator end() {
        return Iterator();
    }
private:
    ListNode<pair<int, int>> *_list;
    ListNode<pair<int, int>> *_tail;
};
