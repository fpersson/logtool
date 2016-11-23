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

#include "logtool.h"
namespace logtool{
    LogTool::LogTool(const QString &profile, QObject *parent) :QObject(parent) {
        utils::FQLog::getInstance().info("", "*************** START *****************");
        utils::FQLog::getInstance().setLevel(utils::LOG::INFO);
        m_blacklistManager = new BlacklistManager(profile);
        m_profile = profile;
        utils::FileReader fileReader;
        m_blacklist.append(m_blacklistManager->getList());
        m_collapseLevel = 0;

        m_logcat = new Logcat();
        connect(m_logcat, SIGNAL(dataAvailable(QString)), this, SLOT(processData(QString)));

        m_filewatch = new utils::FileWatcher;
        m_filewatch->addPath(QString("%1/%2").arg(QDir::homePath()).arg("log_profiles"));

        connect(m_filewatch, SIGNAL(fileCloseWrite(QString)), m_blacklistManager, SLOT(readNewList(QString)));
        connect(m_blacklistManager, SIGNAL(updated(QStringList)), this, SLOT(blacklistUpdated(QStringList)));

        //highlighted msg
        m_searchkeys.append(fileReader.read(
                QString("%1/%2").arg(QDir::homePath()).arg(keyWordFile))); ///@todo add this path to configfile

        m_printer = new utils::OutputPrinter(m_searchkeys);

    }

    void LogTool::blacklistUpdated(const QStringList &list){
        m_blacklist.clear();
        m_blacklist.append(list);
    }

    void LogTool::processData(const QString &data) {
        bool blacklisted = false;
        QStringList lines = data.split('\n');

        foreach(const QString &line, lines) {
            foreach(const QString &key, m_blacklist) {
                if (line.contains(key)) {
                    blacklisted = true;
                    break;
                }
            }
            if(!blacklisted){
                m_printer->colorizeOutput(line);
            }
            blacklisted = false;
        }
    }

}//namespace
