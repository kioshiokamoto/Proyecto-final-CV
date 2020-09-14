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
    ui->xLabel->setText("0");
    ui->yLabel->setText("0");
    ui->zLabel->setText("0");
    ui->scala->setText("1.00");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_horizontalSlider_valueChanged(int value)
{

}

void MainWindow::on_radioButton_clicked()
{

    if (wogl->f2)
        wogl->f2 = false;
    wogl->f1 = true;
    wogl->setXRotation(0);
    wogl->setYRotation(0);
    wogl->setZRotation(0);
    wogl->setScala(1);
    wogl->update();

}

void MainWindow::on_radioButton_2_clicked()
{
    if (wogl->f1)
        wogl->f1 = false;
    wogl->f2 = true;
    wogl->setXRotation(0);
    wogl->setYRotation(0);
    wogl->setZRotation(0);
    wogl->setScala(1);
    wogl->update();
}

void MainWindow::on_radioButton_3_clicked()
{
    wogl->f1 = false;
    wogl->f2 = false;
    wogl->setXRotation(0);
    wogl->setYRotation(0);
    wogl->setZRotation(0);
    wogl->setScala(1);
    wogl->update();
}

void MainWindow::on_actionSalir_triggered()
{
    close();
}

void MainWindow::on_XSlider_valueChanged(int value)
{
    QString texto = QString::fromStdString(std::to_string(value));
    ui->xLabel->setText(texto);

    wogl->setXRotation(value);
    wogl->update();
}

void MainWindow::on_YSlider_valueChanged(int value)
{
    QString texto1 = QString::fromStdString(std::to_string(value));
    ui->yLabel->setText(texto1);

    wogl->setYRotation(value);
    wogl->update();
}

void MainWindow::on_ZSlider_valueChanged(int value)
{
    QString texto2 = QString::fromStdString(std::to_string(value));
    ui->zLabel->setText(texto2);

    wogl->setZRotation(value);
    wogl->update();
}

void MainWindow::on_XSlider_2_valueChanged(int value)
{
}

void MainWindow::on_scalaSlider_valueChanged(int value)
{
    QString texto2 = QString::fromStdString(std::to_string(value/100.0));
    ui->scala->setText(texto2);

    wogl->setScala(value/100.0);
    wogl->update();
}
