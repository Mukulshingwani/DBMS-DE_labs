#include <bits/stdc++.h>
#include <algorithm>
#include <chrono>
#include <cmath>
using namespace std::chrono;
using namespace std;

class whole
{
public:
    typedef struct database
    {
        string book_id;
        string author_id;
        string book;
        string author_name;

        bool operator<(const database &t) const
        {
            return (this->book_id < t.book_id);
        }

        database(string book_id, string author_id, string author_name, string book)
        {
            this->book_id = book_id;
            this->author_id = author_id;
            this->author_name = author_name;
            this->book = book;
        }
    } db_obj;
};

vector<whole::db_obj> create_database()
{
    vector<whole::db_obj> collections;
    collections.emplace_back(whole::db_obj("An_Ch_0103", "Aest_AC_0103", "Anjan Chatterjee", "The Aesthetic Brain"));
    collections.emplace_back(whole::db_obj("An_Da_0104", "Self_AD_0104", "Antonio Damasio", "Self Comes to Mind"));
    collections.emplace_back(whole::db_obj("Ca_Sa_0319", "Anim_CS_0319", "Carl Safina", "What Animals Think"));
    collections.emplace_back(whole::db_obj("Jo_Ro_1018", "Deat_JR_1018", "Joanne K. Rowling", "Deathly Hallows_Harry Potter"));
    collections.emplace_back(whole::db_obj("Jo_Ro_1018", "Fant_JR_1018", "Joanne K. Rowling", "Fantastic Beasts and Where to  Find Them"));
    collections.emplace_back(whole::db_obj("Jo_Ro_1018", "Gobl_JR_1018", "Joanne K. Rowling", "Goblet of Fire_Harry Potter"));
    collections.emplace_back(whole::db_obj("Jo_Ro_1018", "Phil_JR_1018", "Joanne K. Rowling", "Philosopher's Stone_Harry Potter"));
    collections.emplace_back(whole::db_obj("Jo_Ro_1018", "Pris_JR_1018", "Joanne K. Rowling", "Prisoner of Azkaban_Harry Potter"));
    collections.emplace_back(whole::db_obj("La_Ch_1203", "Mind_LC_1203", "Lars Chittka", "The Mind of a Bee"));
    collections.emplace_back(whole::db_obj("Ma_Mi_1313", "Emot_MM_1313", "Marvin Minsky", "Emotion Machine"));
    collections.emplace_back(whole::db_obj("Ma_Mi_1313", "Soci_MM_1313", "Marvin Minsky", "Society of Mind"));
    collections.emplace_back(whole::db_obj("Pe_Wo_1623", "Aunt_PW_1623", "Pelham G. Wodehouse", "Aunts Aren't Gentlemen"));
    collections.emplace_back(whole::db_obj("Pe_Wo_1623", "Wode_PW_1623", "Pelham G. Wodehouse", "Wodehouse at the Wicket"));
    collections.emplace_back(whole::db_obj("Vi_Ra_2218", "Emer_VR_2218", "Vilayanur Ramachandran", "The Emerging Mind"));
    collections.emplace_back(whole::db_obj("Vi_Ra_2218", "Phan_VR_2218", "Vilayanur Ramachandran", "Phantoms in the Brain"));
    return collections;
}

int hash_value(whole::db_obj &l)
{
    int hash = 0;

    int i = 0;
    for (i = 0; i < l.book_id.length(); i++)
    {
        if (l.book_id[i] == '_')
            continue;
        else
            hash = hash + l.book_id[i];
    }
    i = 0;
    for (int i = 0; i < l.author_id.length(); i++)
    {
        if (l.author_id[i] == '_')
            continue;
        else
            hash = hash + l.author_id[i];
    }
    return hash;
}

bool LSB(int num, int K)
{
    return (num & (1 << (K - 1)));
}

int number_of_binary_digits(int num)
{
    int count = 0;
    while (num)
    {
        count++;
        num >>= 1;
    }
    return count;
}

// For Q4   
int hash_function(int starting_k_bits, int ascii)
{
    int k = 0;
    int hash = 0;
    int total_bits = number_of_binary_digits(ascii);

    int temp = total_bits - starting_k_bits;
    while (k < temp)
    {
        ascii = ascii >> 1;
        k++;
    }

    while (k < total_bits)
    {
        hash = hash << 1;
        hash = hash | LSB(ascii, 1);
        ascii = ascii >> 1;
        k++;
    }

    return hash;
}
// defining the hash function
int hash_function(string key, int size_of_global_bucket)
{
    int hash = 0;
    for (int i = 0; i < key.size(); i++)
    {
        // ignoring the underscore since same ascii value
        if (key[i] == '_')
            continue;
        else
            hash += key[i];
    }
    return hash % size_of_global_bucket;
}

