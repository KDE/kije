/*
 *  SPDX-FileCopyrightText: 2021 Carson Black <uhhadd@gmail.com>
 *
 *  SPDX-License-Identifier: LGPL-2.0-or-later
 */

#pragma once

#include <QPointer>
#include <QQmlComponent>

#include "kije_window.h"

#include "kije_app.h"

struct KijeDocApp::Private
{
    QPointer<QQmlComponent> viewDelegate;
    QList<KijeWindow*> windows;
    KijePage* activePage = nullptr;
};
