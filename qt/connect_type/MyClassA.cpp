#include "MyClassA.h"
#include <iostream>

/// The default Qt::ConnectionType value is Qt::AutoConnection.
/// Under Qt::AutoConnection, if the receiver lives in the same thread that emits the signal,
/// Qt::DirectConnection is used. Otherwise, Qt::QueuedConnection is used.

/// when Qt::DirectConnection is being used, the target slot is invoked immediately when the signal
/// is emitted. (the solt is executed in the signalling thread)

/// when Qt::QueuedConnection is being used, the target slot is invoked when control returns to
/// the event loop of the receiver's thread. (they could be the same thread, too)

MyClassA::MyClassA() {
	connect(this, &MyClassA::signal1, this, &MyClassA::slot1);

	connect(this, &MyClassA::signal1, this, &MyClassA::slot2,
		Qt::DirectConnection);

	connect(this, &MyClassA::signal1, this, &MyClassA::slot3,
		Qt::QueuedConnection);
}

/// the output of test method is like this:
///     before invoking `emit blah.signal1()`
///     this is message from slot1
///     this is message from slot2
///     after invoking `emit blah.signal1()`
///     this is message from slot3
void MyClassA::test() {
	std::cout << "before invoking `emit blah.signal1()`" << std::endl;
	emit signal1();
	std::cout << "after invoking `emit blah.signal1()`" << std::endl;
}
