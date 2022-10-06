#ifndef PUSHBUTTON_H
#define PUSHBUTTON_H
#include <QPushButton>
#include <QDrag>
#include <QDragEnterEvent>
#include <QMouseEvent>
#include <QMimeData>

#define SIZE 20

class PushButton : public QPushButton {
	Q_OBJECT

 private:
	int *button;
	bool *first;
	bool processed;
    bool mouseSwap=false;
 public:
	PushButton(int *b, bool *f, QWidget *parent = 0);
public slots:
    void setMouseSwap(bool);
 protected:
	void dragEnterEvent(QDragEnterEvent *e);
	void mousePressEvent(QMouseEvent *e);
	
 signals:
	void solid();
	void dot();
};
#endif
