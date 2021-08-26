#pragma once

#ifdef USE_KIJE_WIDGET_EMBED

#include "kije_widget_embed.h"

struct KijeWidgetEmbed::Private
{
    QPointer<QWidget> lastHovered;
    QPointer<QWidget> widget;
};

#endif
