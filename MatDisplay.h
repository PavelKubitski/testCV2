#ifndef MATDISPLAY_H
#define MATDISPLAY_H


#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QMouseEvent>

class matDisplay : public QLabel
{
    Q_OBJECT
public:
    matDisplay(QWidget *parent = 0);
    ~matDisplay();

protected:

    void mousePressEvent(QMouseEvent *mouse_event);

signals:
    void sendMousePosition(QPoint& );



};
#endif // MATDISPLAY_H
