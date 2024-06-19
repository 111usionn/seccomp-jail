#include "clipboard.h"

ClipBoard::ClipBoard(QObject *parent)
    : QObject{parent}
{
    cb = QGuiApplication::clipboard();
}

void ClipBoard::setClipBoard(QString text)
{
    cb->setText(text);
}
