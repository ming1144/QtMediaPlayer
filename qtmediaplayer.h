#ifndef QTMEDIAPLAYER_H
#define QTMEDIAPLAYER_H

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QtWidgets>
#include <QFiledialog>
#include "ui_qtmediaplayer.h"

class QtMediaPlayer : public QMainWindow
{
	Q_OBJECT

public:
	QtMediaPlayer(QWidget *parent = 0);
	~QtMediaPlayer();

public slots:
	void on_actionTBOpenFile_triggered();
	void on_actionMenuOpenFile_triggered();

private:
	Ui::QtMediaPlayerClass ui;
};


#endif // QTMEDIAPLAYER_H
