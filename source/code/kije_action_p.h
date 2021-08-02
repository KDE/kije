/*
 *  SPDX-FileCopyrightText: 2021 Carson Black <uhhadd@gmail.com>
 *
 *  SPDX-License-Identifier: LGPL-2.0-or-later
 */

#include "kije_action.h"

struct KijeAction::Private
{
    QString identifier;
    QString text;

    QList<KijeAction*> actions;
};