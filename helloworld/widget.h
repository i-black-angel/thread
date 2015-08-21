#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "thread.h"
#include "mutex.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget, public IRunnable
{
    Q_OBJECT
    
public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    virtual void run();
	void set_stop(bool flag = true);
	bool is_stop() const;
	void label_info_set_text(const char *text);
private slots:
    void on_pbtn_login_clicked();
	void on_pbtn_cancel_clicked();
private:
    Ui::Widget *ui;
	Thread *_thread;
	Mutex *_mutex;
	bool _is_stop;
};

#endif // WIDGET_H
