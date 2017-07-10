#ifndef VERSIONBUILD_H
#define VERSIONBUILD_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QTableView>
#include <QTabWidget>

class VersionBuild : public QMainWindow
{
	Q_OBJECT
public:
	VersionBuild(QWidget *parent = 0);
	~VersionBuild();

private slots:
	void SlotTabBarClicked(int nIndex);
	void SlotCreateProduct();
	void SlotCreateGit();
	void SlotCreateHost();
private:
	QVBoxLayout *m_MainLayout;

	QTabWidget *m_TabWidget;
	QTableView *m_TableView;

};

#endif // VERSIONBUILD_H
