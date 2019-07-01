#include <iostream>
#include <cmath>
#include <climits>

using namespace std;


template <typename T>
class Tree {

public:

    class iterator {
    private:
        Tree& tree;
        int currentRank;

    public:

        iterator(Tree& tree, int rank = 0) : tree(tree), currentRank(rank)
        {}

        iterator(const iterator& other) : tree(other.tree), currentRank(other.currentRank)
        {}

        T& operator*() {
            return tree.findByRank(tree.root, currentRank)->data;
        }

        iterator& operator++() {
            ++currentRank;
            return *this;
        }

        iterator operator++(int) {
            return iterator(tree,++currentRank);
        }

        bool operator== (const iterator& other){
            return (this->tree == other.tree) && (this->currentRank == other.currentRank);
        }

        bool operator!= (const iterator& other){
            return !((*this) == other);
        }

    };

protected:

    class TreeNode {
        public:
        T data;
        TreeNode* left;
        TreeNode* right;
        int height;
        int children;

        ~TreeNode(){
            delete left;
            delete right;
        }
    };


    TreeNode* root;


    const T& max(const T& a, const T& b) const {
        return (a > b) ? a : b;
    }

    int height(TreeNode* v) const {
        return v ? v->height : 0;
    }

    int balance(TreeNode* v) const {
        return v ? (this->height(v->left) - this->height(v->right)) : 0;
    }

    void showInOrder(TreeNode* v) const {
        if (v == nullptr) {
            return;
        }
        
        showInOrder(v->left);
        cout << v->data << "(" << v->children << ") ";
        showInOrder(v->right);
    }

    void showPostOrder(TreeNode* v) const {
        if (v == nullptr) {
            return;
        }
        
        cout << "((";
        showPostOrder(v->left);
        cout << ")(";
        showPostOrder(v->right);
        cout << ") " << v->data << ")";
    }

    void showPreOrder(TreeNode* v) const {
        if (v == nullptr) {
            return;
        }

        cout << "(" << v->data << " (";
        showPreOrder(v->left);
        cout << ")(";
        showPreOrder(v->right);
        cout << "))";
    }

    bool find2(TreeNode* v, const T& key) const {
        if (!v) {
            return false;
        }
        if (v->data == key) {
            return true;
        }

        if (key < v->data) {
            return find2(v->left, key);
        } else {
            return find2(v->right, key);
        }
    }

    TreeNode* findmin(TreeNode* v) const {
        if (!v) {
            return nullptr;
        }

        if (v->left == nullptr) {
            return v;
        } else {
            return findmin(v->left);
        }
    }

    TreeNode* findmax(TreeNode* v) const {
        if (!v) {
            return nullptr;
        }

        if (v->right == nullptr) {
            return v;
        } else {
            return findmax(v->right);
        }
    }

    int findRank(TreeNode* v, const T& x) const {
        if (!v) {
            return -1;
        }

        if (x < v->data) {
            return findRank(v->left, x);
        } else if (x > v->data) {
            if (v->left) {
                return v->left->children + 1 + findRank(v->right, x);
            } else {
                return 1 + findRank(v->right, x);
            }
        } else {
            if (v->left) {
                return v->left->children + 1;
            } else {
                return 1;
            }
        }
    }

    TreeNode* findByRank(TreeNode* v, int i) const {
        if (!v) {
            return nullptr;
        }

        int leftcount;

        if (!(v->left)) {
            leftcount = 0;
        } else {
            leftcount = v->left->children;
        }

        if (i <= leftcount) {
            return findByRank(v->left, i);
        } else if (i == (leftcount + 1)) {
            return v;
        } else if(i > (leftcount + 1)) {
            return findByRank(v->right, i - leftcount - 1);
        }

        return nullptr;
    }

    void closestNeighbourHelper(TreeNode* v, const T& x, int& currentDiff, TreeNode*& closestNeighbour) const {
        if (!v) {
            return;
        }

        if (v->data == x) {
            closestNeighbour = v;
            return;
        }

        if (currentDiff > abs(v->data - x)) {
            currentDiff = abs(v->data - x);
            closestNeighbour = v;
        }

        if (x < v->data) {
            closestNeighbourHelper(v->left, x, currentDiff, closestNeighbour);
        } else {
            closestNeighbourHelper(v->right, x, currentDiff, closestNeighbour);
        }
        
    }

    int nodesBetweenHelper(TreeNode* v, const T& x, const T& y) const {
        if(!v) return 0;

        if (v->data == x && v->data == y) {
            return 1;
        }

        if (v->data <= y && v->data >= x) {
            return v->children;
        } else if (v->data < x) {
            return nodesBetweenHelper(v->right, x, y);
        } else {
            return nodesBetweenHelper(v->left, x, y);
        }
    }

