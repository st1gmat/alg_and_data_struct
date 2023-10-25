#include<iostream>
#include<cstring>
#include<fstream>


struct NodeInfo {
    bool isLeaf;
    int numberOfNode;
    int usingsCounter;
    int keyCount;
    int* keys;
    int childCount;
    int* childs_nums;
    NodeInfo()
    {
        isLeaf = false;
        numberOfNode = 0;
        usingsCounter = 0;
        keyCount = 0;
        keys = nullptr;
        childCount = 0;
        childs_nums = nullptr;
    }
};

int searchByNodeInd(const NodeInfo* nodesInfo, int size, int target) {
    int low = 0;
    int high = size - 1;
    while (low <= high)
    {
        int mid = low + (high - low) / 2;

        if (nodesInfo[mid].numberOfNode == target)
        {
            return mid;
        }

        if (nodesInfo[mid].numberOfNode < target)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }

    return -1;
}


template<typename T>
class Stack
{
private:
    T* arr;
    int size_;
    int top_;
public:

    Stack();
    ~Stack();
    void resize(int new_size);
    bool isEmpty() const;
    bool isFull() const;
    void push(T n);
    T pop();
};
template<typename T>
Stack<T>::Stack()
{
    size_ = 100;
    arr = new T[100];
    top_ = -1;
}
template<typename T>
Stack<T>::~Stack()
{
    delete[] arr;
}
template<typename T>
void Stack<T>::resize(int new_size)
{
    delete[] arr;
    arr = new T[new_size];
    size_ = new_size;
}
template<typename T>
bool Stack<T>::isEmpty() const {
    return (top_ == -1);
}
template<typename T>
bool Stack<T>::isFull() const
{
    return (top_ == size_ - 1);
}
template<typename T>
void Stack<T>::push(T n)
{
    if (isFull())
    {
        return;
    }
    top_++;
    //if (top_ == 0)
    //{
    //    arr[top_].currMin = n;
    //    arr[top_].currMax = n;
    //}
    //if (top_ > 0)
    //{
    //    arr[top_].currMin = std::min(arr[top_ - 1].currMin, n);
    //    arr[top_].currMax = std::max(arr[top_ - 1].currMax, n);
    //}
    arr[top_] = n;
}
template<typename T>
T Stack<T>::pop()
{
    if (isEmpty())
    {
        //std::cout << "pop empty error;" << std::endl;
        return 0;
    }
    T item = arr[top_];
    --top_;
    return item;
}
template<typename data>
class Queue // модификация очереди с мин и макс
{
private:
    Stack<data> inside;
    Stack<data> out;
    int size;
public:

    Queue(int size);
    bool empty();
    void enqueue(data n);
    data dequeue();
    int getSize() const;

};
template<typename data>
int Queue<data>::getSize() const
{
    return size;
}

template<typename data>
Queue<data>::Queue(int s)
{
    size = 0;
    inside.resize(s);
    out.resize(s);
}

template<typename data>
bool Queue<data>::empty()
{
    return inside.isEmpty() && out.isEmpty();
}

template<typename data>
void Queue<data>::enqueue(data n)
{
    if (inside.isFull())
    {
        std::cout << "overflow!" << std::endl;
        return;
    }
    ++size;
    inside.push(n);
}


template<typename data>
data Queue<data>::dequeue()
{
    if (out.isEmpty())
    {
        while (!inside.isEmpty())
        {
            out.push(inside.pop());
        }
        size--;
        return out.pop();
    }
    size--;
    return out.pop();
}

class BTree
{
private:
    struct BTreeNode
    {
        bool isLeaf;
        int nodeNumber;
        int keyCount;
        int* keys;
        int childrenCount;
        BTreeNode** childrens;

        BTreeNode()
        {
            isLeaf = false;
            nodeNumber = 0;
            keyCount = 0;
            keys = nullptr;
            childrenCount = 0;
            childrens = nullptr;
        }

