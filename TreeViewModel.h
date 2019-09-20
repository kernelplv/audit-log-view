#pragma once

#include <QStandardItemModel>
#include <vector>
#include <unordered_map>
#include <iostream>

class TreeViewModel : public QStandardItemModel
{
    Q_OBJECT

public:
    TreeViewModel(QObject* parent = nullptr);

    void addColumns(const std::vector<std::string>& );
    void addRow(const QString& sub, const std::vector<std::string>& );

    QHash<int, QByteArray> roleNames() const override;

private:
    std::unordered_map<int, std::string> columns;
    QStandardItem* getSub(const QString& subName);

    QHash<int, QByteArray> m_roleNameMapping;
};

