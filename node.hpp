#ifndef NODE_HPP
#define NODE_HPP

template <typename T>
struct Node {
    // atributos
    T key;
    int height;
    Node *left;
    Node *right;

    // Construtor
    Node(T key, Node *left = nullptr, Node *right = nullptr, int height = 1)
        : key(key), height(height), left(left), right(right)
    {
    }
};

#endif 
