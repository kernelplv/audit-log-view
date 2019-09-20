#include "UICom.h"
#include "TagCommon.h"

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
        qDebug() << "Engine: cant open file";
        return false;
    }

    //  NEXT STL TERRITORY


    treelog->addColumns({"date", "desc", "hash"});

    treelog->addRow("18:30", {"login", "success","1"});
    treelog->addRow("18:30", {"exit", "success", "2"});
    treelog->addRow("19:07", {"login", "failed", "3"});
    treelog->addRow("login", {"complete", "description", "1.5"});

    parser.addTag<TagCommon>("TestColumn1", true, false);
    parser.addTag<TagCommon>("TestColumn2", true, false);
    parser.addTag<TagCommon>("TestColumn3", true, true);
    parser.process();
    parser.printInternal();
    return true;
}

void UICom::test()
{
    qmlRoot->setProperty("title", getAppName());
}

