#ifndef MODELSOURCELIST_H
#define MODELSOURCELIST_H

#include <QAbstractListModel>
#include <vector>
#include <QHash>
class ResourceData
{
public:
	ResourceData(const QString& qsGuid,
		const QString& qsName,
		const int& nType,
		const QString& qsDiscription,
		const QString& qsResourceid,
		const QString& qsPNG)
		:m_qsGuid(qsGuid),
		m_qsName(qsName),
		m_nType(nType),
		m_qsDiscription(qsDiscription),
		m_qsResourceid(qsResourceid),
		m_qsPng(qsPNG)
	{	}

	ResourceData()
	{
		m_qsGuid = "";
		m_qsName = "";
		m_nType = -1;
		m_qsDiscription = "";
		m_qsResourceid = "";
		m_qsPng = "";
	}

	void SetData(const QString& qsGuid,
		const QString& qsName,
		const int& nType,
		const QString& qsDiscription,
		const QString& qsResourceid,
		const QString& qsPNG)
	{
		m_qsGuid = qsGuid;
		m_qsName = qsName;
		m_nType = nType;
		m_qsDiscription = qsDiscription;
		m_qsResourceid = qsResourceid;
		m_qsPng = qsPNG;
	}

	QString  Guid() const { return m_qsGuid; }
	QString  Name() const { return m_qsName; }
	int Type() const { return m_nType; }
	QString  Discription() const { return m_qsDiscription; }
	QString  Resourceid() const { return m_qsResourceid; }
	QString PNG() const { return m_qsPng; }
	QVariant  obj;//当前model的组件对象
private:
	QString m_qsGuid;
	QString m_qsName;
	int m_nType;
	QString m_qsDiscription;
	QString m_qsResourceid;
	QString m_qsPng;
};

class ModelReourceList : public QAbstractListModel
{
	Q_OBJECT
public:
	enum datatype {
		guid = 0x0100 + 1,
		name,
		type,
		discription,
		resourceid,
		png
	};
	ModelReourceList(QObject *parent = 0);
	~ModelReourceList();
	void Remove(int index);
	void Append(ResourceData & rd);
	void Clear();

	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
	int rowCount(const QModelIndex &parent = QModelIndex()) const;
	QHash<int, QByteArray> roleNames()  const;
	void setcuritem(int index, QVariant  j)
	{
		m_datas[index].obj = j;
	}
private:
	//model数据集合 
	std::vector<ResourceData>  m_datas;
};

#endif // MODELSOURCELIST_H
