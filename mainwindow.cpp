#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "operators.h"
#include "gradientdescent.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->widget->setInteraction(QCP::iRangeDrag,true);
    ui->widget->setInteraction(QCP::iRangeZoom,true);
    ui->widget->addGraph();
    ui->widget->xAxis->setRange(-10, 60);
    ui->widget->yAxis->setRange(0, 100);
    ui->widget->graph(0)->setScatterStyle(Disk(QColor("black")));
    ui->widget->graph(0)->setLineStyle(QCPGraph::lsNone);

    vector<pair<string, vector<double>>> three_cols = read_csv("training_dataset.csv");
    for(int i=0; i<(int)three_cols[0].second.size(); i++){
        X.push_back(three_cols[0].second[i]);
        Y.push_back(three_cols[1].second[i]);
//        cout<<three_cols[0].second[i] <<", "<<three_cols[1].second[i]<<endl;
        addPoint(three_cols[0].second[i],three_cols[1].second[i]);
    }

    this->gradientdescen = new GradientDescent(X,Y);
    plot();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addPoint(double x, double y)
{
    qv_x.append(x);
    qv_y.append(y);
    updatMinMax(x,y);
}

void MainWindow::clearData()
{
    qv_x.clear();
    qv_y.clear();
    this->W.clear();
    ui->widget->removeItem(separator);
}

void MainWindow::plot()
{
    ui->widget->graph(0)->setData(qv_x,qv_y);
    ui->widget->replot();
    ui->widget->update();
}

void MainWindow::updatMinMax(double x, double y)
{
    min = (min>x)? x : min;
    min = (min>y)? y : min;
    max = (max<x)? x : max;
    max = (max<y)? y : max;
    max +=(max>0)?max/6:-max/6; min +=(min<0)?min/6:-min/6;
}

void MainWindow::paintLine()
{
    separator = new QCPItemLine(ui->widget);
    QPen pen(QColor("red"));
    pen.setWidth(5);
    separator->setPen(pen);

    separator->start->setCoords(-200, -200*W[0]+W[1]);
    separator->end->setCoords  ( 200,  200*W[0]+W[1]);

    ui->widget->addItem(separator);
    plot();
}

vector<pair<string, vector<double>>> MainWindow::read_csv(string filename)
{
    vector<pair<string, vector<double>>> result;
    ifstream myFile(filename);

    if(!myFile.is_open())
        throw runtime_error("Could not open file");

    string line, colname;
    double val;

    if(myFile.good())
    {
        getline(myFile, line);
        stringstream ss(line);
        while(getline(ss, colname, ',')){
            result.push_back({colname, vector<double> {}});
        }
    }

    while(getline(myFile, line))
    {
        stringstream ss(line);
        int colIdx = 0;
        while(ss >> val){
            result.at(colIdx).second.push_back(val);
            if(ss.peek() == ',') ss.ignore();
            colIdx++;
        }
    }
    myFile.close();
    return result;
}

void MainWindow::on_clearData_clicked()
{
    clearData();
    plot();
    min = 999999; max =-999999;
}

void MainWindow::on_calculateButton_clicked()
{
    this->W.resize(2);
    this->W = this->gradientdescen->gradientMethod(0.01,W,gradientdescen->MSE);
    cout<<"W = ["<<this->W[0]<<", "<<this->W[1]<<"]"<<endl;
//    cout<<"Ls(w) = "<<gradientdescen->MAE(this->W)<<endl;
    paintLine();
}
