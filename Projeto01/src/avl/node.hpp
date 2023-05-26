/**
 * @file node.hpp
 * @author Atílio Gomes, Joabe Alves (few attributes)
 * @brief File containing the Node struct
 * @version 0.1
 * @date 2023-05-19
 * 
 */

#ifndef NODE_HPP
#define NODE_HPP

#include "../data-classes/person.hpp"

template <typename T>
struct Node {
    /* Attributes */
    T key;
    int height;
    Node *left;
    Node *right;

    /* Extra attributes */
    Node *next {nullptr}; // Handles duplicate keys
    const Person *toPerson {nullptr}; // Pointer to the person in the database

    /* Constructor */
    Node(T key, Node *left = nullptr, Node *right = nullptr, int height = 1)
        : key(key), height(height), left(left), right(right) {}
};

#endif 
