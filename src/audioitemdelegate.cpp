
#include <QDebug>
#include <QPainter>
#include <QTextLayout>
#include <QTextLine>
#include "audioitemdelegate.h"

AudioItemDelegate::AudioItemDelegate(QObject *parent) :
    QItemDelegate(parent)
{
}

void AudioItemDelegate::paint ( QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const
{
	int x = option.rect.x() -1 ;
	int y = option.rect.y() -1;
	int w = option.rect.width() -1;
	int h = option.rect.height()-1;

	QFont font = option.font;
	font.setPixelSize(11);
	font.setFamily("	tahoma,arial,verdana,sans-serif,Lucida Sans");
	font.setBold(true);
	QFontMetrics  fm = QFontMetrics(font);

	QTextLayout artist;
	artist.setFont(font);
	artist.setText(index.data(1).toString());
	QPen pen(Qt::SolidLine);
	pen.setColor(QColor("#2B587A"));
	painter->setPen(pen);
	artist.beginLayout();
	int leading = fm.leading();
	qreal height = 0;
	int lineWidth = w - 50;
	while (1)
	{
	    QTextLine line = artist.createLine();
	    if (!line.isValid())
		break;

	    line.setLineWidth(lineWidth);
	    height += leading;
	    line.setPosition(QPointF(0, y+height));
	    height += line.height();
	}

	artist.endLayout();
	artist.draw(painter,QPoint(15,10));


	pen.setStyle(Qt::DashLine);
	painter->setPen(pen);
	painter->drawLine(x ,y+h,x + w,y + h);
	/*
	painter->drawLine(option.rect.x(),option.rect.y(), option.rect.x() + option.rect.width(),option.rect.y() + option.rect.height());
	painter->drawLine(option.rect.x() + option.rect.width(),option.rect.y() , option.rect.x(),option.rect.y() + option.rect.height());
	*/
}


QSize AudioItemDelegate::sizeHint ( const QStyleOptionViewItem & option, const QModelIndex & index ) const
{
	if (!index.isValid())
		return QSize();

	return QSize(option.rect.width(),40);
}
