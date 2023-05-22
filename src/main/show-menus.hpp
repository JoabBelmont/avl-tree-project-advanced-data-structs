#ifndef MENUS_HPP
#define MENUS_HPP

#include <iostream>

void showMainMenu() {
    system("clear || cls");

    std::cout << "╒══════════╭──────────────────╮══════════╕" << '\n';
    std::cout << "╞════[]════│   Data  Viewer   │════[]════╡" << '\n';
    std::cout << "╞══════════╰──────────────────╯══════════╡" << '\n';
    std::cout << "│                                        │" << '\n';
    std::cout << "│                                        │" << '\n';
    std::cout << "│         1 - Consultar por nome         │" << '\n';
    std::cout << "│                                        │" << '\n';
    std::cout << "│         2 - Consultar por CPF          │" << '\n';
    std::cout << "│                                        │" << '\n';
    std::cout << "│         3 - Consultar por data         │" << '\n';
    std::cout << "│                                        │" << '\n';
    std::cout << "│         4 - Opcoes avancadas           │" << '\n';
    std::cout << "│                                        │" << '\n';
    std::cout << "│         0 - Sair                       │" << '\n';
    std::cout << "│                                        │" << '\n';
    std::cout << "│                                        │" << '\n';
    std::cout << "╘════════════════════════════════════════╛" << '\n';
    std::cout << '\n';
    std::cout << "Digite a opcao desejada: ";
}

void showDateSubMenu() {
    std::cout << "o-------------------------------o" << '\n';
    std::cout << "|                               |" << '\n';
    std::cout << "|   1 - Por data única          |" << '\n';
    std::cout << "|                               |" << '\n';
    std::cout << "|   2 - Por intervalo de data   |" << '\n';
    std::cout << "|                               |" << '\n';
    std::cout << "|   0 - Voltar                  |" << '\n';
    std::cout << "|                               |" << '\n';
    std::cout << "o-------------------------------o" << '\n';
    std::cout << '\n';
}

void showDebugSubMenu() {
    system("clear || cls");

    std::cout << "o----------------------------------o" << '\n';
    std::cout << "|                                  |" << '\n';
    std::cout << "|   1 - Mostrar árvores            |" << '\n';
    std::cout << "|                                  |" << '\n';
    std::cout << "|   2 - Escolher arquivo           |" << '\n';
    std::cout << "|                                  |" << '\n';
    std::cout << "|   3 - Mostrar todas as pessoas   |" << '\n';
    std::cout << "|                                  |" << '\n';
    std::cout << "|   0 - Voltar                     |" << '\n';
    std::cout << "|                                  |" << '\n';
    std::cout << "o----------------------------------o" << '\n';
    std::cout << '\n';
}

void showTreeMenu() {
    system("clear || cls");

    std::cout << "o----------------o" << '\n';
    std::cout << "|                |" << '\n';
    std::cout << "|   1 - CPF      |" << '\n';
    std::cout << "|                |" << '\n';
    std::cout << "|   2 - Nome     |" << '\n';
    std::cout << "|                |" << '\n';
    std::cout << "|   3 - Data     |" << '\n';
    std::cout << "|                |" << '\n';
    std::cout << "|   4 - Todas    |" << '\n';
    std::cout << "|                |" << '\n';
    std::cout << "|   0 - Voltar   |" << '\n';
    std::cout << "|                |" << '\n';
    std::cout << "o----------------o" << '\n';
    std::cout << '\n'; 
}

#endif
