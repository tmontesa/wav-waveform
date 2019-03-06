#pragma once

#include <QWidget>
#include <QPainter>
#include <QDebug>


class Canvas : public QWidget
{
	Q_OBJECT

public:
	Canvas(QWidget *parent);
	~Canvas();

public slots:
	void GetFilestream(std::string f, int l, int d);

protected:
	void paintEvent(QPaintEvent* event);

private:
	std::string soundstream;
	int samples;
	int bitdepth;

	int drawmode;
	int canvas_width;
	int canvas_height;

	// Helpers
	std::string LittleEndiantoBigEndian(std::string little);
	int LittleHextoInt(std::string hex);
};
