#include "TreeViewModel.h"

TreeViewModel::TreeViewModel(QObject *parent)
    : QStandardItemModel { parent }
{

}

void TreeViewModel::addColumns(const std::vector<std::string> & col_names)
{
    assert (col_names.empty() == false && "column array is empty");

    int idx = Qt::UserRole +1;

    columns.push_back(col_names[0]);
    m_roleNameMapping[Qt::DisplayRole] = col_names[0].c_str();

    for (size_t i = 1; i < col_names.size(); i++, idx++)
    {
        columns.push_back(col_names[i]);
        m_roleNameMapping[idx] = col_names[i].c_str();
    }

}

QHash<int, QByteArray> TreeViewModel::roleNames() const
{
    return m_roleNameMapping;
}

void TreeViewModel::addRow(const QString& sub, const std::vector<std::string>& values)
{
    assert (columns.size() >= values.size() && "columns count && data count not equal");

    auto subRow = new QStandardItem(values[0].c_str());

    int role = Qt::UserRole + 1;
    for ( size_t i = 1; i < values.size(); i++, role++)
    {
        subRow->setData(values[i].c_str(), role);
    }

    QStandardItem* row = getSub(sub);
    row->appendRow(subRow);
}

QStringList TreeViewModel::getColumnNames()
{
    QStringList names;
    for (const auto& n : columns)
    {
        names.append(n.c_str());
    }

    return names;
}

QStandardItem* TreeViewModel::getSub(const QString& subName)
{
    QStandardItem* row;
    auto rows = findItems( subName , Qt::MatchRecursive);

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
