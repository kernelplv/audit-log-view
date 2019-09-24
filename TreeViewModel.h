#pragma once

#include <QStandardItemModel>
#include <vector>
#include <iostream>

class TreeViewModel : public QStandardItemModel
{
    Q_OBJECT
    Q_PROPERTY(QStringList ColumnNames READ getColumnNames)
public:
    TreeViewModel(QObject* parent = nullptr);

    void addColumns(const std::vector<std::string>& );
    void addRow(const QString& node, const std::vector<std::string>& values  = {} );
    void reset();

    QStringList            getColumnNames();
    QHash<int, QByteArray> roleNames() const override;

private:
    std::vector<std::string> columns;

    QStandardItem*         getNode(const QString& nodeName);
    QHash<int, QByteArray> m_roleNameMapping;
};

