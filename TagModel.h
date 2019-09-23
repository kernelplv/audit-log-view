#pragma once

#include <string>
#include <vector>
#include <functional>

class TagModel
{

protected:
    using string = std::string;

public:

    virtual ~TagModel() = 0;

    virtual operator bool() const = 0;  // prepare model. if (MyModel & doing anything..)

    virtual string Name()      const = 0;
    virtual string StartSeq()  const = 0;
    virtual string EndSeq()    const = 0;

    virtual bool StartMayIgnored() const = 0;
    virtual bool EndMayIngored()   const = 0;

};
