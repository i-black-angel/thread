#include <string>
#include "widget.h"
#include "ui_widget.h"
#if defined(_WIN32) || defined(_WIN64)
# include <windows.h>
#elif defined(__linux__) || defined(__unix__)
# include <unistd.h>
#endif

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
	_thread = new Thread(this);
	_mutex = new Mutex();
	_is_stop = false;

    ui->pbtn_cancel->setEnabled(false);
}

Widget::~Widget()
{
    delete ui;
	if (NULL != _thread) {
		delete _thread; _thread = NULL;
	}
	if (NULL != _mutex) {
		delete _mutex; _mutex = NULL;
	}
}

void Widget::on_pbtn_login_clicked()
{
	set_stop(false);
	_thread->start();

    ui->pbtn_login->setEnabled(false);
    ui->pbtn_cancel->setEnabled(true);
}

void Widget::on_pbtn_cancel_clicked() {
	set_stop();
	_thread->join();
	label_info_set_text("user cancel");

    ui->pbtn_login->setEnabled(true);
    ui->pbtn_cancel->setEnabled(false);
}

void Widget::label_info_set_text(const char *text) {
	_mutex->lock();
    ui->label_info->setText(QString(text));
	_mutex->unlock();
}

void Widget::run() {
	int dot_count = 0;
	std::string info;
	while (!is_stop()) {
		dot_count = (dot_count > 6) ? 0 : dot_count;
		info = "user login";
		for (int i = 0; i < dot_count; ++i) {
			info += ".";
		}
		label_info_set_text(info.c_str());
		usleep(500000);
		++dot_count;
	}
}

bool Widget::is_stop() const {
	return _is_stop;
}

void Widget::set_stop(bool flag) {
	_mutex->lock();
	_is_stop = flag;
	_mutex->unlock();
}
