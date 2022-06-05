#include <iostream>

using namespace std;

int main() {
    int password;
    cin >> password;
    const int PASSWORD = 1540;
    if (password == PASSWORD) {
        cout << "correct" << endl;
    } else {
        cout << "incorrect" << endl;
    }
    
    return 0;
}