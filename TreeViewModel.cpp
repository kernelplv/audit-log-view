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

    for (auto i = col_names.begin() +1; i != col_names.end(); i++, idx++)
    {
        columns.push_back(*i);
        m_roleNameMapping[idx] = i->c_str();
    }

}

QHash<int, QByteArray> TreeViewModel::roleNames() const
{
    return m_roleNameMapping;
}

void TreeViewModel::addRow(const QString& node, const std::vector<std::string>& values)
{
    //assert (columns.size() >= values.size() && "columns count && data count not equal");
    if ( not values.empty() )
    {
        auto subRow = new QStandardItem(values[0].c_str());

        int role = Qt::UserRole + 1;
        for ( auto i = values.begin() + 1; i != values.end(); i++, role++)
        {
            subRow->setData(i->c_str(), role);
        }
        QStandardItem* row = getNode(node);
        row->appendRow(subRow);
    }
    else
        getNode(node);
}

void TreeViewModel::reset()
{
    clear();
    columns.clear();
    m_roleNameMapping.clear();
}

QStringList TreeViewModel::getColumnNames()
{
    QStringList names;
    for (const auto& n : columns) {
        names.append(n.c_str());
    }

    return names;
}

QStandardItem* TreeViewModel::getNode(const QString& nodeName)
{
    QStandardItem* row;
    auto rows = this->findItems(nodeName , Qt::MatchRecursive);

    if (rows.count() > 0) {
        row = rows.at(0);
    }
    else
    {
        row = new QStandardItem(nodeName);
        this->appendRow(row);
    }
    return row;
}
