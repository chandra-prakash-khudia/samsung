#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <unordered_map>
#include <unordered_set>
using namespace std;

struct Node {
    int val;
    Node *left, *right;
    Node(int v): val(v), left(nullptr), right(nullptr) {}
};

// build tree from level-order vector where -1 means null
Node* buildLevelOrder(const vector<int>& vals) {
    if (vals.empty() || vals[0] == -1) return nullptr;
    Node* root = new Node(vals[0]);
    queue<Node*> q;
    q.push(root);
    size_t i = 1;
    while (!q.empty() && i < vals.size()) {
        Node* cur = q.front(); q.pop();
        // left
        if (i < vals.size()) {
            if (vals[i] != -1) {
                cur->left = new Node(vals[i]);
                q.push(cur->left);
            }
            ++i;
        }
        // right
        if (i < vals.size()) {
            if (vals[i] != -1) {
                cur->right = new Node(vals[i]);
                q.push(cur->right);
            }
            ++i;
        }
    }
    return root;
}

unordered_map<Node*, int> dp;
int computeDP(Node* node) {
    if (!node) return 0;
    int L = computeDP(node->left);
    int R = computeDP(node->right);
    int h = 1 + min(L, R); // maximum perfect-tree height we can keep rooted here
    dp[node] = h;
    return h;
}

unordered_set<Node*> keepSet;
void markKeep(Node* node, int h) {
    if (!node || h <= 0) return;
    keepSet.insert(node);
    if (h == 1) return; // node must be a leaf in the final perfect tree
    // children must exist to reach h>1; dp ensures feasibility
    markKeep(node->left, h-1);
    markKeep(node->right, h-1);
}

void collectRemoved(Node* node, vector<int>& removed) {
    if (!node) return;
    if (keepSet.find(node) == keepSet.end()) {
        // whole subtree rooted here is removed; collect all nodes in subtree
        // do a simple DFS to collect
        stack<Node*> st;
        st.push(node);
        while (!st.empty()) {
            Node* cur = st.top(); st.pop();
            removed.push_back(cur->val);
            if (cur->left) st.push(cur->left);
            if (cur->right) st.push(cur->right);
        }
        return;
    }
    // node is kept, recurse into children
    collectRemoved(node->left, removed);
    collectRemoved(node->right, removed);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    vector<int> vals;
    vals.reserve(n);
    for (int i = 0; i < n; ++i) {
        int x; cin >> x;
        vals.push_back(x);
    }
    Node* root = buildLevelOrder(vals);
    // compute dp
    computeDP(root);
    int H = dp.count(root) ? dp[root] : 0;
    // mark nodes to keep (largest perfect subtree rooted at root)
    if (H > 0) markKeep(root, H);
    // collect removed nodes
    vector<int> removed;
    collectRemoved(root, removed);
    // print removed nodes (one per line). If none, print "None"
    if (removed.empty()) {
        cout << "None\n";
    } else {
        // printing in the order they were discovered (may be arbitrary).
        for (int v : removed) cout << v << "\n";
    }
    return 0;
}
