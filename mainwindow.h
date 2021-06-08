#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>

#include <QGraphicsRectItem>
#include <QGraphicsLineItem>
#include <QGraphicsPixmapItem>

#include <QTimer>

#include "fractalnoise.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_setOctavesBtn_clicked();

    void on_comboBox_activated(const QString &arg1);

    void on_squarePxSize_valueChanged(int arg1);

private:
    void fillSqr();
    void setSeed();

    FractalNoise m_fNoise;

    int m_octavesCount;

    int m_sqrSize;

    Ui::MainWindow *ui;
    QGraphicsScene *m_scene;
};
#endif // MAINWINDOW_H
