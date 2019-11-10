#ifndef MINIGAMES_H
#define MINIGAMES_H

#include <QObject>

class Minigames : public QObject
{
    Q_OBJECT
public:
    explicit Minigames(QObject *parent = nullptr);

signals:

public slots:
};

#endif // MINIGAMES_H
