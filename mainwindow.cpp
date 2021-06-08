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
    for (int i = 0; i < m_scene->sceneRect().width() / 10; i++) {
        int sqrY = 0;
        for (int j = 0; j < m_scene->sceneRect().height() / 10; j++) {
            QGraphicsRectItem *wallRect = new QGraphicsRectItem(sqrX, sqrY, 10, 10);
            float wallInd = 0.0f;
            if (m_octavesCount > 1) {
                wallInd = m_fNoise.multiOctaveNoise(static_cast<float>(sqrX) + 2.5f, static_cast<float>(sqrY) + 2.5f, m_octavesCount);
            } else {
                wallInd = m_fNoise.noise(static_cast<float>(sqrX) + 2.5f, static_cast<float>(sqrY) + 2.5f);
            }

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
    }
}