void view_hashed_table(map<int, vector<whole::db_obj>> hash_table)
{
    for (auto it = hash_table.begin(); it != hash_table.end(); it++)
    {
        cout << it->first << " -> ";
        cout << (it->second).size() << '\n';
    }
    cout << "\n";
    for (auto it = hash_table.begin(); it != hash_table.end(); it++)
    {
        cout << it->first << " -> ";
        int i = 0;
        while (i < it->second.size())
        {
            cout << it->second[i].book_id << " " << it->second[i].author_id << " " << it->second[i].author_name << " " << it->second[i].book << " <> ";
            i++;
        }
        cout << endl;
    }
}
map<int, set<whole::db_obj>> linear_hashing_using_set(vector<whole::db_obj> &collections, int size_of_global_bucket, int size_of_local_bucket)
{
    map<int, set<whole::db_obj>> hash_table;

    // initialise the hash table
    int i = 0;
    while (i < size_of_global_bucket)
    {
        hash_table[i] = set<whole::db_obj>();
        i++;
    }
    i = 0;
    while (i < collections.size())
    {
        string key1 = collections[i].book_id;
        string key2 = collections[i].author_id;
        string key = key1 + key2;
        int hash = hash_function(key, size_of_global_bucket);
        hash_table[hash].insert(collections[i]);
        if (hash_table[hash].size() > size_of_local_bucket)
        {
            return linear_hashing_using_set(collections, 2 * size_of_global_bucket, size_of_local_bucket);
        }
        i++;
    }
    return hash_table;
}

map<int, vector<whole::db_obj>> linear_hashing(vector<whole::db_obj> &collections, int size_of_global_bucket, int size_of_local_bucket)
{
    map<int, vector<whole::db_obj>> hash_table;

    // initialise the hash table
    int i = 0;
    for (i = 0; i < size_of_global_bucket; i++)
    {
        hash_table[i] = vector<whole::db_obj>();
    }
    i = 0;
    for (i = 0; i < collections.size(); i++)
    {
        string key1 = collections[i].book_id;
        string key2 = collections[i].author_id;
        string key = key1 + key2;
        int hash = hash_function(key, size_of_global_bucket);
        hash_table[hash].emplace_back(collections[i]);
        if (hash_table[hash].size() > size_of_local_bucket)
        {
            return linear_hashing(collections, size_of_global_bucket * 2, size_of_local_bucket);
        }
    }
    return hash_table;
}

void view_hashed_table_set(map<int, set<whole::db_obj>> hash_table)
{
    auto it = hash_table.begin();
    while (it != hash_table.end())
    {
        cout << it->first << " -> ";
        cout << (it->second).size() << '\n';
        it++;
    }
    cout << "\n";
    it = hash_table.begin();
    while (it != hash_table.end())
    {
        cout << it->first << " -> ";
        // cout<<(it->second).size()<<'\n';
        for (auto it2 = it->second.begin(); it2 != it->second.end(); it2++)
        {
            cout << it2->book_id << " " << it2->author_id << " " << it2->author_name << " " << it2->book << " | ";
        }
        cout << endl;
        it++;
    }
}

// For Q3
void eval_using_set(vector<whole::db_obj> &collections, int size_of_local_bucket, int size_of_global_bucket)
{
    auto begin = high_resolution_clock::now();
    map<int, set<whole::db_obj>> hash_table = linear_hashing_using_set(collections, size_of_global_bucket, size_of_local_bucket);
    auto end = high_resolution_clock::now();
    view_hashed_table_set(hash_table);
    auto duration = duration_cast<microseconds>(end - begin);
    cout << "\n Time of linear hashing using set: " << duration.count() << " microseconds \n\n";
}

// For Q3
void eval_using_list(vector<whole::db_obj> &collections, int size_of_local_bucket, int size_of_global_bucket)
{
    auto begin = high_resolution_clock::now();
    map<int, vector<whole::db_obj>> hash_table = linear_hashing(collections, size_of_global_bucket, size_of_local_bucket);
    auto end = high_resolution_clock::now();
    view_hashed_table(hash_table);

    auto duration = duration_cast<microseconds>(end - begin);
    cout << "\n Time of linear hashing using linear list: " << duration.count() << " microseconds \n\n";
}

