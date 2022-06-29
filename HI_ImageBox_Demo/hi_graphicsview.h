#ifndef HI_GRAPHICSVIEW_H
#define HI_GRAPHICSVIEW_H

#include <QBoxLayout>
#include <QGraphicsView>
#include <qevent.h>

class HI_ImageBox;

class HI_GraphicsView:public QGraphicsView
{
    Q_OBJECT

public:
    HI_GraphicsView(QWidget *parent = 0);
    ~HI_GraphicsView();

    void Init(HI_ImageBox * imageBox){m_imageBox = imageBox;}

    void SetImage(const QImage & image);

protected:
    virtual void wheelEvent(QWheelEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    virtual void mouseDoubleClickEvent(QMouseEvent *event) override;

public slots:
    void ZoomIn();
    void ZoomOut();
    void Zoom(float scaleFactor);
    void Translate(QPointF delta);

private:
    bool m_isTranslate;
    QPoint m_lastMousePos;

    HI_ImageBox * m_imageBox;
    QGraphicsScene * m_scene;
    QGraphicsPixmapItem * m_imageItem;
};

#endif // HI_GRAPHICSVIEW_H
