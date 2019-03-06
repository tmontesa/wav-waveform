#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"

#include <QFileDialog>
#include <QDebug>

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = Q_NULLPTR);

public slots:
	void GetFile();

protected:
	void GetInfo();
	int GetSamples();
	int GetMaxSignal();

signals:
	void SendFilename(QString);
	void SendInfo(QString);
	void SendFilestream(std::string, int, int);	// Steram, number of samples

private:
	Ui::MainWindowClass ui;
	QString filename;
	std::string filestream;
	QString bitdepth;
	QString samplerate;
	QString samples;
	QString maxsignal;

	// Helpers
	std::string LittleEndiantoBigEndian(std::string little);
	QString LittleHextoIntQString(std::string hex);
	int LittleHextoInt(std::string hex);
};
