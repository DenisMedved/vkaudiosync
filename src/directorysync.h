#ifndef DIRECTORYSYNC_H
#define DIRECTORYSYNC_H

#include <QObject>

class DirectorySync : public QObject
{
    Q_OBJECT
public:
    explicit DirectorySync(QObject *parent = 0);

signals:

public slots:

};

#endif // DIRECTORYSYNC_H
