#include <bits/stdc++.h>

using namespace std;

const int MM = 1e5 + 7;

// I tried to frame this knapsack problem in a practical and interesting way.
// I hope I succeeded in this endeavor.

struct food {
    string name;
    int value;
    int diminish;
    int price;
};

int n, budget;
vector <food> foods;

int main() {
    cout << "Imagine you really love food. You assign each food a numerical rating, [PRESS ENTER TO CONTINUE]" << endl;
    cin.ignore();
    cout << "For the enjoyment that it brings you when you consume it." << endl;
    cin.ignore();
    cout << "However, food costs money!" << endl;
    cin.ignore();
    cout << "This program will optimize your enjoyment of priced foods, " << endl;
    cin.ignore();
    cout << "Given your budget." << endl;
    cin.ignore();
    cout << endl << "Please enter the number of food items to choose from: ";
    cin >> n;

    if (n < 4) cout << endl << "Not much variety, huh?";
    else if(n > 8) cout << "Wow, that's a lot of options!";
    else cout << "Okay, decent range of foods to choose from.";
    cin.ignore();
    cout << endl << "Now, realistically, to convert a food item to code, I'm gonna need some information:" << endl;
    cin.ignore();
    cout << "Your enjoyment of it: a numerical value (not on any particular scale; it's all relative)" << endl;
    cin.ignore();
    cout << "The diminishing returns of repeatedly consuming a food item." << endl;
    cin.ignore();
    cout << "This figure is the amount that enjoyment decreases by after each time you consume the food." << endl;
    cin.ignore();
    cout << "Note: it can be negative, meaning you increasingly enjoy eating a food, although that's definitely not very realistic." << endl;
    cin.ignore();
    cout << "Lastly, the name of each food, as well as the price of it." << endl;
    cin.ignore();
    cout << endl << "Please enter the name, enjoyment, diminish value, and price of the foods (" << n << " times)" << endl;

    // get foods
    for (int i = 0; i < n; i++) {
        string s; int v, d, p;
        cin >> s >> v >> d >> p;
        food f; f.name = s; f.value = v; f.diminish = d; f.price = p;
        foods.push_back(f);
    }

    cout << "Great! Now please enter your budget: ";
    cin >> budget;

    // perform knapsack dp

    // initialize dp array
    vector <vector <vector <int>>> dp;
    vector <vector <int>> temp;
    vector <int> tmp;

    vector <vector <int>> valDP;

    for (int j = 0; j <= budget; j++) {
        temp.push_back(tmp);
    }
    for (int i = 0; i < 2; i++) {
        dp.push_back(temp);
    }
    for (int j = 0; j <= budget; j++) {
        tmp.push_back(0);
    }
    for (int i = 0; i < 2; i++) {
        valDP.push_back(tmp);
    }

    // start dp
    for (int i = 0; i < n; i++) {
        vector <int> times;
        times.push_back(0);
        food curFood = foods[i];
        for (int j = 1; j <= budget; j++) {
            // take maximum of adding a new one of this one, or last row, or last row with new one of this one
            if (j < curFood.price) {
                times.push_back(0);
                if (i >= 1) {
                    dp[i%2][j] = dp[(i - 1)%2][j];
                    valDP[i%2][j] = valDP[(i - 1)%2][j];
                }
            } else if (i == 0){
                vector <int> prev = dp[i%2][j - curFood.price];
                prev.push_back(i);

                int lastVal = valDP[i%2][j - 1];
                int cur = valDP[i%2][j - curFood.price] + curFood.value - curFood.diminish * times[j - curFood.price];
                if(lastVal > cur) {
                    valDP[i%2][j] = lastVal;
                    times.push_back(times[j - 1]);
                    dp[i%2][j] = dp[i%2][j -  1];
                } else {
                    valDP[i%2][j] = cur;
                    times.push_back(times[j - curFood.price] + 1);
                    dp[i%2][j] = prev;
                }
            } else {
                vector <int> last = dp[(i - 1)%2][j];
                vector <int> lastCur = dp[(i - 1)%2][j - curFood.price];
                lastCur.push_back(i);
                vector <int> cur = dp[i%2][j - curFood.price];
                cur.push_back(i);

                // find the maxes using valDP
                int lastVal = valDP[(i - 1)%2][j];
                int lastCurVal = valDP[(i - 1)%2][j - curFood.price] + curFood.value;
                int curVal = valDP[i%2][j - curFood.price] + curFood.value - times[j - curFood.price] * curFood.diminish;

                // set max
                valDP[i%2][j] = max(max(valDP[i%2][j - 1], lastVal), max(lastCurVal, curVal));
                if(valDP[i%2][j] == valDP[i%2][j - 1]){
                    times.push_back(0);
                    dp[i%2][j] = dp[i%2][j - 1];
                } else if(valDP[i%2][j] == lastVal) {
                    times.push_back(0);
                    dp[i%2][j] = last;
                } else if(valDP[i%2][j] == lastCurVal) {
                    times.push_back(1);
                    dp[i%2][j] = lastCur;
                } else {
                    times.push_back(times[j - curFood.price] + 1);
                    dp[i%2][j] = cur;
                }
            }
        }
    }

    // print answer
    cout << "Best enjoyment value: " << valDP[(n - 1)%2][budget] << endl;
    cout << "Best combination of food: ";
    for (int i = 0; i < dp[(n - 1)%2][budget].size(); i++) {
        cout << foods[dp[(n - 1)%2][budget][i]].name << ' ';
    }
    cout << endl;
    return 0;
}