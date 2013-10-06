/*************************************************************************************
 *  Copyright (C) 2013 by Alejandro Fiestas Fiestas <afiestas@kde.org>               *
 *                                                                                   *
 *  This program is free software; you can redistribute it and/or                    *
 *  modify it under the terms of the GNU General Public License                      *
 *  as published by the Free Software Foundation; either version 2                   *
 *  of the License, or (at your option) any later version.                           *
 *                                                                                   *
 *  This program is distributed in the hope that it will be useful,                  *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of                   *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                    *
 *  GNU General Public License for more details.                                     *
 *                                                                                   *
 *  You should have received a copy of the GNU General Public License                *
 *  along with this program; if not, write to the Free Software                      *
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA   *
 *************************************************************************************/

#include "filereceiver.h"
#include "../BlueDevilDaemon.h"
#include "obexagent.h"
#include "obex_agent_manager.h"

#include <QDBusConnection>
#include <QDBusPendingCall>
#include <QDBusPendingCallWatcher>

#include <KDebug>

FileReceiver::FileReceiver(QObject* parent) : QObject(parent)
{
    kDebug(dblue());
    qDBusRegisterMetaType<QVariantMap>();

    ObexAgent *obexAgent = new ObexAgent(this);
    org::bluez::obex::AgentManager1 *agent = new org::bluez::obex::AgentManager1("org.bluez.obex", "/org/bluez/obex", QDBusConnection::sessionBus(), this);

    QDBusPendingReply <void > r = agent->RegisterAgent(QDBusObjectPath("/BlueDevil_receiveAgent"));
    QDBusPendingCallWatcher *watcher = new QDBusPendingCallWatcher(r, this);
    connect(watcher, SIGNAL(finished(QDBusPendingCallWatcher*)), SLOT(agentRegistered(QDBusPendingCallWatcher*)));
}

FileReceiver::~FileReceiver()
{

}

void FileReceiver::agentRegistered(QDBusPendingCallWatcher* call)
{
    QDBusPendingReply <void > r = *call;
    kDebug(dblue()) << "Error: " << r.isError();
    if (r.isError()) {
        kDebug(dblue()) << r.error().message();
    }

    call->deleteLater();
}