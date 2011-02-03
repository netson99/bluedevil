/*****************************************************************************
 * This file is part of the KDE project                                      *
 *                                                                           *
 * Copyright (C) 2010-2011 Alejandro Fiestas Olivares <afiestas@kde.org>     *
 * Copyright (C) 2010-2011 UFO Coders <info@ufocoders.com>                   *
 *                                                                           *
 * This library is free software; you can redistribute it and/or             *
 * modify it under the terms of the GNU Library General Public               *
 * License as published by the Free Software Foundation; either              *
 * version 2 of the License, or (at your option) any later version.          *
 *                                                                           *
 * This library is distributed in the hope that it will be useful,           *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of            *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU         *
 * Library General Public License for more details.                          *
 *                                                                           *
 * You should have received a copy of the GNU Library General Public License *
 * along with this library; see the file COPYING.LIB.  If not, write to      *
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,      *
 * Boston, MA 02110-1301, USA.                                               *
 *****************************************************************************/

#include "sendfilewizard.h"
#include <KCmdLineArgs>
#include <KApplication>
#include <KAboutData>
#include <bluedevil/bluedevil.h>

using namespace BlueDevil;

int main(int argc, char *argv[])
{
    KAboutData aboutData("bluedevilsendfile", "bluedevil", ki18n("Bluetooth Send File Helper"), "0.1", ki18n("Bluetooth Send File Helper"),
    KAboutData::License_GPL, ki18n("(c) 2010, UFO Coders"));

    aboutData.addAuthor(ki18n("Alejandro Fiestas Olivares"), ki18n("Developer"), "alex@ufocoders.org",
    "http://www.afiestas.org/");
    aboutData.setProgramIconName("preferences-system-bluetooth");

    KCmdLineArgs::init(argc, argv, &aboutData);

    KCmdLineOptions options;
    options.add("u").add("ubi <ubi>", ki18n("Device UUID where the files will be sent"));
    options.add("f").add("files <files>", ki18n("Files that will be sent"));
    KCmdLineArgs::addCmdLineOptions( options );

    KCmdLineArgs *args = KCmdLineArgs::parsedArgs();

    KApplication app;
    app.setQuitOnLastWindowClosed(false);

    SendFileWizard *sendFileWizard = new SendFileWizard(args->getOption("ubi"), args->getOptionList("files"));

    sendFileWizard->show();

    return app.exec();
}
