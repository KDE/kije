#pragma once

#include "router/router.h"
#include "router/routertree.h"

struct Router::Private {
    QList<QPointer<Route>> routes;
    RouterTree<QPointer<Route>> routeTree;
    QString location;
    QJsonValue parameters;

    bool initialised = false;
    QString awaitingLocation;
};