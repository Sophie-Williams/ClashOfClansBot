#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QProcess>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timeUpdate = new QTimer(this);
    QObject::connect(timeUpdate, SIGNAL(timeout()), this, SLOT(telobota()));
    setWindowIcon(QIcon(":/icons/iconcoc.png"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::telobota()
{
    QString cmd1 = "bash -c \"xdotool search --sync --onlyvisible --class Player\"";
    QProcess *process = new QProcess;
    process->start(cmd1);
    process->waitForBytesWritten();
    process->waitForFinished(100);
    if(process->readAll()==""){
    QMessageBox::information(this,"Ошибка","Genymotion не запущен");
    ui->pushButtonSAS->setText("Старт");
    timeUpdate->stop();
    }
    else{
    QString cmd = "bash -c \"w=`xdotool search --sync --onlyvisible --class Player`; wx=`xdotool getwindowgeometry -shell $w | grep X= | sed 's/X=//'`; wy=`xdotool getwindowgeometry -shell $w | grep Y= | sed 's/Y=//'`; ww=`xdotool getwindowgeometry -shell $w | grep WIDTH= | sed 's/WIDTH=//'`; wh=`xdotool getwindowgeometry -shell $w | grep HEIGHT= | sed 's/HEIGHT=//'`; dx=$(($wx+$(($ww/2)))); dy=$(($wy+$(($wh/2)))); mx=`xdotool getmouselocation --shell | grep X= | sed 's/X=//'`; my=`xdotool getmouselocation --shell | grep Y= | sed 's/Y=//'`; xdotool windowactivate $w windowfocus $w mousemove $dx $dy; sleep 0.03; xdotool mousedown 1; sleep 0.03; xdotool mousemove $(($dx+10)) $dy; sleep 0.03; xdotool mousemove $dx $dy; sleep 0.03; xdotool mouseup 1 windowminimize $w;xdotool mousemove $mx $my;\"";
    QProcess *process = new QProcess;
    process->start(cmd);
    }
}

void MainWindow::on_pushButtonSAS_clicked()
{
    if(ui->pushButtonSAS->text()=="Старт")
    {
        ui->pushButtonSAS->setText("Стоп");
        telobota();
        timeUpdate->start(294000);
    }
    else{
        ui->pushButtonSAS->setText("Старт");
        timeUpdate->stop();
    }
}
