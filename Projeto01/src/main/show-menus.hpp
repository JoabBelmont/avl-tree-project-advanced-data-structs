#ifndef MENUS_HPP
#define MENUS_HPP

#include <iostream>

void showMainMenu() {
    system("clear || cls");

    std::cout << "╒═════════╕╭─────────────────╮╒═════════╕" << '\n';
    std::cout << "╞════[]═══╡╡   Data Viewer   ╞╞═══[]════╡" << '\n';
    std::cout << "╞═════════╛╰─────────────────╯╘═════════╡" << '\n';
    std::cout << "│                                       │" << '\n';
    std::cout << "│                                       │" << '\n';
    std::cout << "│       1 - Search by Name              │" << '\n';
    std::cout << "│                                       │" << '\n';
    std::cout << "│       2 - Search by National ID       │" << '\n';
    std::cout << "│                                       │" << '\n';
    std::cout << "│       3 - Search by Date              │" << '\n';
    std::cout << "│                                       │" << '\n';
    std::cout << "│       4 - Advanced options            │" << '\n';
    std::cout << "│                                       │" << '\n';
    std::cout << "│       0 - Exit                        │" << '\n';
    std::cout << "│                                       │" << '\n';
    std::cout << "│                                       │" << '\n';
    std::cout << "╘═══════════════════════════════════════╛" << '\n';
    std::cout << '\n';
    std::cout << " ╭ Type the desired option \n";
    std::cout << " ╰|> ";
}

void showDateMenu() {
    std::cout << "╭──────────────────────────╮" << '\n';
    std::cout << "│                          │" << '\n';
    std::cout << "│   1 - By single date     │" << '\n';
    std::cout << "│                          │" << '\n';
    std::cout << "│   2 - By date interval   │" << '\n';
    std::cout << "│                          │" << '\n';
    std::cout << "│   0 - Back               │" << '\n';
    std::cout << "│                          │" << '\n';
    std::cout << "╰──────────────────────────╯" << '\n';
    std::cout << '\n';
    std::cout << " ╭ Type the desired option \n";
    std::cout << " ╰|> ";
}

void showDebugMenu() {
    system("clear || cls");

    std::cout << "╭──────────────────────────────────╮" << '\n';
    std::cout << "│                                  │" << '\n';
    std::cout << "│   1 - Show trees                 │" << '\n';
    std::cout << "│                                  │" << '\n';
    std::cout << "│   2 - Show everyone registered   │" << '\n';
    std::cout << "│                                  │" << '\n';
    std::cout << "│   0 - Back                       │" << '\n';
    std::cout << "│                                  │" << '\n';
    std::cout << "╰──────────────────────────────────╯" << '\n';
    std::cout << '\n';
    std::cout << " ╭ Type the desired option \n";
    std::cout << " ╰|> ";
}

void showTreeMenu() {
    system("clear || cls");

    std::cout << "╭─────────────────────╮" << '\n';
    std::cout << "│                     │" << '\n';
    std::cout << "│   1 - National ID   │" << '\n';
    std::cout << "│                     │" << '\n';
    std::cout << "│   2 - Name          │" << '\n';
    std::cout << "│                     │" << '\n';
    std::cout << "│   3 - Date          │" << '\n';
    std::cout << "│                     │" << '\n';
    std::cout << "│   4 - All           │" << '\n';
    std::cout << "│                     │" << '\n';
    std::cout << "│   0 - Back          │" << '\n';
    std::cout << "│                     │" << '\n';
    std::cout << "╰─────────────────────╯" << '\n';
    std::cout << '\n'; 
    std::cout << " ╭ Type the desired option \n";
    std::cout << " ╰|> ";
}

#endif
