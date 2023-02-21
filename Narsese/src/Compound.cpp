#include "../include/Compound.h"

using namespace COMPOUND;

Compound::Compound(Connector connector, Terms& terms) : Compound::Compound(connector)
{

}

Compound::Compound(Connector connector, std::list<Term*> &terms) : Compound::Compound(connector)
{

}

Compound::Compound(Connector connector, std::initializer_list<Term*> terms) : Compound::Compound(connector)
{
    
}


