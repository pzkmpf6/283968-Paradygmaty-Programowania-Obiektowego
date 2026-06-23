#pragma once
#include <string>
#include "IEksportowalny.h"
using namespace std;

// -------------------------------------------------------

class IExporter
{
public:
    virtual void wykonajEksport(IEksportowalny *obj, string nazwaPliku) = 0;
    virtual ~IExporter() {}
};