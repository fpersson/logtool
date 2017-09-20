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
#include <QSettings>
#include <QDebug>

#include "app/logtool.h"
#include "utils/flog.h"

#include "utils/filereader.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    QString logdir ="";
    QString mode = "";
    QString command = "";
    QString settings = "";
    QString profile = "";
    QCoreApplication::setApplicationName("LogTool");
    QCoreApplication::setApplicationVersion("0.1.4");

    QCommandLineParser parser;
    parser.setApplicationDescription("LogTool, A better way debug your software.");
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

    /*
    QCommandLineOption opt_collapse(QStringList() << "c" << "collapse",
                                    QCoreApplication::translate("main", "set collapse level 0=default 1=Only Tags and exception"),
                                    QCoreApplication::translate("main", ""), "");
    parser.addOption(opt_collapse);
     */

    QCommandLineOption opt_mode(QStringList() << "m" << "mode",
                                    QCoreApplication::translate("main", "set mode for logcat (default) or rs232"),
                                    QCoreApplication::translate("main", "logcat | rs232 | cmd"), "");
    parser.addOption(opt_mode);

    QCommandLineOption opt_cmd(QStringList() << "c" << "cmd",
                                QCoreApplication::translate("main", "your own command (tail -f /path/to/log)"),
                                QCoreApplication::translate("main", "path to log"), "");
    parser.addOption(opt_cmd);

    QCommandLineOption opt_settings(QStringList() << "s" << "set",
                               QCoreApplication::translate("main", "use <settings>.ini"),
                               QCoreApplication::translate("main", "setting files to use"), "");
    parser.addOption(opt_settings);

    parser.process(app);
    settings = parser.value(opt_settings);

    if(!settings.isEmpty()){
        QPointer<QSettings> mySettings = new QSettings(settings, QSettings::IniFormat);
        mySettings->beginGroup("System");
        logdir = mySettings->value("logdir", "").toString();
        command = mySettings->value("cmd", "").toString();
        mode = mySettings->value("mode", "").toString();
        profile = mySettings->value("blacklist", "").toString();
        mySettings->endGroup();
        qDebug() << "logdir=" << logdir;
        qDebug() << "cmd=" << command;
        qDebug() << "mode=" << mode;
        qDebug() << "blacklist=" << profile;
    }

    if(logdir.isEmpty()){
        logdir = QDir::homePath()+"/logtool/log";
    }

    //@todo fix this
    //override settings with commandline options
    //profile = parser.value(opt_profile);
    //logdir = parser.value(opt_logdir);
    //mode = parser.value(opt_mode);
    //command = parser.value(opt_cmd);

    qDebug() << "LogDir: " << logdir;

    utils::FQLog::getInstance().init(logdir, "/messages", false);
    logtool::LogTool tool(profile, mode, command);
    /*
    int collapse = parser.value(opt_collapse).toInt();
    if(collapse > 0){
        tool.setCollapseLevel(collapse);
    }
     */

    return app.exec();
}
