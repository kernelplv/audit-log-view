#include "TagCommon.h"


TagCommon::operator bool() const
{
    if ( name.empty() or start_seq.empty()
                      or end_seq.empty()
                      or type == TagModelType::nothing )
        return false;
    else
        return true;
}

TagCommon::~TagCommon()
{

}
