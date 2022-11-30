#include <iostream>
using namespace std;

int hash_value(string book_id, string author_id)
{
    int n1 = book_id.size() - 1;   // 12
    int n2 = author_id.size() - 1; // 10

    int h = 0;
    for (int i = 0; i <= n1; i++)
    {
        if (book_id[i] == '_')
        {
            continue;
        }
        h += book_id[i];
    }

    for (int i = 0; i <= n2; i++)
    {
        if (author_id[i] == '_')
        {
            continue;
        }
        h += author_id[i];
    }

    return h; // 1034 min value , 1676 max value of h
}

int main()
{
    string book_id = "Aest_AC_0103";
    string author_id = "An_Ch_0103";
    int h = hash_value(book_id, author_id);
    cout << h;
    return 0;
}
