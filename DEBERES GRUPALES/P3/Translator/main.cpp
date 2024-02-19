#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>

using namespace std;

// Definition of the dictionary
map<string, string> dictionary;

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
string translateWord(string word) {
    // Search for the word in the dictionary
    auto it = dictionary.find(word);
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

int main() {
    // Name of the file containing the dictionary
    string filename = "dictionary.txt";

    // Load the database at the start of the program
    loadDatabase(filename);

    // Ask the user to enter a word in Spanish
    string spanishWord;
    cout << "Enter a word in Spanish: ";
    cin >> spanishWord;

    // Translate the word entered by the user
    string englishWord = translateWord(spanishWord);

    // Display the translation on the console
    cout << "The translation to English is: " << englishWord << endl;

    // Speak the translated word
    speakWord(englishWord);

    return 0;
}
