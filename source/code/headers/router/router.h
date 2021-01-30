#pragma once

#include <QJSValue>
#include <QJsonValue>
#include <QQmlListProperty>
#include <QObject>
#include <QQmlParserStatus>
#include <QQmlComponent>

#include <optional>

#define synth_prop_impl(kind, name, default)\
std::optional<kind> m_ ## name;\
Q_SIGNAL void name ## _changed();\
public: std::optional<kind> name () {\
    return m_ ## name;\
}\
private: kind name ## _qml () {\
    return m_ ## name.value_or(default);\
}\
public: void set_ ## name(kind t) {\
    if (!m_ ## name.has_value() || m_ ## name.value() != t) {\
        m_ ## name = t; Q_EMIT name ## _changed();\
    }\
}

#define synth_prop(kind, name, default) Q_PROPERTY(kind name READ name ## _qml WRITE set_ ## name NOTIFY name ## _changed) \
synth_prop_impl(kind, name, default)

#define synth_prop_resettable(kind, name, default) Q_PROPERTY(kind name READ name ## _qml WRITE set_ ## name RESET reset_ ## name NOTIFY name ## _changed) \
synth_prop_impl(kind, name, default) \
public: void reset_ ## name() {\
    if (m_ ## name.has_value()) {\
        m_ ## name.reset(); Q_EMIT name ## _changed();\
    }\
}

class Route : public QObject
{
    Q_OBJECT

    synth_prop(QString, path, QString())
    synth_prop(QQmlComponent*, component, nullptr)
    synth_prop_resettable(QVariantMap, components, QVariantMap())
    synth_prop_resettable(QString, name, QString())

    Q_PROPERTY(QJSValue metadata MEMBER metadata WRITE setMetadata NOTIFY metadataChanged)
    public: Q_SIGNAL void metadataChanged();
    public: QJSValue metadata;
    void setMetadata(QJSValue md) {
        metadata = md;
        Q_EMIT metadataChanged();
    }

    Q_PROPERTY(QQmlListProperty<QJSValue> incomingMiddlewares READ incomingMiddlewares)
    public: QList<QJSValue*> _incomingMiddlewares;
    QQmlListProperty<QJSValue> incomingMiddlewares() { return QQmlListProperty<QJSValue>(this, &_incomingMiddlewares); }

    public: QList<QJSValue*> _outgoingMiddlewares;
    QQmlListProperty<QJSValue> outgoingMiddlewares() { return QQmlListProperty<QJSValue>(this, &_outgoingMiddlewares); }

    Q_PROPERTY(QQmlListProperty<Route> children READ children)
    Q_CLASSINFO("DefaultProperty", "children")

    public: QList<QPointer<Route>> _children;
    public: QQmlListProperty<Route> children();

    static void appendRoute(QQmlListProperty<Route>* list, Route*);
    static int routeCount(QQmlListProperty<Route>* list);
    static Route* route(QQmlListProperty<Route>* list, int);
    static void clearRoutes(QQmlListProperty<Route>* list);

};

class Router : public QObject, public QQmlParserStatus
{
    Q_OBJECT
    Q_INTERFACES(QQmlParserStatus)

    Q_PROPERTY(QQmlListProperty<Route> routes READ routes)
    Q_CLASSINFO("DefaultProperty", "routes")

    void classBegin() override {}
    void componentComplete() override;

    Q_PROPERTY(QString location READ location WRITE setLocation NOTIFY locationChanged)

    QString location() const;
    void setLocation(const QString& location);
    Q_SIGNAL void locationChanged();

    Q_PROPERTY(QJsonValue parameters READ parameters NOTIFY parametersChanged)
    QJsonValue parameters();
    Q_SIGNAL void parametersChanged();

    Q_SIGNAL void error(QJSValue any);

public:
    Router(QObject* parent = nullptr);

    QQmlListProperty<Route> routes();

    struct Private;
    QSharedPointer<Private> d;

    static void appendRoute(QQmlListProperty<Route>* list, Route*);
    static int routeCount(QQmlListProperty<Route>* list);
    static Route* route(QQmlListProperty<Route>* list, int);
    static void clearRoutes(QQmlListProperty<Route>* list);
};
