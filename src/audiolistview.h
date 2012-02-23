#ifndef AUDIOLISTVIEW_H
#define AUDIOLISTVIEW_H

#include <QListView>
#include <QMouseEvent>

#include "audiolistmodel.h"

class AudioListView : public QListView
{
	Q_OBJECT
public:
	explicit AudioListView(QWidget *parent = 0);

protected:
	virtual void mouseReleaseEvent ( QMouseEvent * e );

};

#endif // AUDIOLISTVIEW_H
