#include "modelresourcelist.h"

ModelReourceList::ModelReourceList(QObject *parent)
	: QAbstractListModel(parent)
{

}

ModelReourceList::~ModelReourceList()
{

}
void ModelReourceList::Append(ResourceData& rd)
{
	beginInsertRows(QModelIndex(), rowCount(), rowCount());
	m_datas.push_back(rd);
	endInsertRows();
}

void ModelReourceList::Clear()
{
	beginRemoveRows(QModelIndex(), 0, m_datas.size());
	m_datas.clear();
	endRemoveRows();
}

void  ModelReourceList::Remove(int index)
{
	beginRemoveRows(QModelIndex(), index, index);
	m_datas.erase(m_datas.begin() + index);
	endRemoveRows();
}

int ModelReourceList::rowCount(const QModelIndex &parent) const
{
	Q_UNUSED(parent);
	return m_datas.size();
}
QVariant ModelReourceList::data(const QModelIndex &index, int role)  const
{
	if (index.row() < 0 || index.row() >= m_datas.size())
	{
		return QVariant();
	}
	const ResourceData& d = m_datas[index.row()];
	if (role == guid)
		return d.Guid();
	else if (role == name)
		return d.Name();
	else if (role == type)
		return d.Type();
	else if (role == discription)
		return d.Discription();
	else if (role == resourceid)
		return d.Resourceid();
	else if (role == png)
		return d.PNG();
	else
		return QVariant();
}

QHash<int, QByteArray> ModelReourceList::roleNames() const
{
	QHash<int, QByteArray>  d;
	d[guid] = "guid";
	d[name] = "name";
	d[type] = "type";
	d[discription] = "discription";
	d[resourceid] = "resourceid";
	d[png] = "png";
	return  d;
}
