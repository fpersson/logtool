/*
 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License, or (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 51 Franklin Street, Fifth Floor,
 Boston, MA  02110-1301, USA.

 ---
 Copyright (C) 2016, Fredrik Persson <fpersson.se@gmail.com>
 */

#include <QCoreApplication>
#include <QCommandLineParser>
#include <QString>
#include <QDebug>

#include "app/logcat.h"
#include "utils/flog.h"

#include "utils/filereader.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    QString logdir ="";
    QCoreApplication::setApplicationName("LogTool");
    QCoreApplication::setApplicationVersion("0.1.1");

    QCommandLineParser parser;
    parser.setApplicationDescription("LogTool, A better way use Android Debug Bridge (adb)");
    parser.addHelpOption();
    parser.addVersionOption();

    QCommandLineOption opt_logdir(QStringList() << "l" << "logdir",
                                  QCoreApplication::translate("main", "set logdir (/foo/logdir)."),
                                  QCoreApplication::translate("main", "dir"), "/logtool/log");
    parser.addOption(opt_logdir);


    QCommandLineOption opt_profile(QStringList() << "p" << "profile",
                                    QCoreApplication::translate("main", "set profile (/path/to/profile)"),
                                    QCoreApplication::translate("main", "/path/to/profile"), "");
    parser.addOption(opt_profile);

    QCommandLineOption opt_collapse(QStringList() << "c" << "collapse",
                                    QCoreApplication::translate("main", "set collapse level 0=default 1=Only Tags and exception"),
                                    QCoreApplication::translate("main", ""), "");
    parser.addOption(opt_collapse);

    parser.process(app);

    logdir = parser.value(opt_logdir);

    if(logdir.isEmpty()){
        logdir = "/logtool/log";
    }

    utils::FQLog::getInstance().init(logdir, "/messages", false);
    QString profile = parser.value(opt_profile);
    logtool::Logcat lc(profile);
    int collapse = parser.value(opt_collapse).toInt();
    if(collapse > 0){
        lc.setCollapseLevel(collapse);
    }

    return app.exec();
}