    TreeNode* insertInto(TreeNode* v, const T& item) {
        if (!v) {
            TreeNode* leaf = new TreeNode;
            leaf->data = item;
            leaf->height = 1;
            leaf->children = 1;
            leaf->left = leaf->right = nullptr;
            return leaf;
        }

        if (item < v->data) {
            v->left = insertInto(v->left, item);
        } else if (item > v->data) {
            v->right = insertInto(v->right, item);
        } else {
            return v;
        }

        v->height = this->max(this->height(v->left), this->height(v->right)) + 1;
        v->children = (v->left ? v->left->children : 0) + (v->right ? v->right->children : 0) + 1;

        int balance = this->balance(v);

        if (balance > 1 && v->left && item <  v->left->data) {
            return rotate_right(v);
        }

        if (balance < -1 && v->right && item > v->right->data) {
            return rotate_left(v);
        }

        if (balance > 1 && v->left && item > v->left->data) {
            v->left = rotate_left(v->left);
            return rotate_right(v);
        }

        if (balance < -1 && v->right && item < v->right->data) {
            v->right = rotate_right(v->right);
            return rotate_left(v);
        }

        return v;
    }

    TreeNode* del(TreeNode* v, const T& item){
        if(!v) return nullptr;

        if (item < v->data) {
            v->left = del(v->left, item);
        } else if (item > v->data) {
            v->right = del(v->right, item);
        } else {
            if (v->left == nullptr || v->right == nullptr) {
                TreeNode* temp = v->right ? v->right : v->left;
                
                if(temp == nullptr){
                    temp = v;
                    v = nullptr;
                } else {
                    *v = *temp;
                }

                delete temp;
            } else {
                TreeNode* min = findmin(v->right);
                v->data = min->data;
                v->right = del(v->right, min->data);
            }
        }

        if(!v) return v;

        v->height = this->max(this->height(v->left), this->height(v->right)) + 1;
        v->children = (v->left ? v->left->children : 0) + (v->right ? v->right->children : 0) + 1;

        int balance = this->balance(v), leftBalance = this->balance(v->left), rightBalance = this->balance(v->right);

        if (balance > 1 && leftBalance >= 0) {
            return rotate_right(v);
        }

        if(balance > 1 && leftBalance < 0){
            v->left = rotate_left(v->left);
            return rotate_right(v);
        }

        if (balance < -1 && rightBalance <= 0) {
            return rotate_left(v);
        }

        if (balance < -1 && rightBalance > 0) {
            v->right = rotate_right(v->right);
            return rotate_left(v);
        }

        return v;
    }

    TreeNode* rotate_right(TreeNode* v){
        TreeNode *x = v->left, *y = v, *xRight = x ? x->right : nullptr;

        x->right = y;
        y->left = xRight;

        y->height = this->max(this->height(y->left), this->height(y->right)) + 1;
        if (x) {
            x->height = this->max(this->height(x->left), this->height(x->right)) + 1;
        }

        y->children = (y->left ? y->left->children : 0) + (y->right ? y->right->children : 0) + 1;
        if (x) {
            x->children = (x->left ? x->left->children : 0) + (x->right ? x->right->children : 0) + 1;
        }

        return x;
    }

    TreeNode* rotate_left(TreeNode* v){
        TreeNode *x = v, *y = v->right, *yLeft = y ? y->left : nullptr;

        y->left = x;
        x->right = yLeft;

        x->height = this->max(this->height(x->left), this->height(x->right)) + 1;
        if (y) {
            y->height = this->max(this->height(y->left), this->height(y->right)) + 1;
        }

        x->children = (x->left ? x->left->children : 0) + (x->right ? x->right->children : 0) + 1;
        if (y) {
            y->children = (y->left ? y->left->children : 0) + (y->right ? y->right->children : 0) + 1;
        }

        return y;
    }

    TreeNode* doublerotate_lr(TreeNode* v){
        TreeNode *z = v, *x = z->left, *y = x->right, *yLeft = y->left, *yRight = y->right;

        y->left = x;
        y->right = z;
        x->right = yLeft;
        z->left = yRight;

        x->height = this->max(this->height(x->left), this->height(x->right)) + 1;
        z->height = this->max(this->height(z->left), this->height(z->right)) + 1;
        y->height = this->max(this->height(y->left), this->height(y->right)) + 1;

        return y;
    }

