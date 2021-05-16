#include <QtDataVisualization/qutils.h>

#include <QGuiApplication>
#include <QDir>
#include <QtQuick/QQuickView>
#include <QtQml/QQmlEngine>

#include "fractalnoise.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQuickView viewer;

    FractalNoise fNoise;

    viewer.setFormat(QtDataVisualization::qDefaultSurfaceFormat());

    QString extraImportPath(QStringLiteral("%1/../../../../%2"));

    viewer.engine()->addImportPath(extraImportPath.arg(QGuiApplication::applicationDirPath(), QString::fromLatin1("qml")));

    viewer.setSource(QUrl("qrc:/qml/main.qml"));

    viewer.setTitle(QStringLiteral("Dungeon generator"));
    viewer.setResizeMode(QQuickView::SizeRootObjectToView);
    viewer.show();

    return app.exec();
}
