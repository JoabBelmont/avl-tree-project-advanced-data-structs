#ifndef NODE_HPP
#define NODE_HPP

#include <vector>
#include "./data-classes/person.hpp"

template <typename T>
struct Node {
    // atributos
    T key;
    std::vector<Node*> duplicates;
    int height;
    Node *left;
    Node *right;
    const Person *toPerson;

    // Construtor
    Node(T key, Node *left = nullptr, Node *right = nullptr, int height = 1)
        : key(key), height(height), left(left), right(right)
    {
    }
};

#endif 
