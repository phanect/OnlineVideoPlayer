#include <QtGui/QGuiApplication>
#include "qtquick2applicationviewer.h"

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);

    QtQuick2ApplicationViewer viewer;
    viewer.setOrientation(QmlApplicationViewer::ScreenOrientationAuto);

    viewer.setMainQmlFile(QStringLiteral("qml/OnlineVideoPlayer/main.qml"));
    viewer.showExpanded();

    return app.exec();
}
