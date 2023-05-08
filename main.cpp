#include <iostream>
#include <fstream>

#include "avl.hpp"
using namespace std;

vector<Person> readCSV(const string& filename);
avl_tree<int> createTree(vector<Person> people, avl_tree<int> tree);
avl_tree<string> createTree(vector<Person> people, avl_tree<string> tree);
avl_tree<Date> createTree(vector<Person> people, avl_tree<Date> tree);

int main() {
    avl_tree<int> t1;
    avl_tree<string> givenNameTree;
    avl_tree<Date> birthDateTree;
    vector<Person> people;
    vector<Node<string>> test;

    people = readCSV("test.csv");
    givenNameTree = createTree(people, givenNameTree);
    birthDateTree = createTree(people, birthDateTree);

    for (auto person : people) {
        cout << person << endl;
    }

    givenNameTree.bshow();
    birthDateTree.bshow();

    // people.push_back(Person(1, "João", "Silva", Date("01/01/2000"), "São Paulo"));
    // people.push_back(Person(2, "João", "Silva", Date("01/01/2000"), "São Paulo"));
    // people.push_back(Person(3, "João", "Silva", Date("01/01/2000"), "São Paulo"));
    // people.push_back(Person(4, "João", "Silva", Date("01/01/2000"), "São Paulo"));

    // for (auto person : people) {
    //     givenNameTree.add(person.getGivenName());
    // }

    // test = givenNameTree.searchNode("João");

    // for (auto node : test) {
    //     cout << node.key << endl;
    // }

    // for (int i = 1; i <= 20; i++)
    //     t1.add(i);

    // givenNameTree.add("a"); givenNameTree.add("b"); givenNameTree.add("c");
    // givenNameTree.add("d"); givenNameTree.add("e"); givenNameTree.add("f");
    // givenNameTree.add("g"); givenNameTree.add("h"); givenNameTree.add("i");
    // givenNameTree.add("j"); givenNameTree.add("k"); givenNameTree.add("l");
    // givenNameTree.add("m"); givenNameTree.add("n"); givenNameTree.add("o");
    // givenNameTree.add("p"); givenNameTree.add("q"); givenNameTree.add("r");
    // givenNameTree.add("s"); givenNameTree.add("t"); givenNameTree.add("u");
    // givenNameTree.add("v"); givenNameTree.add("w"); givenNameTree.add("x");
    // givenNameTree.add("a"); givenNameTree.add("a"); givenNameTree.add("a");

    // for (int i = 1; i <= 20; i++)
    //     birthDateTree.add(Date(i, i, i));

    // t1.bshow(); cout << endl;
    // givenNameTree.bshow(); cout << endl;
    // birthDateTree.bshow(); cout << endl;
}

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
        person.setNationalID(stoi(field));

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

/* Cria a árvore e aponta os nós para objetos no vector pessoa*/
avl_tree<int> createTree(vector<Person> people, avl_tree<int> tree) {
    vector<Node<int>> node;

    for (auto person : people) {
        tree.add(person.getNationalID());
        node = tree.searchNode(person.getNationalID());
        for (auto n : node) {
            n.toPerson = &person;
        }
    }

    return tree;
}

avl_tree<string> createTree(vector<Person> people, avl_tree<string> tree) {
    vector<Node<string>> node;

    for (auto person : people) {
        tree.add(person.getGivenName());
        node = tree.searchNode(person.getGivenName());
        for (auto n : node) {
            n.toPerson = &person;
        }
    }

    return tree;
}

avl_tree<Date> createTree(vector<Person> people, avl_tree<Date> tree) {
    vector<Node<Date>> node;

    for (auto person : people) {
        tree.add(person.getBirthDate());
        node = tree.searchNode(person.getBirthDate());
        for (auto n : node) {
            n.toPerson = &person;
        }
    }

    return tree;
}