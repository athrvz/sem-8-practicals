#include <bits/stdc++.h>
using namespace std;

class Node {
public:
	int val; 
	Node * left = NULL, * right = NULL;
	Node(int x) {
		val = x;
	}
};

class Tree {
public:
	vector <int> getArr(vector <int> a, int l, int r) {
		vector <int> ret;
		for(int i = l; i <= r; i++) 
			ret.push_back(a[i]);
		for(int x: ret) cout << x << " ";
		cout << endl;
		return ret;
	}

	Node* create(int s, int e, vector<int>& nums) {
        if(s > e) return NULL;
        int mid = s + (e-s)/2;
        Node* root = new Node(nums[mid]);
        root -> left = create(s, mid - 1, nums);
        root -> right = create(mid + 1, e, nums);
        return root;
    }

	void inorder(Node * root) {
		if(root == NULL) return;
		cout << root -> val << " ";
		inorder(root -> left);
		inorder(root -> right);
	}

	void bfs(Node * root) {
		queue <Node*> q;
		q.push(root);
		while(!q.empty()) {
			int k = q.size();
			#pragma omp parallel for num_threads(2)
			for(int i = 0; i < k; i++) {
				Node * curr = q.front(); q.pop();
				if(curr != NULL) {
					cout << curr -> val << " ";
					q.push(curr -> left);
					q.push(curr -> right);
				}
			}
			cout << endl;
		}
	}

	void dfs(Node * root) {
		stack <Node*> st;
		st.push(root);
		while(!st.empty()) {
			int k = st.size();
			#pragma omp parallel for num_threads(2)
			for(int i = 0; i < k; i++) {
				Node * curr = st.top(); st.pop();
				if(curr != NULL) {
					cout << curr -> val << " ";
					st.push(curr -> left);
					st.push(curr -> right);
				}
			}
		}

	}
};

int main() {
	vector <int> a = {1, 2, 3, 4, 5};
	Tree tree;
	Node * root = tree.create(0, 4, a);
	tree.inorder(root);
	cout << endl;
	tree.dfs(root);
	// tree.bfs(root);
}