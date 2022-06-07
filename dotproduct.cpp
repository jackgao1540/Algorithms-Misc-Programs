#include <iostream>

using namespace std;

const int MM = 10007;

unsigned long long int dotProd(int* v1, int* v2, int size) {
    unsigned long long int ans = 0;
    for(int i = 0; i < size; i++) {
        ans += (v1[i] * v2[i]) % MM;
        ans %= MM;
    }
    return ans;
}

int main() {
    cout << "Please enter vector size (< " << MM << "): ";
    int size; 
    cin >> size;
    int v1[MM], v2[MM];
    cout << endl << "Please enter the entries for two vectors separated by spaces: " << endl;
    for(int i = 0; i < size; i++) {
        cin >> v1[i];
    }
    for(int i = 0; i < size; i++) {
        cin >> v2[i];
    }
    cout << "The dot product of these two vectors is: " << dotProd(v1, v2, size) << endl;
    return 0;
}