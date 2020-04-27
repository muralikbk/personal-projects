#ifndef status_h
#define status_h

#include <string>

using namespace std;

struct Status
{
    int returnCode;
    string message;
    //Default constructor
    Status():returnCode(0),message("")
    {}
    //Parameterized constructors
    Status(int rc):returnCode(rc), message("")
    {}
    Status(string msg):returnCode(0),message(msg)
    {}
    Status(int rc, string msg):returnCode(0),message(msg)
    {}
    //Copy constructor
    Status(const Status &in):returnCode(in.returnCode),message(in.message)
    {}
    //Assignment operator
    Status& operator=(const Status &in)
    {
        returnCode = in.returnCode;
        message = in.message;
        return *this;
    }
};

#endif
