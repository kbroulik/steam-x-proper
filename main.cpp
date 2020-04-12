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

#include <QDebug>
#include <QGuiApplication>
#include <QSessionManager>

#include <KWindowSystem>

#include "steamxproper.h"

int main(int argc, char ** argv)
{
    qputenv("QT_QPA_PLATFORM", "xcb");

    QGuiApplication::setDesktopSettingsAware(false);
#if QT_VERSION >= QT_VERSION_CHECK(5, 14, 0)
    QCoreApplication::setAttribute(Qt::AA_DisableSessionManager);
#endif

    QGuiApplication app(argc, argv);

    if (!KWindowSystem::isPlatformX11()) {
        qFatal("steamxproper is only useful XCB. Aborting");
    }

#if QT_VERSION < QT_VERSION_CHECK(5, 14, 0)
    auto disableSessionManagement = [](QSessionManager &sm) {
        sm.setRestartHint(QSessionManager::RestartNever);
    };
    QObject::connect(&app, &QGuiApplication::commitDataRequest, disableSessionManagement);
    QObject::connect(&app, &QGuiApplication::saveStateRequest, disableSessionManagement);
#endif

    app.setQuitOnLastWindowClosed(false);

    SteamXProper proper;

    return app.exec();
}
