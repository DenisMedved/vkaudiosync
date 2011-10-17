#ifndef AUDIOITEMDELEGATE_H
#define AUDIOITEMDELEGATE_H

#include <QItemDelegate>

class AudioItemDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    explicit AudioItemDelegate(QObject *parent = 0);

	virtual void	paint ( QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const;

	QSize sizeHint ( const QStyleOptionViewItem & option, const QModelIndex & index ) const;
signals:

public slots:

};

#endif // AUDIOITEMDELEGATE_H
