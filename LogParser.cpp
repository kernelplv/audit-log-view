#include "LogParser.h"
#include "TagDefault.h"

using namespace std;

LogParser::operator bool() const
{
    return logfile.is_open();
}

string LogParser::next(const TagModel & tag)
{
    //! warning: end of line '\n' may differ on other platform
    //!          and need rework with wchar_t & wstring
    //! todo: cout >> debug.log

    std::string result("");

    bool start_ignore = tag.StartMayIgnored();
    bool end_ignore = tag.EndMayIngored();
    bool opened = false;
    bool closed = false;

    std::string part("");
    char buff = '\0';
    unsigned i = 0;

    logfile.unsetf(std::ios_base::skipws);

    while ( !closed and logfile.peek() != EOF
                    and logfile >> buff)
    {
        if ( buff == '\n' ) {
            break;
        }

        if ( !opened and !start_ignore )
        {
            if ( i < tag.StartSeq().size() -1
                    and tag.StartSeq()[i++] == buff )
                continue;  
            else
            if ( tag.StartSeq()[i] == buff
                    and i == tag.StartSeq().size() -1 )
                opened = true;

            i = 0;
        }
        // wait tag close
        if ( !closed and !end_ignore )
        {
            if ( i < tag.EndSeq().size() -1
                    and tag.EndSeq()[i++] == buff)
            {
                part.push_back(buff);
                continue;
            }
            else if ( tag.EndSeq()[i] == buff
                        and i == tag.EndSeq().size() -1 )
            {
                part.clear();
                closed = true;
            }
            else {
                result.append(part + buff);
                part.clear();
            }
            i = 0;
        }
        else
            result.push_back(buff);
    }

    if ( i > 0 and !opened and !start_ignore ) cout << "tag was not open" << endl;
    if ( !closed and !end_ignore ) cout << "tag was not close" << endl;

    return result;
}

LogParser::LogParser(const std::string logpath)
{
    logfile.open(logpath, ios::binary);

}

size_t LogParser::countTags()
{
    return tags.size();
}

void LogParser::printInternal(std::ostream& out)
{
    if ( logtable.empty() ) {
        out << "internal data is empty" << endl;
        return;
    }
    for (const auto& r : logtable)
    {
        if ( r.empty() ) {
            out << "row is empty" << endl;
            continue;
        }
        out << endl;
        for (const auto& c : r) {
            out << c << " " << endl;
        }
    }
}

const std::vector<TagModel*> & LogParser::getTags() const
{
    return tags;
}

const std::vector<std::vector<std::string>> & LogParser::getTable() const
{
    return logtable;
}

void LogParser::reset()
{
    tags.clear();
    logtable.clear();
}

bool LogParser::run()
{
    if ( !(*this) ) {
        cout << "cant open file" << endl;
        return false;
    }

    assert( !tags.empty() && "no tags");

    // fill column names
    for(const auto& t : tags) {
        logtable.emplace_back();
        logtable.back().push_back(t->Name());
    }

    string value("");
    while ( logfile.peek() != EOF )
    {
        for (unsigned j = 0; j < tags.size(); j++)
        {
            value = next(*tags[j]);

            if ( not value.empty() ) {
                logtable[j].push_back(value);
            }
            else
                cout << "tag not found" << endl;
        }
    }

    return true;
}
