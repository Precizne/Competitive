// Trie

class Trie {
public:
    vector<array<int, 26>> nxt;
    vector<int> end;

    Trie() {
        nxt.push_back({});
        nxt[0].fill(-1);
        end.push_back(0);
    }

    void insert(string s) {
        int v = 0;
        for(char c : s) {
            int x = c - 'a';
            if(nxt[v][x] == -1) {
                nxt[v][x] = nxt.size();
                nxt.push_back({});
                nxt.back().fill(-1);
                end.push_back(0);
            }
            v = nxt[v][x];
        }
        end[v]++;
    }

    bool find(string s) {
        int v = 0;
        for(char c : s) {
            int x = c - 'a';
            if(nxt[v][x] == -1)
                return false;
            v = nxt[v][x];
        }
        return end[v];
    }
};


// Hash Trie

class HashTrie {
public:
    vector<unordered_map<char, int>> nxt;
    vector<int> end;

    HashTrie() {
        nxt.push_back({});
        end.push_back(0);
    }

    void insert(string s) {
        int v = 0;
        for(char c : s) {
            if(!nxt[v].count(c)) {
                nxt[v][c] = nxt.size();
                nxt.push_back({});
                end.push_back(0);
            }
            v = nxt[v][c];
        }
        end[v]++;
    }

    bool find(string s) {
        int v = 0;
        for(char c : s) {
            if(!nxt[v].count(c))
                return false;
            v = nxt[v][c];
        }
        return end[v];
    }
};