        BTreeNode(bool leaf, int nodeNum, int numKeys, const int* arrOfkeys, int numChilds)
        {
            isLeaf = leaf;
            nodeNumber = nodeNum;
            keyCount = numKeys;
            keys = new int[numKeys];
            for (size_t i = 0; i < numKeys; i++)
            {
                keys[i] = arrOfkeys[i];
            }
            //keys = arrOfkeys;
            childrenCount = numChilds;
            if (childrenCount == 0)
            {
                childrens = nullptr;
            }
            else
            {
                childrens = new BTreeNode * [numChilds] {nullptr};
            }
        }
    };

    bool trash;
    int N;
    int t;
    int level;
    BTreeNode* root;
    /*void printTree(BTreeNode* node, int depth = 0) const
    {
        if (node == nullptr)
            return;

        for (int i = 0; i < depth; i++)
            std::cout << "  ";

        std::cout << "Node " << node->nodeNumber << " (Leaf: " << node->isLeaf << ", Keys: ";

        for (int i = 0; i < node->keyCount; i++)
            std::cout << node->keys[i] << " ";

        std::cout << ")" << std::endl;

        for (int i = 0; i < node->childrenCount; i++)
            printTree(node->childrens[i], depth + 1);
    }*/
   
    
    
    
public:
    BTree()
    {
        N = 0;
        t = 2;
        root = nullptr;
        level = 0;
        trash = true;
    }
    //void destroy(BTreeNode* startNod)
    //{
    //    if (startNode != nullptr)
    //    {
    //        /*if (startNode->isLeaf == false)
    //        {*/
    //        for (int i = 0; i < startNode->childrenCount; i++)
    //        {
    //            destroy(startNode->childrens[i]);
    //        }
    //        if (trash == false)
    //        {
    //            delete[] startNode->keys;
    //        }
    //        delete[] startNode->childrens;
    //        delete startNode;
    //        //}

    //        //delete startNode;
    //    }

    //}
    void destroy(BTreeNode* startNode)
    {
        if (startNode != nullptr)
        {
            /*if (startNode->isLeaf == false)
            {*/
            for (int i = 0; i < startNode->childrenCount; i++)
            {
                destroy(startNode->childrens[i]);
            }
            //if (trash == false)
            //{
                delete[] startNode->keys;
            //}
            delete[] startNode->childrens;
            delete startNode;
            //}

            //delete startNode;
        }

    }

