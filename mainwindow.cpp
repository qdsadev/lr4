#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QPainter>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    data.region = allocateString(STRING_SCALE);
    data.name = allocateString(STRING_SCALE);
    data.fileExists = false;
    ui->setupUi(this);
    connect(ui->pushButtonAddFile, &QPushButton::clicked, this, &MainWindow::openWindowFile);
    connect(ui->pushButtonCalc, &QPushButton::clicked, this, &MainWindow::calc);
}


MainWindow::~MainWindow()
{
    freeString(data.region);
    freeString(data.name);
    if (data.fileExists){
        freeMatrix(data.table, data.size, data.countColumn);
        freeArr(data.nameColumn, data.countColumn);
    }
    delete ui;
}


void MainWindow::showErrorWindow(char* nameError){
    if(nameError == NULL){
        return;
    } else {
        QMessageBox::warning(this, "ERROR", nameError);
    }
}


void MainWindow::openWindowFile(){
    QString pathFileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", "CSV File (*.csv)");
    data.name = QstringToCharArray(pathFileName);
    ui->labelFileName->setText(pathFileName);
    if(ui->labelFileName == NULL){
        return;
    }
}


char* MainWindow::QstringToCharArray(QString qstr){
    char *str = (char*)malloc(sizeof(char)*(qstr.size() + 1));
    int i;
    for (i = 0; i < qstr.size(); i++){
        str[i] = qstr.at(i).unicode();
    }
    str[i] = 0;
    return str;
}


QStringList MainWindow::ConvertRowToQTFormat(char **row, size_t size){
    QStringList qsl = {};
    for(size_t i = 0; i < size; i++){
        qsl.append(QString::fromUtf8(row[i]));
    }
    return qsl;
}


void MainWindow::calc(){
    doOperation(LoadData, data, NULL, error);
    if(error!=Success){
        errorsReturn(error);
        error = Success;
        return;
    }
    qDebug() << "Ошибок не было";
    move();
    doOperation(Calculate, data, data.countColumn, error);
    qDebug() << "Логику загрузил";
    graph();
    qDebug() << "График нарисовал";
    qDebug() << "Ошибок не было";
}

void MainWindow::move(){
    steps();
    offsets();
    rotations();
    norms();
}

void MainWindow::steps(){
    data.steps.x = ui->stepX->text().toDouble();
    data.steps.y = ui->stepY->text().toDouble();
    data.steps.z = ui->stepZ->text().toDouble();
}


void MainWindow::offsets(){
    data.offsets.x = ui->offsetX->text().toDouble();
    data.offsets.y = ui->offsetY->text().toDouble();
    data.offsets.z = ui->offsetZ->text().toDouble();
}


void MainWindow::rotations(){
    data.rotations.x = ui->rotationX->text().toDouble();
    data.rotations.y = ui->rotationY->text().toDouble();
    data.rotations.z = ui->rotationZ->text().toDouble();
}


void MainWindow::norms(){
    data.norm.a = ui->normFrom->text().toDouble();
    data.norm.b = ui->normTo->text().toDouble();
}


void MainWindow::graph(){
    QPixmap *pix = new QPixmap(AXIS_X, AXIS_Y);
    QPainter paint(pix);
    paint.setPen(QColor(Qt::GlobalColor::black));
    paint.fillRect(0, 0, AXIS_X, AXIS_Y, QBrush(Qt::white));
    paint.translate(AXIS_X/POS2,AXIS_Y/POS2);
    for(int i = 0; i < data.size;i++){
        for(int j = 0 ; j < data.countColumn - 1;j++){
            paint.drawLine(data.coord2D[i][j].x, data.coord2D[i][j].y, data.coord2D[i][j + 1].x, data.coord2D[i][j + 1].y);
        }
    }
    for(int i = 0; i < data.size - 1;i++){
        for(int j = 0 ; j < data.countColumn;j++){
            paint.drawLine(data.coord2D[i][j].x, data.coord2D[i][j].y, data.coord2D[i + 1][j].x, data.coord2D[i + 1][j].y);
        }
    }
    ui->label->setPixmap(*pix);
}


void MainWindow::errorsReturn(Errors error){
    switch(error){
    case PtrIsNull:
        showErrorWindow("PtrIsNull");
        break;
    case File:
        showErrorWindow("No file");
        break;
    case Success:
        break;
    }
}