    TreeNode* doublerotate_rl(TreeNode* v){
        TreeNode *x = v, *z = x->right, *y = z->left, *yLeft = y->left, *yRight = y->right;

        y->left = x;
        y->right = z;
        x->right = yLeft;
        z->left = yRight;

        x->height = this->max(this->height(x->left), this->height(x->right)) + 1;
        z->height = this->max(this->height(z->left), this->height(z->right)) + 1;
        y->height = this->max(this->height(y->left), this->height(y->right)) + 1;

        return y;
    }





public:

    Tree(){
        root = nullptr;
    }

    ~Tree(){
        delete root;
    }

    bool operator== (const Tree<T>& other){
        return root == other.root;
    }

    bool empty() const {
        return root == nullptr;
    }

    void inorder() const {
        showInOrder(root);
    }

    void postorder() const {
        showPostOrder(root);
    }

    void preorder() const {
        showPreOrder(root);
    }

    bool find(const T& key) const {
        return find2(root,key);
    }

    const T& min() const {
        TreeNode* min = findmin(root);
        return min->data;
    }

    const T& max() const {
        TreeNode* max = findmax(root);
        return max->data;
    }

    void insert(const T& item){
        root = insertInto(root, item);
    }

    void remove(const T& item){
        root = del(root, item);
    }

    const T& operator[](int i) const {
        if (i < 0 || i > elements()) {
            throw "out_of_bounds";
        }

        return (findByRank(root, i))->data;
    };

    int elements() const {
        return root ? root->children : 0;
    }

    int position(const T& x) const {
        return find(x) ? findRank(root, x) : -1;
    }

    const T& closestNeighbour(const T& x) const {
        int diff = INT_MAX;
        TreeNode* result = nullptr;

        closestNeighbourHelper(root, x, diff, result);

        return result->data;
    }

    int nodesBetween(const T& x, const T& y) const {
        return nodesBetweenHelper(root, x, y);
    }

    const T& median(const T& x, const T& y) const {
        int xRank = position(x), yRank = position(y), minimum = min(), maximum = max();

        if (x < minimum) {
            xRank = 1;
        }
        if (y > maximum) {
            yRank = elements();
        }
        if (xRank == -1) {
            T closest = closestNeighbour(x);
            xRank = position(closest);

            if (closest < x) {
                xRank++;
            }
        }
        if (yRank == -1) {
            T closest = closestNeighbour(y);
            yRank = position(closest);

            if (closest > y) {
                yRank--;
            }
        }

        return this->operator[](ceil((yRank - xRank) / 2) + xRank);
    }


    iterator begin(){
        return iterator(*this, 1);
    }

    iterator end(){
        return iterator(*this, root->children + 1);
    }

};



int main() {

    Tree<int> tree;

    int command, parameter1, parameter2;

    while (true) {
        cin >> command;

        if (command == 4) {
            break;
        }

        if (command == 1) {
            cin >> parameter1;
            tree.insert(parameter1);
        }

        if (command == 2) {
            cin >> parameter1;
            tree.remove(parameter1);
        }

        if (command == 3) {
            cin >> parameter1 >> parameter2;

            if (tree.empty()) {
                cout << "notfound" << endl;
                continue;
            }
            if (parameter1 == parameter2) {
                if(tree.find(parameter1)) cout << parameter1 << endl;
                else cout << "notfound" << endl;
                continue;
            } else if(parameter2 < tree.min() || parameter1 > tree.max()) {
                cout << "notfound" << endl;
                continue;
            } else if(tree.nodesBetween(parameter1,parameter2) == 0) {
                cout << "notfound" << endl;
                continue;
            }

            cout << tree.median(parameter1, parameter2) << endl;
        }

        //custom (mostly debug) commands
        if (command == 5) {
            tree.inorder();
            cout << endl;
            tree.preorder();
            cout << endl;
            cout << "sizeof(tree) = " << tree.elements() << endl;
        }

        if (command == 6) {
            cin >> parameter1;
            cout << "tree[" << parameter1 << "] = " << tree[parameter1] << endl;
        }

        if (command == 7) {
            cin >> parameter1;
            cout << "rank(" << parameter1 << ") = " << tree.position(parameter1) << endl;
        }

        if (command == 8) {
            cin >> parameter1;
            cout << "closestNeighbour = " << tree.closestNeighbour(parameter1) << endl;
        }

        if (command == 9) {
            cin >> parameter1 >> parameter2;
            cout << "nodesBetween = " << tree.nodesBetween(parameter1, parameter2) << endl;
        }

        if (command == 10) {
            for (int i : tree) {
                cout << i << " ";
            }
            cout << endl;
        }
    }


    return 0;
}
