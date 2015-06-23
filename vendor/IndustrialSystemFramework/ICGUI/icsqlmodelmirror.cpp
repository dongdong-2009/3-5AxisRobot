#include "icsqlmodelmirror.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>

ICSqlModelMirror::ICSqlModelMirror(QObject *parent) :
    QAbstractTableModel(parent),
    dataSizeLimit_(120),
    colCount_(0)
{
}

int ICSqlModelMirror::columnCount(const QModelIndex &parent) const
{
    if(parent.isValid()) return 0;
    return colCount_;
    int row = parent.row();
    if(row  >= 0 && row < datas_.size())
    {
        return datas_.at(row).FieldCount();
    }
    return 0;
}

int ICSqlModelMirror::rowCount(const QModelIndex &parent) const
{
    if(parent.isValid()) return 0;
    return datas_.size();
}

QVariant ICSqlModelMirror::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || role != Qt::DisplayRole)
        return QVariant();
    int row = index.row();
    if(row >= 0 && row < datas_.size())
    {
        int col = index.column();
        if(col < datas_.at(row).FieldCount())
        {
            return datas_.at(row).FieldValue(col);
        }
    }
    return QVariant();
}

void ICSqlModelMirror::AppendData(const ICSqlModelMirrorData &data)
{
    datas_.prepend(data);
    if(datas_.size() > DataSizeLimit())
    {
        datas_.pop_back();
    }
}

void ICSqlModelMirror::SyncDatasFromDB(const QString &tableName)
{
    QSqlQuery query;
    query.exec(QString("SELECT * FROM %1 ORDER BY id ASC").arg(tableName));
    ICSqlModelMirrorData data;
    QSqlRecord record;
    ClearData();
    while(query.next())
    {
        record = query.record();
        data.ClearValues();
        for(int i = 0; i != record.count(); ++i)
        {
            data.AppendFieldValue(record.value(i));
        }
        AppendData(data);
    }
    colCount_ = record.count();
    reset();
}

void ICSqlModelMirror::fetchMore(const QModelIndex &parent)
{
    reset();
}

QVariant ICSqlModelMirror::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role != Qt::DisplayRole)
    {
        return QVariant();
    }
    if(orientation == Qt::Vertical)
    {
        return section + 1;
    }
    else
    {
        if(colSection_.size() < section)
        {
            return "";
        }
        return colSection_.at(section);
    }
}

bool ICSqlModelMirror::setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role)
{
    Q_UNUSED(role)
    if(orientation == Qt::Vertical)
    {
        return QAbstractTableModel::setHeaderData(section, orientation, value, role);
    }
    else
    {
        while(colSection_.size() <= section)
        {
            colSection_.append("");
        }
        colSection_[section] = value.toString();
        emit headerDataChanged(orientation, section, section);
        return true;
    }
}
