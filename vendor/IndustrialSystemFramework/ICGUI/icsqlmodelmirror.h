#ifndef ICSQLMODELMIRROR_H
#define ICSQLMODELMIRROR_H

#include <QAbstractTableModel>
#include <QMap>
#include <QStringList>

class ICSqlModelMirrorData
{
public:
    int FieldCount() const { return values_.size();}
    QVariant FieldValue(int index) const { return values_.at(index);}
    void SetFieldValue(int index, const QVariant& v) { values_[index] = v;}
    void AppendFieldValue(const QVariant& v) { values_.append(v);}
    void ClearValues() { values_.clear();}
private:
    QVariantList values_;

};

typedef  QList<ICSqlModelMirrorData> ICSqlModelMirrorDatas;
class ICSqlModelMirror : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit ICSqlModelMirror(QObject *parent = 0);
    virtual int	columnCount (const QModelIndex & parent = QModelIndex()) const;
    virtual QVariant data (const QModelIndex & index, int role = Qt::DisplayRole) const;
    virtual int rowCount ( const QModelIndex & parent = QModelIndex() ) const;

    void AppendData(const ICSqlModelMirrorData &data);
    void ClearData() { datas_.clear();}
    void SyncDatasFromDB(const QString& tableName);

    int DataSizeLimit() const { return dataSizeLimit_;}
    void SetDataSizeLimit(int limit) { dataSizeLimit_ = limit; }
    void fetchMore(const QModelIndex &parent);

    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    bool setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role = Qt::DisplayRole);

signals:

public slots:

private:
    ICSqlModelMirrorDatas datas_;
    int dataSizeLimit_;
    QStringList colSection_;
    int colCount_;

};

#endif // ICSQLMODELMIRROR_H
