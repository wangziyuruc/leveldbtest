#include "leveldb/db.h"
#include <cassert>
#include <iostream>
#include <string>
#include <sstream>
#include <sys/time.h>

using namespace std;
using namespace leveldb;

void int2str(const int &int_temp, string &string_temp)
{
    stringstream stream;
    stream << int_temp;
    string_temp = stream.str(); //此处也可以用 stream>>string_temp
}

uint64_t NowMicros()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return static_cast<uint64_t>(tv.tv_sec) * 1000000 + tv.tv_usec;
}

int main()
{
    const uint64_t start_micros = NowMicros();

    cout <<"start time :"<<start_micros<<endl;

    leveldb::DB *db;
    leveldb::Options options;
    options.create_if_missing = true;
    leveldb::Status status = leveldb::DB::Open(options, "testdb", &db);
    cout << status.ok() << endl;
    assert(status.ok());
    int i = 1;
    int n = 1;
    string str = "";
    // int2str(i, str);
    // status = db->Put(WriteOptions(), str, str);
    while (n < 1000000000)
    {
        string s = "";
        int2str(i, s);
        status = db->Put(WriteOptions(), s, s);
        i++;
        assert(status.ok());
        n++;
    }

    // int readNum1 = 0;
    // string res1;
    // while (readNum1 < 10)
    // {
    //     status = db->Get(ReadOptions(), "1", &res1);
    //     std::cout << readNum1 << std::endl;
    //     readNum1++;
    // }
    const uint64_t end_micros = NowMicros();

    cout <<"end time :"<<end_micros<<endl;
    cout <<"consume time : "<<end_micros-start_micros<<endl;
    // while (n < 100000000)
    // {
    //     string s = "";
    //     int2str(i, s);
    //     //cout<<s<<endl;
    //     status = db->Put(WriteOptions(), s, s);
    //     i++;
    //     assert(status.ok());
    //     n++;
    // }
    // std::cout << "end" << endl;
    // // int readNum = 0;
    // // string res;
    // // while(readNum<10){
    // //     status = db->Get(ReadOptions(), "1", &res);
    // //     std::cout<<readNum<<std::endl;
    // //     readNum++;
    // // }

    // // while(n < 150000){
    // //     string s = "";
    // //     int2str(i,s);
    // //     //cout<<s<<endl;
    // //     status = db->Put(WriteOptions(), s, s);
    // //     i++;
    // //     assert(status.ok());
    // //     n++;

    // // }

    // // status = db->Get(ReadOptions(), "1", &res);
    // // string res;
    // // status = db->Get(ReadOptions(), "JimZuoLin", &res);
    // // assert(status.ok());
    // // cout << res << endl;
    //getchar();
    delete db;
    return 0;
}