#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QThread>
#include <QInputDialog>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_scene = new QGraphicsScene(0, 0, 618, 578, this);
    ui->graphicsView->setScene(m_scene);
    m_scene->addRect(m_scene->sceneRect());
    this->setWindowTitle("Dungeon generator");
    this->setFixedSize(800, 600);
    connect(ui->magicBtn, &QPushButton::clicked, this, &MainWindow::fillSqr);
    connect(ui->setSeedBtn, &QPushButton::clicked, this, &MainWindow::setSeed);

    m_sqrSize = 5;
    m_octavesCount = 1;
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
    for (int i = 0; i < m_scene->sceneRect().width() / m_sqrSize; i++) {
        int sqrY = 0;
        for (int j = 0; j < m_scene->sceneRect().height() / m_sqrSize; j++) {
            QGraphicsRectItem *wallRect = new QGraphicsRectItem(sqrX, sqrY, m_sqrSize, m_sqrSize);
            float wallInd = 0.0f;
            if (m_octavesCount > 1) {
                wallInd = m_fNoise.multiOctaveNoise(static_cast<float>(sqrX) * 0.01f/* + 2.5f*/, static_cast<float>(sqrY) * 0.01f/*+ 2.5f*/, m_octavesCount);
            } else {
                wallInd = m_fNoise.noise(static_cast<float>(sqrX) * 0.01f/* + 2.5f*/, static_cast<float>(sqrY) * 0.01f/* + 2.5f*/);
            }

            qDebug() << wallInd;

            if (wallInd >= 0 /*<= -0.15f*/) {
                QColor rectColor(QColorConstants::Black);
                wallRect->setBrush(rectColor);
            }

            m_scene->addItem(wallRect);

            qApp->processEvents();

            sqrY += m_sqrSize;
        }
        sqrX += m_sqrSize;
    }

    qApp->processEvents();
}

void MainWindow::setSeed()
{
    m_fNoise.generatePermutationTable(QInputDialog::getInt(this, tr("Set initial data"),tr("Input random seed value")));

}

void MainWindow::on_setOctavesBtn_clicked()
{
    m_octavesCount = QInputDialog::getInt(this, tr("Set octaves count"),tr("Input octaves count"));
}


void MainWindow::on_comboBox_activated(const QString &arg1)
{
    if (arg1 == "Quintic") {
        m_fNoise.setInterpolationFunc(FractalNoise::Interpolation::QUINTIC);
    } else if (arg1 == "Cosine") {
        m_fNoise.setInterpolationFunc(FractalNoise::Interpolation::COSINE);
    } else if (arg1 == "Cubic") {
        m_fNoise.setInterpolationFunc(FractalNoise::Interpolation::CUBIC);
    } else if (arg1 == "Linear") {
        m_fNoise.setInterpolationFunc(FractalNoise::Interpolation::LINEAR);
    }
}


void MainWindow::on_squarePxSize_valueChanged(int arg1)
{
    m_sqrSize = arg1;
}

