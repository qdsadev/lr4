#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "entrypoint.h"
#include "filemanager.h"
#include "logic.h"

#define POS2 2
#define PEN_WIDTH 2

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Data data;
    Errors error = Success;
    QStringList ConvertRowToQTFormat(char **row, size_t size);
    void graph();
    char* QstringToCharArray(QString qstr);
    void errorsReturn(Errors error);
    void showErrorWindow(char* nameError);
    void openWindowFile();
    void calc();
    void steps();
    void offsets();
    void rotations();
    void norms();
    void move();
};
#endif // MAINWINDOW_H
