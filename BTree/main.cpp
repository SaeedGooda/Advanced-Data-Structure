#include <iostream>

using namespace std;

template <class T, int order>
struct Node
{
    int counter;
    T keys[order - 1];
    Node *children[order];
};

template <class T, int order>
class BTree
{

public:
    BTree();
    void Insert(const T& item);
    void Print();

private:
    Node<T, order> *root;
    void searchNode(Node<T, order> *current, const T& item, bool& found, int& location);
    void insertBTree(Node<T, order> *current, const T& item, T& median, Node<T, order>* &rightChild, bool& isTaller);
    void insertNode(Node<T, order> *current, const T& item, Node<T, order>* &rightChild, int position);
    void splitNode (Node<T, order> *current, const T& item, Node<T, order>* rightChild, int position,
                    Node<T, order>* &rightNode, T &median);
    void helpForPrint(Node<T, order> *current);
};

template <class T, int order>
BTree<T, order>::BTree()
{
    root = NULL;
}

template <class T, int order>
void BTree<T, order>::searchNode (Node<T, order> *current, const T& item, bool& found, int& location)
{
    location = 0;

    while (location < current->counter && item > current->keys[location])
        location++;

    if (location < current->counter && item == current->keys[location])
        found = true;
    else
        found = false;
}

template <class T, int order>
void BTree<T, order>::Insert(const T& item)
{
    bool isTaller = false;
    T median;

    Node<T, order> *rightChild;

    insertBTree(root, item, median, rightChild, isTaller);

    if (isTaller)
    {
        Node<T, order> *temp;
        temp = new Node<T, order>;
        temp->counter = 1;
        temp->keys[0] = median;
        temp->children[0] = root;
        temp->children[1] = rightChild;

        root = temp;
    }
}

template <class T, int order>
void BTree<T, order>::insertBTree (Node<T, order> *current, const T& item, T& median,
                                    Node<T, order>* &rightChild, bool& isTaller)
{
    int position;
    isTaller = false;

    if (current == NULL)
    {
        median = item;
        rightChild = NULL;
        isTaller = true;
    }
    else
    {
        bool found;

        searchNode(current, item, found, position);

        if (found)
            cout << "Cannot insert duplicate record." << endl;
        else
        {
            T newMedian;

            Node<T, order> *newChild;

            insertBTree(current->children[position], item,
                        newMedian, newChild, isTaller);

            if (isTaller)
            {
                if (current->counter < order - 1)
                {
                    isTaller = false;
                    insertNode(current, newMedian,
                               newChild, position);
                }
                else
                    splitNode(current, newMedian, newChild,
                              position, rightChild, median);
            }
        }
    }
}

template <class T, int order>
void BTree<T, order>::insertNode(Node<T, order> *current, const T& item,
                                Node<T, order>* &rightChild, int position)
{
    int index;

    for (index = current->counter; index > position;
                                    index--)
    {
        current->keys[index] = current->keys[index - 1];
        current->children[index + 1] = current->children[index];
    }

    current->keys[index] = item;
    current->children[index + 1] = rightChild;
    current->counter++;
}

template <class T, int order>
void BTree<T, order>::splitNode(Node<T, order> *current, const T& item, Node<T, order>* rightChild,
                                int position, Node<T, order>* &rightNode, T &median)
{
    rightNode = new Node<T, order>;

    int mid = (order - 1) / 2;

    if (position <= mid)
    {
        int index = 0;
        int i = mid;

        while (i < order - 1)
        {
            rightNode->keys[index] = current->keys[i];
            rightNode->children[index + 1] =
                                current->children[i + 1];
            index++;
            i++;
        }

        current->counter = mid;
        insertNode(current, item, rightChild,
                   position);
        (current->counter)--;

        median = current->keys[current->counter];

        rightNode->counter = index;
        rightNode->children[0] =
                  current->children[current->counter + 1];
    }
    else
    {
        int i = mid + 1;
        int index = 0;

        while (i < order - 1)
        {
            rightNode->keys[index] = current->keys[i];
            rightNode->children[index + 1] =
                                  current->children[i + 1];
            index++;
            i++;
        }

        current->counter = mid;
        rightNode->counter = index;

        median = current->keys[mid];
        insertNode(rightNode, item, rightChild,
                   position - mid - 1);
        rightNode->children[0] =
                  current->children[current->counter + 1];
    }
}

template <class T, int order>
void BTree<T, order>::Print()
{
    helpForPrint(root);
}

template <class T, int order>
void BTree<T, order>::helpForPrint
                     (Node<T, order> *current)
{
    if (current != NULL)
    {
        for(int i = 0 ; i < current->counter ; i++){
            cout << current->keys[i] << " ";
        }
        cout << endl;
        for(int i = 0 ; i < order ; i++){
            helpForPrint(current->children[i]);
        }
    }
}

int main() {
        BTree<char,5> t;

    // Look at the example in our lecture:
    t.Insert('G');
    t.Insert('I');
    t.Insert('B');
    t.Insert('J');
    t.Insert('C');
    t.Insert('A');
    t.Insert('K');
    t.Insert('E');
    t.Insert('D');
    t.Insert('S');
    t.Insert('T');
    t.Insert('R');
    t.Insert('L');
    t.Insert('F');
    t.Insert('H');
    t.Insert('M');
    t.Insert('N');
    t.Insert('P');
    t.Insert('Q');

    t.Print(); // Should output the following on the screen:



    return 0;
}
