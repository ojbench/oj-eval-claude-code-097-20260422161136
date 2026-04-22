#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <queue>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

TreeNode* buildTree(const vector<string>& nodes) {
    if (nodes.empty() || nodes[0] == "null") return NULL;

    TreeNode* root = new TreeNode(stoi(nodes[0]));
    queue<TreeNode*> q;
    q.push(root);

    int i = 1;
    while (!q.empty() && i < nodes.size()) {
        TreeNode* curr = q.front();
        q.pop();

        if (i < nodes.size() && nodes[i] != "null") {
            curr->left = new TreeNode(stoi(nodes[i]));
            q.push(curr->left);
        }
        i++;

        if (i < nodes.size() && nodes[i] != "null") {
            curr->right = new TreeNode(stoi(nodes[i]));
            q.push(curr->right);
        }
        i++;
    }
    return root;
}

void reverseInorder(TreeNode* root, int& cnt, int& result) {
    if (!root || result != -1) return;

    reverseInorder(root->right, cnt, result);

    if (result != -1) return;

    cnt--;
    if (cnt == 0) {
        result = root->val;
        return;
    }

    reverseInorder(root->left, cnt, result);
}

int main() {
    string line;
    // The input format is "root = [12, 5, 18, 2, 9, 15, 20], cnt = 4"
    // We need to parse this string.

    if (getline(cin, line)) {
        size_t root_pos = line.find("root = [");
        size_t root_end = line.find("]", root_pos);
        if (root_pos == string::npos || root_end == string::npos) return 0;

        string root_str = line.substr(root_pos + 8, root_end - (root_pos + 8));

        size_t cnt_pos = line.find("cnt = ", root_end);
        if (cnt_pos == string::npos) return 0;
        int cnt = stoi(line.substr(cnt_pos + 6));

        vector<string> nodes;
        stringstream ss(root_str);
        string item;
        while (getline(ss, item, ',')) {
            // Remove spaces
            item.erase(remove(item.begin(), item.end(), ' '), item.end());
            if (!item.empty()) {
                nodes.push_back(item);
            }
        }

        TreeNode* root = buildTree(nodes);
        int result = -1;
        reverseInorder(root, cnt, result);
        cout << result << endl;
    }

    return 0;
}
