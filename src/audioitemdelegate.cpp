
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

	QString artistStr = "Mauris dignissim ";
	QString titleStr = "title title";
	QRect selectedRect(x,y,w,h);
	if (option.state & (QStyle::State_Selected | QStyle::State_MouseOver) )
	{
		painter->fillRect(selectedRect,QColor("#E1E7ED"));
	} else {
		painter->fillRect(selectedRect, QColor("#ffffff"));
	}

	QFont font = option.font;
	QFontMetrics  fm = QFontMetrics(font);
	int leading = fm.leading();

	QPen pen(Qt::SolidLine);

	qreal height = 0;
	int artistLineWidth = 30 * w / 100;

	//draw artist
	pen.setColor(QColor("#2B587A"));
	painter->setPen(pen);

	font.setPixelSize(11);
	font.setFamily("	tahoma,arial,verdana,sans-serif,Lucida Sans");
	font.setBold(true);

	QTextLayout artist;
	artist.setFont(font);
	artist.setText(artistStr);
	artist.beginLayout();
	    QTextLine line = artist.createLine();
	    line.setLineWidth(artistLineWidth);
	    height += leading;
	    line.setPosition(QPointF(0, y+height));
	artist.endLayout();

	artist.draw(painter,QPoint(15,h/3));

	//draw title
	pen.setColor(Qt::black);
	painter->setPen(pen);

	font.setBold(false);

	int titleLineWidth = 30 * w / 100;
	QTextLayout title;
	title.setFont(font);
	title.setText(titleStr);
	title.beginLayout();
	    line = title.createLine();
	    line.setLineWidth(titleLineWidth);
	    height += leading;
	    line.setPosition(QPointF(0, y+height));
	title.endLayout();

	title.draw(painter,QPoint(15 + x+artistLineWidth ,h/3));

	pen.setStyle(Qt::DashLine);
	painter->setPen(pen);
	painter->drawLine(x ,y+h,x + w,y + h);
}


QSize AudioItemDelegate::sizeHint ( const QStyleOptionViewItem & option, const QModelIndex & index ) const
{
	if (!index.isValid())
		return QSize();

	return QSize(option.rect.width(),40);
}
