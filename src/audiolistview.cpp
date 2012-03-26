
#include "audiolistview.h"

AudioListView::AudioListView(QWidget *parent /*= 0*/) :
	QListView(parent)
{
}

void AudioListView::mouseReleaseEvent ( QMouseEvent * e )
{
	QModelIndex index = indexAt(e->pos());
	if (index.isValid()) {
		unsigned short status = model()->data(index,AudioListModel::ROLE_STATUS).toInt();
		if (status != AudioItem::STATUS_SYNCHRONIZED) {
			if (status == AudioItem::STATUS_NOTSYNCHNIZE) {
				status = AudioItem::STATUS_UNDEFINED;
			} else {
				status = AudioItem::STATUS_NOTSYNCHNIZE;
			}
		}
		model()->setData(index,QVariant(status),AudioListModel::ROLE_STATUS);
	}
	QListView::mouseReleaseEvent(e);
}