map<int, set<whole::db_obj>> distributed_hashing_using_map_and_set(int starting_k_bits, int local_bucket_size, vector<whole::db_obj> &collections)
{
    int hash = 0;
    int i = 0;
    map<int, set<whole::db_obj>> hash_table;
    while (i < collections.size())
    {
        hash = hash_function(starting_k_bits, hash_value(collections[i]));
        hash_table[hash].insert(collections[i]);
        if (hash_table[hash].size() > local_bucket_size)
        {
            cout << "Bucket Oveflow !!! " << hash << endl;
            return hash_table;
        }
        i++;
    }
    return hash_table;
}

map<int, vector<whole::db_obj>> distributed_hasing_using_linear_list(int starting_k_bits, int local_bucket_size, vector<whole::db_obj> &collections)
{
    int hash = 0;
    int i = 0;
    map<int, vector<whole::db_obj>> hash_table;
    while (i < collections.size())
    {
        hash = hash_function(starting_k_bits, hash_value(collections[i]));
        hash_table[hash].emplace_back(collections[i]);
        if (hash_table[hash].size() > local_bucket_size)
        {
            cout << "Bucket Oveflow !!! " << hash << endl;
            return hash_table;
        }
        i++;
    }
    return hash_table;
}

void get_hashe_table(map<int, vector<whole::db_obj>> hash_table)
{
    auto it = hash_table.begin();
    while (it != hash_table.end())
    {
        cout << it->first << " -> ";
        cout << (it->second).size() << endl;
        it++;
    }
    cout << "\n";
    it = hash_table.begin();
    while (it != hash_table.end())
    {
        cout << it->first << " -> ";
        int i = 0;
        while (i < it->second.size())
        {
            cout << it->second[i].book_id << " " << it->second[i].author_id << " " << it->second[i].author_name << " " << it->second[i].book << " <> ";
            i++;
        }
        it++;
        cout << endl;
    }
}

// for Q4
void eval_using_linear_list(vector<whole::db_obj> &collections, int local_bucket_size, int global_bucket_size)
{
    cout << "local bucket size : " << local_bucket_size << "\n";
    cout << "global bucket size : " << global_bucket_size << "\n";
    auto start = high_resolution_clock::now();
    map<int, vector<whole::db_obj>> hash_table = distributed_hasing_using_linear_list(global_bucket_size, local_bucket_size, collections);
    auto stop = high_resolution_clock::now();
    get_hashe_table(hash_table);
    auto duration = duration_cast<microseconds>(stop - start);

    cout << "\n Time taken by distributed hashing using linear list (vector): " << duration.count() << " microseconds" << endl;
}

// For Q4
void eval_using_map_and_set(vector<whole::db_obj> &collections, int local_bucket_size, int global_bucket_size)
{
    cout << "local bucket size : " << local_bucket_size << "\n";
    cout << "global bucket size : " << global_bucket_size << "\n";
    auto start = high_resolution_clock::now();
    map<int, set<whole::db_obj>> hash_table = distributed_hashing_using_map_and_set(global_bucket_size, local_bucket_size, collections);
    auto stop = high_resolution_clock::now();
    view_hashed_table_set(hash_table);
    auto duration = duration_cast<microseconds>(stop - start);

    cout << "\n Time taken by distributed hashing using set(red black trees): " << duration.count() << " microseconds" << endl;
}

vector<int> hashfunc(vector<string> Author_ID, vector<string> Book_ID)
{
    vector<int> out;
    int n = Author_ID.size();
    int val = 0;
    for (int i = 0; i < n; i++)
    {
        val = 0;
        for (int j = 0; j < (Author_ID[i]).length(); j++)
        {
            if (Author_ID[i][j] == '_')
            {
                continue;
            }
            else
                val += int(Author_ID[i][j]);
        }
        for (int j = 0; j < (Book_ID[i]).length(); j++)
        {
            if (Book_ID[i][j] == '_')
            {
                continue;
            }
            else
                val += int(Book_ID[i][j]);
        }
        out.push_back(val);
    }
    return out;
}

int hashVal(string str)
{
    int val = 0;
    for (int i = 0; i < str.size(); i++)
    {

        if (str[i] == '_')
        {
            continue;
        }
        else
            val += int(str[i]);
    }
    return val;
}

int decimalToBinary(int N)
{
    // To store the binary number
    unsigned long long B_Number = 0;
    int cnt = 0;
    while (N != 0)
    {
        int rem = N % 2;
        unsigned long long c = pow(10, cnt);
        B_Number += rem * c;
        N /= 2;
        // Count used to store exponent value
        cnt++;
    }
    return B_Number;
}

