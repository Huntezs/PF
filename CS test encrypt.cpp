#include <iostream>
#include <string>
#include <vector>

using namespace std;

string encryptRailFence(string text, int key) {
    if (key <= 1) return text;
    
    vector<string> rail(key);
    int row = 0;
    bool dir_down = false;

    for (char c : text) {
        rail[row] += c;
        if (row == 0 || row == key - 1) {
            dir_down = !dir_down;
        }
        row += dir_down ? 1 : -1;
    }

    string result = "";
    for (int i = 0; i < key; i++) {
        result += rail[i];
    }
    return result;
}

string decryptRailFence(string cipher, int key) {
    if (key <= 1) return cipher;

    int len = cipher.length();
    vector<string> rail(key, string(len, '*'));
    
    int row = 0;
    bool dir_down = false;

    // Mark the zigzag path positions with '*'
    for (int i = 0; i < len; i++) {
        rail[row][i] = '\n'; // visual temporary marker
        if (row == 0 || row == key - 1) {
            dir_down = !dir_down;
        }
        row += dir_down ? 1 : -1;
    }

    // Fill the marked positions with actual cipher letters row by row
    int index = 0;
    for (int i = 0; i < key; i++) {
        for (int j = 0; j < len; j++) {
            if (rail[i][j] == '\n' && index < len) {
                rail[i][j] = cipher[index++];
            }
        }
    }

    // Read the matrix in zigzag order to reconstruct the plaintext
    string result = "";
    row = 0;
    dir_down = false;
    for (int i = 0; i < len; i++) {
        result += rail[row][i];
        if (row == 0 || row == key - 1) {
            dir_down = !dir_down;
        }
        row += dir_down ? 1 : -1;
    }
    return result;
}

int main() {
    string text = "HELLORAILFENCE";
    int key = 3;

    cout << "Original: " << text << endl;
    string cipher = encryptRailFence(text, key);
    cout << "Encrypted: " << cipher << endl;
    string plain = decryptRailFence(cipher, key);
    cout << "Decrypted: " << plain << endl;

    return 0;
}