    //void print() const
    //{
    //    printTree(root);
    //}
    BTree(NodeInfo* nodesInfo, int amStrN, int t, int root_num)
    {
        /*amStrN = */
        this->N = amStrN;
        this->t = t;
        this->level = 0;
        this->trash = false;
        this->root = nullptr;

        //BTreeNode* query = new BTreeNode[100];
        Queue<BTreeNode*> queue(amStrN);
        //BTreeNode** childOrderStorage = new BTreeNode*[amStrN + amStrN/2];
        /*int bottomOfStorage = -1;
        int topOfStorage = -1;
        int sizeOfStorage = 0;*/
        int rootNodeIndex = searchByNodeInd(nodesInfo, amStrN, root_num);
        //std::cout << "\n\n\nroot num: " << root_num << " ind: "<< rootNodeIndex;
        if (rootNodeIndex == -1)
        {
            trash = true;
            for (size_t i = 0; i < amStrN; i++)
            {
                delete[] nodesInfo[i].keys;
                nodesInfo[i].keys = nullptr;
                delete[] nodesInfo[i].childs_nums;
                nodesInfo[i].childs_nums = nullptr;
            }
            delete[] nodesInfo;
            return;
        }

        ++nodesInfo[rootNodeIndex].usingsCounter;
        root = new BTreeNode(nodesInfo[rootNodeIndex].isLeaf, 
                            nodesInfo[rootNodeIndex].numberOfNode, 
                            nodesInfo[rootNodeIndex].keyCount, 
                            nodesInfo[rootNodeIndex].keys, 
                            nodesInfo[rootNodeIndex].childCount);
        //print_(root);
       /* std::cout << "\n\nNode number:" << root->nodeNumber << "\n";
        std::cout << "IsLeaf:" << root->isLeaf << "\n";
        std::cout << "NumOfKeys:" << root->keyCount << "\n";
        std::cout << "Keys:";*/
        /*for (size_t idx = 0; idx < root->keyCount; idx++)
        {
            std::cout << root->keys[idx] << " ";
        }*/
        /*std::cout << "\nChildren Count: " << root->childrenCount << "\n"; */
        
        for (size_t i = 0; i < root->childrenCount; i++)
        {
            int childNodeNumber = searchByNodeInd(nodesInfo, amStrN, nodesInfo[rootNodeIndex].childs_nums[i]);
            if (childNodeNumber == -1)
            {
                trash = true;
                for (size_t i = 0; i < amStrN; i++)
                {
                    delete[] nodesInfo[i].keys;
                    nodesInfo[i].keys = nullptr;
                    delete[] nodesInfo[i].childs_nums;
                    nodesInfo[i].childs_nums = nullptr;
                }
                delete[] nodesInfo;
                return;
            }

            ++nodesInfo[childNodeNumber].usingsCounter;

            if (nodesInfo[childNodeNumber].usingsCounter > 1)
            {
                trash = true;
                for (size_t i = 0; i < amStrN; i++)
                {
                    delete[] nodesInfo[i].keys;
                    nodesInfo[i].keys = nullptr;
                    delete[] nodesInfo[i].childs_nums;
                    nodesInfo[i].childs_nums = nullptr;
                }
                delete[] nodesInfo;
                return;
            }

            root->childrens[i] = new BTreeNode(nodesInfo[childNodeNumber].isLeaf,
                                        nodesInfo[childNodeNumber].numberOfNode,
                                        nodesInfo[childNodeNumber].keyCount,
                                        nodesInfo[childNodeNumber].keys,
                                        nodesInfo[childNodeNumber].childCount);


            queue.enqueue(root->childrens[i]);
            /*(bottomOfStorage == -1) ? ++bottomOfStorage : bottomOfStorage;
            childOrderStorage[++topOfStorage] = root->childrens[i];
            ++sizeOfStorage;*/
        }
        //while(bottomOfStorage != topOfStorage)
        while (!queue.empty())
        {
            int qSize = queue.getSize();
            for (size_t i = 0; i < qSize/*sizeOfStorage*/; i++)
            {
                BTreeNode* node = queue.dequeue()/*childOrderStorage[bottomOfStorage++]*/;
                //int toFind = node->nodeNumber;
                int currNodeIndex = searchByNodeInd(nodesInfo, amStrN, node->nodeNumber /*nodesInfo[rootNodeIndex].numberOfNode*/);
                if (currNodeIndex == -1)
                {
                    trash = true;
                    for (size_t i = 0; i < amStrN; i++)
                    {
                        delete[] nodesInfo[i].keys;
                        nodesInfo[i].keys = nullptr;
                        delete[] nodesInfo[i].childs_nums;
                        nodesInfo[i].childs_nums = nullptr;
                    }
                    delete[] nodesInfo;
                    //delete[] childOrderStorage;

                    return;
                }
                for (size_t j = 0; j < nodesInfo[currNodeIndex].childCount; j++)
                {
                    /*if (nodesInfo[currNodeIndex].isLeaf == true)
                    {
                        break;
                    }*/
                    int childNodeIndex = searchByNodeInd(nodesInfo, amStrN, nodesInfo[currNodeIndex].childs_nums[j]);
                    if (childNodeIndex == -1)
                    {
                        trash = true;
                        for (size_t i = 0; i < amStrN; i++)
                        {
                            delete[] nodesInfo[i].keys;
                            nodesInfo[i].keys = nullptr;
                            delete[] nodesInfo[i].childs_nums;
                            nodesInfo[i].childs_nums = nullptr;
                        }
                        delete[] nodesInfo;
                        //delete[] childOrderStorage;

                        return;
                    }
                    /*10 3 9
                        leaf: 0x1 (2: 1 2)                      0 id
                        leaf: 0x2 (3: 4 5 6)                    1 id
                        leaf: 0x3 (2: 8 9)                      3 id
                        leaf: 0x4 (2: 11 12)                    4 id
                        leaf: 0x5 (2: 14 15)                    5 id
                        leaf: 0x6 (3: 17 18 19)                 6 id
                        leaf: 0x7 (4: 21 22 23 24)              7 id
                        branch: 0x8 (3: 3 7 10) (4: 1 2 3 4)    8 id
                        branch: 0x9 (1: 13) (2: 8 10)           9 id
                        branch: 0x10 (2: 16 20) (3: 5 6 7)      10 id
*/
                    ++nodesInfo[childNodeIndex].usingsCounter; // почему увеличивается когда не надо, исправить //upd: уже норм
                    if (nodesInfo[childNodeIndex].usingsCounter > 1)
                    {
                        trash = true;
                        //print_(root);
                        for (size_t i = 0; i < amStrN; i++)
                        {
                            delete[] nodesInfo[i].keys;
                            nodesInfo[i].keys = nullptr;
                            delete[] nodesInfo[i].childs_nums;
                            nodesInfo[i].childs_nums = nullptr;
                        }
                        delete[] nodesInfo;
                        //delete[] childOrderStorage;
                        return;
                    }

                    if (node->childrens != nullptr)
                    {
                        node->childrens[j] = new BTreeNode(nodesInfo[childNodeIndex].isLeaf,
                                                            nodesInfo[childNodeIndex].numberOfNode,
                                                            nodesInfo[childNodeIndex].keyCount,
                                                            nodesInfo[childNodeIndex].keys,
                                                            nodesInfo[childNodeIndex].childCount);
                        //node->childrens[j]->
                            /*for (size_t idx = 0; idx < node->childrens[j]->keyCount; idx++)
                            {
                                std::cout << node->childrens[j]->keys[idx] << " ";
                            }*/
                        queue.enqueue(node->childrens[j]);
                        //sizeOfStorage++;
                        //childOrderStorage[++topOfStorage] = node->childrens[j];
                    }

                }

            }
            ++level;
        }
        //print_(root);

        for (size_t i = 0; i < amStrN; i++)
        {
            //delete[] nodesInfo[i].keys;
            delete[] nodesInfo[i].childs_nums;
        }
        delete[] nodesInfo;

        //print();
        
        //delete[] childOrderStorage;
        //std::cout << "Success!\n************8";
        
    }
    ~BTree()
    {
        destroy(root);
    }

