#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButtonSAS_clicked();
    void telobota();

private:
    Ui::MainWindow *ui;
    QTimer *timeUpdate;
};

#endif // MAINWINDOW_H
