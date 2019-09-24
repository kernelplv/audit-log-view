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

    QString node("");
    while (tmpSize > ++r)
    {
        for (size_t c = 0; c < table.size(); c++) {
            if ( c == 0 or c == 1) //! todo: group or not group
            {
                if ( node.isEmpty() ) {
                    treelog->addRow(table[c][r].c_str());
                    node = table[c][r].c_str();
                }
                else {
                    treelog->addRow(node,{table[c][r]});
                    node = table[c][r].c_str();
                }
            }
            else
                tmpRowData.push_back(table[c][r]);
        }
        treelog->addRow(node, tmpRowData);
        tmpRowData.clear();
        node.clear();
    }
    emit changedData(0);

}

void UICom::test()
{
    qmlRoot->setProperty("title", getAppName());
}

