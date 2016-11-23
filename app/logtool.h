#ifndef LOGTOOL_LOGTOOL_H
#define LOGTOOL_LOGTOOL_H
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

#include <QDebug>
#include <QObject>
#include <QStringList>
#include <QByteArray>
#include <QPointer>
#include <QFileSystemWatcher>

#include "utils/outputprinter.h"
#include "utils/flog.h"
#include "utils/filereader.h"
#include "utils/unix_color.h"
#include "utils/filewatcher.h"
#include "blacklistmanager.h"
#include "logcat.h"

namespace logtool {
    const QString keyWordFile = "log_profiles/keys"; ///@todo remove this and create a nice config file.

    class LogTool : public QObject {
    Q_OBJECT
    public:
        explicit LogTool(const QString &profile, QObject *parent =0 );
        ~LogTool(){;}
        void setCollapseLevel(int level) { m_collapseLevel = level; }

    private slots:
        void processData(const QString &data);

        void blacklistUpdated(const QStringList &list);

    private:
        QPointer<Logcat> m_logcat;
        QStringList m_blacklist;
        QStringList m_searchkeys;
        int m_collapseLevel;
        QString m_profile;
        BlacklistManager *m_blacklistManager;
        utils::FileWatcher *m_filewatch;
        utils::OutputPrinter *m_printer;

    };
} //namespace


#endif //LOGTOOL_LOGTOOL_H
