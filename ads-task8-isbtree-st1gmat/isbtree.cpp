#include <fstream>

class BTree {
 private:
  struct Node {
    bool leaf; // является ли узел листом
    int n; // количчество ключей
    Node* child; // дин массив указателей
    int* keys; // дин массив ключей
    Node(bool leaf):n(0), leaf(leaf)
    {
    }
  };

  int t;  // MIN DEGREE
  Node* root;

 public:
};

int main(int argc, char* argv[]) { return 0; }
