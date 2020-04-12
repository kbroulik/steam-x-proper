/*
 * Copyright 2020 Kai Uwe Broulik <kde@broulik.de>
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "steamxproper.h"

#include <QDebug>

#include <QX11Info>

#include <KServiceTypeTrader>
#include <KWindowSystem>
#include <KWindowSystem/netwm.h>

SteamXProper::SteamXProper(QObject *parent)
    : QObject(parent)
{
    // Get the STEAM_GAME atom
    QScopedPointer<xcb_intern_atom_reply_t, QScopedPointerPodDeleter> atomReply(xcb_intern_atom_reply(QX11Info::connection(),
        xcb_intern_atom_unchecked(QX11Info::connection(), false, 10, "STEAM_GAME"),
    nullptr));

    if (atomReply.isNull()) {
        qWarning() << "Failed to get STEAM_GAME atom";
        return;
    }

    m_steamGameAtom = atomReply->atom;

    // Is it intentional I get a windowAdded for all windows initially?
    connect(KWindowSystem::self(), &KWindowSystem::windowAdded, this, &SteamXProper::onWindowAdded);

    /*const auto windows = KWindowSystem::windows();
    for (WId id : windows) {
        onWindowAdded(id);
    }*/
}

SteamXProper::~SteamXProper() = default;

void SteamXProper::onWindowAdded(WId id)
{
    auto *c = QX11Info::connection();

    auto cookie = xcb_get_property(c, false, id, m_steamGameAtom, XCB_ATOM_CARDINAL, 0, 1);
    QScopedPointer<xcb_get_property_reply_t, QScopedPointerPodDeleter> reply(xcb_get_property_reply(QX11Info::connection(), cookie, nullptr));
    if (reply.isNull() || reply.data()->value_len != 1 || reply.data()->format != uint8_t(32)) {
        return;
    }

    auto *data = reinterpret_cast<uint32_t *>(xcb_get_property_value(reply.data()));
    if (!data) {
        return;
    }

    const auto steamGameId = *data;

    // Find matching steam game
    // TODO cache this?
    const auto services = KServiceTypeTrader::self()->query(QStringLiteral("Application"),
                                                            QStringLiteral("exist Exec and ('steam steam://rungameid/%1' == Exec)").arg(QString::number(steamGameId)));
    if (services.isEmpty()) {
        qDebug() << "Could not find corresponding game with id" << steamGameId;
        return;
    }

    const auto service = services.first();

    NETWinInfo info(c, id, QX11Info::appRootWindow(), {}, NET::WM2DesktopFileName);
    info.setDesktopFileName(qUtf8Printable(service->entryPath()));

    qDebug() << "marked window" << id << "as steam game" << steamGameId << "from" << service->entryPath();
}
