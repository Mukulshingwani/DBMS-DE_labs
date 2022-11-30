#include <iostream>
#include <windows.h>
#include <mysql.h>

using namespace std;

MYSQL *conn;


void display(){
    MYSQL_RES *result=mysql_store_result(conn);
    MYSQL_ROW row;
    //display attribute names
    for(int i=0;i<mysql_num_fields(result);i++){
        cout<<mysql_fetch_field_direct(result,i)->name<<" ";
    }
    cout<<endl;
    while((row=mysql_fetch_row(result))){
        for(int i=0;i<mysql_num_fields(result);i++){
            cout<<row[i]<<" ";
        }
        cout<<endl;
    }
}


void displayA(){
    int query_status=mysql_query(conn,"SELECT * FROM salesmen_info;");
    if(query_status){
        cout<<"Error : "<<mysql_error(conn)<<endl;
        exit(1);
    }
    else{
        display();
    }

}

void displayB(){
    int query_status=mysql_query(conn,"SELECT * FROM salesmen_info WHERE name='abc';");
    if(query_status){
        cout<<"Error : "<<mysql_error(conn)<<endl;
        exit(1);
    }
    else{
        display();
    }

}
void displayC(){
    int query_status=mysql_query(conn,"SELECT commission FROM salesmen_info WHERE address_city='Mumbai' OR 'Chennai';");
    if(query_status){
        cout<<"Error : "<<mysql_error(conn)<<endl;
        exit(1);
    }
    else{
        display();
    }

}
void displayD(){
    int query_status=mysql_query(conn,"SELECT salesmen_infoman_id,name FROM salesmen_info WHERE address_city=coverage_city;");
    if(query_status){
        cout<<"Error : "<<mysql_error(conn)<<endl;
        exit(1);
    }
    else{
        display();
    }

}
void displayE(){
    int query_status=mysql_query(conn,"SELECT salesmen_infoman_id,name FROM salesmen_info WHERE address_city=coverage_city;");
    if(query_status){
        cout<<"Error : "<<mysql_error(conn)<<endl;
        exit(1);
    }
    else{
        display();
    }

}

void displayF(){
    int query_status=mysql_query(conn,"SELECT MAX(commission) FROM salesmen_info;");
    if(query_status){
        cout<<"Error : "<<mysql_error(conn)<<endl;
        exit(1);
    }
    else{
        display();
    }

}

void displayG(){
    int query_status=mysql_query(conn,"SELECT coverage_city, MAX(commission) FROM salesmen_info;");
    if(query_status){
        cout<<"Error : "<<mysql_error(conn)<<endl;
        exit(1);
    }
    else{
        display();
    }

}
void displayH(){
    int query_status=mysql_query(conn,"SELECT AVG(commission) ORDER by coverage_city;");
    if(query_status){
        cout<<"Error : "<<mysql_error(conn)<<endl;
        exit(1);
    }
    else{
        display();
    }

}
void displayI(){
    int query_status=mysql_query(conn,"SELECT coverage_city FROM salesmen_info GROUP BY commission HAVING count(*)=1;");
    if(query_status){
        cout<<"Error : "<<mysql_error(conn)<<endl;
        exit(1);
    }
    else{
        display();
    }

}
void displayJ(){
    int query_status=mysql_query(conn,"SELECT * FROM salesmen_info;");
    if(query_status){
        cout<<"Error : "<<mysql_error(conn)<<endl;
        exit(1);
    }
    else{
        display();
    }

}
void displayK(){
    int query_status=mysql_query(conn,"SELECT * FROM salesmen_info As a WHERE Exists ( SELECT 1 FROM salesmen_infomen_info As b WHERE b.name = a.name And b.coverage_city != a.coverage_city );");
    if(query_status){
        cout<<"Error : "<<mysql_error(conn)<<endl;
        exit(1);
    }
    else{
        display();
    }

}
void displayL(){
    int query_status=mysql_query(conn,"ALTER TABLE salesmen_info ADD date_of_employment date, ADD date_of_release date;");
    if(query_status){
        cout<<"Error : "<<mysql_error(conn)<<endl;
        exit(1);
    }
    else{
        display();
    }

}

int main()
{
    conn = mysql_init(NULL);
    if (conn == NULL) {
        cout<<"Error: "<<mysql_error(conn)<<endl;
        exit(1);
    }

    // mysql_real_connect(Connection Instance, Username, Password, Database, Port, Unix Socket, Client Flag)
    if (mysql_real_connect(conn, "localhost", "mukul", "pass123", "databse1", 3306, NULL, 0)) {
        cout<<"Connected Successfully!"<<endl;
       ;
        char query[256];

        displayA();
        displayB();
        displayC();
        displayD();
        displayE();
        displayF();

        displayG();

        displayH();

        displayI();
        displayJ();

        displayK();

        displayL();

        

    }
        return 0;

}