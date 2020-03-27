#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QImage>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    QImage blackandwhite(const QImage& image);
    QImage sepia(const QImage& image);
    ~MainWindow();

private slots:
    void on_loadButton_clicked();
    void on_negativeButton_clicked();
    void on_blackandwhiteButton_clicked();
    void on_sepiaButton_clicked();

    void on_brightnessSlider_valueChanged(int value);

    void on_changeBrightness_clicked();

private:
    Ui::MainWindow *ui;
    QImage image;
    QImage changedImage;
    int brightnessChangeValue;
};
#endif // MAINWINDOW_H
