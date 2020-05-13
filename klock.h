#ifndef KLOCK_H
#define KLOCK_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Klock; }
QT_END_NAMESPACE

class Klock : public QMainWindow
{
    Q_OBJECT

public:
    Klock(QWidget *parent = nullptr);
    ~Klock();


private:
    Ui::Klock *ui;
};
#endif // KLOCK_H
