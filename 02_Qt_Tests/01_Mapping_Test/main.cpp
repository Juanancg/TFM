/*
 * #include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
*/
//#include <QGuiApplication>
#include <QtWidgets/QApplication>
#include <QtQml/QQmlContext>
#include <QtQuick/QQuickView>
#include <QtCore/QDir>
#include <QQmlApplicationEngine>


static const std::string scAPPLICATION_NAME = "Test";

/********************************************************************************************//**
 ******************************* FUNCTION *******************************************************
 ************************************************************************************************/
int main(int argc, char *argv[])
{



    /** Instantiate QML object */
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication app(argc, argv);
 //   app.setWindowIcon(QIcon("view/images/iconGMV.png"));
 //   DataBackendSettings dataBackendSettingsObj ;

 //   dataBackendStatus objDataBackendStatus;

    /** Instantiate backend project */
    QQmlApplicationEngine engine;
    //QGuiApplication engine;
   // engine.rootContext()->setContextProperty("dataBackend", &dataBackendObj);
   // engine.rootContext()->setContextProperty("dataBackendSettings", &dataBackendSettingsObj);

    /** Start QML engine */
    int exitcode;
    // Cargar dos ventanas
    engine.load(QUrl(QLatin1String("qrc:MainWindow.qml")));
    //engine.load(QUrl(QLatin1String("qrc:/view/GisSection/GisWindow.qml")));

    if (engine.rootObjects().isEmpty())
    {
        exitcode = -1;
    }
    else
    {
        /** Launch execution of app object */

    }
    exitcode = app.exec();

    return exitcode;


}
