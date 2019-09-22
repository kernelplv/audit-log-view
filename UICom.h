#pragma once

#include <QObject>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>
#include <QDebug>
#include <QQuickItem>
#include <string>
#include <algorithm>

#include "TreeViewModel.h"
#include "LogParser.h"

class UICom : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString AppName READ getAppName)

private:

    QString appname = "AudIt";

    QQmlApplicationEngine engine;
    QObject* qmlRoot;

    TreeViewModel* treelog;

public:
    explicit UICom(QObject *parent = nullptr);

    QString getAppName();

    Q_INVOKABLE
    bool processLog(QUrl);
    void processModel(const std::vector<std::vector<std::string>> table);

signals:
    void changedData(size_t idx);

public slots:
    void test();
};

