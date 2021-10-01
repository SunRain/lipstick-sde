/***************************************************************************
**
** Copyright (c) 2012-2019 Jolla Ltd.
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

#include <NgfClient>
#include <QWaylandSurface>
#include <QUrl>

#include "lipstickcompositor.h"
#include "lipstickcompositorwindow.h"
#include "notificationmanager.h"
#include "lipsticknotification.h"
#include "notificationfeedbackplayer.h"

namespace {

enum PreviewMode {
    AllNotificationsEnabled = 0,
    ApplicationNotificationsDisabled,
    SystemNotificationsDisabled,
    AllNotificationsDisabled
};

}

NotificationFeedbackPlayer::NotificationFeedbackPlayer(QObject *parent) :
    QObject(parent),
    m_ngfClient(new Ngf::Client(this)),
    m_minimumPriority(0),
    m_doNotDisturbSetting(QLatin1String("/lipstick/do_not_disturb"))
{
    connect(NotificationManager::instance(), SIGNAL(notificationRemoved(uint)), this, SLOT(removeNotification(uint)));

    QTimer::singleShot(0, this, SLOT(init()));
}

void NotificationFeedbackPlayer::init()
{
    m_ngfClient->connect();
}

void NotificationFeedbackPlayer::addNotification(uint id)
{
    LipstickNotification *notification = NotificationManager::instance()->notification(id);

    // feedback on progress update just directly omitted, not expecting practical use for playing feedback on every update
    if (notification != 0 && !notification->hasProgress()) {
        // Stop feedback previously generated by this notification, if current
        QMultiHash<LipstickNotification *, uint>::iterator it = m_idToEventId.find(notification);
        while (it != m_idToEventId.end() && it.key() == notification) {
            m_ngfClient->stop(it.value());
            it = m_idToEventId.erase(it);
        }

        // Play the feedback related to the notification if any
        const QString feedback = notification->hints().value(LipstickNotification::HINT_FEEDBACK).toString();
        QStringList feedbackItems = feedback.split(QStringLiteral(","), QString::SkipEmptyParts);

        int minimumPriority = m_minimumPriority;

        if (feedbackItems.isEmpty() && isEnabled(notification, 0)) {
            // Add generic feedback type
            feedbackItems << "default";
            // Play default feedback regardless of priorities
            minimumPriority = 0;
        }

        if (isEnabled(notification, minimumPriority) && !feedbackItems.isEmpty()) {
            QMap<QString, QVariant> properties;
            if (notification->body().isEmpty() && notification->summary().isEmpty()) {
                properties.insert("media.leds", false);
            }
            if (notification->hints().value(LipstickNotification::HINT_SUPPRESS_SOUND, false).toBool()) {
                properties.insert("media.audio", false);
            }
            if (!notification->hints().value(LipstickNotification::HINT_ORIGIN_PACKAGE).toString().isEmpty()) {
                // android notification, play vibra only when explicitly asked via separate hint
                properties.insert("media.vibra", false);
            }

            if (doNotDisturbMode()) {
                // no sound or vibra, but led is allowed
                properties.insert("media.vibra", false);
                properties.insert("media.audio", false);
            } else {
                QString soundFile = notification->hints().value(LipstickNotification::HINT_SOUND_FILE).toString();
                if (!soundFile.isEmpty()) {
                    if (soundFile.startsWith(QStringLiteral("file://"))) {
                        soundFile = QUrl(soundFile).toLocalFile();
                    }

                    properties.insert(QStringLiteral("sound.filename"), soundFile);
                    // Sound is enabled explicitly if sound-file hint is set.
                    properties.insert(QStringLiteral("sound.enabled"), true);
                }
            }

            foreach (const QString &item, feedbackItems) {
                m_ngfClient->stop(item);
                m_idToEventId.insert(notification, m_ngfClient->play(item, properties));
            }
        }

        // vibra played if it's asked regardless of priorities
        if (!doNotDisturbMode() && isEnabled(notification, 0)
                && notification->hints().value(LipstickNotification::HINT_VIBRA, false).toBool()) {
            m_ngfClient->stop("vibra");
            m_idToEventId.insert(notification, m_ngfClient->play("vibra", QMap<QString, QVariant>()));
        }
    }
}

void NotificationFeedbackPlayer::removeNotification(uint id)
{
    LipstickNotification *notification = NotificationManager::instance()->notification(id);

    if (notification != 0) {
        // Stop the feedback related to the notification, if any
        QMultiHash<LipstickNotification *, uint>::iterator it = m_idToEventId.find(notification);
        while (it != m_idToEventId.end() && it.key() == notification) {
            m_ngfClient->stop(it.value());
            it = m_idToEventId.erase(it);
        }
    }
}

bool NotificationFeedbackPlayer::isEnabled(LipstickNotification *notification, int minimumPriority)
{
    if (notification->restored())
        return false;

    uint mode = AllNotificationsEnabled;
    LipstickCompositorWindow *win = LipstickCompositor::instance()->m_windows.value(LipstickCompositor::instance()->topmostWindowId());
    if (win != 0) {
        mode = win->notificationMode();
    }

    int urgency = notification->urgency();
    int priority = notification->priority();
    int notificationIsCritical = urgency >= 2 || notification->hints().value(LipstickNotification::HINT_DISPLAY_ON).toBool();

    return (priority >= minimumPriority || notificationIsCritical)
            && (mode == AllNotificationsEnabled
                || (mode == ApplicationNotificationsDisabled && notificationIsCritical)
                || (mode == SystemNotificationsDisabled && urgency < 2));
}

int NotificationFeedbackPlayer::minimumPriority() const
{
    return m_minimumPriority;
}

void NotificationFeedbackPlayer::setMinimumPriority(int minimumPriority)
{
    m_minimumPriority = minimumPriority;

    emit minimumPriorityChanged();
}

bool NotificationFeedbackPlayer::doNotDisturbMode() const
{
    return m_doNotDisturbSetting.value().toBool();
}
