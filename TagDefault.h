#pragma once

#include "TagModel.h"

// Simple tag with space " " brackets
class TagDefault : public virtual TagModel
{

private:
    string       name         = "Common";
    string       start_seq    = " ";
    string       end_seq      = " ";
    bool         start_ignore = false;
    bool         end_ignore   = false;

public:
    TagDefault( string name ) : name(name) {}

    TagDefault( string name, bool ignore_start, bool ignore_end )
        : name(name), start_ignore(ignore_start), end_ignore(ignore_end) {}

    TagDefault( string name, string start_seq, string end_seq)
        : name(name), start_seq(start_seq), end_seq(end_seq){}

    ~TagDefault() override;

          string Name() const override      { return name; }
          string StartSeq() const override  { return start_seq; }
          string EndSeq() const override    { return end_seq; }

    operator bool() const override;

    bool StartMayIgnored() const override { return start_ignore; }
    bool EndMayIngored() const override   { return end_ignore; }

};

