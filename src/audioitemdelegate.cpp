
#include <QDebug>
#include <QPainter>

#include "audioitemdelegate.h"

AudioItemDelegate::AudioItemDelegate(QObject *parent) :
    QItemDelegate(parent)
{
}

void AudioItemDelegate::paint ( QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const
{
	qDebug() << index.data(1).toString();
	painter->drawText(option.rect,0,index.data(1).toString());

	//( const QRect & rectangle, int flags, const QString & text, QRect * boundingRect = 0 )
}


QSize AudioItemDelegate::sizeHint ( const QStyleOptionViewItem & option, const QModelIndex & index ) const
{
	return QSize(100,20);
}
