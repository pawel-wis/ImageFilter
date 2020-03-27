#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_loadButton_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Otwórz"), "", tr("Zdjęcia *.png *.jpg"));

    if(QString::compare(filename, QString()) != 0 ){
        bool valid  = image.load(filename);
        if(valid){
            ui->imageViewLabel->setPixmap(QPixmap::fromImage(image));
            ui->imageViewLabel->setScaledContents(true);
        } else{
            QMessageBox::critical(this,"Błąd", "Nie można wczytać obrazu");
        }
    }
}



void MainWindow::on_negativeButton_clicked()
{
    if(image.isNull()){
        QMessageBox::warning(this,"Błąd", "Brak obrazu");
    } else{
        changedImage = image.copy();
        changedImage.invertPixels();
        ui->changedImageViewLabel->setPixmap(QPixmap::fromImage(changedImage));
        ui->changedImageViewLabel->setScaledContents(true);
    }
}



void MainWindow::on_blackandwhiteButton_clicked()
{
    if(image.isNull()){
        QMessageBox::warning(this,"Błąd", "Brak obrazu");
    } else{
        changedImage = blackandwhite(image);
        ui->changedImageViewLabel->setPixmap(QPixmap::fromImage(changedImage));
        ui->changedImageViewLabel->setScaledContents(true);
    }
}


QImage MainWindow::blackandwhite(const QImage &image){
    changedImage = image.copy();
    QSize imageSize = changedImage.size();


    // Black and White effect
    for(int i =0; i < imageSize.width(); i++){
        for(int j = 0; j < imageSize.height(); j++){
           auto color = changedImage.pixel(i, j);
           int red = qRed(color);
           int green = qGreen(color);
           int blue = qBlue(color);

           int newRed = 0.299*red + 0.587*green + 0.114*blue;
           int newGreen = newRed;
           int newBlue = newGreen;

           QRgb newPixelColor = qRgb(newRed, newGreen, newBlue);
           changedImage.setPixel(i, j, newPixelColor);
        }
}
    return changedImage;
}


QImage MainWindow::sepia(const QImage &image){
    QImage processedImage = image.copy();
    QSize imageSize = processedImage.size();
    int w = 10; // sepia parameter this value is set by experiece :D
    // sepia
    for(int i =0; i < imageSize.width(); i++){
        for(int j = 0; j < imageSize.height(); j++){
           auto color = processedImage.pixel(i, j);
           int red = qRed(color);
           int green = qGreen(color);
           int blue = qBlue(color);

           int newRed = red + 2*w;
           int newGreen = green + w;
           int newBlue = blue;

           QRgb newPixelColor = qRgb(newRed, newGreen, newBlue);
           processedImage.setPixel(i, j, newPixelColor);
        }
}
    return processedImage;
}

void MainWindow::on_sepiaButton_clicked()
{
    if(image.isNull()){
        QMessageBox::warning(this,"Błąd", "Brak obrazu");
    } else{
        changedImage = blackandwhite(image);
        changedImage = sepia(changedImage);
        ui->changedImageViewLabel->setPixmap(QPixmap::fromImage(changedImage));
        ui->changedImageViewLabel->setScaledContents(true);
    }
}



void MainWindow::on_brightnessSlider_valueChanged(int value)
{
    ui->brightnessLabel->setText("Jasność " + QString::number(value) + " %");
    brightnessChangeValue = value;
}
