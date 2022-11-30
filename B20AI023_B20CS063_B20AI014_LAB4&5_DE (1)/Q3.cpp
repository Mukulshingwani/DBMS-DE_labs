#include "main_helper.h"

int main()
{
    cout << "\n --------------------------------- Q3 Part A ---------------------------------- \n";
    cout << " global bucket_Size = 5";

    vector<whole::db_obj> collections = create_database();

    cout << "\n --------------------------------- Q3 Part B ---------------------------------- \n";
    eval_using_list(collections, 4, 5);

    cout << "\n --------------------------------- Q3 Part C ---------------------------------- \n";

    cout << "Changing global bucket size to 3 (smaller)\n";
    eval_using_list(collections, 4, 3);

    cout << "Changing global bucket size to 7 (larger)\n";

    eval_using_list(collections, 4, 7);

    cout << "\n --------------------------------- Q3 Part D ---------------------------------- \n";

    cout << " Changing local bucket size to 3 (smaller) \n";
    eval_using_list(collections, 3, 5);

    cout << "Changing local bucket size to 5 (larger) \n";
    eval_using_list(collections, 5, 5);

    cout << "\n --------------------------------- Q3 Part E ---------------------------------- \n";
    cout << "\n performing linear hashing using Map and Set datastructure \n";
    eval_using_set(collections, 4, 7);

    return 0;
}