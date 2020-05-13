#include "clock.h"
#include "ui_clock.h"

#include <QtDebug>
#include <QTimer>

Clock::Clock(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::Clock)
{
    ui->setupUi(this);
    this->second = 0, this->minute = 0, this->hour = 0, this->centisecond = 0, this->lastTime = 0;
}

Clock::~Clock()
{
    delete ui;
}

void Clock::on_pushButton_2_clicked()
{
    if (!this->isActive) {
        this->startStopwatch();
    } else {
        this->stopStopwatch();
    }
}

void Clock::on_update() {
    this->updateTimes();
    ui->label->setText(this->getTimeStr());
}

void Clock::startStopwatch() {
    this->isActive = true;
    ui->pushButton_2->setText("Stop");
    this->timer.start();
    this->intervalTimer = new QTimer(this);
    this->intervalTimer->setInterval(10);
    connect(this->intervalTimer, &QTimer::timeout, this, &Clock::on_update);
    this->intervalTimer->start();
}

void Clock::stopStopwatch() {
    this->isActive = false;
    ui->pushButton_2->setText("Resume");
    this->lastTime = this->timer.elapsed()+this->lastTime;
    disconnect(this->intervalTimer, &QTimer::timeout, this, &Clock::on_update);
}

void Clock::resetStopwatch() {
    ui->pushButton_2->setText("Start");
    this->timer.restart();
    this->lastTime = 0;
    this->isActive = false;
    disconnect(this->intervalTimer, &QTimer::timeout, this, &Clock::on_update);
}

void Clock::updateTimes() {
    this->centisecond = ((this->timer.elapsed()+this->lastTime)/10);
    this->second = (this->centisecond/100);
    this->minute = (this->second/60);
    this->hour = (this->minute/60);
}

QString Clock::getTimeStr() {
    std::string tmp =
            (this->hour < 10 ? "0": "") + std::to_string(this->hour) + ":" +
            (this->minute%60 < 10 ? "0": "") + std::to_string(this->minute%60) + ":" +
            (this->second%60 < 10 ? "0": "") + std::to_string(this->second%60) + "," +
            (this->centisecond%100 < 10 ? "0" : "") + std::to_string(this->centisecond%100);
    return QString::fromStdString(tmp);
}

void Clock::on_pushButton_clicked()
{
    this->resetStopwatch();
    this->on_update();
}
