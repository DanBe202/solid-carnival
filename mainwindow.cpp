#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(this->ui->addSet, &QPushButton::clicked, this, &MainWindow::addSetClicked);
    connect(this->ui->addPoint, &QPushButton::clicked, this, &MainWindow::addPointClicked);
    connect(this->ui->setSelector, &QComboBox::currentIndexChanged, this, &MainWindow::onCurrentSetChanged);
}

MainWindow::~MainWindow()
{
    delete ui;
}

PointsSet *MainWindow::getCurrentSet() {
    return this->sets[this->selectedSet];
}

void MainWindow::setCurrentSet(int index) {
    this->selectedSet = index;
}

void MainWindow::updateDistanceComponent() {
    QString content = "Points sorted by distance:\n";
    PointsList list(*this->getCurrentSet()->getList());
    list.sortByDistance();
    PointsListItem *item = list.getFirst();
    while (item != NULL) {
        content.append("Point(");
        content.append(QString::number(item->X));
        content.append(" , ");
        content.append(QString::number(item->Y));
        content.append(") - ");
        content.append(QString::number(PointsList::distanceFromBegin(*item)));
        content.append("\n");
        item = item->next;
    }
    this->ui->sortedByDistance->setText(content);
}

void MainWindow::updateAngleComponent() {
    QString content = "Points sorted by distance:\n";
    PointsList list(*this->getCurrentSet()->getList());
    list.sortByAngle();
    PointsListItem *item = list.getFirst();
    while (item != NULL) {
        content.append("Point(");
        content.append(QString::number(item->X));
        content.append(" , ");
        content.append(QString::number(item->Y));
        content.append(") - ");
        content.append(QString::number(PointsList::angleFromOX(*item)));
        content.append("\n");
        item = item->next;
    }
    this->ui->sortedByAngle->setText(content);
}

void MainWindow::update() {
    this->updateDistanceComponent();
    this->updateAngleComponent();
}

void MainWindow::addPointClicked()
{
    int X = this->ui->inputX->text().toInt();
    int Y = this->ui->inputY->text().toInt();
    this->getCurrentSet()->getList()->addPoint(X, Y);
    this->update();
}

void MainWindow::addSetClicked()
{
    string name = this->ui->inputSetName->text().toStdString();
    this->sets.push_back(new PointsSet(name));
    this->ui->setSelector->addItem(QString::fromStdString(name));
    this->ui->setSelector->setCurrentIndex(this->sets.size() - 1);
    this->ui->inputSetName->clear();
}


void MainWindow::onCurrentSetChanged(int index)
{
    this->setCurrentSet(index);
    this->update();
}


