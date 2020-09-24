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

void MainWindow::on_radioButton_clicked()
{
   
    if (wogl->f2) wogl->f2 = false;
    if (wogl->f3) wogl->f3 = false;
    if (wogl->f4) wogl->f4 = false;
    if (wogl->f5) wogl->f5 = false;

    wogl->f1 = true;
    wogl->update();

}

void MainWindow::on_radioButton_2_clicked()
{
    if (wogl->f1) wogl->f1 = false;
    if (wogl->f3) wogl->f3 = false;
    if (wogl->f4) wogl->f4 = false;
    if (wogl->f5) wogl->f5 = false;
    wogl->f2 = true;
    wogl->update();
}

void MainWindow::on_radioButton_4_clicked()
{
    if (wogl->f1) wogl->f1 = false;
    if (wogl->f2) wogl->f2 = false;
    if (wogl->f4) wogl->f4 = false;
    if (wogl->f5) wogl->f5 = false;
    wogl->f3 = true;
    wogl->update();
}

void MainWindow::on_radioButton_5_clicked()
{
    if (wogl->f1) wogl->f1 = false;
    if (wogl->f2) wogl->f2 = false;
    if (wogl->f3) wogl->f3 = false;
    if (wogl->f5) wogl->f5 = false;
    wogl->f4 = true;
    wogl->update();
}

void MainWindow::on_radioButton_6_clicked()
{
    if (wogl->f1) wogl->f1 = false;
    if (wogl->f2) wogl->f2 = false;
    if (wogl->f3) wogl->f3 = false;
    if (wogl->f4) wogl->f4 = false;
    wogl->f5 = true;
    wogl->update();
}

void MainWindow::on_radioButton_3_clicked()
{
    wogl->f1 = false;
    wogl->f2 = false;
    wogl->f3 = false;
    wogl->f4 = false;
    wogl->f5 = false;
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
    wogl->base.rotate(wogl->xRot,1.0f,0.0f,0.0f);
    wogl->update();
}

void MainWindow::on_YSlider_valueChanged(int value)
{
    QString texto1 = QString::fromStdString(std::to_string(value));
    ui->yLabel->setText(texto1);
    wogl->setYRotation(value);
    wogl->base.rotate(wogl->yRot,0.0f,1.0f,0.0f);
    wogl->update();
}

void MainWindow::on_ZSlider_valueChanged(int value)
{
    QString texto2 = QString::fromStdString(std::to_string(value));
    ui->zLabel->setText(texto2);
    wogl->setZRotation(value);
    wogl->base.rotate(wogl->zRot,0.0f,0.0f,1.0f);
    wogl->update();
}

void MainWindow::on_scalaSlider_valueChanged(int value)
{
    QString texto2 = QString::fromStdString(std::to_string(value/100.0));
    ui->scala->setText(texto2);
    wogl->setScala(value/100.0);
    wogl->update();
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    wogl->x=value;
    wogl->update();
}

void MainWindow::on_horizontalSlider_2_valueChanged(int value)
{
    wogl->y=value;
    wogl->update();
}

void MainWindow::on_checkBox_toggled(bool checked)
{
    wogl->smooth= checked;
    wogl->update();
}

void MainWindow::on_checkBox_2_toggled(bool checked)
{
    wogl->wire= checked;
    wogl->update();
}
