#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include "PoinstSet/pointsset.h"
#include "QtWidgets/qgraphicsscene.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void update();
    PointsSet *getCurrentSet();
    void setCurrentSet(int index);

private slots:
    void addPointClicked();

    void addSetClicked();

    void onCurrentSetChanged(int index);

private:
    Ui::MainWindow *ui;
    std::vector<PointsSet*> sets = {};
    int selectedSet = 0;
    void updateDistanceComponent();
    void updateAngleComponent();
    void updateGraphicsComponent();
};
#endif // MAINWINDOW_H
