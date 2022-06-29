#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_imageBox.Init(ui->verticalLayout);
//    connect(&m_imageBox,&HI_ImageBox::ImageClick,this,&MainWindow::ActImageClick);

    connect(ui->pushButtonOpenCamera,&QPushButton::pressed,[this]{
        QString filename = QFileDialog::getOpenFileName();
        if(filename.isEmpty())
            return;
        m_imageBox.SetImage(filename);
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

//void MainWindow::ActImageClick(int x, int y)
//{
//    QString pos = QString("x:%1 y:%2").arg(x).arg(y);
//    statusBar()->showMessage(pos);
//}

