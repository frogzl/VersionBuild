#include "dlgresourceselector.h"
#include <QStandardItemModel>
#include <QHeaderView>

DlgResourceSelector::DlgResourceSelector(QWidget *parent)
	: QDialog(parent)
{
	setWindowTitle(QString::fromLocal8Bit("资源选择"));
	resize(QSize(300, 400));

	m_BtnAdd = new QPushButton();
	m_BtnAdd->setText(QString::fromLocal8Bit("添加"));
	m_BtnCancle = new QPushButton();
	m_BtnCancle->setText(QString::fromLocal8Bit("取消"));
	QHBoxLayout *layBtn = new QHBoxLayout();
	layBtn->addWidget(m_BtnAdd);
	layBtn->addWidget(m_BtnCancle);
	layBtn->addStretch();

	m_TV = new QTableView();
	QVBoxLayout *layLeft = new QVBoxLayout();
	layLeft->addLayout(layBtn);
	layLeft->addWidget(m_TV);

	m_RightArea = new QWidget();
	m_MainLayout = new QHBoxLayout();
	m_MainLayout->addLayout(layLeft);
	m_MainLayout->addWidget(m_RightArea);

	m_MainLayout->setStretchFactor(layLeft, 1);
	m_MainLayout->setStretchFactor(m_RightArea, 1);
	setLayout(m_MainLayout);

	// 属性设置========================================
	m_BtnAdd->setFixedSize(QSize(60, 25));
	m_BtnCancle->setFixedSize(QSize(60, 25));

	QStandardItemModel *sim = new QStandardItemModel();
	sim->setHorizontalHeaderItem(0, new QStandardItem(QString::fromLocal8Bit("类型")));

	m_TV->setModel(sim);
	m_TV->setColumnWidth(0, 50);
	m_TV->setStyleSheet(QString(""));
	m_TV->setSelectionMode(QAbstractItemView::SingleSelection);
	m_TV->setEditTriggers(QAbstractItemView::NoEditTriggers);
	m_TV->setSelectionBehavior(QAbstractItemView::SelectRows);
	m_TV->horizontalHeader()->setStretchLastSection(true);
	m_TV->verticalHeader()->setVisible(false);
}

DlgResourceSelector::~DlgResourceSelector()
{

}
