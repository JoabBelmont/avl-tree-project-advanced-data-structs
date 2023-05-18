#include "main-functions.hpp"

int main() {
    avl_tree<NationalID> nationalIDTree;
    avl_tree<Name> nameTree;
    avl_tree<Date> birthDateTree;

    vector<Person> people;
    Person person;

    readCSV("./src/data.csv", people);

    nationalIDTree.populateTree(people, getNationalID);
    nameTree.populateTree(people, getFullName);
    birthDateTree.populateTree(people, getBirthDate);

    nationalIDTree.bshow();
    cout << '\n';
    nameTree.bshow();
    cout << '\n';
    birthDateTree.bshow();
    cout << '\n';

    // Node<Name> *node = nameTree.searchNode(Name("Ti"));
    // cout << *node->toPerson << '\n';
    // cout << *node->next->toPerson << '\n';
    // cout << *node->next->next->toPerson << '\n';

    // nationalIDTree.searchPeople(NationalID("992.809.969-32"));
    nameTree.searchPeople(Name("Sa"));
    // searchPeopleByDateInterval(birthDateTree, Date("01/01/1930"), Date("31/12/1960"));

    // Name n1("Kai Cunha");
    // Name n2("K");

    // cout << (n2 == n1 ? "True" : "False") << endl;

    return 0;
}
