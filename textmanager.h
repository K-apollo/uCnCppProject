#ifndef TEXTMANAGER_H
#define TEXTMANAGER_H

#include <QString>
#include <QObject>

class TextManager
{
public:
    TextManager();
    QString getText(int index) const;

private:
    QString texts[11];  // 0부터 10까지 사용할 수 있는 배열
};

#endif // TEXTMANAGER_H
