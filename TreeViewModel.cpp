#include "TreeViewModel.h"

TreeViewModel::TreeViewModel(QObject *parent)
    : QStandardItemModel { parent }
{

    m_roleNameMapping[Roles::Name] = "name";
    m_roleNameMapping[Roles::Description] = "desc";
    m_roleNameMapping[Roles::Hash] = "hash";


    addRow("18:30","login", "success");
    addRow("18:30","exit", "success");
    addRow("19:07", "login", "failed");
    addRow("login", "complete", "description");

}

QHash<int, QByteArray> TreeViewModel::roleNames() const
{
    return m_roleNameMapping;
}

void TreeViewModel::addRow(const QString &sub, const QString name, const QString &description)
{
    auto subRow = new QStandardItem (name);
    subRow->setData(description, Roles::Description);

    QStandardItem* row = getSub(sub);
    row->appendRow(subRow);
}

QStandardItem *TreeViewModel::getSub(const QString &subName)
{
    QStandardItem* row;
    auto rows = findItems( subName );

    if (rows.count() > 0)
    {
        row = rows.at(0);
    }
    else
    {
        row = new QStandardItem(subName);
        appendRow( row );
    }
    return row;
}
