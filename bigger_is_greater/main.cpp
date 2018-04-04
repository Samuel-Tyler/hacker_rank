#include <bits/stdc++.h>

using namespace std;

string biggerIsGreater(string w) {
    string orig = w;
    std::next_permutation(w.begin(), w.end());
    if (strcmp(w.c_str(), orig.c_str()) <= 0)
    {
        return "no answer";
    }
    return w;
}

int main() {
    int T;
    cin >> T;
    for(int a0 = 0; a0 < T; a0++){
        string w;
        cin >> w;
        string result = biggerIsGreater(w);
        cout << result << endl;
    }
    return 0;
}
