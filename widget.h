#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QVBoxLayout>

namespace Ui {
class Widget;
}

class MyRectItem;
class MyScene;

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();
protected:
    void showEvent(QShowEvent *event) override;
private:
    Ui::Widget *ui;
    MyScene* m_scene = nullptr;
    QGraphicsView* m_view = nullptr;
    MyRectItem* m_first = nullptr;
};

#endif // WIDGET_H
