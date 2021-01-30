#pragma once

#include <QObject>
#include <QJSValue>
#include <QJSEngine>

class Caller : public QObject
{
    Q_OBJECT

    std::function<void(QJSValue)> f;

public:
    Caller(std::function<void(QJSValue)> f) : QObject(nullptr), f(f)
    {

    }

    Q_INVOKABLE void call(QJSValue v) {
        f(v);
    }
};

QJSValue newFunction(QJSEngine* forEngine, std::function<void(QJSValue)> f);
