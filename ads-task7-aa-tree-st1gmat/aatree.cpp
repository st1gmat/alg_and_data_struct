#include <iostream>
#include <fstream>

class AATree
{
private:
    struct Node
    {
        int value;
        int level;
        Node* left;
        Node* right;

        Node(int value, int level, Node* left = nullptr, Node* right = nullptr) : value(value), level(level), left(left), right(right) {}
    };

    Node* root;

    Node* skew(Node* t)
    {
        if (t == nullptr)
        {
            return nullptr;
        }
        else if (t->left == nullptr)
        {
            return t;
        }
        else if (t->left->level == t->level)
        {
            Node* newT = t->left;
            t->left = newT->right;
            newT->right = t;
            return newT;
        }
        else
        {
            return t;
        }
    }

    Node* split(Node* t)
    {
        if (t == nullptr)
        {
            return nullptr;
        }
        else if (t->right == nullptr || t->right->right == nullptr)
        {
            return t;
        }
        else if (t->level == t->right->right->level)
        {
            Node* newT = t->right;
            t->right = newT->left;
            newT->left = t;
            newT->level++;
            return newT;
        }
        else
        {
            return t;
        }
    }

    Node* insert(int x, Node* t)
    {
        if (t == nullptr)
        {
            return new Node(x, 1);
        }
        else if (x < t->value)
        {
            t->left = insert(x, t->left);
        }
        else if (x > t->value)
        {
            t->right = insert(x, t->right);
        }
        t = skew(t);
        t = split(t);
        return t;
    }

    Node* Predecessor(Node* t)
    {
        t = t->left;
        while (t->right != nullptr)
        {
            t = t->right;
        }
        return t;
    }

    Node* Successor(Node* t)
    {
        t = t->right;
        while (t->left != nullptr)
        {
            t = t->left;
        }
        return t;
    }

    Node* decreaseLevel(Node* t)
    {
        int shouldBe = (!t->left || !t->right) ? 1 : std::min(t->left->level, t->right->level) + 1;
        if (shouldBe < t->level)
        {
            t->level = shouldBe;
            if (t->right && t->right->level > t->level)
            {
                t->right->level = shouldBe;
            }
        }
        return t;
    }

    Node* erase(int x, Node* t)
    {
        if (t == nullptr)
        {
            return t;
        }
        else if (x > t->value)
        {
            t->right = erase(x, t->right);
        }
        else if (x < t->value)
        {
            t->left = erase(x, t->left);
        }
        else
        {
            if (t->left == nullptr && t->right == nullptr)
            { // leaf(t)
                delete t;
                return nullptr;
            }
            else if (t->left == nullptr)
            { // тольк прав дерево
                Node* l = t->right;
                delete t;
                return l;
            }
            else if (t->right == nullptr)
            { // тольк лев дерево
                Node* l = t->left;
                delete t;
                return l;
            }
            else
            {
                Node* l = Successor(t); // след после t элемент
                t->value = l->value;
                t->right = erase(l->value, t->right);
            }
        }
        t = decreaseLevel(t);
        t = skew(t);
        if (t->right != nullptr)
        {
            t->right = skew(t->right);
            t->right->right = skew(t->right->right);
        }
        t = split(t);
        t->right = split(t->right);
        return t;
    }

    int getLevel(Node* node) const
    {
        if (node == nullptr)
        {
            return 0;
        }
        return node->level;
    }
    void clearTree(Node* t)
    {
        if (t == nullptr)
        {
            return;
        }
        clearTree(t->left);
        clearTree(t->right);
        delete t;
    }
public:
    AATree() : root(nullptr) {

    };

    ~AATree()
    {
        clearTree(root);
    }

    

    void insert(int x)
    {
        root = insert(x, root);
    }

    void erase(int x)
    {
        root = erase(x, root);
    }

    bool find(int x) const
    {
        Node* cur = root;
        while (cur != nullptr)
        {
            if (x == cur->value)
            {
                return true;
            }
            else if (x < cur->value)
            {
                cur = cur->left;
            }
            else
            {
                cur = cur->right;
            }
        }
        return false;
    }
    int getLevel() const
    {
        return getLevel(root);
    }
};

int main(int argc, char* argv[])
{
    std::ifstream inFile(argv[1]);
    std::ofstream outFile(argv[2]);
    int n;
    inFile >> n;

    AATree l;

    for (int i = 0; i < n; i++)
    {
        char arg;
        int val;
        inFile >> arg;
        if (arg == '+')
        {
            inFile >> val;
            l.insert(val);
            outFile << l.getLevel();
        }
        else if (arg == '-')
        {
            inFile >> val;
            l.erase(val);
            outFile << l.getLevel();
        }
        else if (arg == '?')
        {
            inFile >> val;

            (l.find(val)) ? outFile << "true" : outFile << "false";
        }
        if (i == n - 1)
        {
            break;
        }
        outFile << std::endl;
    }
    inFile.close();
    outFile.close();

    return 0;
}