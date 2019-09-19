#include "UICom.h"
#include "TreeViewModel.h"
#include "TagCommon.h"

UICom::UICom(QObject *parent)
    : QObject(parent)
{
    qDebug() << "UICom Initialize...";

    TreeViewModel* mLog = new TreeViewModel();

    engine.rootContext()->setContextProperty("logmodel", mLog);
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

    //  NEXT STL TERRITORY

    if (!parser)  {
        qDebug() << "Engine: cant open file";
        return false;
    }

    //
    parser.addTag<TagCommon>("TestColumn1", true, false);   // example: "value1 ... value2" If open tag is space " "
    parser.addTag<TagCommon>("TestColumn2", true, false);
    parser.addTag<TagCommon>("TestColumn3", true, true);   // example: "value1 ... value2" If close tag is space " "
    parser.process();
    parser.printInternal();
    return true;
}

void UICom::test()
{
    qmlRoot->setProperty("title", getAppName());
}

