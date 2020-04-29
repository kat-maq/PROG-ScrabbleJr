
#include "editIO.h"
#include <limits>
#include <iostream>

#ifdef _WIN32  // Windows compatibility
#include <windows.h>
#include <cstdlib>
#define NOMINMAX
#endif


void clearScreen() {
#ifdef _WIN32
    COORD coordScreen = { 0, 0 };  // upper left corner
    DWORD cCharsWritten;
    DWORD dwConSize;
    HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hCon, &csbi);
    dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
    // fill with spaces
    FillConsoleOutputCharacter(hCon, TEXT(' '), dwConSize, coordScreen, &cCharsWritten);
    GetConsoleScreenBufferInfo(hCon, &csbi);
    FillConsoleOutputAttribute(hCon, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten);
    // cursor to upper left corner
    SetConsoleCursorPosition(hCon, coordScreen);
#else
    std::cout << "\033[2J\033[1;1H";
#endif
}



void readDimentions(unsigned &col, unsigned &lines) {
    std::cout << "Number of lines ? ";
    std::cin >> lines;
    while (std::cin.fail() || lines < 0 || lines > 20) {
        if (std::cin.fail()) {
            if (std::cin.eof()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "User chose to close the input.\n";
                break;
            } else {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Failed to read number. Try again: ";
                std::cin >> lines;
            }
        } else {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "That is not a valid number of lines. Remember, maximum allowed is 20. Try again: ";
            std::cin >> lines;
        }
    }

    std::cout << "Number of columns ? ";
    std::cin >> col;
    while (std::cin.fail() || col < 0 || col > 20) {
        if (std::cin.fail()) {
            if (std::cin.eof()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "User chose to close the input.\n";
                break;
            } else {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Failed to read number. Try again: ";
                std::cin >> col;
            }
        } else {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "That is not a valid number of columns. Remember, maximum allowed is 20. Try again: ";
            std::cin >> col;
        }
    }

}


void readCoordinates(std::pair<char, char> &coords, const Board &board) {
    std::cout << "Starting position line ? ";
    std::cin >> coords.first;
    while (std::cin.fail() || !isalpha(coords.first) || coords.first - 65 > board.getnLines()) {
        if (std::cin.eof()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "User chose to close input.\n";
            break;
        } else {
            std::cout << "Invalid line choice. Try again: ";
            std::cin >> coords.first;
        }
    }

    std::cout << "Starting position column ? ";
    std::cin >> coords.second;
    while (std::cin.fail() || !isalpha(coords.second) || coords.second - 97 > board.getnCols()) {
        if (std::cin.eof()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "User chose to close input.\n";
            break;
        } else {
            std::cout << "Invalid column choice. Try again: ";
            std::cin >> coords.second;
        }

    }

    coords.first -= 65;
    coords.second -= 97;

}

void readOrientation(char &orientation) {
    std::cout << "Orientation ? ";
    std::cin >> orientation;
    while (std::cin.fail() || (orientation != 'V' && orientation != 'H') || std::cin.peek() != '\n') {
        if (std::cin.eof()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "User chose to close input.\n";
            break;
        } else {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid orientation. Insert V for vertical or H for horizontal. Try again: ";
            std::cin >> orientation;
        }
    }
}

void readWord(std::string &word) {
    std::cout << "Word ? ";
    std::cin >> word;

    while (true) {
        while (std::cin.fail() || std::cin.peek() != '\n') {
            if (std::cin.eof()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "User chose to close input.\n";
                break;
            } else {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input. Remember, your word must not have any spaces. Try again: ";
                std::cin >> word;
            }
        }
        for (const char i : word) {
            if (!isalpha(i)) {
                std::cout << "Word must not include numbers or symbols. Try again: ";
                std::cin >> word;
            }
        }
        break;
    }
}

void readFileName(std::string &fileName) {
    std::cout
            << "Be aware of your operating system's naming limitations.\nWindows - no reserved names, no <>:\\/|?*,"
               " don't end with \' \' or \'.\'\nLinux - no \'/\' \n";

    std::cout << "File name (without extension) ? ";
    std::cin >> fileName;
    fileName += ".txt";



    while (true) {
        std::ofstream test(fileName);
        if (std::cin.fail() || !test) {
            std::cout << "Invalid file name. Try again: ";
            std::cin >> fileName;
            fileName += ".txt";
        } else {
            break;
        }
    }
}

void searchFile(std::string &fileName) {

    std::cout << "Search for board (without file extention) : ";
    std::cin >> fileName;

    while (true) {
        fileName += ".txt";
        std::ifstream file(fileName);
        if (!file.good()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Board not found. Try again : ";
            std::cin >> fileName;
        } else {
            break;
        }
    }
}