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

#ifndef SWIFTWORKER_H
#define SWIFTWORKER_H

#ifndef QT_NO_SYSTEMTRAYICON

#include <QObject>
#include <QThread>
#include <QDialog>
#include <QString>
#include <QSystemTrayIcon>

#include "plugininterface.h"

class SwiftWorker : public QObject
{
    Q_OBJECT

public:
    SwiftWorker(QObject *parent = nullptr);
    ~SwiftWorker();

    static void declareQML();

    Q_INVOKABLE void messageSended(QString message);
    Q_INVOKABLE void openLinkInBrowser(QString url);
    Q_INVOKABLE void newText(QString text);
    Q_INVOKABLE void getPluginList();
    Q_INVOKABLE void sendMessageToPlugin(QString message, QString pluginIid);
    Q_INVOKABLE void removePlugin(QString iid);
    Q_INVOKABLE void actuPlugins();

public slots:
    void reponseReceived(QString reponse, bool isFin, QString typeMessage, QString url);
    void open();
    void addProp(QString prop);
    void removeAllProp();
    void removeProp(int index);
    void showQmlFile(QString qmlUrl);
    void pluginTrouved(QString name);
    void messageToQml(QString message, QString pluginIid);
    void trayIconActivated(QSystemTrayIcon::ActivationReason reason);

signals:
    void reponse(QString text, bool isFin, QString typeMessage, QString url);
    void message(QString message);
    void textChanged(QString text);
    void showWindow(int x, int y);
    void addProposition(QString prop);
    void removeAllProposition();
    void removeProposition(int index);
    void addBaseProp();
    void showQml(QString qmlUrl);
    void getAllPlugin();
    void pluginName(QString name);
    void signalSendMessageToPlugin(QString message, QString pluginIid);
    void pluginSendedMessageToQml(QString message, QString pluginIid);
    void signalRemovePlugin(QString iid);
    void signalActuPlugins();

private:
    void setIcon(QString path);
    void createActions();
    void createTrayIcon();

    QThread engineThread;

    QAction *restoreAction;
    QAction *quitAction;

    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;
};

#endif

#endif
