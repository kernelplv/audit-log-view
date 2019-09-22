#include "TagDefault.h"


TagDefault::operator bool() const
{
    if ( name.empty() or start_seq.empty()
                      or end_seq.empty() )
        return false;
    else
        return true;
}

TagDefault::~TagDefault()
{

}
