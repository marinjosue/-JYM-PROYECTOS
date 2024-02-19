#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <locale>
#include <algorithm>

using namespace std;

// Definition of the dictionary
map<string, string> dictionary;

void gotoxy(int x, int y) {
    cout << "\033[" << y << ";" << x << "H";
}

void clearScreen() {
    cout << "\033[2J\033[1;1H";
}

void color(int foreground, int background) {
    cout << "\033[" << foreground << ";" << background + 40 << "m";
}

void menuSelection(const char *title, const char *options[], int numOptions, int &select) {
    int key;
    bool running = true;

    do {
        clearScreen();
        cout << "\t\t" << title << endl;
        for (int i = 0; i < numOptions; i++) {
            if ((i + 1) == select) {
                color(37, 44);  // Highlighted color
                cout << "\t\t" << options[i] << endl;
                color(0, 0); // Reset color
            } else {
                cout << "\t\t" << options[i] << endl;
            }
        }

        do {
            key = getchar();
        } while ((key != 65) && (key != 66) && (key != 10)); // UP: 65, DOWN: 66, ENTER: 10

        switch (key) {
            case 65:  // Up arrow
                select--;
                if (select < 1) {
                    select = numOptions;
                }
                break;
            case 66:  // Down arrow
                select++;
                if (select > numOptions) {
                    select = 1;
                }
                break;
            case 10:  // Enter
                running = false;
                break;
        }
    } while (running);
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
        // Add the word to the dictionary
        dictionary[spanishWord] = englishWord;
    }

    file.close();
}

// Function to translate a word
string translateWord(const string& word) {
    // Convert the word to lowercase
    string lowerCaseWord = word;
    transform(lowerCaseWord.begin(), lowerCaseWord.end(), lowerCaseWord.begin(), ::tolower);

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
    string expresion, post, prefijo;
    int op = 0;
    bool aux = true;
    string ecuacion;
    const char *titulo = "\t\t<<<<<TRANSLATOR>>>>>";
    const char *opciones[] =
    {
        "\t\t1. Translate Word",
        "\t\t2. Exit"
    };
    int numeroOpciones = 2;
    int selec;

    do {
        system("cls");
        cout << titulo << endl;
        for (int i = 0; i < numeroOpciones; i++) {
            cout << opciones[i] << endl;
        }
        cout << "Enter your choice: ";
        cin >> selec;

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
                        cin.ignore(); // Clear the input buffer
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
                
            default:
                {
                    system("cls");
                    cout << "Invalid option. Please enter a valid option." << endl;
                    system("pause");
                    break;
                }
        }
    } while (aux);
}


int main() {
    MenuPrincipal();
    return 0;
}
