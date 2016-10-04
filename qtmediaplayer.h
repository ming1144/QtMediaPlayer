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
	void appOpen();

public slots:
	void on_actionTBOpenFile_triggered();
	void on_actionMenuOpenFile_triggered();
	void on_fileList_clicked(const QModelIndex &);

private:
	Ui::QtMediaPlayerClass ui;
	QStringList filenameList;
	//QStringListModel* filenameModel;
};


#endif // QTMEDIAPLAYER_H
