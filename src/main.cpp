/* Swift Assistant is a simple, user-friendly assistant based on an extension system.

   Copyright (C) <2021>  <SwiftApp>

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>. */

#include <QQuickStyle>
#include <QSystemTrayIcon>
#include <QMessageBox>
#include <QtWebEngine/qtwebengineglobal.h>
#include <QtQml/QQmlApplicationEngine>
#include <QtQml/QQmlContext>
#include <QTranslator>
#include <QDir>

#ifndef QT_NO_WIDGETS
#include <QtWidgets/QApplication>
typedef QApplication Application;
#else
#include <QtGui/QGuiApplication>
typedef QGuiApplication Application;
#endif

#include "swiftworker.h"
#include "plugininterface.h"

#ifndef QT_NO_SYSTEMTRAYICON

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(res);

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QCoreApplication::setApplicationName("Swift Assistant");
    QCoreApplication::setOrganizationName("swiftapp");
    QCoreApplication::setApplicationVersion(QT_VERSION_STR);
    QtWebEngine::initialize();

    Application app(argc, argv);

    QString locale = QLocale::system().name().section('_', 0, 0);

    QTranslator translator;
    if (!translator.load(QString(":/ts/swiftassistant_") + locale != "fr" ? locale : "")) {
        if (locale != "fr") {
            translator.load(QString(":/ts/swiftassistant_en"));
            app.installTranslator(&translator);
        }
    }
    else {
        app.installTranslator(&translator);
    }

    if (!QSystemTrayIcon::isSystemTrayAvailable()) {
        QMessageBox::critical(nullptr, QObject::tr("Systray"),
                              QObject::tr("I couldn't detect any system tray "
                                          "on this system."));
        return 1;
    }

    QQuickStyle::setStyle("Imagine");

    QQmlApplicationEngine appEngine;
    SwiftWorker::declareQML();
    appEngine.load(QUrl("qrc:/main.qml"));

    return app.exec();
}

#endif
