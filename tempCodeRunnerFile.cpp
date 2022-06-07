  for (int i = 0; i < nodes.size(); i++){
        cout << i + 1 << "'s connections: " << endl;
        for (int j = 0; j < nodes[i].connections.size(); j++) {
            cout << nodes[i].connections[j].index << ' ';
        }
        cout << endl;