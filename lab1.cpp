// Command to Compile: g++ demo.cpp -o demo.exe -lmysql

#include <iostream>
#include <windows.h>
#include <mysql.h>

using namespace std;

MYSQL *conn;

int main()
{
    conn = mysql_init(NULL);
    if (conn == NULL)
    {
        cout << "Error: " << mysql_error(conn) << endl;
        exit(1);
    }

    // mysql_real_connect(Connection Instance, Username, Password, Database, Port, Unix Socket, Client Flag)
    if (mysql_real_connect(conn, "localhost", "sawan", "password", "lab_01", 3306, NULL, 0))
    {
        cout << "Connected Successfully!" << endl;
        ;
        char query[256];

        snprintf(query, 256, "CREATE TABLE `%s` ( `user_id` varchar(255) NOT NULL, `passwd` varchar(255) NOT NULL);", "login");

        snprintf(query, 256, "CREATE TABLE `%s` ( `book_id` varchar(255) NOT NULL, `user_id` varchar(255) NOT NULL, `name` varchar(255) NOT NULL,`genre` varchar(255));", "book");
        snprintf(query, 256, "CREATE TABLE `%s` ( `first_name` varchar(255) NOT NULL,`last_name` varchar(255) NOT NULL, `user_id` varchar(255) NOT NULL, `contact_no` int NOT NULL,`address` varchar(255));", "user_info");

        int createTableStatus = mysql_query(conn, query);
        if (createTableStatus != 0)
        {
            cout << "Error while creating table: " << mysql_error(conn) << endl;
        }
    }
    else
    {
        cout << "Error while connecting!" << endl;
    }

    return 0;
}