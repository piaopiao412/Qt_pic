#include "hi_graphicsview.h"

#include <QGraphicsPixmapItem>
#include "hi_imagebox.h"

HI_GraphicsView::HI_GraphicsView(QWidget *parent):
    QGraphicsView(parent),
    m_isTranslate(false),
    m_scene(new QGraphicsScene()),
    m_imageItem(new QGraphicsPixmapItem())
{
    m_scene->addItem(m_imageItem);
    setScene(m_scene);

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setRenderHint(QPainter::Antialiasing);

    setSceneRect(INT_MIN/2, INT_MIN/2, INT_MAX, INT_MAX);
    setTransformationAnchor(QGraphicsView::AnchorViewCenter);

    centerOn(0, 0);
}

HI_GraphicsView::~HI_GraphicsView()
{
    m_scene->deleteLater();
    delete m_imageItem;
}

void HI_GraphicsView::SetImage(const QImage &image)
{
    m_imageItem->setPixmap(QPixmap::fromImage(image));

    QPoint newCenter(image.width() / 2 ,image.height()/2);

    //设置scene中心到图像中点
    centerOn(newCenter);

    show();
}

void HI_GraphicsView::wheelEvent(QWheelEvent *event)
{
    // 滚轮的滚动量
    QPoint scrollAmount = event->angleDelta();
    // 正值表示滚轮远离使用者放大负值表示朝向使用者缩小
    scrollAmount.y() > 0 ? ZoomIn() : ZoomOut();
}

void HI_GraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    if(m_isTranslate)
    {
        //获取
        QPointF mouseDelta = event->pos()-m_lastMousePos;
        Translate(mouseDelta);
    }
    m_lastMousePos = event->pos();
    QGraphicsView::mouseMoveEvent(event);
}

void HI_GraphicsView::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        m_isTranslate = true;
        m_lastMousePos = event->pos();
    }
    else if(event->button()==Qt::RightButton)
    {
        QPointF point = mapToScene(event->pos());
        //只有点击图片时才发送
        if (scene()->itemAt(point, transform()) != NULL)
        {
            emit m_imageBox->ImageClick(point.x(),point.y());
        }
    }

    QGraphicsView::mousePressEvent(event);
}

void HI_GraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
        m_isTranslate = false;

    QGraphicsView::mouseReleaseEvent(event);
}

void HI_GraphicsView::mouseDoubleClickEvent(QMouseEvent *event)
{
    centerOn(m_imageItem->pixmap().width()/2,m_imageItem->pixmap().height()/2);
    QGraphicsView::mouseDoubleClickEvent(event);
}

void HI_GraphicsView::ZoomIn()
{
    Zoom(1.1);
}

void HI_GraphicsView::ZoomOut()
{
    Zoom(0.9);
}

void HI_GraphicsView::Zoom(float scaleFactor)
{
    // 防止过小或过大
    qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
    if (factor < 0.07 || factor > 100)
        return;

    scale(scaleFactor, scaleFactor);
}

void HI_GraphicsView::Translate(QPointF delta)
{
    int w = viewport()->rect().width();
    int h = viewport()->rect().height();
    QPoint newCenter(w / 2. - delta.x()+0.5,  h / 2. - delta.y()+0.5);
    centerOn(mapToScene(newCenter));
}
