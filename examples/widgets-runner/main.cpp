/*
 *  SPDX-FileCopyrightText: 2020 Carson Black <uhhadd@gmail.com>
 *
 *  SPDX-License-Identifier: LGPL-2.0-or-later
 */
 
#include <QApplication>
#include <QCoreApplication>
#include <QQmlApplicationEngine>
#include <QUrl>

int main(int argc, char* argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setApplicationName("kije-widgets-qmlrunner");
    QCoreApplication::setOrganizationName("KDE");

    QApplication app(argc, argv);

    QQmlApplicationEngine engine;

    const QUrl url(app.arguments()[1]);
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreated,
        &app,
        [url](QObject* obj, const QUrl& objUrl) {
            if ((obj == nullptr) && url == objUrl) {
                QCoreApplication::exit(-1);
            }
        },
        Qt::QueuedConnection);
    engine.load(url);

    return QApplication::exec();
}