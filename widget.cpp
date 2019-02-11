#include "widget.h"
#include "ui_widget.h"

const int SZ_GRID = 24;

qreal alignToGrid(qreal coord)
{
    return round(coord / SZ_GRID) * SZ_GRID;
}

class MyRectItem : public QGraphicsRectItem
{
public:
    MyRectItem(const QRectF &rect, QGraphicsItem *parent = Q_NULLPTR) : QGraphicsRectItem(rect, parent)
    {
        setFlags(QGraphicsItem::ItemIsSelectable |
                 QGraphicsItem::ItemIsMovable |
                 QGraphicsItem::ItemSendsGeometryChanges);
    }
protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override
    {
        if (change == ItemPositionChange && scene())
        {
            QPointF newPos = value.toPointF();
            newPos.setX(alignToGrid(newPos.x()));
            newPos.setY(alignToGrid(newPos.y()));
            return newPos;
        }
        return QGraphicsRectItem::itemChange(change, value);
    }
};

class MyScene : public QGraphicsScene
{
public:
    MyScene(const int aWidth, const int aHeight) : QGraphicsScene(0, 0, aWidth, aHeight)
    {
    }
protected:
    void drawBackground(QPainter *painter, const QRectF &rect) override
    {
        qreal top = alignToGrid(rect.top());
        qreal left = alignToGrid(rect.left());
        painter->setPen(Qt::gray);
        for (qreal y = top; y <= rect.bottom(); y += SZ_GRID)
            for (qreal x = left; x <= rect.right(); x += SZ_GRID)
                painter->drawPoint(x, y);
    }
};

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);

    m_scene = new MyScene(3000, 2000);
    for (int i = 0; i < 10; i++)
    {
        MyRectItem* item = new MyRectItem(QRectF(i*SZ_GRID, i*SZ_GRID, 6*SZ_GRID, 4*SZ_GRID));
        m_scene->addItem(item);
        if (i == 0) m_first = item;
    }
    m_view = new QGraphicsView(m_scene);

    QVBoxLayout* vbox = new QVBoxLayout(this);
    vbox->addWidget(m_view);

}

Widget::~Widget()
{
    delete ui;
}

void Widget::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);
    m_first->ensureVisible();
}
