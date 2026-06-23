#pragma once
#include <string>
#include <map>
using namespace std;

// -------------------------------------------------------

class IEksportowalny
{
public:
    virtual map<string, string> eksportuj() = 0;
    virtual ~IEksportowalny() {}
};