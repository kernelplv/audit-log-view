#pragma once

#include <QStandardItemModel>

class TreeViewModel : public QStandardItemModel
{
    Q_OBJECT

public:
    TreeViewModel(QObject* parent = nullptr);

    enum Roles
    {
        Name = Qt::DisplayRole,
        Description = Qt::WhatsThisRole,
        Hash = Qt::UserRole + 1
    };

    QHash<int, QByteArray> roleNames() const override;
private:
    void addRow(const QString& sub, const QString name, const QString& description);
    QStandardItem* getSub(const QString& subName);
    QHash<int, QByteArray> m_roleNameMapping;
};