string toBinary(int n)
{
    string r;
    while (n != 0)
    {
        r = (n % 2 == 0 ? "0" : "1") + r;
        n /= 2;
    }
    return r;
}

vector<vector<string> *> insert(vector<vector<string> *> mapping, int *k, int bucket_size, string element);

vector<vector<string> *> split(vector<vector<string> *> mapping, int k, int bucket_size, string element)
{
    int n = pow(2, k);
    vector<vector<string> *> arr;
    for (int i = 0; i < n; i++)
    {
        vector<string> *temp = NULL;
        temp = new (vector<string>);
        // cout<<"address"<<temp<<endl;
        arr.push_back(temp);
    }
    string point = element.substr(element.size() - k + 1, k - 1);
    int point_int = stoi(point, 0, 2);
    // cout<<"point_int "<<point_int<<endl;
    vector<string> *temp = mapping[point_int];
    // cout<<mapping.size()<<endl;

    for (int i = 0; i < (*(mapping[point_int])).size(); i++)
    {
        continue;
        // cout<<(*(mapping[point_int]))[i]<<" ";
    }
    // cout<<"temp"<<endl;

    // string temp1='0'+point;
    // string temp2='1'+point;
    // int b0=stoi(temp1,0,2);
    // int b1=stoi(temp2,0,2);
    string temp1, temp2;
    int b0, b1;
    for (int i = 0; i < bucket_size; i++)
    {
        string num = (*temp)[i];
        for (int j = 0; j < n; j++)
        {
            if (j == 0)
            {
                temp1 = '0';
            }
            else
                temp1 = toBinary(j);
            // cout<<"temp1 "<<temp1<<endl;
            if (temp1.length() < k)
            {
                for (int flag = 0; flag < k - temp1.length(); flag++)
                {
                    temp1 = '0' + temp1;
                }
            }
            if (num.substr(num.size() - k, k) == temp1)
            {
                b0 = stoi(temp1, 0, 2);
                (*(arr[b0])).push_back(num);
            }
            // else {

            //     b1=stoi(temp1,0,2);
            //     (*(arr[b1])).push_back(num);
            // }
        }
        // cout<<endl;
    }
    temp1 = element.substr(element.size() - k, k);
    b0 = stoi(temp1, 0, 2);
    arr = insert(arr, &k, bucket_size, element);

    // for (int i=0;i<bucket_size;i++){
    //     // cout<<"for_looking"<<(*(mapping[point_int])).size()<<endl;
    //     string num = (*temp)[i];
    //     // cout<<"here "<<endl;
    //     if (num.substr(num.size()-k,k) == temp1){
    //         (*(arr[b0])).push_back(num);
    //     }
    //     else {
    //         cout<<"here"<<num.substr(num.size()-k,k)<<endl;;

    //         (*(arr[b1])).push_back(num);
    //     }
    // }
    for (int i = 0; i < pow(2, k - 1); i++)
    {
        if (i == point_int)
        {
            continue;
        }

        else
        {
            if (i == 0)
            {
                point = '0';
            }
            else
                point = toBinary(i);
            // cout<<"point"<<point<<endl;
            temp1 = '0' + point;
            temp2 = '1' + point;
            b0 = stoi(temp1, 0, 2);
            b1 = stoi(temp2, 0, 2);
            // cout<<"p"<<point<<endl;
            // cout<<"Bs "<<b0<<" "<<b1<<endl;
            (arr[b0]) = mapping[i];
            (arr[b1]) = mapping[i];
        }
    }
    // cout<<"split_count"<<(*(arr[1])).size()<<endl;
    // for (int i=0;i<n;i++){
    //     for (int j=0;j<(*(arr[i])).size();j++){
    //         cout<<(*(arr[i]))[j]<<" ";
    //     }
    //     cout<<endl;
    // }
    return arr;
}

vector<vector<string> *> insert(vector<vector<string> *> mapping, int *k, int bucket_size, string element)
{
    vector<vector<string> *> out;
    string point = element.substr(element.size() - ((*k)), (*k));
    int point_int = stoi(point, 0, 2);
    vector<string> *pointer = mapping[point_int];

    // vector<string> pointer = *p;
    if ((*pointer).size() == bucket_size)
    {
        (*k) = (*k) + 1;
        out = split(mapping, *k, bucket_size, element);
        return out;
    }
    else
    {
        (*pointer).push_back(element);

        return mapping;
    }
}

