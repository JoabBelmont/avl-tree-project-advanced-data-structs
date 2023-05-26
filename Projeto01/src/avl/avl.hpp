/**
 * @file avl.hpp
 * @authors Atílio Gomes, Joabe Alves (some functions)
 * @brief File containing the AVL Tree class.
 * @version 0.1
 * @date 2023-05-19
 * 
 */

#ifndef AVL_HPP
#define AVL_HPP

#include <string>

#include "../data-classes/person.hpp"
#include "../data-classes/date.hpp"
#include "../data-classes/nationalId.hpp"
#include "../data-classes/name.hpp"
#include "node.hpp"

template <typename T>
class avl_tree {
public:
    avl_tree() = default;

    avl_tree(const avl_tree &t) {
        this->root = clone_rec(t.root);
    }

    avl_tree &operator=(const avl_tree &t) {
        if(this != &t) {
            clear();
            this->root = clone_rec(t.root);
        }
        return *this;
    } 

    int height() const {
        return root->height;
    }

    void bshow() const {
        bshow(root, "");
    }

    ~avl_tree() {
        clear();
    }

    void add(const T &key) { //*
        root = add(root, key);
    } // O(lg n)

    Node<T> *searchNode(const T &key1, const T &key2 = T()) { //*
        return searchNode(root, key1, key2);
    } // O(lg n)

    void clear() { //*
        root = clear(root);
    } // O(n)

    void remove(T key) {
        root = remove(root, key);
    } // O(lg n)

    void access_keys_inorder(void (*f)(T &key)) {
        inorder_rec(root, f);
    } // O(n)

    void keys_as_vector(std::vector<T> &v) const {
        inorder_rec(root, v);
    } // O(n)

    /* Searches people by 3 different methods:
     * Single, Prefix & Interval search
     * depending on the number of arguments and of found objects.
     * This function has O(lg n) complexity in medium
     * and O(n) in the worst case. */
    void searchPeople(const T& key1, const T& key2 = T()) { //*
        Node<T>* first { nullptr };
        Node<T>* predecessor { nullptr };
        Node<T>* successor { nullptr };
        Node<T>* foundLeft { nullptr };
        Node<T>* foundRight { nullptr };

        try {
            if (key2 == T()) { // Single or Prefix search
                first = this->searchNode(key1); // First node found (O(lg n))

                if (first == nullptr) {
                    throw std::runtime_error(" Person not found.");
                }

                predecessor = this->maximum(first->left); // Predecessor of first (O(lg n))
                successor = this->minimum(first->right); // Successor of first (O(lg n))

                // If key1 is equal to a predecessor or successor, then it is a muliple search
                if ((predecessor && key1 == predecessor->key) || (successor && key1 == successor->key)) {
                    searchPeopleRec(first, key1, key2); // Multiple search (O(n))
                } else {
                    std::cout << *first->toPerson << '\n';
                    showDuplicates(first); // Shows duplicates, if there are any (O(n))
                }
                std::cout << " All people have been shown.\n";
            } else { // Interval search
                first = this->searchNode(key1, key2); // First node found (O(lg n))

                if (first == nullptr) {
                    throw std::runtime_error(" There is no person that satisfies that interval.");
                }

                foundLeft = this->searchNode(first->left, key1, key2); // Found node in the left subtree (O(lg n))
                foundRight = this->searchNode(first->right, key1, key2); // Found node in the right subtree (O(lg n))

                if (foundLeft || foundRight) { // If there is a node in one of the subtrees that satisfies the interval
                    searchPeopleRec(first, key1, key2); // Multiple search (O(n))
                } else {
                    std::cout << *first->toPerson << '\n';
                    showDuplicates(first); // Shows duplicates, if there are any (O(n))
                }
                std::cout << " All people that satisfy the interval have been shown.\n";
            }
        } catch (std::runtime_error& e) {
            std::cout << e.what() << '\n';
            return;
        }
    }

    /* Adds nodes to the tree and points them
     * to each corresponding object in the vector.
     * O(n) in the worst case. */
    template<typename F>
    void populateTree(std::vector<Person> &people, F getter) { //*
        T key;
        Node<T> *node;
        for (const auto &person : people) {
            key = (person.*getter)();
            this->add(key);
            node = this->searchNode(key);
            while(node->next) {
                node = node->next;
            }
            node->toPerson = &person;
        }
    }

    Node<T> *minimum(Node<T> *node) { //*
        if (node == nullptr) return nullptr;
        else {
            Node<T> *aux = node;
            while (aux->left != nullptr) aux = aux->left;
            return aux;
        }
    }

    Node<T> *maximum(Node<T> *node) { //*
        if (node == nullptr) return nullptr;
        else {
            Node<T> *aux = node;
            while (aux->right != nullptr) aux = aux->right;
            return aux;
        }
    }

