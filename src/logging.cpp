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

#include "logging.h"

#ifdef VERBOSE_DBG
#define DBG_LEVEL QtDebugMsg
#else
#define DBG_LEVEL QtWarningMsg
#endif

Q_LOGGING_CATEGORY(lcLipstickCoreLog,           "org.nemomobile.lipstick",                  DBG_LEVEL)
Q_LOGGING_CATEGORY(lcLipstickHwcLog,            "org.nemomobile.lipstick.hwc",              DBG_LEVEL)
Q_LOGGING_CATEGORY(lcLipstickAppLaunchLog,      "org.nemomobile.lipstick.applaunch",        DBG_LEVEL)
Q_LOGGING_CATEGORY(lcLipsitckCompositorLog,     "org.nemomobile.lipstick.compositor",       DBG_LEVEL)
Q_LOGGING_CATEGORY(lcLipsitckDisplayStateLog,   "org.nemomobile.lipstick.display",          DBG_LEVEL)
Q_LOGGING_CATEGORY(lcLipsitckNotificationsLog,  "org.nemomobile.lipstick.notifications",    DBG_LEVEL)
Q_LOGGING_CATEGORY(lcLipstickTouchScreenLog,    "org.nemomobile.lipstick.touchscreen",      DBG_LEVEL)
Q_LOGGING_CATEGORY(lcLipstickVolCtrlLog,        "org.nemomobile.lipstick.volume",           DBG_LEVEL)
