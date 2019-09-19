#pragma once

#include "TagModel.h"

// Simple tag with space " " brackets
class TagCommon : public virtual TagModel
{

private:
    string       name         = "Common";
    string       start_seq    = " ";
    string       end_seq      = " ";
    bool         start_ignore = false;
    bool         end_ignore   = false;
    TagModelType type         = TagModelType::Description;

public:
    TagCommon( string name ) : name(name) {}

    TagCommon( string name, bool ignore_start, bool ignore_end )
        : name(name), start_ignore(ignore_start), end_ignore(ignore_end) {}

    TagCommon( string name, string start_seq, string end_seq, TagModelType type )
        : name(name), start_seq(start_seq), end_seq(end_seq), type(type) {}

    ~TagCommon() override;

          string Name() const override      { return name; }
          string StartSeq() const override  { return start_seq; }
          string EndSeq() const override    { return end_seq; }
    TagModelType Type() const override      { return type; }

    operator bool() const override;

    bool StartMayIgnored() const override { return start_ignore; }
    bool EndMayIngored() const override   { return end_ignore; }

};

