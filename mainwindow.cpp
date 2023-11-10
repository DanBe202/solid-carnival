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

void MainWindow::updateGraphicsComponent() {
    this->ui->graphicsView->setBackgroundBrush(QBrush(Qt::white));
    QGraphicsScene *scene = new QGraphicsScene;
    scene->setSceneRect(0, 0, this->ui->graphicsView->width() - 10, this->ui->graphicsView->height() - 10);
    int scale = this->ui->graphicsView->width() / 40;
    int offsetX = this->ui->graphicsView->width() / 2;
    int offsetY = this->ui->graphicsView->height() / 2;
    scene->addLine(0, offsetY, this->ui->graphicsView->width(), offsetY, QPen());
    scene->addLine(offsetX, 0, offsetX, this->ui->graphicsView->height(), QPen());
    PointsListItem *item = this->getCurrentSet()->getList()->getFirst();
    while (item != NULL) {
        scene->addEllipse((item->X * scale) + offsetX - 3, ((-item->Y * scale) + offsetY) - 3, 6, 6, QPen(), QBrush(Qt::red));
        item = item->next;
    }
    this->ui->graphicsView->setScene(scene);
}

void MainWindow::update() {
    this->updateDistanceComponent();
    this->updateAngleComponent();
    this->updateGraphicsComponent();
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


