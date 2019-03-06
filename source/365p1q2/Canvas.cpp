#include "Canvas.h"

Canvas::Canvas(QWidget *parent)
	: QWidget(parent)
{
	drawmode = 0;
	canvas_width = 1024;
	canvas_height = 128;
}

Canvas::~Canvas()
{
}

// =========================
// SLOTS
// =========================

// Get data hex string from MainWindow, as well as additional values necessary for rendering waveform.
void Canvas::GetFilestream(std::string f, int s, int d) {
	soundstream = f;
	samples = s;
	bitdepth = d;

	drawmode = 1;
	this->update();
}

// =========================
// FUNCTIONS
// =========================

// This event draws the waveform.
void Canvas::paintEvent(QPaintEvent* event) {
	QPainter painter(this); 
	
	if (drawmode == 1) {
		qDebug() << "Painting waveform...";

		// px = previous x, py = previous y on the canvas.
		int max_sample = pow(2, bitdepth) - 1;	
		int px = 0;	
		int	py = (LittleHextoInt(soundstream.substr(0, 2)) / max_sample) * canvas_height;
		int x, y = 0;

		/*
		for (int i = 1; i < samples; i += 2) {
			x = floor(i * canvas_width / samples) ;
			y = floor(LittleHextoInt(soundstream.substr(i, 2)) * canvas_height / max_sample) ;

			painter.drawLine(px, py, x, y);
			px = x;
			py = y;
		}
		*/

		// Set (0, y), where y is the first sample.
		py = LittleHextoInt(soundstream.substr(0, 2));

		// Goes through the data and plots the y=signal at every (1/canvas_width);
		for (int i = 0; i < canvas_width; i++) {
			x = i;
			y = LittleHextoInt(soundstream.substr(((i * samples / canvas_width) - ((i * samples / canvas_width) % 2)) + 1, 2));

			painter.drawLine(px, py, x, y);
			painter.drawLine(px, py, x, (canvas_height * 2) - y);
			px = x;
			py = y;

		}

		qDebug() << "Painting done.";
	}
	
	return;
}

// =========================
// HELPERS
// =========================

// Changing a little endian value to big endian.
// Takes a string of hex, and reverses the order of pairs of hex.
// ie. 0xaabbcc -> 0xccbbaa
std::string Canvas::LittleEndiantoBigEndian(std::string little) {
	std::string big;
	for (int i = little.length() - 1; i > 0; i -= 2) {
		big.append(little.substr(i - 1, 2));
	}
	return big;
}

// Converts a little endian hex string to int.
int Canvas::LittleHextoInt(std::string hex) {
	// Hex String "Substring -> Convert Little Endian to Big Endian --> Convert Big Endian Hex to Int
	return std::stoi(LittleEndiantoBigEndian(hex), nullptr, 16);
}

