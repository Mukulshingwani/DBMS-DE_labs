#include <bits/stdc++.h>
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

int dec_to_bin(int decimal)
{
    int binary = 0, remainder, product = 1;
    while (decimal != 0)
    {
        remainder = decimal % 2;
        binary = binary + (remainder * product);
        decimal = decimal / 2;
        product *= 10;
    }
    return binary;
}

vector<int> ret_hash_vals(vector<string>book_ids, vector<string>author_ids)
{
    vector<int>hsh_vals;
    for(int i=0;i<book_ids.size();i++)
    {
        int h = hash_value(book_ids[i],author_ids[i]);
        hsh_vals.emplace_back(h);
    }
    return hsh_vals;
}

vector<int> convert_to_bin(vector<int>&hsh_vals)
{
    vector<int>binary_equivalent;
    for(int i=0;i<hsh_vals.size();i++)
    {
        int x = dec_to_bin(hsh_vals[i]);
        binary_equivalent.emplace_back(x);
    }
    return binary_equivalent;
}


int main()
{
    vector<string>author_ids={"An_Ch_0103","An_Da_0104","Ca_Sa_0319", "Jo_Ro_1018", "Jo_Ro_1018", "Jo_Ro_1018", "Jo_Ro_1018", "Jo_Ro_1018", "La_Ch_1203", "Ma_Mi_1313","Ma_Mi_1313", "Pe_Wo_1623","Pe_Wo_1623", "Vi_Ra_2218","Vi_Ra_2218"};
    vector<string>book_ids={"Aest_AC_0103","Self_AD_0104","Anim_CS_0319", "Deat_JR_1018", "Fant_JR_1018", "Gobl_JR_1018", "Phil_JR_1018", "Pris_JR_1018", "Mind_LC_1203", "Emot_MM_1313","Soci_MM_1313", "Aunt_PW_1623","Wode_PW_1623", "Emer_VR_2218","Phan_VR_2218"};

    vector<int>hash_values = ret_hash_vals(book_ids,author_ids);
    for(int i=0;i<hash_values.size();i++)
    {
        cout<<hash_values[i]<<" ";
    }
    cout<<endl;

    vector<int>bin_eqs = convert_to_bin(hash_values);
    for(int i=0;i<bin_eqs.size();i++)
    {
        cout<<bin_eqs[i]<<" ";
    }
    cout<<endl;
    // string book_id = "Aest_AC_0103";
    // string author_id = "An_Ch_0103";
    // int h = hash_value(book_id, author_id);
    // cout << h;


    

    return 0;

};
  


