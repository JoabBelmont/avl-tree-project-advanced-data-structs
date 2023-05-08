#ifndef NODE_HPP
#define NODE_HPP

#include <vector>
#include "person.hpp"

template <typename T>
struct Node {
    // atributos
    T key;
    std::vector<Node*> duplicates;
    int height;
    Node *left;
    Node *right;
    Person *toPerson;

    // Construtor
    Node(T key, Node *left = nullptr, Node *right = nullptr, int height = 1, Person *toPerson = nullptr)
        : key(key), height(height), left(left), right(right), toPerson(toPerson)
    {
    }
};

#endif 
