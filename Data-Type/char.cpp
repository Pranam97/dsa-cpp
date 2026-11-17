# include <bits/stdc++.h> // This is enough in g++ compilers.

#include <iostream>
#include <cctype>   // Required for isalpha, isdigit, toupper, tolower, etc.

using namespace std;

int main() {
    // 1. Character Classification (<cctype>)
    char c1 = 'A', c2 = '7', c3 = ' ', c4 = '#';

    cout << "--- 1. <cctype> Classification ---\n";
    cout << "isalpha('A'): " << (isalpha(c1) ? "Yes" : "No") << "\n";
    cout << "isupper('A'): " << (isupper(c1) ? "Yes" : "No") << "\n";
    cout << "islower('A'): " << (islower(c1) ? "Yes" : "No") << "\n";
    cout << "isdigit('7'): " << (isdigit(c2) ? "Yes" : "No") << "\n";
    cout << "isalnum('7'): " << (isalnum(c2) ? "Yes" : "No") << "\n";
    cout << "isspace(' '): " << (isspace(c3) ? "Yes" : "No") << "\n";
    cout << "ispunct('#'): " << (ispunct(c4) ? "Yes" : "No") << "\n";


    // 2. Case Conversion (<cctype>)
    // Note: toupper() and tolower() return an int, so cast back to (char)
    cout << "\n--- 2. <cctype> Case Conversion ---\n";
    cout << "tolower('A'): " << (char)tolower('A') << "\n"; // 'a'
    cout << "toupper('z'): " << (char)toupper('z') << "\n"; // 'Z'


    // 3. Char Digit <-> Integer Conversion (- '0' and + '0')
    cout << "\n--- 3. Digit Arithmetic ---\n";
    char digitChar = '8';
    int num = digitChar - '0';              // '8' (56) - '0' (48) = 8
    char backToChar = (char)(num + '0');    // 8 + '0' (48) = '8' (56)
    cout << "Char '8' to int: " << num << "\n";
    cout << "Int 8 to char: " << backToChar << "\n";


    // 4. Alphabet Indexing (- 'a' and - 'A') -> Maps 'a'-'z' to 0-25
    cout << "\n--- 4. Alphabet Indexing ---\n";
    char letter = 'e';
    int index = letter - 'a';               // 'e' (101) - 'a' (97) = 4
    char fromIndex = (char)(index + 'a');   // 4 + 'a' = 'e'
    cout << "'e' index (0-25): " << index << "\n";
    cout << "Index 4 back to char: " << fromIndex << "\n";


    // 5. Frequency Array Trick (Common in DSA)
    cout << "\n--- 5. Frequency Array ---\n";
    char sample[] = "apple";
    int freq[26] = {0};
    for (int i = 0; sample[i] != '\0'; i++) {
        freq[sample[i] - 'a']++;
    }
    cout << "Count of 'p' in 'apple': " << freq['p' - 'a'] << "\n"; // 2


    // 6. Manual ASCII Case Conversion & Range Checks
    cout << "\n--- 6. Manual ASCII Tricks ---\n";
    char ch = 'm';
    if (ch >= 'a' && ch <= 'z') {
        char manualUpper = (char)(ch - 'a' + 'A'); // 'M'
        cout << "Manual uppercase of 'm': " << manualUpper << "\n";
    }

    // 7. Bitwise Case Toggle (^ 32 or ^ ' ')
    char toggle = 'G';
    toggle ^= 32;                           // 'G' -> 'g'
    cout << "Toggled 'G': " << toggle << "\n";
    toggle ^= 32;                           // 'g' -> 'G'
    cout << "Toggled back: " << toggle << "\n";


    // 8. Circular Alphabet Wrap-Around (% 26)
    char zChar = 'z';
    int shift = 3;
    char wrapped = (char)((zChar - 'a' + shift) % 26 + 'a'); // 'c'
    cout << "'z' shifted by 3: " << wrapped << "\n";

    return 0;
}