    bool search(int key) const
    {
        BTreeNode* currentNode = root;
        while (currentNode != nullptr) 
        {
            BTreeNode* next_node = nullptr;
            int i = 0;
            int j = 0;
            bool checked = false;
            for (; j < currentNode->childrenCount; ++j)
            {
                if (key == currentNode->keys[i]) 
                {
                    return true;
                }
                    if (i == 0 && !checked) 
                    {
                        if (key < currentNode->keys[i]) 
                        {
                            next_node = currentNode->childrens[0];
                            break;
                        }
                        checked = true;
                    }
                    else if (i == currentNode->keyCount - 1 && j == currentNode->childrenCount - 1) 
                    {
                        next_node = currentNode->childrens[j];
                    }
                    else 
                    {
                        if (key > currentNode->keys[i - 1] && key < currentNode->keys[i]) 
                        {
                            next_node = currentNode->childrens[j];
                            break;
                        }
                    }

                if (i != currentNode->keyCount - 1) 
                {
                    ++i;
                }
            }

            if (currentNode->isLeaf)
            {
                for (int i = 0; i < currentNode->keyCount; ++i) 
                {
                    if (currentNode->keys[i] == key) 
                    {
                        return true;
                    }
                }
            }

            currentNode = next_node;
        }

        return false;
    }