    avl_tree *intercala(const avl_tree &t) {
        std::vector<T> v1, v2, v;                                   // O(1)
        this->keys_as_vector(v1);                                   // O(m)
        t.keys_as_vector(v2);                                       // O(n)
        merge_vector(v1, v2, v);                                    // O(m+n)
        if(has_repeated_keys(v))                                    // O(m+n)
            throw std::runtime_error("chaves repetidas");           // O(1)
        Node<T> *r = build_complete_tree(v, 0, v.size()-1);         // O(m+n)
        height_rec(r);                                              // O(m+n)
        avl_tree<T> *ptr = new avl_tree<T>;                         // O(1)
        ptr->root = r;                                              // O(1)
        return ptr;                                                 // O(1)
    }

private:
    Node<T> *root {nullptr};

    int height(Node<T> *node) {
        return (node == nullptr) ? 0 : node->height;
    }

    int balance(Node<T> *node) {
        return height(node->right) - height(node->left);
    }

    Node<T> *rightRotation(Node<T> *p) {
        Node<T> *u = p->left;
        p->left = u->right;
        u->right = p;
        // recalcular as alturas de p e de u
        p->height = 1 + std::max(height(p->left), height(p->right));
        u->height = 1 + std::max(height(u->left), height(u->right));
        return u;
    }

    Node<T> *leftRotation(Node<T> *p) {
        Node<T> *u = p->right;
        p->right = u->left;
        u->left = p;
        // recalcular as alturas de p e de u
        p->height = 1 + std::max(height(p->right), height(p->left));
        u->height = 1 + std::max(height(u->left), height(u->right));
        return u;
    }

    /* Adds a node to the tree, handling duplicate keys
     * by putting them on a linked list. O(n) in the worst case. */
    Node<T> *add(Node<T> *p, const T &key) { //*
        if(p == nullptr) return new Node(key);
        if(key == p->key) { // If the key is equal to an existing one
            Node<T> *q = p;
            while (q->next != nullptr) q = q->next; // Travel to the last duplicate node
            q->next = new Node(key); // Insert it on the last position of the list
            return p;
        }
        if(key <= p->key) p->left = add(p->left, key);
        else p->right = add(p->right, key);

        p = fixup_node(p, key);

        return p;
    }

    /* Searches node by interval or uniquely,
     * depending on the number of arguments. 
     * O(lg n) in the worst case. */
    Node<T> *searchNode(Node<T> *node, const T &key1, const T &key2 = T()) { //*
        if (key2 == T()) {
            if (node == nullptr) return node;
            if (key1 == node->key) return node;
            if (key1 < node->key) return searchNode(node->left, key1);
            return searchNode(node->right, key1);
        } else {
            if (node == nullptr) return node;
            if (key1 <= node->key && key2 >= node->key) return node;
            if (key1 < node->key) return searchNode(node->left, key1, key2);
            return searchNode(node->right, key1, key2);
        }
    }

    /* Show every object pointed by a node
     * in the duplicate linked list. O(n) in the worst case. */
    void showDuplicates(Node<T> *node) { //*
        if (node == nullptr) return;
        if (node->next) {
            std::cout << *node->next->toPerson << '\n';
            showDuplicates(node->next);
        }
    }

    /* Searches people recursively by interval or uniquely,
     * depending on the number of arguments.
     * This function traverses a whole subtree, 
     * so its O(n) in the worst case. */
    void searchPeopleRec(Node<T> *node, const T &key1, const T &key2 = T()) { //*
        if (key2 == T()) {
            if (node == nullptr) return;
            else if (key1 == node->key) {
                std::cout << *node->toPerson << '\n';
                showDuplicates(node);
            }
            searchPeopleRec(node->left, key1);
            searchPeopleRec(node->right, key1);
        } else {
            if (node == nullptr) return;
            else if (key1 <= node->key && key2 >= node->key) {
                std::cout << *node->toPerson << '\n';
                showDuplicates(node);
            }
            searchPeopleRec(node->left, key1, key2);
            searchPeopleRec(node->right, key1, key2);
        }
    }

    Node<T> *fixup_node(Node<T> *p, const T &key) {
        // recalcula a altura de p
        p->height = 1 + std::max(height(p->left), height(p->right));

        // calcula o balanço do p
        int bal = balance(p);

        if(bal >= -1 && bal <= 1) return p;

        if(bal < -1 && key < p->left->key) p = rightRotation(p);

        else if(bal < -1 && key > p->left->key) {
            p->left = leftRotation(p->left);
            p = rightRotation(p);
        }

        else if(bal > 1 && key > p->right->key) p = leftRotation(p);

        else if(bal > 1 && key < p->right->key) {
            p->right = rightRotation(p->right);
            p = leftRotation(p);
        }

        return p;
    }

