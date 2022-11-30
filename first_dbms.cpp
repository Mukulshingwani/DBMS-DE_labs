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

    // mysql_real_connect(Connection Instance, Username, Password,
    // Database, Port, Unix Socket, Client Flag)
    if (mysql_real_connect(conn, "localhost", "mukul", "pass123", "databse1", 3306, NULL, 0))
    {

        cout << "Connected Successfully!" << endl;
    }
    else
    {
        cout << "Error while connecting!" << endl;
    }
    char tableName[256] = "demo_table";
    char query[512];
    snprintf(query, 512, "CREATE TABLE `%s` (`id` int NOT NULL PRIMARY KEY, `name` varchar(255), `email` varchar(255), `phone` varchar(255));",
             tableName);
    int createTableStatus = mysql_query(conn, query);
    if (createTableStatus != 0)
    {
        cout << "Error while creating table: " << mysql_error(conn) << endl;
    }
    return 0;
}