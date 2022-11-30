#include "main_helper.h"

int main()
{

    vector<whole::db_obj> collections = create_database();

    cout << "\n --------------------------------- Q4 Part A ---------------------------------- \n";

    eval_using_linear_list(collections, 4, 5);

    cout << "\n --------------------------------- Q4 Part B ---------------------------------- \n";

    eval_using_linear_list(collections, 4, 5);

    cout << "\n --------------------------------- Q4 Part C ---------------------------------- \n";

    eval_using_linear_list(collections, 4, 3);

    eval_using_linear_list(collections, 4, 7);

    cout << "\n --------------------------------- Q4 Part D ---------------------------------- \n";

    eval_using_linear_list(collections, 3, 5);

    eval_using_linear_list(collections, 5, 5);

    cout << "\n --------------------------------- Q4 Part E ---------------------------------- \n";
    eval_using_map_and_set(collections, 4, 5);

    return 0;
}