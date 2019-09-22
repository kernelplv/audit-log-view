#include "UICom.h"
#include "TagDefault.h"

UICom::UICom(QObject *parent)
    : QObject(parent)
{
    qDebug() << "UICom Initialize...";

    treelog = new TreeViewModel();

    engine.rootContext()->setContextProperty("logmodel", treelog);
    engine.rootContext()->setContextProperty("UICom", this);
    engine.load(QUrl(QStringLiteral("qrc:/WMain.qml")));

    if (engine.rootObjects().isEmpty())
        qDebug() << "no qml objects!";
    else
        qmlRoot = engine.rootObjects().first();

    qDebug() << "UICom Initialize OK";
}

QString UICom::getAppName()
{
    return appname;
}

bool UICom::processLog(QUrl logpath)
{
    LogParser parser(logpath.path().toStdString());

    if (!parser)  {
        std::cout << "Engine: cant open file";
        return false;
    }

    // NEXT STL TERRITORY

    parser.addTag<>("date", true, false);
    parser.addTag<>("desc", true, false);
    parser.addTag<>("hash", true, true);
    parser.process();

    processModel( parser.getTable() );


//    treelog->addColumns({"date", "desc", "hash"});

//    treelog->addRow("18:30", {"login", "success","1"});
//    treelog->addRow("18:30", {"exit", "success", "2"});
//    treelog->addRow("19:07", {"login", "failed", "3"});
//    treelog->addRow("login", {"complete", "description", "1.5"});


    return true;
}

void UICom::processModel(const std::vector<std::vector<std::string> > table)
{
    std::vector<std::string> headers;
    if ( !table.empty() )
    {
        for (const auto& c : table) {
            headers.push_back(c.front());
        }
    }

    treelog->addColumns( headers );

    //! todo: optimize
    std::vector<std::string> tmpRowData;
    size_t i = 0, tmpSize = table[0].size();

    while (tmpSize > ++i)
    {
        for (size_t j = 0; j < table.size(); j++)
        {
            tmpRowData.push_back(table[j][i]);
            emit changedData(j);
        }
        treelog->addRow("", tmpRowData);
        tmpRowData.clear();
    }

}

void UICom::test()
{
    qmlRoot->setProperty("title", getAppName());
}

