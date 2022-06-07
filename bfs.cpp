#include <bits/stdc++.h>

using namespace std;

const int MM = 10007;

struct Node {
    int index;
    vector <Node> connections;
};

// Was debugging for almost an hour because of errors copying struct Node for priority Queue
// Next time if you have an existing array of all the Nodes, don't use list<Node> for pQ
// Instead just use list<int> and access the nodes by index; less memory and less errors created

/*
Example inputs:

numNodes: 5
Connections: 8
             (1, 2)
             (1, 3)
             (2, 1)
             (2, 3)
             (2, 5)
             (3, 4)
             (4, 1)
             (4, 5)

Test Cases  (A, B)   ANSWER FORMAT:  (distance, {path})
            (1, 5) : expected output (2, {1, 2, 5}) 
            (5, 1) : expected output "No such path"
            (4, 3) : expected output (2, {4, 1, 3}) 
            (3, 2) : expected output (3, {3, 4, 1, 2}) 
*/

vector <Node> nodes;

vector <int> bfs(int a, int b) {
    bool visited[MM] = {0};
    list <int> pQ;
    list <vector <int>> dist;
    pQ.push_back(a);
    vector <int> tmp; tmp.push_back(a);
    dist.push_back(tmp);
    while(!pQ.empty()){
        int top = pQ.front();
        pQ.pop_front();
        vector <int> path = dist.front();
        dist.pop_front();
        
        //debug
        cout << "Visiting: " << top + 1 << endl;

        if (visited[top]) continue;
        cout << "    Not visited!" << endl;
        visited[top] = true;
        if (top == b) {
            return path;
        } 
        cout << "    Has " << nodes[top].connections.size() << " neighbours!" << endl;
        cout << "    Added: ";
        for(int i = 0; i < nodes[top].connections.size(); i++){
            pQ.push_back(nodes[top].connections[i].index);
            cout << nodes[top].connections[i].index + 1 << ' ';
            vector <int> temp = path;
            temp.push_back(nodes[top].connections[i].index);
            dist.push_back(temp);
        }
        cout << endl << endl;
    }
    vector <int> noSol; noSol.push_back(-1);
    return noSol;
}

int main() {
    Node temp;
    int numNodes, q;

    cout << "Please enter the number of nodes in the directed unweighted graph (< " << MM << "): ";
    cin >> numNodes;

    // prep vectors
    for (int i = 0; i < numNodes; i++) {
        temp.index = i;
        nodes.push_back(temp);
    }

    cout << endl << "Please enter the number of associations you would like to make between nodes: ";
    cin >> q;
    cout << endl << "Please enter " << q << " statements with two space-separated integers denoting that the i-th node has a connection to the j-th node" << endl;
    for (int a, b, i = 0; i < q; i++) {
        cin >> a >> b;
        nodes[a - 1].connections.push_back(nodes[b - 1]);
    }

    cout << endl << "Please enter statements with two space-separated integers denoting the i-th and j-th nodes. Enter -1 to exit" << endl;
    while(true) {
        int a, b;
        cin >> a >> b;
        if (a == -1 || b == -1) break;
        vector <int> ans = bfs(a - 1, b - 1);
        if(ans[0] == -1) {
            cout << "No such path" << endl;
        } else {
            cout << "The shortest distance from node " << a << " to node " << b << " is " << ans.size() - 1 << endl;
            cout << "Path: ";
            for (int i = 0; i < ans.size(); i++) cout << ans[i] + 1 << (i == ans.size() - 1 ? "" : " -> ");
        }
        
        cout << endl;
    }

}