string retrieve(vector<string> db, vector<string> binary, string hash_value)
{

    map<string, string> data_map;
    for (int i = 0; i < binary.size(); i++)
    {
        data_map[binary[i]] = db[i];
    }
    return data_map[hash_value];
}

void compare_insertion(vector<whole::db_obj> &collections)
{
    cout << "\n --------------------------------- Q5 Part B ---------------------------------- \n";
    auto begin = high_resolution_clock::now();
    whole::db_obj l = whole::db_obj("Ko_Ya_0103", "Fin_KY_0103", "Kobi Yamada", "Finding Muchness");
    map<int, vector<whole::db_obj>> hash_table = linear_hashing(collections, 4, 5);
    collections.emplace_back(l);
    string key = l.book_id + l.author_id;
    int hash = hash_function(key, 5);
    hash_table[hash].emplace_back(l);
    if (hash_table[hash].size() > 4)
    {
        cout << "Overflow occured\n";
        cout << "Rehashing the hash table\n";
        hash_table = linear_hashing(collections, 4, 10);
    }
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - begin);
    cout << "Time taken to add new record in linear hashing: " << duration.count() << " microseconds" << endl;

    /// --------------

    begin = high_resolution_clock::now();
    l = whole::db_obj("Ko_Ya_0103", "Fin_KY_0103", "Kobi Yamada", "Finding Muchness");
    hash_table = distributed_hasing_using_linear_list(5, 4, collections);
    collections.emplace_back(l);
    key = l.book_id + l.author_id;
    hash = hash_function(key, 5);
    hash_table[hash].emplace_back(l);
    if (hash_table[hash].size() > 4)
    {
        cout << "Overflow occured\n";
        cout << "Rehashing the hash table\n";
        hash_table = linear_hashing(collections, 4, 10);
    }
    end = high_resolution_clock::now();
    duration = duration_cast<microseconds>(end - begin);
    cout << "Time taken to add new record in distributed hashing: " << duration.count() << " microseconds" << endl;

    /// -----------------
    vector<string> Author_ID = {"An_Ch_0103",
                                "An_Da_0104",
                                "Ca_Sa_0319",
                                "Jo_Ro_1018",
                                "Jo_Ro_1018",
                                "Jo_Ro_1018",
                                "Jo_Ro_1018",
                                "Jo_Ro_1018",
                                "La_Ch_1203",
                                "Ma_Mi_1313",
                                "Ma_Mi_1313",
                                "Pe_Wo_1623",
                                "Pe_Wo_1623",
                                "Vi_Ra_2218",
                                "Vi_Ra_2218"};

    vector<string> Book_ID = {
        "Aest_AC_0103",
        "Self_AD_0104 ",
        "Anim_CS_0319",
        "Deat_JR_1018",
        "Fant_JR_1018",
        "Gobl_JR_1018",
        "Phil_JR_1018",
        "Pris_JR_1018",
        "Mind_LC_1203",
        "Emot_MM_1313",
        "Soci_MM_1313",
        "Aunt_PW_1623",
        "Wode_PW_1623",
        "Emer_VR_2218",
        "Phan_VR_2218"};

    vector<string> binary;
    auto start = high_resolution_clock::now();
    vector<int> hasher = hashfunc(Author_ID, Book_ID);
    for (int i = 0; i < hasher.size(); i++)
    {
        string temp;
        temp = toBinary(hasher[i]);
        binary.push_back(temp);
    }
    vector<vector<string> *> mapping;
    int k = 1;
    vector<int *> check;
    for (int i = 0; i < pow(2, k); i++)
    {
        vector<string> *temp = NULL;
        temp = new (vector<string>);
        mapping.push_back(temp);
    }
    int bucket_size = 4;
    for (int i = 0; i < binary.size(); i++)
    {
        mapping = insert(mapping, &k, bucket_size, binary[i]);
    }

    auto stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "\n Time taken by Extended hashing using linear list (vector): " << duration.count() << " microseconds" << endl;
}

