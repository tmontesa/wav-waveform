/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.11.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
#include "canvas.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindowClass
{
public:
    QWidget *centralWidget;
    QFrame *frame;
    Canvas *CanvasWidget;
    QLabel *lblFilename;
    QLabel *lblInfo;
    QPushButton *btnQuit;
    QPushButton *btnFile;

    void setupUi(QMainWindow *MainWindowClass)
    {
        if (MainWindowClass->objectName().isEmpty())
            MainWindowClass->setObjectName(QStringLiteral("MainWindowClass"));
        MainWindowClass->resize(1051, 321);
        centralWidget = new QWidget(MainWindowClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        frame = new QFrame(centralWidget);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setGeometry(QRect(10, 50, 1031, 261));
        frame->setAutoFillBackground(true);
        frame->setFrameShape(QFrame::Box);
        frame->setFrameShadow(QFrame::Sunken);
        frame->setLineWidth(1);
        CanvasWidget = new Canvas(frame);
        CanvasWidget->setObjectName(QStringLiteral("CanvasWidget"));
        CanvasWidget->setGeometry(QRect(0, -1, 1031, 261));
        lblFilename = new QLabel(centralWidget);
        lblFilename->setObjectName(QStringLiteral("lblFilename"));
        lblFilename->setGeometry(QRect(10, 10, 731, 16));
        QFont font;
        font.setPointSize(8);
        font.setBold(true);
        font.setWeight(75);
        lblFilename->setFont(font);
        lblInfo = new QLabel(centralWidget);
        lblInfo->setObjectName(QStringLiteral("lblInfo"));
        lblInfo->setGeometry(QRect(10, 20, 741, 20));
        QFont font1;
        font1.setPointSize(8);
        font1.setBold(false);
        font1.setWeight(50);
        lblInfo->setFont(font1);
        btnQuit = new QPushButton(centralWidget);
        btnQuit->setObjectName(QStringLiteral("btnQuit"));
        btnQuit->setGeometry(QRect(970, 10, 71, 31));
        btnFile = new QPushButton(centralWidget);
        btnFile->setObjectName(QStringLiteral("btnFile"));
        btnFile->setGeometry(QRect(890, 10, 71, 31));
        MainWindowClass->setCentralWidget(centralWidget);

        retranslateUi(MainWindowClass);
        QObject::connect(btnQuit, SIGNAL(released()), MainWindowClass, SLOT(close()));
        QObject::connect(btnFile, SIGNAL(released()), MainWindowClass, SLOT(GetFile()));
        QObject::connect(MainWindowClass, SIGNAL(SendFilename(QString)), lblFilename, SLOT(setText(QString)));
        QObject::connect(MainWindowClass, SIGNAL(SendInfo(QString)), lblInfo, SLOT(setText(QString)));
        QObject::connect(MainWindowClass, SIGNAL(SendFilestream(std::string,int,int)), CanvasWidget, SLOT(GetFilestream(std::string,int,int)));

        QMetaObject::connectSlotsByName(MainWindowClass);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindowClass)
    {
        MainWindowClass->setWindowTitle(QApplication::translate("MainWindowClass", "365 Project 1 Task 2 (tmontesa)", nullptr));
        lblFilename->setText(QApplication::translate("MainWindowClass", "No file selected.", nullptr));
        lblInfo->setText(QApplication::translate("MainWindowClass", "0-bit, 0Hz sample rate, 0 samples (0 maximum signal)", nullptr));
        btnQuit->setText(QApplication::translate("MainWindowClass", "Quit", nullptr));
        btnFile->setText(QApplication::translate("MainWindowClass", "File", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindowClass: public Ui_MainWindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
