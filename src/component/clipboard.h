#ifndef CLIPBOARD_H
#define CLIPBOARD_H

#include <QObject>
#include <QClipboard>
#include <QGuiApplication>

class ClipBoard : public QObject
{
    Q_OBJECT
public:
    explicit ClipBoard(QObject *parent = nullptr);

signals:

public slots:
    void setClipBoard(QString text);

private:
    QClipboard *cb;
};

#endif // CLIPBOARD_H