void compare_1_retrieval(vector<whole::db_obj> &collections)
{
    cout << "\n --------------------------------- Q5 Part C ---------------------------------- \n";

    whole::db_obj l = whole::db_obj("Ca_Sa_0319", "Anim_CS_0319", "Carl Safina", "What Animals Think");
    map<int, vector<whole::db_obj>> hash_table = linear_hashing(collections, 4, 5);
    auto begin = high_resolution_clock::now();
    string key = l.book_id + l.author_id;
    int hash = hash_function(key, 5);
    vector<whole::db_obj> bucket = hash_table[hash];
    int index = -1;
    for (int i = 0; i < bucket.size(); i++)
    {
        if (bucket[i].book_id == l.book_id && bucket[i].author_id == l.author_id)
        {
            index = i;
            break;
        }
    }
    if (index == -1)
    {
        std::cout << "Record not found" << endl;
    }
    else
    {
        std::cout << "Record found" << endl;
    }
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - begin);
    cout << "Time taken to retrieve a record in linear hashing: " << duration.count() << " microseconds" << endl;

    // ----------------------------------------

    l = whole::db_obj("Ca_Sa_0319", "Anim_CS_0319", "Carl Safina", "What Animals Think");
    hash_table = distributed_hasing_using_linear_list(4, 5, collections);
    begin = high_resolution_clock::now();
    key = l.book_id + l.author_id;
    hash = hash_function(key, 5);
    bucket = hash_table[hash];
    index = -1;
    for (int i = 0; i < bucket.size(); i++)
    {
        if (bucket[i].book_id == l.book_id && bucket[i].author_id == l.author_id)
        {
            index = i;
            break;
        }
    }
    if (index == -1)
    {
        std::cout << "Record not found" << endl;
    }
    else
    {
        std::cout << "Record found" << endl;
    }
    end = high_resolution_clock::now();
    duration = duration_cast<microseconds>(end - begin);
    cout << "Time taken to retrieve a record in Distributed hashing: " << duration.count() << " microseconds" << endl;

    // ---------------------------------------------------------------------

    vector<string> db = {
        "An_Ch_0103 Aest_AC_0103 Anjan Chatterjee The Aesthetic Brain",
        "An_Da_0104  Self_AD_0104  Antonio Damasio Self Comes to Mind",
        "Ca_Sa_0319 Anim_CS_0319 Carl Safina What Animals Think",
        "Jo_Ro_1018 Deat_JR_1018 Joanne K. Rowling Deathly Hallows_Harry Potter",
        "Jo_Ro_1018 Fant_JR_1018 Joanne K. Rowling Fantastic Beasts and Where to  Find Them",
        "Jo_Ro_1018 Gobl_JR_1018 Joanne K. Rowling Goblet of Fire_Harry Potter",
        "Jo_Ro_1018 Phil_JR_1018 Joanne K. Rowling Philosopher’s Stone_Harry Potter",
        "Jo_Ro_1018 Pris_JR_1018 Joanne K. Rowling Prisoner of Azkaban_Harry Potter",
        "La_Ch_1203 Mind_LC_1203 Lars Chittka The Mind of a Bee",
        "Ma_Mi_1313 Emot_MM_1313 Marvin Minsky Emotion Machine",
        "a_Mi_1313 Soci_MM_1313 Marvin Minsky Society of Mind",
        "Pe_Wo_1623 Aunt_PW_1623 Pelham G. Wodehouse Aunts Aren’t Gentlemen",
        "Pe_Wo_1623 Wode_PW_1623 Pelham G. Wodehouse Wodehouse at the Wicket",
        "Vi_Ra_2218 Emer_VR_2218Vilayanur Ramachandran The Emerging Mind",
        "Vi_Ra_2218 Phan_VR_2218 Vilayanur Ramachandran Phantoms in the Brain"};

    string auth = "Ca_Sa_0319", bookk = "Anim_CS_0319";
    int hashv_int = hashVal(auth + bookk);
    string hashv = toBinary(hashv_int);

    vector<string> Author_ID = {"An_Ch_0103",
                                "An_Da_0104",
                                "Ca_Sa_0319",
                                "Jo_Ro_1018",
                                "Jo_Ro_1018",
                                "Jo_Ro_1018",
                                "Jo_Ro_1018",
                                "Jo_Ro_1018",
                                "La_Ch_1203",
                                "Ma_Mi_1313",
                                "Ma_Mi_1313",
                                "Pe_Wo_1623",
                                "Pe_Wo_1623",
                                "Vi_Ra_2218",
                                "Vi_Ra_2218"};

    vector<string> Book_ID = {
        "Aest_AC_0103",
        "Self_AD_0104 ",
        "Anim_CS_0319",
        "Deat_JR_1018",
        "Fant_JR_1018",
        "Gobl_JR_1018",
        "Phil_JR_1018",
        "Pris_JR_1018",
        "Mind_LC_1203",
        "Emot_MM_1313",
        "Soci_MM_1313",
        "Aunt_PW_1623",
        "Wode_PW_1623",
        "Emer_VR_2218",
        "Phan_VR_2218"};

    vector<string> binary;
    vector<int> hasher = hashfunc(Author_ID, Book_ID);
    for (int i = 0; i < hasher.size(); i++)
    {
        string temp;
        temp = toBinary(hasher[i]);
        binary.push_back(temp);
    }

    auto start = high_resolution_clock::now();
    string retrived_item = retrieve(db, binary, hashv);
    auto stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "\n Time taken by Extended hashing using linear list (vector): " << duration.count() << " microseconds" << endl;
}

