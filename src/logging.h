/***************************************************************************
**
** Copyright (c) 2020 Open Mobile Platform LLC.
**
** This file is part of lipstick.
**
** This library is free software; you can redistribute it and/or
** modify it under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation
** and appearing in the file LICENSE.LGPL included in the packaging
** of this file.
**
****************************************************************************/


#ifndef LIPSTICK_LOGGING_H
#define LIPSTICK_LOGGING_H

#include <QLoggingCategory>

Q_DECLARE_LOGGING_CATEGORY(lcLipstickCoreLog)
Q_DECLARE_LOGGING_CATEGORY(lcLipstickHwcLog)
Q_DECLARE_LOGGING_CATEGORY(lcLipstickAppLaunchLog)
Q_DECLARE_LOGGING_CATEGORY(lcLipsitckCompositorLog)
Q_DECLARE_LOGGING_CATEGORY(lcLipsitckDisplayStateLog)
Q_DECLARE_LOGGING_CATEGORY(lcLipsitckNotificationsLog)
Q_DECLARE_LOGGING_CATEGORY(lcLipstickTouchScreenLog)
Q_DECLARE_LOGGING_CATEGORY(lcLipstickVolCtrlLog)

#define lcCmpstrDBG     qCDebug(lcLipsitckCompositorLog)
#define lcDsplySateDBG  qCDebug(lcLipsitckDisplayStateLog)
#define lcNotifyDBG     qCDebug(lcLipsitckNotificationsLog)
#define lcTuchScrenDBG  qCDebug(lcLipstickTouchScreenLog)
#define lcVolCtrlDBG    qCDebug(lcLipstickVolCtrlLog)

#endif
