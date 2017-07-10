#ifndef DLGLINEEDIT_H
#define DLGLINEEDIT_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
class DlgLineEdit : public QFrame
{
	Q_OBJECT
public:
	enum EnumElement
	{
		Label = 1,
		LineEdit = 2,
		ComboBox = 4
	};
public:
	DlgLineEdit(int ee = Label | LineEdit, QWidget *parent = 0);
	~DlgLineEdit();
	void SetTitle(QString qsTitle);
	void SetContent(QString qsContent);
	void SetPlaceholderText(QString qsPlaceholder);
	void SetList(QStringList qslList);

	QString Content() { return m_pLEContent->text(); }
	QString Type() { return m_pCBList->currentText(); }
private:
	QLabel *m_pLBTitle;
	QLineEdit *m_pLEContent;
	QComboBox *m_pCBList;
};

#endif // DLGLINEEDIT_H
