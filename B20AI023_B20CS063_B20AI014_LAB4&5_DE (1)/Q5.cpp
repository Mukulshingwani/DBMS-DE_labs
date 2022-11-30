#include "main_helper.h"

int main()
{
    vector<whole::db_obj> collections = create_database();
    compare_insertion(collections);
    compare_1_retrieval(collections);
    compare_full_retrieval(collections);
}