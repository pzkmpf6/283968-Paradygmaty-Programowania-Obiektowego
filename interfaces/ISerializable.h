#pragma once
#include <string>
using namespace std;

// -------------------------------------------------------

class ISerializable
{
public:
    virtual string serialize() = 0;
    virtual ~ISerializable() {}
};