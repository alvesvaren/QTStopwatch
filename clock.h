#ifndef CLOCK_H
#define CLOCK_H

#include <QFrame>
#include <QElapsedTimer>

namespace Ui {
class Clock;
}

class Clock : public QFrame
{
    Q_OBJECT

public:
    explicit Clock(QWidget *parent = nullptr);
    ~Clock();

    long centisecond, second, minute, hour;

    QString getTimeStr();
    void startStopwatch();
    void stopStopwatch();
    void resetStopwatch();
    void updateTimes();
    bool isActive;

private slots:
    void on_pushButton_2_clicked();
    void on_update();


    void on_pushButton_clicked();

private:
    Ui::Clock *ui;
    QElapsedTimer timer;
    QTimer* intervalTimer;
    long lastTime;
};

#endif // CLOCK_H
