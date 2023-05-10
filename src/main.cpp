#include <iostream>
#include <fstream>

#include "avl.hpp"
using namespace std;

template <typename T>
std::vector<Node<T>*> *nodeToVector(Node<T> *node);
vector<Person> readCSV(const string& filename);
void populateTree(vector<Person> &people, avl_tree<NationalID> &tree);
void populateTree(vector<Person> &people, avl_tree<string> &tree);
void populateTree(vector<Person> &people, avl_tree<Date> &tree);
void searchPersonByNationalID(avl_tree<NationalID> &nationalIDTree, NationalID nationalID);

int main() {
    avl_tree<NationalID> nationalIDTree;
    avl_tree<string> givenNameTree;
    avl_tree<Date> birthDateTree;
    vector<Person> people;
    Person person;

    people = readCSV("./src/data.csv");
    populateTree(people, givenNameTree);
    populateTree(people, birthDateTree);
    populateTree(people, nationalIDTree);

    givenNameTree.bshow();
    birthDateTree.bshow();
    nationalIDTree.bshow();

    searchPersonByNationalID(nationalIDTree, NationalID("340.578.487-54"));

    return 0;
}

// Função que busca uma pessoa pelo CPF
void searchPersonByNationalID(avl_tree<NationalID> &nationalIDTree, NationalID nationalID) {
    Node<NationalID> *node;
    vector<Node<NationalID>*> *nodeVec;
    node = nationalIDTree.searchNode(nationalID);
    nodeVec = nodeToVector(node);

    for (auto node : *nodeVec) {
        if (node->key == nationalID)
            cout << *node->toPerson << endl;
    }
}

void searchPeopleByDateInterval(avl_tree<Date> &birthDateTree, Date begin, Date end) {
    vector<Node<Date>*> *nodeVec;
    
}

// void searchPeopleByFullNamePrefix()

vector<Person> readCSV(const string& filename) {
    vector<Person> people;

    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Failed to open the file." << endl;
        return people;
    }

    string line;
    getline(file, line); // Skip the header line

    while (getline(file, line)) {
        stringstream ss(line);
        string field;
        Person person;

        // Read each field separated by the delimiter (comma in this case)
        getline(ss, field, ',');
        person.setNationalID(field);

        getline(ss, field, ',');
        person.setGivenName(field);

        getline(ss, field, ',');
        person.setSurname(field);

        getline(ss, field, ',');
        person.setBirthDate(field);

        getline(ss, field, '\n');
        person.setCity(field);

        people.push_back(person);
    }

    file.close();
    return people;
}

/* Cria uma árvore de CPF's e aponta os nós para objetos no vector pessoa */
void populateTree(vector<Person>& people, avl_tree<NationalID>& tree) {
    Node<NationalID> *node;
    vector<Node<NationalID>*> *nodeVec;

    for (const auto &person : people) {
        tree.add(person.getNationalID());
        node = tree.searchNode(person.getNationalID());
        nodeVec = nodeToVector(node);
        for (auto &n : *nodeVec) n->toPerson = &person;
    }
}


/* Cria uma árvore de NOMES e aponta os nós para objetos no vector pessoa */
void populateTree(vector<Person>& people, avl_tree<string>& tree) {
    Node<string> *node;
    vector<Node<string>*> *nodeVec;

    for (const auto &person : people) {
        tree.add(person.getGivenName());
        node = tree.searchNode(person.getGivenName());
        nodeVec = nodeToVector(node);
        for (auto &n : *nodeVec) n->toPerson = &person;
    }
}

// /* Cria uma árvore de DATAS e aponta os nós para objetos no vector pessoa */
void populateTree(vector<Person>& people, avl_tree<Date>& tree) {
    Node<Date> *node;
    vector<Node<Date>*> *nodeVec;

    for (const auto &person : people) {
        tree.add(person.getBirthDate());
        node = tree.searchNode(person.getBirthDate());
        nodeVec = nodeToVector(node);
        for (auto &n : *nodeVec) n->toPerson = &person;
    }
}

template <typename T>
std::vector<Node<T>*> *nodeToVector(Node<T> *node) {
    vector<Node<T>*> *result = new vector<Node<T>*>();
    result->push_back(node);
    for (Node<T>* duplicate : node->duplicates)
        result->push_back(duplicate);
    return result;
}
