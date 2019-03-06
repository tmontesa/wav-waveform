#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

// =========================
// SLOTS
// =========================

void MainWindow::GetFile() {
	// Open file picker to get file path.
	filename = QFileDialog::getOpenFileName(this, tr("Open File"),
				"/home", tr("Images (*.wav)"));

	// Open file and stop if it does not exist.
	QFile file(filename);
	if (!file.exists()) return;
	file.open(QIODevice::ReadOnly);

	// Turn the raw binary of the file into a string of hex characters. 
	QDataStream data(&file);
	filestream = file.readAll().toHex().toStdString();
	
	// Extract file information from the hex string and send it to the "info display" label.
	GetInfo();
	emit SendFilename(filename);

	// Send the "data" portion of the hex string to the canvas display widget.
	emit SendFilestream(filestream.substr(44 * 2), GetSamples(), LittleHextoInt(filestream.substr(32 * 2, 2 * 2)));
	return;
}

// =========================
// FUNCTIONS
// =========================

//  Extract file information from the hex string.
void MainWindow::GetInfo() {
	bitdepth = LittleHextoIntQString(filestream.substr(32 * 2, 2 * 2));
	samplerate = LittleHextoIntQString(filestream.substr(24 * 2, 4 * 2));
	samples = QString::number(GetSamples());
	maxsignal = QString::number(GetMaxSignal());

	emit SendInfo(QString(bitdepth + " -bit, " + samplerate + "Hz samplerate, " + samples + " samples (" + maxsignal + " max signal)"));
}

// Gets the number of samples from the file.
int MainWindow::GetSamples() {
	return (filestream.substr(44 * 2).length())/2;
}

// Looks through the values and returns the largest one.
int MainWindow::GetMaxSignal() {
	int m = 0;
	for (int s = 0; s < samples; s += 2) {
		m = std::max(m, LittleHextoInt(filestream.substr((44*2)+s, 2)));
	}
	return m;
}


// =========================
// HELPERS
// =========================

// Changing a little endian value to big endian.
// Takes a string of hex, and reverses the order of pairs of hex.
// ie. 0xaabbcc -> 0xccbbaa
std::string MainWindow::LittleEndiantoBigEndian(std::string little) {
	std::string big;
	for (int i = little.length() - 1; i > 0; i -= 2) {
		big.append(little.substr(i - 1, 2));
	}
	return big;
}

// Converts a little endian hex string to int, then to string.
QString MainWindow::LittleHextoIntQString(std::string hex) {
	// Hex String "Substring -> Convert Little Endian to Big Endian --> Convert Big Endian Hex to Int -> Convert to QString
	return QString::number(std::stoi(LittleEndiantoBigEndian(hex), nullptr, 16));
}

// Converts a little endian hex string to int.
int MainWindow::LittleHextoInt(std::string hex) {
	// Hex String "Substring -> Convert Little Endian to Big Endian --> Convert Big Endian Hex to Int
	return std::stoi(LittleEndiantoBigEndian(hex), nullptr, 16);
}