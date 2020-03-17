#include "mysql.h" 

#include <cstdio> 

#include <cstdlib> 

#include <string> 

#include <iostream> 

#include <sstream> 

 

using namespace std; 

bool  IL1tracker = false; 

bool IL2tracker  = false; 

bool PC1tracker = false; 

 

 

MYSQL *con = mysql_init(NULL); 

 

void finish_with_error(MYSQL *con) 

{ 

  fprintf(stderr, "%s\n", mysql_error(con)); 

  mysql_close(con); 

  exit(1);         

} 

 

int main(){ 

 

  if (con == NULL) { 

      fprintf(stderr, "%s\n", mysql_error(con)); 

      exit(1); 

  } 

 

if (mysql_real_connect(con,"localhost", "root", "55011392MM", "testdb", 0, NULL, 0) == NULL) { 

        finish_with_error(con); 

  } 

 

MYSQL_RES *please = mysql_store_result(con); 

 

if (please == NULL)  

{ 

      finish_with_error(con); 

} 

 

 

MYSQL_ROW pleasee; 

 

while((pleasee=mysql_fetch_row(please))){ 

         

        string sensorID=pleasee[2]; 

        int percent=0; 

        if(sensorID.compare("IL1")==0){ 

                IL1tracker=true; 

        } 

         if(sensorID.compare("IL2")==0){ 

                IL2tracker=true;} 

        else if(sensorID.compare("PC1")==0){ 

                PC1tracker=true;; 

        } 

 

} 

 

if (mysql_query(con,"select NumPPL from output_table WHERE RstrntID=1")){ 

     finish_with_error(con); 

  } 

    

MYSQL_RES *result = mysql_store_result(con); 

   

if (result == NULL)  

{ 

      finish_with_error(con); 

} 

 

MYSQL_ROW row; 

row=mysql_fetch_row(result); 

int np = atoi(row[0]); 

cout <<"Number of people: " <<  np << endl; 

 

 

if (mysql_query(con,"select linelength from restaurantinfotable WHERE RstrntID=1")){ 

     finish_with_error(con); 

  } 

    

MYSQL_RES *feet = mysql_store_result(con); 

 

if (feet == NULL)  

{ 

      finish_with_error(con); 

} 

 

MYSQL_ROW feett; 

 

feett=mysql_fetch_row(feet); 

int total = atoi(feett[0]); 

cout << "Total feet: "<< total << endl; 

 

float z =2.5; 

float x = np * z; 

cout <<"Number of feet taken up: " << x << endl; 

int percent =0; 

double twoThirdsMark = 2*total/3; 

cout << "twoThirdsMark: " << twoThirdsMark << endl; 

double fullMark = total - 1; 

double oneThirdsMark =total/3; 

cout << "oneThirdsMark: " << oneThirdsMark<< endl; 

cout << "fullMark: " << fullMark<< endl;; 

 

cout << "IL1: " << IL1tracker << endl; 

cout << "IL2: " << IL2tracker << endl; 

if( x >= fullMark && IL1tracker && IL2tracker)  

{ 

         percent =100; 

        cout << 100<<endl;}  

else if ( twoThirdsMark <= x && x <fullMark && IL1tracker && IL2tracker){ 

        percent =66; 

        cout << 66 <<endl;} 

else if (oneThirdsMark<= x && x<= twoThirdsMark && IL1tracker){ 

        percent =33; 

        cout << 33 << endl;} 

else{ 

        percent = 0; 

        cout << 0 << endl; 

} 

stringstream percentSStr; 

percentSStr << percent; 

string percentStr = percentSStr.str(); 

cout << percentStr << endl; 

string updateStatement = "UPDATE output_table SET PercentFull=" + percentSStr.str() + "  WHERE RstrntID=1"; 

if (mysql_query(con, updateStatement.c_str())) { 

                finish_with_error(con); 

        } 

  mysql_free_result(result); 

  mysql_free_result(feet); 

  mysql_close(con); 

  exit (0); 

} 

 
