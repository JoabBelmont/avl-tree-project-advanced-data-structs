#ifndef NODE_HPP
#define NODE_HPP

#include "../data-classes/person.hpp"

template <typename T>
struct Node {
    // atributos
    T key;
    int height;
    Node *left;
    Node *right;

    // Atributos extras
    Node *parent;
    Node *next {nullptr};
    const Person *toPerson {nullptr};

    // Construtor
    Node(T key, Node *left = nullptr, Node *right = nullptr, int height = 1)
        : key(key), height(height), left(left), right(right) {}
};

#endif 
