#include "mainwindow.h"
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QToolBar>
#include <QPushButton>
#include <QStatusBar>
#include <QLabel> //标签主要是用来显示内容
#include <QTextEdit>
#include <QDockWidget>




#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    resize(800,600);
    //菜单栏
    QMenuBar *mBar = menuBar(); //因为内部给我们分配了一个菜单栏，所有不需要用new
    //添加菜单
    QMenu *pFile = mBar->addMenu("文件");
    //添加菜单项
    QAction *pNew = pFile->addAction("新建");

    connect(pNew, &QAction::triggered,
            [=]()
            {
                qDebug() << "新建被按下";
            }

            );

     pFile->addSeparator();//添加分割线；
     QAction *pOpen = pFile->addAction("打开");


    //工具栏，菜单项的快捷方式
    QToolBar *toolBar = addToolBar("toolBar");
    //工具栏添加快捷键
    toolBar->addAction(pNew);

    QPushButton *b = new QPushButton(this);
    b->setText("^_^");
    //添加小控件
    toolBar->addWidget(b);
    connect(b,&QPushButton::clicked,
            [=]()
            {
              b->setText("123");
            }

            );

    //状态栏
    QStatusBar *sBar = statusBar();
    QLabel *label = new QLabel(this);
    label->setText("Norma text file");
    sBar->addWidget(label);
    //addWidget 从左往右添加
    sBar->addWidget(new QLabel("2",this));
    //addPermanentWidget 从右往左添加
    sBar->addPermanentWidget(new QLabel("3", this));

    //核心控件
    QTextEdit *textEdit1 = new QTextEdit(this);
    setCentralWidget(textEdit1);

    //浮动窗口
    QDockWidget *dock = new QDockWidget(this);
    addDockWidget(Qt::RightDockWidgetArea,dock);

    //给浮动窗口添加控件
    QTextEdit *textEdit2 = new QTextEdit(this);
    dock->setWidget(textEdit2);

}

MainWindow::~MainWindow()
{

}
