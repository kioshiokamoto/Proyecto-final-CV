#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "widget_opengl.h"

#include <QHBoxLayout>

#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    wogl = new WidgetOpenGL();
    ui->horizontalLayout->addWidget(wogl);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_horizontalSlider_valueChanged(int value)
{

    wogl->xRot=value;
    //wogl->yRot=value;
    wogl->setXRotation(value);
    QString texto = QString::fromStdString(std::to_string(value/100.0));
    ui->lineEdit->setText(texto);

    wogl->update();
}

void MainWindow::on_radioButton_clicked()
{
    if (wogl->f2)
        wogl->f2 = false;
    wogl->f1 = true;
    wogl->update();
}

void MainWindow::on_radioButton_2_clicked()
{
    if (wogl->f1)
        wogl->f1 = false;
    wogl->f2 = true;
    wogl->update();
}

void MainWindow::on_radioButton_3_clicked()
{
    wogl->f1 = false;
    wogl->f2 = false;
    wogl->update();
}

void MainWindow::on_actionSalir_triggered()
{
    close();
}