    bool isValid() const
    {
        if (trash)
        {
            return false;
        }
    
        if (root != nullptr)
        {
            bool numOfKeysValidCheck = root->keyCount >= 1 && root->keyCount <= 2 * t - 1;
            bool numOfchildValidCheck = !root->isLeaf && (root->childrenCount == root->keyCount + 1);
            //bool mainCheck = !(numOfKeysValidCheck && (numOfchildValidCheck || root->isLeaf));
            if (!(numOfKeysValidCheck && (numOfchildValidCheck || root->isLeaf)))
            {
                //trash = false;
                return false;
            }

            int prev;
            if (root->keyCount > 0)
            {
                prev = root->keys[0];
                for (size_t i = 0; i < root->keyCount; i++) // проверка на правильный порядок ключей(по возрастанию)
                {
                    if (root->keys[i] < prev)
                    {
                        return false;
                    }
                    prev = root->keys[i];
                }
            }

            
            //int currBranchKey = 0;
            bool checkVal = false;
            /*for (size_t i = 0; i < root->childrenCount; i++)
            {
                for (size_t j = 0; j < root->childrens[i]->keyCount; j++)
                {
                    std::cout << root->childrens[i]->keys[j] << " ";

                }
                std::cout << "\n";

            }*/
            
            for (size_t currBranchKey = 0, childIdx = 0; childIdx < root->childrenCount; childIdx++)
            {
                for (size_t extKeysIdx = 0; extKeysIdx < root->childrens[childIdx]->keyCount; extKeysIdx++) // обход по внешним ключам и проверка, не превосходят ли они родителя
                {
                    if (currBranchKey == 0 && !checkVal)
                    {
                        if (root->childrens[childIdx]->keys[extKeysIdx] >= root->keys[currBranchKey]) // слева от ключа родителя
                        {
                            return false;
                        }
                        //if(root->childrenCount)
                    }
                    else if ((currBranchKey == root->keyCount - 1) && (childIdx == root->childrenCount - 1)) // справа крайний от ключа родителя 
                    {
                        if (root->childrens[childIdx]->keys[extKeysIdx] <= root->keys[currBranchKey])
                        {
                            return false;
                        }
                    }
                    else // проходка между(серединная) учитывая что ключи потомков должны быть между двумя ключами curridx - 1 и curridx
                    {
                        if (root->childrens[childIdx]->keys[extKeysIdx] <= root->keys[currBranchKey - 1]
                            || root->childrens[childIdx]->keys[extKeysIdx] >= root->keys[currBranchKey])
                        {
                            return false;
                        }
                    }
                }
                checkVal = true;
                if (currBranchKey != root->keyCount - 1)
                {
                    currBranchKey++;
                }
            }
                //childIdx++;
            Queue<BTreeNode*> queue(N + 1);

            for (size_t i = 0; i < root->childrenCount; i++)
            {
                queue.enqueue(root->childrens[i]);
            }
            while (!queue.empty())
            {
                bool oneLevelCheck = false;
                int qSize = queue.getSize();
                for (size_t i = 0; i < qSize; i++)
                {
                    BTreeNode* currChildNode = queue.dequeue(); /********************/

                    if (i == 0)
                    {
                        oneLevelCheck = currChildNode->isLeaf;
                    }
                    /*bool numKeysValidCheck = (currChildNode->keyCount >= t - 1) && (currChildNode->keyCount <= 2 * t - 1);
                    bool branchNumKeysCheck = (currChildNode->isLeaf == false) && (currChildNode->childrenCount == currChildNode->keyCount + 1);*/
                    /*if ((numKeysValidCheck && (currChildNode->isLeaf || branchNumKeysCheck)
                        && currChildNode->isLeaf == oneLevelCheck) == false)*/
                    /*std::cout << "\n\n";

                    for (size_t i = 0; i < currChildNode->keyCount; i++)
                    {
                        std::cout << currChildNode->keys[i] << " ";
                    }
                    std::cout << "\n\n";*/

                    if (!(currChildNode->keyCount >= t - 1 && currChildNode->keyCount <= 2 * t - 1
                        && ((!currChildNode->isLeaf && currChildNode->childrenCount == currChildNode->keyCount + 1) || currChildNode->isLeaf)
                        && currChildNode->isLeaf == oneLevelCheck)){
                        
                        return false;
                    }

                    int tmp;
                    if (currChildNode->keyCount > 0)
                    {
                        tmp = currChildNode->keys[0];
                        for (size_t i = 0; i < currChildNode->keyCount; i++) // проверка на правильный порядок ключей(по возрастанию)
                        {
                            if (currChildNode->keys[i] < tmp) // провести тест f_n_f - ошибка чтения
                            {
                                return false;
                            }
                            if (!search(currChildNode->keys[i]))
                            {
                                return false;
                            }
                            tmp = currChildNode->keys[i];
                        }
                    }




                    //int currBranchKey = 0;
                    bool checkVal = false;
                    /*for (size_t i = 0; i < root->childrenCount; i++)
                    {
                        for (size_t j = 0; j < root->childrens[i]->keyCount; j++)
                        {
                            std::cout << root->childrens[i]->keys[j] << " ";

                        }
                        std::cout << "\n";

                    }*/

                    for (size_t currBranchKey = 0, childIdx = 0; childIdx < currChildNode->childrenCount; childIdx++)
                    {
                        for (size_t extKeysIdx = 0; extKeysIdx < currChildNode->childrens[childIdx]->keyCount; ++extKeysIdx) // ошибка на дампе 24 и 10// обход по внешним ключам и проверка, не превосходят ли они родителя
                        {
                            if (currBranchKey == 0 && !checkVal)
                            {
                                if (currChildNode->childrens[childIdx]->keys[extKeysIdx] >= currChildNode->keys[currBranchKey]) // слева от ключа родителя
                                {
                                    return false;
                                }
                                //if(root->childrenCount)
                            }
                            else if ((currBranchKey == currChildNode->keyCount - 1) && (childIdx == currChildNode->childrenCount - 1)) // справа крайний от ключа родителя 
                            {
                                if (currChildNode->childrens[childIdx]->keys[extKeysIdx] <= currChildNode->keys[currBranchKey])
                                {
                                    return false;
                                }
                            }
                            else // проходка между(серединная) учитывая что ключи потомков должны быть между двумя ключами curridx - 1 и curridx
                            {
                                if (currChildNode->childrens[childIdx]->keys[extKeysIdx] <= currChildNode->keys[currBranchKey - 1]
                                    || currChildNode->childrens[childIdx]->keys[extKeysIdx] >= currChildNode->keys[currBranchKey])
                                {
                                    return false;
                                }
                            }
                        }
                        checkVal = true;
                        if (currBranchKey != currChildNode->keyCount - 1)
                        {
                            currBranchKey++;
                        }
                    }
                    for (size_t i = 0; i < currChildNode->childrenCount; i++)
                    {
                        queue.enqueue(currChildNode->childrens[i]);
                    }
                }
            }
        }
        return true;
    }




    
    

};


