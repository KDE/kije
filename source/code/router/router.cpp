#include <QQmlContext>

#include "router/router.h"
#include "router/router_p.h"

#include "router/routerslot.h"

QQmlListProperty<Route> Router::routes()
{
    return QQmlListProperty<Route>(this, nullptr, appendRoute, routeCount, route, clearRoutes);
}

void Router::appendRoute(QQmlListProperty<Route>* list, Route* route)
{
    qobject_cast<Router*>(list->object)->d->routes << QPointer(route);
}

int Router::routeCount(QQmlListProperty<Route>* list)
{
    return qobject_cast<Router*>(list->object)->d->routes.count();
}

Route* Router::route(QQmlListProperty<Route>* list, int idx)
{
    return qobject_cast<Router*>(list->object)->d->routes[idx];
}

void Router::clearRoutes(QQmlListProperty<Route>* list)
{
    qobject_cast<Router*>(list->object)->d->routes.clear();
}

void Router::componentComplete()
{
    std::function<void(QList<QPointer<Route>>,QString)> registerRec
    =
    [this, &registerRec](QList<QPointer<Route>> items, QString prefix) {
        for (const auto& item : items) {
            d->routeTree.insert((prefix + item->path().value()).split("/", Qt::SkipEmptyParts), item);

            registerRec(item->_children, item->path().value());
        }
    };

    registerRec(d->routes, QString());
    qmlContext(this)->parentContext()->setContextProperty("$router", this);

    d->initialised = true;
    setLocation(d->awaitingLocation);

    qDebug() << d->routeTree.lookup({"users", "popcorn", "delete"}).value();
}

QString Router::location() const
{
    return d->location;
}

QString normalisedLocation(const QString& in)
{
    return "/" + in.split("/", Qt::SkipEmptyParts).join("/");
}

void Router::setLocation(const QString& location)
{
    if (!d->initialised) {
        d->awaitingLocation = location;
        return;
    }

    if (d->location == normalisedLocation(location)) {
        return;
    }

    auto mu = d->routeTree.lookup(normalisedLocation(location).split("/", Qt::SkipEmptyParts));
    if (!mu.has_value()) {
        Q_EMIT error(QJSValue(QString("route not found: %1").arg(normalisedLocation(location))));
        return;
    }

    auto& [lhs, rhs] = mu.value();
    d->parameters = lhs;

    Q_EMIT parametersChanged();

    d->location = normalisedLocation(location);

    qDebug() << qmlContext(this)->parentContext()->findChild<RouterSlot*>(QString(), Qt::FindDirectChildrenOnly);
}

QJsonValue Router::parameters()
{
    return d->parameters;
}


Router::Router(QObject* parent) : QObject(parent), d(new Private)
{

}


void Route::appendRoute(QQmlListProperty<Route>* list, Route* route)
{
    qobject_cast<Route*>(list->object)->_children << QPointer(route);
}

int Route::routeCount(QQmlListProperty<Route>* list)
{
    return qobject_cast<Route*>(list->object)->_children.count();
}

Route* Route::route(QQmlListProperty<Route>* list, int idx)
{
    return qobject_cast<Route*>(list->object)->_children[idx];
}

void Route::clearRoutes(QQmlListProperty<Route>* list)
{
    qobject_cast<Route*>(list->object)->_children.clear();
}

QQmlListProperty<Route> Route::children()
{
    return QQmlListProperty<Route>(this, nullptr, appendRoute, routeCount, route, clearRoutes);
}
