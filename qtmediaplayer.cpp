#include "qtmediaplayer.h"
#include <atlstr.h>
#include "CxImage\ximage.h"

QtMediaPlayer::QtMediaPlayer(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

QtMediaPlayer::~QtMediaPlayer()
{
}

void QtMediaPlayer::on_actionTBOpenFile_triggered(){
	filenameList = QFileDialog::getOpenFileNames(this, tr("Open  File"), "/", "(*.tif)");
	if (filenameList.isEmpty())
	{
		ui.fileList->clearPropertyFlags();
		ui.textBrowser->setText("No Input File.");
		return;
	}
	ui.textBrowser->setText(filenameList[0]);
	QStringListModel* filenameModel = new QStringListModel(this);
	filenameModel->setStringList(filenameList);
	ui.fileList->setModel(filenameModel);

	QByteArray byteArray = filenameList[0].toLatin1();
	const char *c_str = byteArray.data();
	CString cString = c_str;
	CxImage Image;
	Image.Load(cString);

	BYTE *buffer = NULL;
	long len = 0;
	Image.Encode(buffer, len, CXIMAGE_FORMAT_TIF);

	CxImage dst(buffer, len, CXIMAGE_FORMAT_TIF);

	QImage Qimage(dst.GetBits(), dst.GetWidth(), dst.GetHeight(), QImage::Format_RGB888);
	QImage frame = Qimage.rgbSwapped().mirrored();
	QPixmap map = QPixmap::fromImage(frame);
	QGraphicsScene* scene = new QGraphicsScene();
	QGraphicsPixmapItem* item = new QGraphicsPixmapItem(map);
	scene->addItem(item);
	ui.graphicsViewOrigin->setScene(scene);
	ui.graphicsViewAfter->setScene(scene);
}

void QtMediaPlayer::on_actionMenuOpenFile_triggered(){
	filenameList = QFileDialog::getOpenFileNames(this, tr("Open  File"), "/", "(*.tif)");
	if (filenameList.isEmpty())
	{
		ui.fileList->clearFocus();
		ui.textBrowser->setText("No Input File.");
		return;
	}
	ui.textBrowser->setText(filenameList[0]);
	QStringListModel* filenameModel = new QStringListModel(this);
	filenameModel->setStringList(filenameList);
	ui.fileList->setModel(filenameModel);

	QByteArray byteArray = filenameList[0].toLatin1();
	const char *c_str = byteArray.data();
	CString cString = c_str;
	CxImage Image;
	Image.Load(cString);

	BYTE *buffer = NULL;
	long len = 0;
	Image.Encode(buffer, len, CXIMAGE_FORMAT_TIF);

	CxImage dst(buffer, len, CXIMAGE_FORMAT_TIF);

	QImage Qimage(dst.GetBits(), dst.GetWidth(), dst.GetHeight(), QImage::Format_RGB888);
	QImage frame = Qimage.rgbSwapped().mirrored();

	QGraphicsScene* scene = new QGraphicsScene();
	QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(QImage(frame)));
	scene->addItem(item);
	ui.graphicsViewOrigin->setScene(scene);
	ui.graphicsViewAfter->setScene(scene);
}

void QtMediaPlayer::appOpen()
{
	filenameList = QFileDialog::getOpenFileNames(this, tr("Open  File"), "/", "(*.tif)");
	if (filenameList.isEmpty())
	{
		ui.fileList->clearFocus();
		ui.textBrowser->setText("No Input File.");
		return;
	}
	ui.textBrowser->setText(filenameList[0]);
	QStringListModel* filenameModel = new QStringListModel(this);
	filenameModel->setStringList(filenameList);
	ui.fileList->setModel(filenameModel);

	QByteArray byteArray = filenameList[0].toLatin1();
	const char *c_str = byteArray.data();
	CString cString = c_str;
	CxImage Image;
	Image.Load(cString);

	BYTE *buffer = NULL;
	long len = 0;
	Image.Encode(buffer, len, CXIMAGE_FORMAT_TIF);

	CxImage dst(buffer, len, CXIMAGE_FORMAT_TIF);

	QImage Qimage(dst.GetBits(), dst.GetWidth(), dst.GetHeight(), QImage::Format_RGB888);
	QImage frame = Qimage.rgbSwapped().mirrored();

	QGraphicsScene* scene = new QGraphicsScene();
	QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(QImage(frame)));
	scene->addItem(item);
	ui.graphicsViewOrigin->setScene(scene);
	ui.graphicsViewAfter->setScene(scene);
}

void QtMediaPlayer::on_fileList_clicked(const QModelIndex &Index)
{
	ui.textBrowser->setText(filenameList[Index.row()]);
	QByteArray byteArray = filenameList[Index.row()].toLatin1();
	const char *c_str = byteArray.data();
	CString cString = c_str;
	CxImage Image;
	Image.Load(cString);

	BYTE *buffer = NULL;
	long len = 0;
	Image.Encode(buffer, len, CXIMAGE_FORMAT_TIF);

	CxImage dst(buffer, len, CXIMAGE_FORMAT_TIF);

	QImage Qimage(dst.GetBits(), dst.GetWidth(), dst.GetHeight(), QImage::Format_RGB888);
	QImage frame = Qimage.rgbSwapped().mirrored();

	QGraphicsScene* scene = new QGraphicsScene();
	QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(QImage(frame)));
	scene->addItem(item);
	ui.graphicsViewOrigin->setScene(scene);
	ui.graphicsViewAfter->setScene(scene);
}