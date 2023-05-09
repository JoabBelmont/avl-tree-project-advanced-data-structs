#include <iostream>
#include <fstream>

#include "avl.hpp"
using namespace std;

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

    people = readCSV("test.csv");
    populateTree(people, givenNameTree);
    populateTree(people, birthDateTree);
    populateTree(people, nationalIDTree);

    // for (auto person : people) {
    //     cout << person << endl;
    // }

    givenNameTree.bshow();
    birthDateTree.bshow();
    nationalIDTree.bshow();

    vector<Node<string>> test = givenNameTree.searchNode("Estevan");
    for (auto node : test) {
        cout << *node.toPerson << endl;
    }

    // vector<Node<NationalID>> test = nationalIDTree.searchNode(NationalID("715.379.468-97"));
    // for (auto node : test) {
    //     cout << *node.toPerson << endl;
    // }
    // 388.624.732-57 -> Kai Cunha: tá me dando Luis Sousa
    // 992.809.969-32 -> Tiago Gomes: tá me dando erro de segmentação
    // 518.376.278-35 -> Estevan Azevedo: tá me dando Kai Cunha
    // 715.379.468-97 -> Luis Sousa: tá me dando Tiago Gomes

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

    return 0;
}

// Função que busca uma pessoa pelo CPF
void searchPersonByNationalID(avl_tree<NationalID> &nationalIDTree, NationalID nationalID) {
    vector<Node<NationalID>> nodes;
    nodes = nationalIDTree.searchNode(nationalID);

    for (auto node : nodes) {
        if (node.key == nationalID) {
            cout << *node.toPerson << endl;
        }
    }
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
void populateTree(vector<Person> &people, avl_tree<NationalID> &tree) {
    vector<Node<NationalID>> nodeVec;

    for (const auto &person : people) {
        tree.add(person.getNationalID());
        nodeVec = tree.searchNode(person.getNationalID());
        for (auto &n : nodeVec) n.toPerson = &person;
    }
}

/* Cria uma árvore de NOMES e aponta os nós para objetos no vector pessoa */
void populateTree(vector<Person> &people, avl_tree<string> &tree) {
    vector<Node<string>> nodeVec;

    for (const auto &person : people) {
        tree.add(person.getGivenName());
        nodeVec = tree.searchNode(person.getGivenName());
        for (auto &n : nodeVec) n.toPerson = &person;
    }
}

/* Cria uma árvore de DATAS e aponta os nós para objetos no vector pessoa */
void populateTree(vector<Person> &people, avl_tree<Date> &tree) {
    vector<Node<Date>> nodeVec;

    for (const auto &person : people) {
        tree.add(person.getBirthDate());
        nodeVec = tree.searchNode(person.getBirthDate());
        for (auto &n : nodeVec) n.toPerson = &person;
    }
}
