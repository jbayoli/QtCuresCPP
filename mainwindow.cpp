#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QColorDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    updateUi();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnAstroid_clicked()
{
    this->ui->renderArea->setShape(RenderArea::Astroid);
    this->ui->renderArea->repaint();
    updateUi();
}

void MainWindow::on_btnCycloid_clicked()
{
    this->ui->renderArea->setShape(RenderArea::Cycloid);
    this->ui->renderArea->repaint();
    updateUi();
}

void MainWindow::on_btnHygens_clicked()
{
    this->ui->renderArea->setShape(RenderArea::HuygensCycloid);
    this->ui->renderArea->repaint();
    updateUi();
}

void MainWindow::on_btnHypo_clicked()
{
    this->ui->renderArea->setShape(RenderArea::HypoCycloid);
    this->ui->renderArea->repaint();
    updateUi();
}

void MainWindow::on_btnLine_clicked()
{
    this->ui->renderArea->setShape(RenderArea::Line);
    this->ui->renderArea->repaint();
    updateUi();
}

void MainWindow::on_spinScale_valueChanged(double scale)
{
    this->ui->renderArea->setScale(static_cast<float>(scale));
}

void MainWindow::updateUi()
{
    this->ui->spinScale->setValue(static_cast<double>(this->ui->renderArea->scale()));
    this->ui->spinInterval->setValue(static_cast<double>(this->ui->renderArea->intervalLenght()));
    this->ui->spinCount->setValue(this->ui->renderArea->stepCount());
}

void MainWindow::on_spinInterval_valueChanged(double intervalLenght)
{
    this->ui->renderArea->setIntervalLenght(static_cast<float>(intervalLenght));
}

void MainWindow::on_spinCount_valueChanged(int count)
{
    this->ui->renderArea->setStepCount(count);
}

void MainWindow::on_btnBackground_clicked()
{
    QColor color = QColorDialog::getColor(this->ui->renderArea->backgroundColor(), this, "Select Color");
    this->ui->renderArea->setBackgroundColor(color);
    repaint();
}

void MainWindow::on_btnLineColor_clicked()
{
    QColor color = QColorDialog::getColor(this->ui->renderArea->shapeColor(), this, "Select Color");
    this->ui->renderArea->setShapeColor(color);
    repaint();
}
