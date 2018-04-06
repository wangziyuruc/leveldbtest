#include "leveldb/db.h"
#include <cassert>
#include <iostream>
#include <string> 
#include <sstream>
using namespace std;
using namespace leveldb;

void int2str(const int &int_temp,string &string_temp)  
{  
        stringstream stream;  
        stream<<int_temp;  
        string_temp=stream.str();   //此处也可以用 stream>>string_temp  
}  

int main() {

    leveldb::DB *db;
    leveldb::Options options;
    options.create_if_missing = true;
    leveldb::Status status = leveldb::DB::Open(options, "testdb", &db);
    cout << status.ok() <<endl;
    assert(status.ok());
    int i = 1;
    int n = 1;
    string str = "";
    int2str(i,str);
    status = db->Put(WriteOptions(), str, str);
    
    int readNum1 = 0;
    string res1;    
    while(readNum1<10){
        status = db->Get(ReadOptions(), "1", &res1);
        //std::cout<<readNum1<<std::endl;
        readNum1++;
    }


    while(n < 1000000){
        string s = "";
        int2str(i,s);
        //cout<<s<<endl;
        status = db->Put(WriteOptions(), s, s);
        i++;
        assert(status.ok());
        n++;

    }
    int readNum = 0;
    string res;    
    while(readNum<10){
        status = db->Get(ReadOptions(), "1", &res);
        std::cout<<readNum<<std::endl;
        readNum++;
    }
    
    // while(n < 150000){
    //     string s = "";
    //     int2str(i,s);
    //     //cout<<s<<endl;
    //     status = db->Put(WriteOptions(), s, s);
    //     i++;
    //     assert(status.ok());
    //     n++;

    // }

    // status = db->Get(ReadOptions(), "1", &res);
    // string res;
    // status = db->Get(ReadOptions(), "JimZuoLin", &res);
    // assert(status.ok());
    // cout << res << endl;
    getchar();

    delete db;
    return 0;
}