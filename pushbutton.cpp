#include "pushbutton.h"
#include <iostream>

// button & first are pointers to the parent's variables. These are used to
// convey information that the parent needs. "button" for which mouse button
// was pressed, and "first" for whether this was the first operation in
// a "click and drag" operation or not.
PushButton::PushButton(int *b, bool *f, QWidget *parent) : button(b), first(f), QPushButton(parent) {
	setAcceptDrops(true);
	setStyleSheet("background-color: rgb(215, 215, 215)");
	setMinimumSize(SIZE, SIZE);
	setMaximumSize(SIZE, SIZE);
    processed = false;
}

void PushButton::setMouseSwap(bool tf)
{
    mouseSwap = tf;
}

void PushButton::mousePressEvent(QMouseEvent *e) {
	if (e->button() != Qt::LeftButton && e->button() != Qt::RightButton) {
		return;
	}
	*(button) = e->button();
	*(first) = true;
    processed = true;
    if ( (e->button() == Qt::LeftButton) ^ mouseSwap ) {
//		std::cout << "emit solid" << std::endl;
		emit solid();
	}
	else {
//		std::cout << "emit dot" << std::endl;
		emit dot();
	}
	// Qt will clean up the QDrag and associated QMimeData objects, so they mustn't be deleted.
	QDrag *drag = new QDrag(this);
	QMimeData *md = new QMimeData();
	drag->setMimeData(md);
	drag->exec(Qt::IgnoreAction);
	// After a drag action the released signal isn't auto-emitted, but we need it.
	emit released();
}

void PushButton::dragEnterEvent(QDragEnterEvent *e) {
	if (processed) {
		processed = false;
		return;
	}
    if (*(button) == Qt::LeftButton ^ mouseSwap) {
		emit solid();
	}
	else {
		emit dot();
	}
}
