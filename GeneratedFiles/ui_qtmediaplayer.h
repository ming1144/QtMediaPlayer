/********************************************************************************
** Form generated from reading UI file 'qtmediaplayer.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTMEDIAPLAYER_H
#define UI_QTMEDIAPLAYER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtMediaPlayerClass
{
public:
    QAction *actionTBOpenFile;
    QAction *actionTBPlayVideo;
    QAction *actionPause;
    QAction *actionMenuOpenFile;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QGraphicsView *graphicsViewOrigin;
    QGraphicsView *graphicsViewAfter;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QListView *fileList;
    QTextBrowser *textBrowser;
    QMenuBar *menuBar;
    QMenu *menu;
    QStatusBar *statusBar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *QtMediaPlayerClass)
    {
        if (QtMediaPlayerClass->objectName().isEmpty())
            QtMediaPlayerClass->setObjectName(QStringLiteral("QtMediaPlayerClass"));
        QtMediaPlayerClass->resize(779, 596);
        actionTBOpenFile = new QAction(QtMediaPlayerClass);
        actionTBOpenFile->setObjectName(QStringLiteral("actionTBOpenFile"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/QtMediaPlayer/icon/open.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionTBOpenFile->setIcon(icon);
        actionTBPlayVideo = new QAction(QtMediaPlayerClass);
        actionTBPlayVideo->setObjectName(QStringLiteral("actionTBPlayVideo"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/QtMediaPlayer/icon/play.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionTBPlayVideo->setIcon(icon1);
        actionPause = new QAction(QtMediaPlayerClass);
        actionPause->setObjectName(QStringLiteral("actionPause"));
        actionPause->setEnabled(false);
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/QtMediaPlayer/icon/pause.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionPause->setIcon(icon2);
        actionMenuOpenFile = new QAction(QtMediaPlayerClass);
        actionMenuOpenFile->setObjectName(QStringLiteral("actionMenuOpenFile"));
        centralWidget = new QWidget(QtMediaPlayerClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        graphicsViewOrigin = new QGraphicsView(centralWidget);
        graphicsViewOrigin->setObjectName(QStringLiteral("graphicsViewOrigin"));

        horizontalLayout->addWidget(graphicsViewOrigin);

        graphicsViewAfter = new QGraphicsView(centralWidget);
        graphicsViewAfter->setObjectName(QStringLiteral("graphicsViewAfter"));

        horizontalLayout->addWidget(graphicsViewAfter);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 500, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 0, 1, 2, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        fileList = new QListView(centralWidget);
        fileList->setObjectName(QStringLiteral("fileList"));

        horizontalLayout_2->addWidget(fileList);

        textBrowser = new QTextBrowser(centralWidget);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));

        horizontalLayout_2->addWidget(textBrowser);


        gridLayout->addLayout(horizontalLayout_2, 1, 0, 1, 1);

        QtMediaPlayerClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(QtMediaPlayerClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 779, 22));
        menu = new QMenu(menuBar);
        menu->setObjectName(QStringLiteral("menu"));
        QtMediaPlayerClass->setMenuBar(menuBar);
        statusBar = new QStatusBar(QtMediaPlayerClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        QtMediaPlayerClass->setStatusBar(statusBar);
        toolBar = new QToolBar(QtMediaPlayerClass);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        QtMediaPlayerClass->addToolBar(Qt::TopToolBarArea, toolBar);

        menuBar->addAction(menu->menuAction());
        menu->addAction(actionMenuOpenFile);
        toolBar->addAction(actionTBOpenFile);
        toolBar->addAction(actionTBPlayVideo);
        toolBar->addAction(actionPause);

        retranslateUi(QtMediaPlayerClass);

        QMetaObject::connectSlotsByName(QtMediaPlayerClass);
    } // setupUi

    void retranslateUi(QMainWindow *QtMediaPlayerClass)
    {
        QtMediaPlayerClass->setWindowTitle(QApplication::translate("QtMediaPlayerClass", "QtMediaPlayer", 0));
        actionTBOpenFile->setText(QApplication::translate("QtMediaPlayerClass", "\351\226\213\345\225\237\346\252\224\346\241\210", 0));
        actionTBPlayVideo->setText(QApplication::translate("QtMediaPlayerClass", "\346\222\255\346\224\276", 0));
        actionPause->setText(QApplication::translate("QtMediaPlayerClass", "\346\232\253\345\201\234", 0));
        actionMenuOpenFile->setText(QApplication::translate("QtMediaPlayerClass", "\351\226\213\345\225\237\346\252\224\346\241\210", 0));
        menu->setTitle(QApplication::translate("QtMediaPlayerClass", "\346\252\224\346\241\210", 0));
        toolBar->setWindowTitle(QApplication::translate("QtMediaPlayerClass", "toolBar", 0));
    } // retranslateUi

};

namespace Ui {
    class QtMediaPlayerClass: public Ui_QtMediaPlayerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTMEDIAPLAYER_H
