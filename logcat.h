#ifndef LOGCAT_H
#define LOGCAT_H

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

#include <iostream>

#include <QProcess>
#include <QDebug>
#include <QObject>
#include <QStringList>
#include <QByteArray>
#include <QPointer>
#include <QFileSystemWatcher>

#include "flog.h"
#include "filereader.h"
#include "unix_color.h"
#include "filewatcher.h"

const QString keyWordFile = "log_profiles/keys"; ///@todo remove this and create a nice config file.

class Logcat : public QObject{
    Q_OBJECT
public:
    explicit Logcat(QString profile,QObject *parent =0);
    ~Logcat();
    void setCollapseLevel(int level){m_collapseLevel=level;}
    void connectAdb();

signals:

private slots:
    void gotData();
    void gotError(QProcess::ProcessError err);
    void onExit(int exitCode, QProcess::ExitStatus exitStatus);
    void blackListChanged(QString file);
    void profileUpdated(const QString &file);

private:
    QPointer<QProcess> m_process;
    QStringList m_blacklist;
    QStringList m_searchkeys;
    //QFileSystemWatcher fileWatch;
    int m_collapseLevel;
    QString m_profile;
    FileWatcher *m_filewatch;
};

#endif // LOGCAT_H
