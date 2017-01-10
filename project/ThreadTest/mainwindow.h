#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "myjob.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void on_stop();

private slots:
    void on_startBtn_clicked();

    void on_stopBtn_clicked();

public slots:
    void newNumber(QString name, int number);


private:
    Ui::MainWindow *ui;
    MyJob mJob;
};

#endif // MAINWINDOW_H