void printNode(const NodeInfo& node) {
    std::cout << "Is Leaf: " << (node.isLeaf ? "true" : "false") << std::endl;
    std::cout << "Index of node: " << node.numberOfNode << std::endl;
    std::cout << "Number of keys: " << node.keyCount << std::endl;
    std::cout << "Keys: ";
    for (int i = 0; i < node.keyCount; i++) {
        std::cout << node.keys[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "Number of childrens: " << node.childCount << std::endl;
    std::cout << "Index of child node: ";
    for (int i = 0; i < node.childCount; i++) {
        std::cout << node.childs_nums[i] << " ";
    }
    std::cout << std::endl;
}



int partition(NodeInfo* nodesInfo, int low, int high) {
    int pivot = nodesInfo[high].numberOfNode;
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        if (nodesInfo[j].numberOfNode < pivot) {
            i++;
            std::swap(nodesInfo[i], nodesInfo[j]);
        }
    }

    std::swap(nodesInfo[i + 1], nodesInfo[high]);
    return (i + 1);
}

void quickSort(NodeInfo* nodesInfo, int low, int high) {
    if (low < high) {
        int pivot = partition(nodesInfo, low, high);
        quickSort(nodesInfo, low, pivot - 1);
        quickSort(nodesInfo, pivot + 1, high);
    }
}



int parseNum(char*& str, char delimiter) {
    int num = 0;
    int sign = 1;

    while (*str != 0 && *str == ' ')
    {
        str++;
    }

    if (*str == '-') 
    {
        sign = -1;
        str++;
    }

    while (*str != 0 && *str != delimiter) 
    {
        if (*str >= '0' && *str <= '9') 
        {
            num = num * 10 + (*str - '0');
            str++;
        }
        else 
        {
            break;
        }
    }

    return num * sign;
}

NodeInfo* fillBtreeInfo(const char* filename, int& nodeCount, int& t, int& root) {
    std::ifstream file(filename);
    file >> nodeCount >> t >> root;
    file.ignore();
    char line[2048];
    NodeInfo* nodesInfo = new NodeInfo[nodeCount];
    for (size_t i = 0; i < nodeCount; i++)
    {
        file.getline(line, sizeof(line));
        //std::cout << line << "\n";
        //std::cout << line;
        char* pos = line;
        if (strncmp(pos, "leaf", 4) == 0) {
            nodesInfo[i].isLeaf = true;
            pos += 8;
            //std::cout << pos<<'\n';
            //std::cout<<parseNum(pos, ' ');
            nodesInfo[i].numberOfNode = parseNum(pos, ' ');
            pos += 2;
            nodesInfo[i].keyCount = parseNum(pos, ':');
            nodesInfo[i].keys = new int[nodesInfo[i].keyCount];
            pos += 2;
            for (size_t extKeysIdx = 0; extKeysIdx < nodesInfo[i].keyCount; extKeysIdx++)
            {
                if (extKeysIdx == nodesInfo[i].keyCount - 1)
                {
                    nodesInfo[i].keys[extKeysIdx] = parseNum(pos, ')');
                    //std::cout << pos << '\n';

                }
                else
                {
                    nodesInfo[i].keys[extKeysIdx] = parseNum(pos, ' ');
                    //std::cout << pos << '\n';

                }
                //std::cout << nodesInfo[i].keys[extKeysIdx] << " ";
            }
            
        }
        else {
            nodesInfo[i].isLeaf = false;
            pos += 10;
            //std::cout << pos<<'\n';
            //std::cout<<parseNum(pos, ' ');
            nodesInfo[i].numberOfNode = parseNum(pos, ' ');
            pos += 2;
            nodesInfo[i].keyCount = parseNum(pos, ':');
            nodesInfo[i].keys = new int[nodesInfo[i].keyCount];
            pos += 2;
            for (size_t extKeysIdx = 0; extKeysIdx < nodesInfo[i].keyCount; extKeysIdx++)
            {
                if (extKeysIdx == nodesInfo[i].keyCount - 1)
                {
                    nodesInfo[i].keys[extKeysIdx] = parseNum(pos, ')');
                    //std::cout << pos << '\n';

                }
                else
                {
                    nodesInfo[i].keys[extKeysIdx] = parseNum(pos, ' ');
                    //std::cout << pos << '\n';
                    
                }
                //std::cout << nodesInfo[i].keys[extKeysIdx] << " ";
            }
            //std::cout << '\n';
            pos += 3;
            nodesInfo[i].childCount = parseNum(pos, ':');
            nodesInfo[i].childs_nums = new int[nodesInfo[i].childCount];
            pos += 2;
            for (size_t extKeysIdx = 0; extKeysIdx < nodesInfo[i].childCount; extKeysIdx++)
            {
                if (extKeysIdx == nodesInfo[i].childCount - 1)
                {
                    nodesInfo[i].childs_nums[extKeysIdx] = parseNum(pos, ')');
                    //std::cout << pos << '\n';

                }
                else
                {
                    nodesInfo[i].childs_nums[extKeysIdx] = parseNum(pos, ' ');
                    //std::cout << pos << '\n';
                }
                //std::cout << nodesInfo[i].childs_nums[extKeysIdx] << " ";
            }
            //std::cout << pos << '\n';

            //break;

        }
    }
    /*for (size_t i = 0; i < nodeCount; i++)
    {
        printNode(nodesInfo[i]);
        std::cout << '\n';
    }*/
    
    file.close();

    return nodesInfo;
}


int main(int argc, char* argv[])
{
    const char* filename = argv[1];
    //const char* filename = "dump24.txt";

    int N;
    int root;
    int t;
    NodeInfo* nodesInfo = fillBtreeInfo(filename, N, t, root);

    quickSort(nodesInfo, 0, N - 1);

    BTree tree(nodesInfo, N, t, root);
    //std::cout << "\n";

    std::cout << (tree.isValid() ? "yes" : "no");
    //tree.destroy();
    //std::cout << "fhdskjhfdksfhkdshf";
    /*for (size_t i = 0; i < N; i++)
    {
        delete[] nodesInfo[i].childs_nums;
    }*/


    return 0;

}

/********************************рабочий парсер но гитхаб не принял*****/
//NodeInfo* fillBtreeInfo(const char* filename, int& nodeCount, int& t, int& root) {
//    std::ifstream file(filename);
//
//    char line[256];
//    file.getline(line, sizeof(line));
//    char* context = nullptr;
//    char* token = strtok_s(line, " ", &context);
//    nodeCount = parseInt(token);  
//    token = strtok_s(nullptr, " ", &context);
//    t = parseInt(token); 
//    token = strtok_s(nullptr, " ", &context);
//    root = parseInt(token); 
//
//    NodeInfo* nodesInfo = new NodeInfo[nodeCount]; 
//
//    for (int i = 0; i < nodeCount; i++) {
//        file.getline(line, sizeof(line));
//        token = strtok_s(line, " ", &context);
//
//        if (strcmp(token, "branch:") == 0) {
//            nodesInfo[i].isLeaf = false;
//            nodesInfo[i].usingsCounter = 0;
//            token = strtok_s(nullptr, " ", &context);
//            int nodeNumber = parseInt(token);  
//            nodesInfo[i].numberOfNode = nodeNumber;
//            token = strtok_s(nullptr, "(:", &context);
//            int keyCount = parseInt(token);  
//            nodesInfo[i].keyCount = keyCount;
//            nodesInfo[i].keys = new int[keyCount];
//            for (int j = 0; j < keyCount; j++) {
//                token = strtok_s(nullptr, " )", &context);
//
//                nodesInfo[i].keys[j] = parseInt(token);
//            }
//
//            token = strtok_s(nullptr, " (:", &context);
//            int childCount = parseInt(token); // Number of children
//            nodesInfo[i].childCount = childCount;
//            nodesInfo[i].childs_nums = new int[childCount];
//
//            for (int j = 0; j < childCount; j++) {
//                token = strtok_s(nullptr, " )", &context);
//                nodesInfo[i].childs_nums[j] = parseInt(token);
//            }
//
//            //nodesInfo[nodeNumber] = branchNode;
//        }
//        else if (strcmp(token, "leaf:") == 0) {
//            // Process leaf node line
//            nodesInfo[i].isLeaf = true;
//            nodesInfo[i].childCount = 0;
//            nodesInfo[i].childs_nums = nullptr;
//
//
//            token = strtok_s(nullptr, " ", &context);
//            int nodeNumber = parseInt(token);
//            nodesInfo[i].numberOfNode = nodeNumber;
//
//
//            token = strtok_s(nullptr, "(:", &context);
//            int keyCount = parseInt(token);  // Number of keys
//            nodesInfo[i].keyCount = keyCount;
//            nodesInfo[i].keys = new int[keyCount];
//
//
//
//            for (int j = 0; j < keyCount; j++) {
//                token = strtok_s(nullptr, " )", &context);
//                nodesInfo[i].keys[j] = parseInt(token);
//            }
//
//
//        }
//
//    }
//    /*for (size_t i = 0; i < nodeCount; i++)
//    {
//        printNode(nodesInfo[i]);
//        std::cout << '\n';
//    }*/
//    file.close();
//
//    return nodesInfo;
//
//
//
//    //delete[] nodesInfo;
//
//    //file.close();
//}