void compare_full_retrieval(vector<whole::db_obj> &collections)
{
    cout << "\n --------------------------------- Q5 Part D ---------------------------------- \n";
    map<int, vector<whole::db_obj>> hash_table = linear_hashing(collections, 4, 5);
    string author_id = "Ma_Mi_0101";
    auto begin = high_resolution_clock::now();
    vector<whole::db_obj> result;
    for (auto it = hash_table.begin(); it != hash_table.end(); it++)
    {
        vector<whole::db_obj> bucket = it->second;
        for (int i = 0; i < bucket.size(); i++)
        {
            if (bucket[i].author_id == author_id)
            {
                result.emplace_back(bucket[i]);
            }
        }
    }

    if (result.size() == 0)
    {
        cout << "Record not found\n";
    }
    else
    {
        cout << "Record found \n";
    }

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - begin);
    cout << "Time taken to get all the records using linear hashing: " << duration.count() << " microseconds \n";

    // -----------

    hash_table = distributed_hasing_using_linear_list(4, 5, collections);
    author_id = "Ma_Mi_0101";
    begin = high_resolution_clock::now();
    for (auto it = hash_table.begin(); it != hash_table.end(); it++)
    {
        vector<whole::db_obj> bucket = it->second;
        for (int i = 0; i < bucket.size(); i++)
        {
            if (bucket[i].author_id == author_id)
            {
                result.emplace_back(bucket[i]);
            }
        }
    }

    if (result.size() == 0)
    {
        cout << "Record not found\n";
    }
    else
    {
        cout << "Record found \n";
    }

    end = high_resolution_clock::now();
    duration = duration_cast<microseconds>(end - begin);
    cout << "Time taken to get all the records using Distributed hashing: " << duration.count() << " microseconds \n";

    // --------------------

    vector<string> db = {
        "An_Ch_0103 Aest_AC_0103 Anjan Chatterjee The Aesthetic Brain",
        "An_Da_0104  Self_AD_0104  Antonio Damasio Self Comes to Mind",
        "Ca_Sa_0319 Anim_CS_0319 Carl Safina What Animals Think",
        "Jo_Ro_1018 Deat_JR_1018 Joanne K. Rowling Deathly Hallows_Harry Potter",
        "Jo_Ro_1018 Fant_JR_1018 Joanne K. Rowling Fantastic Beasts and Where to  Find Them",
        "Jo_Ro_1018 Gobl_JR_1018 Joanne K. Rowling Goblet of Fire_Harry Potter",
        "Jo_Ro_1018 Phil_JR_1018 Joanne K. Rowling Philosopher’s Stone_Harry Potter",
        "Jo_Ro_1018 Pris_JR_1018 Joanne K. Rowling Prisoner of Azkaban_Harry Potter",
        "La_Ch_1203 Mind_LC_1203 Lars Chittka The Mind of a Bee",
        "Ma_Mi_1313 Emot_MM_1313 Marvin Minsky Emotion Machine",
        "Ma_Mi_1313 Soci_MM_1313 Marvin Minsky Society of Mind",
        "Pe_Wo_1623 Aunt_PW_1623 Pelham G. Wodehouse Aunts Aren’t Gentlemen",
        "Pe_Wo_1623 Wode_PW_1623 Pelham G. Wodehouse Wodehouse at the Wicket",
        "Vi_Ra_2218 Emer_VR_2218 Vilayanur Ramachandran The Emerging Mind",
        "Vi_Ra_2218 Phan_VR_2218 Vilayanur Ramachandran Phantoms in the Brain"};

    string auth = "Ca_Sa_0319", bookk = "Anim_CS_0319";
    int hashv_int = hashVal(auth + bookk);
    string hashv = toBinary(hashv_int);

    vector<string> Author_ID = {"An_Ch_0103",
                                "An_Da_0104",
                                "Ca_Sa_0319",
                                "Jo_Ro_1018",
                                "Jo_Ro_1018",
                                "Jo_Ro_1018",
                                "Jo_Ro_1018",
                                "Jo_Ro_1018",
                                "La_Ch_1203",
                                "Ma_Mi_1313",
                                "Ma_Mi_1313",
                                "Pe_Wo_1623",
                                "Pe_Wo_1623",
                                "Vi_Ra_2218",
                                "Vi_Ra_2218"};

    vector<string> Book_ID = {
        "Aest_AC_0103",
        "Self_AD_0104 ",
        "Anim_CS_0319",
        "Deat_JR_1018",
        "Fant_JR_1018",
        "Gobl_JR_1018",
        "Phil_JR_1018",
        "Pris_JR_1018",
        "Mind_LC_1203",
        "Emot_MM_1313",
        "Soci_MM_1313",
        "Aunt_PW_1623",
        "Wode_PW_1623",
        "Emer_VR_2218",
        "Phan_VR_2218"};

    vector<string> Book = {
        "The Aesthetic Brain",
        "Self Comes to Mind",
        "What Animals Think",
        "Deathly Hallows_Harry Potter",
        "Fantastic Beasts and Where to Find Them",
        "Goblet of Fire_Harry Potter",
        "Philosopher's Stone_Harry Potter",
        "Prisoner of Azkaban_Harry Potter",
        "The Mind of a Bee",
        "Emotion Machine",
        "Society of Mind",
        "Aunts Aren't Gentlemen",
        "Wodehouse at the Wicket",
        "The Emerging Mind",
        "Phantoms in the Brain"};

    vector<string> binary;
    vector<int> hasher = hashfunc(Author_ID, Book_ID);
    for (int i = 0; i < hasher.size(); i++)
    {
        string temp;
        temp = toBinary(hasher[i]);
        binary.push_back(temp);
    }
    auto start = high_resolution_clock::now();
    for (int i = 0; i < Author_ID.size(); i++)
    {
        if (Author_ID[i] == "Ma_Mi_1313")
        {
            cout << Book[i] << endl;
        }
    }
    // string retrived_item = retrieve(db, binary, hashv);
    auto stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "\n Time taken by Extended hashing using linear list (vector): " << duration.count() << " microseconds" << endl;
}

