#include "klock.h"
#include "ui_klock.h"

Klock::Klock(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Klock)
{
    ui->setupUi(this);
}

Klock::~Klock()
{
    delete ui;
}
