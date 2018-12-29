/********************************************************************************
** Form generated from reading UI file 'clienwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLIENWIDGET_H
#define UI_CLIENWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ClienWidget
{
public:
    QGridLayout *gridLayout;
    QLabel *labelport;
    QLineEdit *lineEditPort;
    QPushButton *buttonConnect;
    QLabel *labelip;
    QLineEdit *lineEditIP;
    QTextEdit *textEditRead;
    QTextEdit *textEditWrite;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *buttonSend;
    QSpacerItem *horizontalSpacer;
    QPushButton *buttonclose;
    QSpacerItem *horizontalSpacer_3;

    void setupUi(QWidget *ClienWidget)
    {
        if (ClienWidget->objectName().isEmpty())
            ClienWidget->setObjectName(QStringLiteral("ClienWidget"));
        ClienWidget->resize(400, 300);
        gridLayout = new QGridLayout(ClienWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        labelport = new QLabel(ClienWidget);
        labelport->setObjectName(QStringLiteral("labelport"));

        gridLayout->addWidget(labelport, 0, 0, 1, 1);

        lineEditPort = new QLineEdit(ClienWidget);
        lineEditPort->setObjectName(QStringLiteral("lineEditPort"));

        gridLayout->addWidget(lineEditPort, 0, 1, 1, 2);

        buttonConnect = new QPushButton(ClienWidget);
        buttonConnect->setObjectName(QStringLiteral("buttonConnect"));

        gridLayout->addWidget(buttonConnect, 0, 3, 2, 1);

        labelip = new QLabel(ClienWidget);
        labelip->setObjectName(QStringLiteral("labelip"));

        gridLayout->addWidget(labelip, 1, 0, 1, 1);

        lineEditIP = new QLineEdit(ClienWidget);
        lineEditIP->setObjectName(QStringLiteral("lineEditIP"));

        gridLayout->addWidget(lineEditIP, 1, 1, 1, 2);

        textEditRead = new QTextEdit(ClienWidget);
        textEditRead->setObjectName(QStringLiteral("textEditRead"));
        textEditRead->setReadOnly(true);

        gridLayout->addWidget(textEditRead, 2, 0, 1, 5);

        textEditWrite = new QTextEdit(ClienWidget);
        textEditWrite->setObjectName(QStringLiteral("textEditWrite"));

        gridLayout->addWidget(textEditWrite, 3, 0, 1, 5);

        horizontalSpacer_2 = new QSpacerItem(69, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 4, 0, 1, 1);

        buttonSend = new QPushButton(ClienWidget);
        buttonSend->setObjectName(QStringLiteral("buttonSend"));

        gridLayout->addWidget(buttonSend, 4, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(107, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 4, 2, 1, 1);

        buttonclose = new QPushButton(ClienWidget);
        buttonclose->setObjectName(QStringLiteral("buttonclose"));

        gridLayout->addWidget(buttonclose, 4, 3, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(23, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 4, 4, 1, 1);


        retranslateUi(ClienWidget);

        QMetaObject::connectSlotsByName(ClienWidget);
    } // setupUi

    void retranslateUi(QWidget *ClienWidget)
    {
        ClienWidget->setWindowTitle(QApplication::translate("ClienWidget", "Form", 0));
        labelport->setText(QApplication::translate("ClienWidget", "\346\234\215\345\212\241\345\231\250\347\253\257\345\217\243\357\274\232", 0));
        lineEditPort->setText(QApplication::translate("ClienWidget", "8888", 0));
        buttonConnect->setText(QApplication::translate("ClienWidget", "connect", 0));
        labelip->setText(QApplication::translate("ClienWidget", "\346\234\215\345\212\241\345\231\250IP\357\274\232", 0));
        lineEditIP->setText(QApplication::translate("ClienWidget", "127.0.0.1", 0));
        buttonSend->setText(QApplication::translate("ClienWidget", "send", 0));
        buttonclose->setText(QApplication::translate("ClienWidget", "close", 0));
    } // retranslateUi

};

namespace Ui {
    class ClienWidget: public Ui_ClienWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLIENWIDGET_H
