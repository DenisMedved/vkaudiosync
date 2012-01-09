#ifndef ABOUT_H
#define ABOUT_H

#include <QDialog>
#include "ui_about.h"

namespace Ui
{
class About;
}

class About : public QDialog
{
	Q_OBJECT

private:
	Ui::About *ui;

public:
	explicit About(QWidget *parent = 0);
	~About();

signals:

public slots:

};

#endif // ABOUT_H
