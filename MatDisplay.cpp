#include "MatDisplay.h"

matDisplay::matDisplay(QWidget *parent) : QLabel(parent)
{
    this->setMouseTracking(true);
}

matDisplay::~matDisplay()
{

}



void matDisplay::mousePressEvent(QMouseEvent *mouse_event)
{
    if(mouse_event->button() == Qt::LeftButton)
    {
        printf("LeftButton\n");
        QPoint mouse_pos = mouse_event->pos();

        if(mouse_pos.x() <= this->size().width() && mouse_pos.y() <= this->size().height())
        {
            if(mouse_pos.x() >= 0 && mouse_pos.x() >= 0)
            {
                emit sendMousePosition(mouse_pos);
            }
        }
    }
}


