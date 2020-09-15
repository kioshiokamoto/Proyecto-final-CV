#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <widget_opengl.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_horizontalSlider_valueChanged(int value);

    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

    void on_radioButton_3_clicked();

    void on_actionSalir_triggered();

    void on_XSlider_valueChanged(int value);

    void on_YSlider_valueChanged(int value);

    void on_ZSlider_valueChanged(int value);

    void on_XSlider_2_valueChanged(int value);

    void on_scalaSlider_valueChanged(int value);

    void on_radioButton_4_clicked();

    void on_radioButton_5_clicked();

private:
    Ui::MainWindow *ui;
    WidgetOpenGL *wogl;
};
#endif // MAINWINDOW_H
