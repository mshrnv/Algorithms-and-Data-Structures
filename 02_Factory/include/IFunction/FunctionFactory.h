#ifndef IFUNCTION_FUNCTIONFACTORY_H
#define IFUNCTION_FUNCTIONFACTORY_H

#include "IFunction.h"
#include <vector>

using namespace std;

void RegisterLoaders();
vector<FunctionPtr> Load(ifstream& stream);
void Save(ostream& stream, FunctionPtr* bases, int count);

#endif //IFUNCTION_FUNCTIONFACTORY_H
