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

void MainMenu() {
    int select = 1;
    const char *title = "<<<<<TRANSLATOR>>>>>";
    const char *options[] =
    {
        "Translate Word",
        "Exit"
    };
    int numOptions = 2;

    do {
        menuSelection(title, options, numOptions, select);
        switch (select) {
            case 1:
                {
                    try {
                        clearScreen();
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
                        cout << endl;
                        cout << "Press Enter to continue...";
                        cin.ignore(); // Ignore the newline character from previous input
                        cin.get();    // Wait for user to press Enter
                    } catch (const std::exception& e) {
                        cerr << "An error occurred: " << e.what() << endl;
                        cout << "Press Enter to continue...";
                        cin.ignore(); // Ignore the newline character from previous input
                        cin.get();    // Wait for user to press Enter
                    }
                    break;
                }

            case 2:
                {
                    clearScreen();
                    cout << "Exiting the program..." << endl;
                    break;
                }
        }
    } while (select != 2);
}

int main() {
    MainMenu();
    return 0;
}
