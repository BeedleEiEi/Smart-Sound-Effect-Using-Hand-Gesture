/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLabel *display;
    QPushButton *openCamButton;
    QPushButton *setupButton;
    QPushButton *browseButton5;
    QLineEdit *lineEdit5;
    QCheckBox *checkBox;
    QLineEdit *lineEdit4;
    QLineEdit *lineEdit3;
    QPushButton *browseButton4;
    QPushButton *browseButton3;
    QLineEdit *lineEdit2;
    QLineEdit *lineEdit1;
    QPushButton *browseButton2;
    QPushButton *browseButton1;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->setEnabled(true);
        MainWindow->resize(1280, 600);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        display = new QLabel(centralWidget);
        display->setObjectName(QStringLiteral("display"));
        display->setGeometry(QRect(80, 20, 500, 500));
        display->setMaximumSize(QSize(500, 500));
        display->setAutoFillBackground(true);
        display->setFrameShape(QFrame::Box);
        display->setTextFormat(Qt::PlainText);
        display->setAlignment(Qt::AlignCenter);
        openCamButton = new QPushButton(centralWidget);
        openCamButton->setObjectName(QStringLiteral("openCamButton"));
        openCamButton->setGeometry(QRect(800, 130, 131, 61));
        setupButton = new QPushButton(centralWidget);
        setupButton->setObjectName(QStringLiteral("setupButton"));
        setupButton->setGeometry(QRect(800, 30, 131, 71));
        browseButton5 = new QPushButton(centralWidget);
        browseButton5->setObjectName(QStringLiteral("browseButton5"));
        browseButton5->setGeometry(QRect(1100, 460, 101, 31));
        lineEdit5 = new QLineEdit(centralWidget);
        lineEdit5->setObjectName(QStringLiteral("lineEdit5"));
        lineEdit5->setGeometry(QRect(720, 460, 371, 31));
        lineEdit5->setReadOnly(true);
        checkBox = new QCheckBox(centralWidget);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        checkBox->setGeometry(QRect(820, 510, 301, 41));
        QFont font;
        font.setPointSize(18);
        checkBox->setFont(font);
        lineEdit4 = new QLineEdit(centralWidget);
        lineEdit4->setObjectName(QStringLiteral("lineEdit4"));
        lineEdit4->setGeometry(QRect(720, 400, 371, 31));
        lineEdit4->setReadOnly(true);
        lineEdit3 = new QLineEdit(centralWidget);
        lineEdit3->setObjectName(QStringLiteral("lineEdit3"));
        lineEdit3->setGeometry(QRect(720, 340, 371, 31));
        lineEdit3->setReadOnly(true);
        browseButton4 = new QPushButton(centralWidget);
        browseButton4->setObjectName(QStringLiteral("browseButton4"));
        browseButton4->setGeometry(QRect(1100, 402, 101, 31));
        browseButton3 = new QPushButton(centralWidget);
        browseButton3->setObjectName(QStringLiteral("browseButton3"));
        browseButton3->setGeometry(QRect(1100, 342, 101, 31));
        lineEdit2 = new QLineEdit(centralWidget);
        lineEdit2->setObjectName(QStringLiteral("lineEdit2"));
        lineEdit2->setGeometry(QRect(720, 290, 371, 31));
        lineEdit2->setReadOnly(true);
        lineEdit1 = new QLineEdit(centralWidget);
        lineEdit1->setObjectName(QStringLiteral("lineEdit1"));
        lineEdit1->setEnabled(true);
        lineEdit1->setGeometry(QRect(720, 240, 371, 31));
        lineEdit1->setReadOnly(true);
        browseButton2 = new QPushButton(centralWidget);
        browseButton2->setObjectName(QStringLiteral("browseButton2"));
        browseButton2->setGeometry(QRect(1100, 290, 101, 31));
        browseButton1 = new QPushButton(centralWidget);
        browseButton1->setObjectName(QStringLiteral("browseButton1"));
        browseButton1->setGeometry(QRect(1100, 240, 101, 31));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(680, 250, 47, 13));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(680, 300, 47, 13));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(680, 350, 47, 13));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(680, 410, 47, 13));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(680, 470, 47, 13));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1280, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        display->setText(QApplication::translate("MainWindow", "DISPLAY", Q_NULLPTR));
        openCamButton->setText(QApplication::translate("MainWindow", "START", Q_NULLPTR));
        setupButton->setText(QApplication::translate("MainWindow", "Setup Gesture", Q_NULLPTR));
        browseButton5->setText(QApplication::translate("MainWindow", "Browse", Q_NULLPTR));
        checkBox->setText(QApplication::translate("MainWindow", "MUTE SOUND EFFECT", Q_NULLPTR));
        browseButton4->setText(QApplication::translate("MainWindow", "Browse", Q_NULLPTR));
        browseButton3->setText(QApplication::translate("MainWindow", "Browse", Q_NULLPTR));
        browseButton2->setText(QApplication::translate("MainWindow", "Browse", Q_NULLPTR));
        browseButton1->setText(QApplication::translate("MainWindow", "Browse", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "Effect1", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "Effect2", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "Effect3", Q_NULLPTR));
        label_4->setText(QApplication::translate("MainWindow", "Effect4", Q_NULLPTR));
        label_5->setText(QApplication::translate("MainWindow", "Effect5", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
