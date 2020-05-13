#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <QWidget>
#include <QElapsedTimer>

namespace Ui {
class Stopwatch;
}

class Stopwatch : public QWidget
{
    Q_OBJECT

public:
    explicit Stopwatch(QWidget *parent = nullptr);
    ~Stopwatch();

    long centisecond, second, minute, hour;

    QString getTimeStr();
    void startStopwatch();
    void stopStopwatch();
    void resetStopwatch();
    void updateTimes();
    bool isActive;

private slots:
    void on_state_button_clicked();
    void on_update();
    void on_reset_button_clicked();

private:
    Ui::Stopwatch *ui;
    QElapsedTimer timer;
    QTimer* intervalTimer;
    long lastTime;
};

#endif // STOPWATCH_H
