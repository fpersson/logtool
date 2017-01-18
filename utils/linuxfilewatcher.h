#ifndef LINUXFILEWATCHER_H
#define LINUXFILEWATCHER_H
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


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#include <errno.h>
#include <sys/types.h>
#include <sys/inotify.h>

#include <QObject>
#include <QDebug>
#include <QThread>
#include <QtCore/QFile>

namespace utils {
#define EVENT_SIZE (sizeof(struct inotify_event))
#define EVENT_BUF_LEN (1024*(EVENT_SIZE+16))

    class LinuxFileWatcher : public QObject {
    Q_OBJECT
    public:
        explicit LinuxFileWatcher(QObject *parent = 0);

        ~LinuxFileWatcher();

        /**
         * Path to dir
         * @param path
         */
        void addPath(const QString path) { m_path = path; } //todo implement this

    signals:

        void fileCreate(const QString &file);

        void fileDelete(const QString &file);

        void fileCloseWrite(const QString &file);

        void fileMove(const QString &file);

        void dirCreate(const QString &dir);

        void dirDelete(const QString &dir);

        void dirCloseWrite(const QString &dir);

        void dirMove(const QString &dir);

        /**
         * misc error messages
         * @param err
         */
        void error(const QString err);

    public slots:

        void startWatch();

    private:
        void watch();

        int m_filewatch;
        int m_filedescriptor;
        QString m_path;
    };
} //namespace

#endif // LINUXFILEWATCHER_H
