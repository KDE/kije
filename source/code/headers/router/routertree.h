#pragma once

#include <QPair>
#include <QMap>
#include <QList>
#include <QJsonObject>
#include <QJsonArray>

#include <tuple>
#include <utility>
#include <variant>
#include <ranges>

template<typename Leaf>
class RouterTree {

    using Route = std::pair<QStringList,Leaf>;
    QList<Route> routes;

public:
    void insert(const QStringList& path, const Leaf& leaf)
    {
        routes << std::make_pair(path, leaf);
    }

    [[nodiscard]] std::optional<std::pair<QJsonObject,QList<Leaf>>> lookup(const QStringList& path) const
    {
        QJsonArray wildcards;
        QJsonObject params;

        auto nestedLookup = [this](const QStringList& path) -> std::optional<Leaf> {
            for (Route route : routes) {
                if (route.first.length() != path.length()) {
                    continue;
                }

                for (int i = 0; i < route.first.length(); i++) {
                    QString matchingAgainst = route.first[i];
                    auto with = path[i];

                    if (matchingAgainst.startsWith(":") || matchingAgainst == '*' || matchingAgainst == with) {
                        continue;
                    }

                    goto lambdaNestedContinue;
                }

                return route.second;

            lambdaNestedContinue:
                continue;
            }

            return {};
        };

        for (Route route : routes) {
            if (route.first.length() != path.length()) {
                continue;
            }

            for (int i = 0; i < route.first.length(); i++) {
                QString matchingAgainst = route.first[i];
                auto with = path[i];

                if (matchingAgainst.startsWith(":")) {
                    auto objName = matchingAgainst.mid(1);

                    params[objName] = with;
                    continue;
                } else if (matchingAgainst == '*') {
                    wildcards.append(with);
                    continue;
                } else if (matchingAgainst == with) {
                    continue;
                }

                goto nestedContinue;
            }

            {
                QJsonObject obj;
                obj["wildcards"] = wildcards;
                obj["params"] = params;

                auto copy = path;
                copy.pop_back();

                QList<Leaf> leaves;
                while (copy.length() != 0) {
                    auto i = nestedLookup(copy);
                    if (i.has_value()) {
                        leaves << i.value();
                    }
                    copy.pop_back();
                }

                std::reverse(leaves.begin(), leaves.end());

                return std::make_pair(obj, leaves + QList{route.second});
            }

        nestedContinue:
            continue;
        }

        return {};
    }

};