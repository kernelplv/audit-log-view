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

    parser.reset();
    parser.addTag<>("Date", true, false);
    parser.addTag<>("Description", true, false);
    parser.addTag<>("Hash", true, true);
    parser.run();

    processModel( parser.getTable() );

    return true;
}

void UICom::processModel(const std::vector<std::vector<std::string> > table)
{
    treelog->reset();

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
    size_t r = 0, tmpSize = table[0].size();

    while (tmpSize > ++r)
    {
        for (size_t c = 1; c < table.size(); c++)
        {
            tmpRowData.push_back(table[c][r]);

        }
        treelog->addRow(table[0][r].c_str(), tmpRowData);
        tmpRowData.clear();
    }
    emit changedData(0);

}

void UICom::test()
{
    qmlRoot->setProperty("title", getAppName());
}

