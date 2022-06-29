#ifndef HI_IMAGEBOX_H
#define HI_IMAGEBOX_H

#include <QtCore/qglobal.h>

//#if defined(HI_IMAGEBOX_LIBRARY)
//#  define HI_IMAGEBOX_EXPORT Q_DECL_EXPORT
//#else
//#  define HI_IMAGEBOX_EXPORT Q_DECL_IMPORT
//#endif

#include <QImage>
#include <QBoxLayout>

class HI_GraphicsView;

/**
 * @brief The HI_ImageBox class
 * 图片展示控件，封装了图片加载，放缩，选点操作
 */
class  HI_ImageBox:public QObject
{
    Q_OBJECT

public:
    HI_ImageBox();
    ~HI_ImageBox();


    /**
     * @brief 获取当前控件版本
     * @return
     */
    QString Version();

    /**
     * @brief 初始化
     * @param panel: 展示图片的容器
     */
    void Init(QBoxLayout * panel);

    /**
     * @brief 获取当前显示的图片
     * @return 当前显示的图片
     */
    const QImage & GetImage(){return m_image;}

    /**
     * @brief 设置图片
     * @param image: 要显示的图片
     */
    void SetImage(const QImage & image);

    /**
     * @brief 设置图片
     * @param image: 要展示图片的地址
     */
    void SetImage(const QString & image);


    //信号
signals:

    /**
     * @brief 点击图片的信号
     * @param x: 点击的图片X坐标
     * @param y: 点击的图片Y坐标
     */
    void ImageClick(int x,int y);

    //变量
private:
    HI_GraphicsView * m_widget;   /**< 用于操作绘图的控件*/
    QImage m_image;               /**< 当前显示图片*/
    friend class HI_GraphicsView;
};

#endif // HI_IMAGEBOX_H
