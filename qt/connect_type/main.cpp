#include "MyClassA.h"
#include <QApplication>
#include <QObject>
#include <iostream>

int main(int argc, const char **argv) {
	QApplication app(argc, const_cast<char **>(argv));

	MyClassA blah;
	blah.test();

	return app.exec();
}
