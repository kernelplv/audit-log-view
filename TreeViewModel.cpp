#include "TreeViewModel.h"

TreeViewModel::TreeViewModel(QObject *parent)
    : QStandardItemModel { parent }
{

}

void TreeViewModel::addColumns(const std::vector<std::string> & col_names)
{
    int idx = Qt::UserRole +1;

    columns[Qt::DisplayRole] = col_names[0];
    m_roleNameMapping[Qt::DisplayRole] = col_names[0].c_str();

    for (size_t i = 1; i < col_names.size(); i++, idx++)
    {
        columns[idx] = col_names[i];
        m_roleNameMapping[idx] = col_names[i].c_str();
    }


}

QHash<int, QByteArray> TreeViewModel::roleNames() const
{
    return m_roleNameMapping;
}

void TreeViewModel::addRow(const QString& sub, const std::vector<std::string>& values)
{
    if ( columns.size() < values.size() ) {
        std::cout << "columns count && data count not equal" << std::endl;
        return;
    }

    auto subRow = new QStandardItem(values[0].c_str());
    for ( size_t i = 1, role = Qt::UserRole + 1; i < values.size(); i++, role++)
    {
        subRow->setData(values[i].c_str(), role);
    }

    QStandardItem* row = getSub(sub);
    row->appendRow(subRow);
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
