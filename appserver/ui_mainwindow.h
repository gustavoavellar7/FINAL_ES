/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Sat Nov 16 15:46:07 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QTextEdit>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QTextEdit *textEdit;
    QPushButton *btnStart;
    QPushButton *btnStop;
    QPushButton *btnQuit;
    QLabel *fondo;
    QLabel *lproducto;
    QLabel *lqr;
    QTextEdit *textdesc;
    QLabel *labelvans;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1280, 640);
        MainWindow->setMouseTracking(true);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        textEdit = new QTextEdit(centralWidget);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(20, 70, 221, 61));
        textEdit->setReadOnly(true);
        btnStart = new QPushButton(centralWidget);
        btnStart->setObjectName(QString::fromUtf8("btnStart"));
        btnStart->setGeometry(QRect(10, 10, 91, 23));
        btnStop = new QPushButton(centralWidget);
        btnStop->setObjectName(QString::fromUtf8("btnStop"));
        btnStop->setGeometry(QRect(100, 10, 91, 23));
        btnQuit = new QPushButton(centralWidget);
        btnQuit->setObjectName(QString::fromUtf8("btnQuit"));
        btnQuit->setGeometry(QRect(220, 10, 75, 23));
        fondo = new QLabel(centralWidget);
        fondo->setObjectName(QString::fromUtf8("fondo"));
        fondo->setGeometry(QRect(0, 0, 1280, 640));
        fondo->setPixmap(QPixmap(QString::fromUtf8("../../../Desktop/fondo-madera-negro.jpg")));
        lproducto = new QLabel(centralWidget);
        lproducto->setObjectName(QString::fromUtf8("lproducto"));
        lproducto->setGeometry(QRect(370, 30, 201, 270));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lproducto->sizePolicy().hasHeightForWidth());
        lproducto->setSizePolicy(sizePolicy);
        lproducto->setMaximumSize(QSize(16777215, 270));
        lproducto->setScaledContents(true);
        lqr = new QLabel(centralWidget);
        lqr->setObjectName(QString::fromUtf8("lqr"));
        lqr->setGeometry(QRect(380, 310, 151, 151));
        lqr->setScaledContents(true);
        textdesc = new QTextEdit(centralWidget);
        textdesc->setObjectName(QString::fromUtf8("textdesc"));
        textdesc->setGeometry(QRect(20, 150, 221, 131));
        textdesc->setAutoFillBackground(true);
        labelvans = new QLabel(centralWidget);
        labelvans->setObjectName(QString::fromUtf8("labelvans"));
        labelvans->setGeometry(QRect(0, 470, 171, 131));
        labelvans->setPixmap(QPixmap(QString::fromUtf8(":/imagenes/v5")));
        labelvans->setScaledContents(true);
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(370, 470, 181, 131));
        label->setPixmap(QPixmap(QString::fromUtf8(":/imagenes/adidas1.jpg")));
        label->setScaledContents(true);
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(800, 470, 121, 131));
        label_2->setPixmap(QPixmap(QString::fromUtf8(":/imagenes/camisa1.jpg")));
        label_2->setScaledContents(true);
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(1160, 470, 121, 131));
        label_3->setPixmap(QPixmap(QString::fromUtf8(":/imagenes/camisa22.jpg")));
        label_3->setScaledContents(true);
        MainWindow->setCentralWidget(centralWidget);
        fondo->raise();
        textEdit->raise();
        btnStart->raise();
        btnStop->raise();
        btnQuit->raise();
        lproducto->raise();
        textdesc->raise();
        labelvans->raise();
        label->raise();
        label_2->raise();
        label_3->raise();
        lqr->raise();
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1280, 25));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        btnStart->setText(QApplication::translate("MainWindow", "Start Server", 0, QApplication::UnicodeUTF8));
        btnStop->setText(QApplication::translate("MainWindow", "Stop Server", 0, QApplication::UnicodeUTF8));
        btnQuit->setText(QApplication::translate("MainWindow", "Salir", 0, QApplication::UnicodeUTF8));
        fondo->setText(QString());
        lproducto->setText(QString());
        lqr->setText(QString());
        textdesc->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", 0, QApplication::UnicodeUTF8));
        labelvans->setText(QString());
        label->setText(QString());
        label_2->setText(QString());
        label_3->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
