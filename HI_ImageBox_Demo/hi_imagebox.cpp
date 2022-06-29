#include "hi_imagebox.h"
#include "hi_graphicsview.h"

HI_ImageBox::HI_ImageBox():
    m_widget(nullptr)
{
}

HI_ImageBox::~HI_ImageBox()
{
    if(m_widget)
        m_widget->deleteLater();
}


QString HI_ImageBox::Version()
{
    return "HI_ImageBox V1.0.21724";
}


void HI_ImageBox::Init(QBoxLayout *panel)
{
    if(m_widget!=nullptr)
        return;
    m_widget = new HI_GraphicsView(nullptr);
    if(panel)
        panel->addWidget(m_widget);
    m_widget->Init(this);
}

void HI_ImageBox::SetImage(const QImage &image)
{
    m_image = image;
    m_widget->SetImage(image);
}

void HI_ImageBox::SetImage(const QString &image)
{
    QImage img = QImage(image);
    if(!img.isNull())
    {
        m_image = img;
        m_widget->SetImage(img);
    }
}
