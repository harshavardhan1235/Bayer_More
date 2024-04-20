#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

const int NO_OF_CHARS = 256;

// A utility function to get maximum of two integers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// The preprocessing function for Boyer Moore's bad character heuristic
void badCharHeuristic(const string& str, int size, vector<int>& badchar) {
    for (int i = 0; i < NO_OF_CHARS; i++)
        badchar[i] = -1;
    for (int i = 0; i < size; i++)
        badchar[(int) str[i]] = i;
}

void search(const string& txt, const string& pat) {
    int m = pat.size();
    int n = txt.size();

    vector<int> badchar(NO_OF_CHARS, -1);

    badCharHeuristic(pat, m, badchar);

    int s = 0; // s is shift of the pattern with respect to text
    while (s <= (n - m)) {
        int j = m - 1;
        while (j >= 0 && pat[j] == txt[s + j])
            j--;
        if (j < 0) {
            cout << "Pattern occurs at shift = " << s << endl;
            s += (s + m < n) ? m - badchar[txt[s + m]] : 1;
        } else
            s += max(1, j - badchar[txt[s + j]]);
    }
}

int main() {
    string txt, pat;
    cout << "Enter the text: ";
    getline(cin, txt);
    cout << "Enter the pattern to search: ";
    getline(cin, pat);
    search(txt, pat);
    return 0;
}
