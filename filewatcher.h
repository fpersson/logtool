#ifndef FILEWATCHER_H
#define FILEWATCHER_H
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

#include <QObject>
#include <QString>
#include <QDir>
#include <QFileSystemWatcher>
#include <QFile>
#include <QStringList>
#include <QDebug>
#include <QThread>

#include "linuxfilewatcher.h"

class FileWatcher : public QObject
{
Q_OBJECT
public:
    FileWatcher(){;}
    FileWatcher(const QString &file);
    ~FileWatcher();

    void addPath(const QString &path);

private slots:
    void fileCreated(const QString &file);
    void fileDeleted(const QString &file);
    void fileClosedWrite(const QString &file);
    void fileMoved(const QString &file);

    void dirCreated(const QString &dir);
    void dirDeleted(const QString &dir);
    void dirClosedWrite(const QString &dir);
    void dirMoved(const QString &dir);

    void gotError(const QString &msg);

signals:
    void fileCloseWrite(const QString &file);
private:

};

#endif // FILEWATCHER_H