    void bshow(Node<T> *node, std::string heranca) const {
        if(node != nullptr && (node->left != nullptr || node->right != nullptr))
            bshow(node->right, heranca + "r");
        for(int i = 0; i < (int) heranca.size() - 1; i++)
            std::cout << (heranca[i] != heranca[i + 1] ? "│   " : "    ");
        if(heranca != "")
            std::cout << (heranca.back() == 'r' ? "╭───" : "╰───");
        if(node == nullptr){
            std::cout << "#" << std::endl;
            return;
        }
        std::cout << node->key << std::endl;
        if(node != nullptr && (node->left != nullptr || node->right != nullptr))
            bshow(node->left, heranca + "l");
    }

    /* Clears a subtree, including duplicate nodes */
    Node<T> *clear(Node<T>* node) { //*
        Node<T> *current { node }, *nextNode { nullptr };

        if (node != nullptr) {
            node->left = clear(node->left);
            node->right = clear(node->right);

            while (current) {
                nextNode = current->next;
                delete current;
                current = nextNode;
            }

            node = nullptr;
        }

        return nullptr;
    }


    Node<T> *remove(Node<T> *node, T &key) {
        if(node == nullptr) // node nao encontrado
            return nullptr; /*L\pauseL*/
        if(key < node->key) 
            node->left = remove(node->left, key);
        else if(key > node->key)
            node->right = remove(node->right, key); /*L\pauseL*/
        // encontramos no node
        else if(node->right == nullptr) { // sem filho direito
            Node<T> *child = node->left;
            delete node;
            return child;
        }
        else // tem filho direito: troca pelo sucessor
            node->right = remove_successor(node, node->right); /*L\pauseL*/
        
        // Atualiza a altura do node e regula o node
        node = fixup_deletion(node); 
        return node;
    }

    Node<T> *remove_successor(Node<T> *root, Node<T> *node) {
        if(node->left != nullptr)
            node->left = remove_successor(root, node->left);
        else {
            root->key = node->key;
            Node<T> *aux = node->right;
            delete node;
            return aux;
        }
        // Atualiza a altura do node e regula o node
        node = fixup_deletion(node);
        return node;
    }

    Node<T> *fixup_deletion(Node<T> *node) {
        node->height = 1 + std::max(height(node->left), height(node->right));

        int bal = balance(node);

        // node pode estar desregulado, ha 4 casos a considerar
        if(bal > 1 && balance(node->right) >= 0) {
            return leftRotation(node);
        }
        else if(bal > 1 && balance(node->right) < 0) {
            node->right = rightRotation(node->right);
            return leftRotation(node);
        }
        else if(bal < -1 && balance(node->left) <= 0) {
            return rightRotation(node);
        }
        else if(bal < -1 && balance(node->left) > 0) { 
            node->left = leftRotation(node->left);
            return rightRotation(node);
        }
        return node;
    }

    Node<T> *clone_rec(Node<T> *node) {
        if(node == nullptr)
            return nullptr;
        else {
            Node<T> *aux = new Node(node->key);
            aux->left = clone_rec(node->left);
            aux->right = clone_rec(node->right);
            return aux;
        }
    }

    void inorder_rec(Node<T> *node, std::vector<T> &v) {
        if(node != nullptr) {
            inorder_rec(node->left, v);
            v.push_back(node->key);
            inorder_rec(node->right, v);
        }
    }

    void merge_vector(const std::vector<T> &v1, const std::vector<T> &v2, std::vector<T> &v3) {
        int i {0}, j {0};
        while(i < v1.size() && j < v2.size()) {
            if(v1[i] <= v2[j])
                v3.push_back(v1[i++]);
            else   
                v3.push_back(v2[j++]);
        }
        while(i < v1.size()) v3.push_back(v1[i++]);
        while(j < v2.size()) v3.push_back(v2[j++]);
    }

    Node<T> *build_complete_tree(const std::vector<T> &v, int l, int r) {
        if(l <= r) {
            int m = (l+r)/2;
            Node<T> *aux = new Node(v[m]);
            aux->left = build_complete_tree(v, l, m-1);
            aux->right = build_complete_tree(v, m+1, r);
            return aux;
        }
        return nullptr;
    }

    int height_rec(Node<T> *node) {
        if(node == nullptr)
            return 0;
        else {
            node->height = 1 + std::max(height_rec(node->left), height_rec(node->right));
            return node->height;
        }
    }

    bool has_repeated_keys(const std::vector<T> &v) {
        for(int i {0}; i < (int)v.size() - 1; ++i) {
            if(v[i] == v[i+1])
                return true;
        }
        return false;
    }
};

#endif
