#include "stopwatch.h"
#include "ui_stopwatch.h"

#include <QtDebug>
#include <QTimer>

Stopwatch::Stopwatch(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Stopwatch)
{
    ui->setupUi(this);
    this->second = 0, this->minute = 0, this->hour = 0, this->centisecond = 0, this->lastTime = 0;
}

Stopwatch::~Stopwatch()
{
    delete ui;
}

void Stopwatch::on_state_button_clicked()
{
    if (!this->isActive) {
        this->startStopwatch();
    } else {
        this->stopStopwatch();
    }
}

void Stopwatch::on_reset_button_clicked()
{
    this->resetStopwatch();
    this->on_update();
}

void Stopwatch::on_update() {
    this->updateTimes();
    ui->timer_label->setText(this->getTimeStr());
}

void Stopwatch::startStopwatch() {
    this->isActive = true;
    ui->state_button->setText("Stop");
    this->timer.start();
    this->intervalTimer = new QTimer(this);
    this->intervalTimer->setInterval(10);
    connect(this->intervalTimer, &QTimer::timeout, this, &Stopwatch::on_update);
    this->intervalTimer->start();
}

void Stopwatch::stopStopwatch() {
    this->isActive = false;
    ui->state_button->setText("Resume");
    this->lastTime = this->timer.elapsed()+this->lastTime;
    disconnect(this->intervalTimer, &QTimer::timeout, this, &Stopwatch::on_update);
}

void Stopwatch::resetStopwatch() {
    ui->state_button->setText("Start");
    this->timer.restart();
    this->lastTime = 0;
    this->isActive = false;
    disconnect(this->intervalTimer, &QTimer::timeout, this, &Stopwatch::on_update);
}

void Stopwatch::updateTimes() {
    this->centisecond = ((this->timer.elapsed()+this->lastTime)/10);
    this->second = (this->centisecond/100);
    this->minute = (this->second/60);
    this->hour = (this->minute/60);
}

QString Stopwatch::getTimeStr() {
    std::string tmp =
            (this->hour < 10 ? "0": "") + std::to_string(this->hour) + ":" +
            (this->minute%60 < 10 ? "0": "") + std::to_string(this->minute%60) + ":" +
            (this->second%60 < 10 ? "0": "") + std::to_string(this->second%60) + "," +
            (this->centisecond%100 < 10 ? "0" : "") + std::to_string(this->centisecond%100);
    return QString::fromStdString(tmp);
}
