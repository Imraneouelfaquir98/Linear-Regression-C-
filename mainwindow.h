#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include "disk.h"
#include <string>
#include <fstream>
#include <vector>
#include <utility> // pair
#include <stdexcept> // runtime_error
#include <sstream>
#include "gradientdescent.h"

using namespace std;

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    vector<double> X;
    vector<double> Y;
    vector<double> W;

    GradientDescent * gradientdescen;

    double min = 999999, max =-999999;
    QCPItemLine     *separator;
    void addPoint(double x, double y);
    void clearData();
    void plot     ();
    void updatMinMax(double x, double y);
    void paintLine();
    vector<pair<string, vector<double>>> read_csv(string filename);


private slots:
    void on_clearData_clicked();
//    void clickedGraph(QMouseEvent * event);

    void on_calculateButton_clicked();

private:
    Ui::MainWindow *ui;
    QVector<double> qv_x, qv_y;
};

#endif // MAINWINDOW_H
