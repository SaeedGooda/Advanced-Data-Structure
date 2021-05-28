#include <iostream>

using namespace std;
const int Max = 1000;

class linkedList{
    struct Node {
       int data;
       struct Node *next;
    };
public:
    Node* head = NULL;
    void insert(int new_data) {
       struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));
       new_node->data = new_data;
       new_node->next = head;
       head = new_node;
    }
};

class Node
{
private:
    Node *child[Max];
    linkedList *indexes;
public:
    Node()
    {
        indexes = new linkedList;
        for (int i = 0; i < Max; i++)
            child[i] = NULL;
    }
    void insert(string s, int index){
        indexes->insert(index);

        if (s.length() > 0)
        {
            char ch = s.at(0);

            if (child[ch] == NULL)
                child[ch] = new Node();

            child[ch]->insert(s.substr(1), index+1);
        }
    }
    linkedList* search(string s){
        if (s.length() == 0)
        return indexes;

        if (child[s.at(0)] != NULL)
            return (child[s.at(0)])->search(s.substr(1));

        else return NULL;
    }
};

class SuffixTrie
{
private:
    Node root;
public:
    SuffixTrie(string input)
    {
        for (int i = 0; i < input.length(); i++)
            root.insert(input.substr(i), i);
    }

    void Search(string s){
        linkedList *result = root.search(s);

        if (result == NULL)
            cout << "Doesn't Exist" << endl;
        else
        {
            cout << "Positions: ";
            while(result->head != NULL){
                cout << result->head->data - s.length() << " ";
                result->head = result->head->next;
            }
            cout << endl;
        }
    }
};


int main()
{
    SuffixTrie t("bananabanaba$");
    t.Search("ana"); // Prints: 1 3 7
    t.Search("naba"); // Prints: 4 8
    return 0;

}



