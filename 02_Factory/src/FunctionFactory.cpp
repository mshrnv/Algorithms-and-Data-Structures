#include <iostream>
#include <map>
#include <vector>
#include "IFunction/IFunction.h"
#include "IFunction/EllipseFunction.h"
#include "IFunction/HyperbolaFunction.h"

using namespace std;

class FunctionFactory
{
public:
    void RegisterLoader(const string& name, IFunctionPtr loader)
    {
        _registered[name] = loader;
    }

    IFunctionPtr GetLoader(const string& typeName)
    {
        if (_registered.find(typeName) == _registered.end())
            throw std::runtime_error("Illegal type!");

        return _registered[typeName];
    }

    static FunctionFactory& GetInstance()
    {
        static FunctionFactory instance;
        return instance;
    }
private:
    map<string, IFunctionPtr> _registered;
};

void RegisterLoaders()
{
    FunctionFactory::GetInstance().RegisterLoader("Ellipse", EllipseFunction::Load);
    FunctionFactory::GetInstance().RegisterLoader("Hyperbola", HyperbolaFunction::Load);
}

vector<FunctionPtr> Load(ifstream& stream)
{
    vector<FunctionPtr> result;

    string typeName;

    while (stream >> typeName)
    {
        IFunction* base = FunctionFactory::GetInstance().GetLoader(typeName)(stream);

        FunctionPtr basePtr(base);
        result.push_back(basePtr);
    }

    return result;
}

void Save(ostream& stream, FunctionPtr * bases, int count)
{
    for (size_t i = 0; i < count; i++)
        bases[i]->Save(stream);
}