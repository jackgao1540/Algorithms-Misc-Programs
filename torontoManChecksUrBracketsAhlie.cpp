#include <bits/stdc++.h>

using namespace std;

const int MM = 10007;

bool checkBrackets(string s) {
    stack <char> st;
    for(int i = 0; i < s.size(); i++) {
        if (s[i] == '(' || s[i] == '[' || s[i] == '{') {
            st.push(s[i]);
        } else {
            switch(s[i]) {
                case ')':
                    if(st.top() == '('){
                        st.pop();
                    } else return false;
                break;
                case ']':
                    if(st.top() == '['){
                        st.pop();
                    } else return false;
                break;
                case '}':
                    if(st.top() == '{'){
                        st.pop();
                    } else return false;
                break;
                default: return false;
            }
        }
    }
    return st.empty();
}

int main(){
    cout << "Please enter a sequence of brackets using (), {}, and []. Other characters are lowed styll. Jus be sure the length doesn't exceed " << MM << " ahlie?" << endl;
    cout << "Also, if ur tryna dip, dun know fam." << endl;
    while(true) {
        string s;
        getline(cin, s);
        if(s.compare("dun know fam") == 0) return 0;
        string noOtherChars = "";
        for(int i = 0; i < s.size(); i++) {
            if(s[i] == '(' || s[i] == ')' || s[i] == '{' || s[i] == '}' || s[i] == '[' || s[i] == ']') {
                noOtherChars += s[i];
            }
        }
        if (checkBrackets(noOtherChars)) {
            cout << "Mashallah, brackets are valid fr." << endl;
        } else {
            cout << "Wallahi the brackets r buggin fam." << endl;
        }
    }
}