void evaluate_extended_hashing(int bucket_size)
{
    vector<string> Author_ID = {
        "An_Ch_0103", "An_Da_0104", "Ca_Sa_0319", "Jo_Ro_1018", "Jo_Ro_1018",
        "Jo_Ro_1018", "Jo_Ro_1018", "Jo_Ro_1018", "La_Ch_1203", "Ma_Mi_1313",
        "Ma_Mi_1313", "Pe_Wo_1623", "Pe_Wo_1623", "Vi_Ra_2218", "Vi_Ra_2218"};

    vector<string> Book_ID = {
        "Aest_AC_0103", "Self_AD_0104 ", "Anim_CS_0319", "Deat_JR_1018", "Fant_JR_1018",
        "Gobl_JR_1018", "Phil_JR_1018", "Pris_JR_1018", "Mind_LC_1203", "Emot_MM_1313",
        "Soci_MM_1313", "Aunt_PW_1623", "Wode_PW_1623", "Emer_VR_2218", "Phan_VR_2218"};

    vector<int> hash;
    vector<string> binary;

    auto start = high_resolution_clock::now();

    hash = hashfunc(Author_ID, Book_ID);
    cout << "Binary values" << endl;
    for (int i = 0; i < hash.size(); i++)
    {
        string temp;
        temp = toBinary(hash[i]);
        cout << temp << " ";
        binary.push_back(temp);
    }

    vector<vector<string> *> mapping;

    int k = 1;
    vector<int *> check;
    for (int i = 0; i < pow(2, k); i++)
    {
        vector<string> *temp = NULL;
        temp = new (vector<string>);
        mapping.push_back(temp);
    }
    // int bucket_size = 7;
    for (int i = 0; i < binary.size(); i++)
    {
        mapping = insert(mapping, &k, bucket_size, binary[i]);
    }
    cout << endl;
    cout << endl;
    cout << "Extendible Hashing" << endl;
    for (int i = 0; i < mapping.size(); i++)
    {
        cout << "bucket " << i << ":   ";
        for (int j = 0; j < (*(mapping[i])).size(); j++)
        {
            cout << (*(mapping[i]))[j] << " ";
        }
        cout << endl;
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "\n Time taken by Extended hashing using linear list (vector): " << duration.count() << " microseconds" << endl;
}
