#include <iostream>
using namespace std;

class SuffixArray
{
    private:
        string *text;
        int length;
        int *index;
        string *suffixArr;
    public:
        SuffixArray(string text)  // Lecture example "ACGACTACGATAAC$"
        {
            this->text = new string[text.length()];
            for (int i = 0; i < text.length(); i++)
            {
                this->text[i] = text.substr(i, 1);
            }
            //                      text attribute
            //  0   1   2   3   4   5   6   7   8   9   10  11  12  13  14
            //  A   C   G   A   C   T   A   C   G   A   T   A   A   C   $

            this->length = text.length();           // length = 15
            this->index = new int[length];
            for (int i = 0; i < length; i++)
            {
                index[i] = i;
            }
            //                          index
            //  0   1   2   3   4   5   6   7   8   9   10  11  12  13  14
            suffixArr = new string[length];
        }

        void ConstructUsingPrefixDoubling()
        {
            for(int i = 0; i < length; i++)         // loop in index
            {
                string temp = "";
                for (int j = i; j < length; j++)    //  loop on text
                {
                    temp += this->text[j];
                }
                suffixArr[i] = temp;
            }
            /*
                        suffixArr
                text                  index
            ACGACTACGATAAC$             0
            CGACTACGATAAC$              1
            GACTACGATAAC$               2
            ACTACGATAAC$                3
            CTACGATAAC$                 4
            TACGATAAC$                  5
            ACGATAAC$                   6
            CGATAAC$                    7
            GATAAC$                     8
            ATAAC$                      9
            TAAC$                       10
            AAC$                        11
            AC$                         12
            C$                          13
            $                           14
            */
            for (int i = 1; i < length; i++)
            {
                int j;
                string temp = suffixArr[i];
                int tempIndex = index[i];
                cout << temp << "             " << tempIndex << endl;
                for (j = i - 1 ; j >= 0 ; j--)
                {
                    if (suffixArr[j].compare(temp) > 0)
                    {
                        suffixArr[j + 1] = suffixArr[j];
                        index[j + 1] = index[j];
                    }
                    else
                    {
                        break;
                    }
                }
                suffixArr[j + 1] = temp;
                index[j + 1 ] = tempIndex;
            }
        }
        void Print(){
            for (int i = 0; i < length; i++)
            {
                cout << index[i]<< " " ;
            }
            cout << endl;
        }
};

int main()
{
        SuffixArray t("ACGACTACGATAAC$");

    t.ConstructUsingPrefixDoubling();

    t.Print(); // Prints:  14 11 12  0  6  3  9 13  1  7  4  2  8 10  5

    return 0;

}
