#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QThread>
#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_scene = new QGraphicsScene(0, 0, 620, 580, this);
    ui->graphicsView->setScene(m_scene);
    m_scene->addRect(m_scene->sceneRect());
    this->setWindowTitle("Dungeon generator");
    connect(ui->magicBtn, &QPushButton::clicked, this, &MainWindow::fillSqr);
    connect(ui->setSeedBtn, &QPushButton::clicked, this, &MainWindow::setSeed);

    setSeed();
}

MainWindow::~MainWindow()
{
    m_scene->clear();
    delete ui;
}

void MainWindow::fillSqr()
{
    m_scene->clear();
    int sqrX = 0;
    for (int i = 0; i < m_scene->sceneRect().width() / 10; i++) {
        int sqrY = 0;
        for (int j = 0; j < m_scene->sceneRect().height() / 5; j++) {
            QGraphicsRectItem *wallRect = new QGraphicsRectItem(sqrX, sqrY, 10, 10);
            float wallInd = m_fNoise.noise(static_cast<float>(sqrX) + 2.5f, static_cast<float>(sqrY) + 2.5f);
            if (wallInd <= -0.25f) {
                QColor rectColor(QColorConstants::Black);
                wallRect->setBrush(rectColor);
            }

            m_scene->addItem(wallRect);

            qApp->processEvents();

            sqrY += 10;
        }
        sqrX += 10;
    }

    qApp->processEvents();
}

void MainWindow::setSeed()
{
    m_fNoise.generatePermutationTable(QInputDialog::getInt(this, tr("Set initial data"),tr("Input random seed value")));

}

