#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <locale>
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <algorithm> // Para la funci�n transform

using namespace std;

// Definition of the dictionary
map<string, string> dictionary;

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void color(int foreground, int background) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), foreground + (background * 16));
}
void menuSeleccion(const char *titulo, const char *opciones[], int numeroOpciones, int &selec) {
    int tecla;
    bool aux = true;

    do {
        system("cls");
        gotoxy(15, 2);
        printf("\t\t%s",titulo);
        for (int i = 0; i < numeroOpciones; i++) {
            gotoxy(30, 5 + i);
            if ((i + 1) == selec) {
                color(15, 9);  // Highlighted color
                printf("%s", opciones[i]);
                color(15, 0); /// Highlighted color
            } else {
                printf("%s", opciones[i]);
            }
        }

        do {
            fflush(stdin);
            tecla = getch();
        } while ((tecla != 72) && (tecla != 80) && (tecla != 13));

        switch (tecla) {
            case 72:  // Up arrow
                selec--;
                if (selec < 1) {
                    selec = numeroOpciones;
                }
                aux = true;
                break;
            case 80:  // Down arrow
                selec++;
                if (selec > numeroOpciones) {
                    selec = 1;
                }
                aux = true;
                break;
            case 13:  // Enter
                aux = false;
                break;
        }
    } while (aux);
}


// Function to load the database from a file
void loadDatabase(const string& filename) {
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Error: Couldn't open the file." << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        // Using a stringstream to split the line into words
        stringstream ss(line);
        string spanishWord, englishWord;
        // Read the Spanish word
        getline(ss, spanishWord, ':'); // Assuming words are separated by ':'
        // Read the English word
        getline(ss, englishWord);
        
        // Remove spaces from the words
        spanishWord.erase(remove_if(spanishWord.begin(), spanishWord.end(), ::isspace), spanishWord.end());
        englishWord.erase(remove_if(englishWord.begin(), englishWord.end(), ::isspace), englishWord.end());

        // Add the word to the dictionary
        dictionary[spanishWord] = englishWord;
    }

    file.close();
}

// Function to translate a word
string translateWord(const string& word) {
    // Convert the word to lowercase and remove spaces
    string lowerCaseWord = word;
    transform(lowerCaseWord.begin(), lowerCaseWord.end(), lowerCaseWord.begin(), ::tolower);
    lowerCaseWord.erase(remove_if(lowerCaseWord.begin(), lowerCaseWord.end(), ::isspace), lowerCaseWord.end());

    // Search for the word in the dictionary
    auto it = dictionary.find(lowerCaseWord);
    if (it != dictionary.end()) {
        // If the word is found, return its translation
        return it->second;
    } else {
        // If the word is not found in the dictionary, return a message indicating that the translation was not found
        return "Translation not found";
    }
}


// Function to speak a word
void speakWord(const string& word) {
    string command = "espeak \"" + word + "\"";
    system(command.c_str());
}

void MenuPrincipal() {
    
    string expresion, post,prefijo;
    int op = 0;
    bool aux = true;
    string ecuacion;
    const char *titulo = "\t\t<<<<<TRANSLATOR>>>>>";
    const char *opciones[] =
    {
        "\t\tTranslate Word",
        "\t\tExit"
    };
    int numeroOpciones = 2;
    int selec = 1;

    do {
        menuSeleccion(titulo, opciones, numeroOpciones, selec);
        switch (selec) {
          case 1:
                {
                    try {
                        system("cls");
                        // Configure the locale for UTF-8
                        setlocale(LC_ALL, "spanish");

                        // Name of the file containing the dictionary
                        string filename = "dictionary.txt";

                        // Load the database at the start of the program
                        loadDatabase(filename);

                        // Ask the user to enter a word in Spanish
                        string spanishWord;
                        cout << "Enter a word in Spanish: ";
                        getline(cin, spanishWord); // Read the entire line, including spaces

                        // Translate the word entered by the user
                        string englishWord = translateWord(spanishWord);

                        // Display the translation on the console
                        cout << "The translation to English is: " << englishWord << endl;

                        // Speak the translated word
                        speakWord(englishWord);
                        system("pause");
                    } catch (const std::exception& e) {
                        system("pause");
                        MenuPrincipal();
                        break;
                    }
                    break;
                }

            case 2:
                {
                    system("cls");
                    cout << "Exit to the program..." << endl;
                    aux = false; // Salir del bucle
                    break;
                }
        }
    } while (aux);
}
int main() {
    MenuPrincipal();

    return 0;
}