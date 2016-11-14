#include "logcat.h"
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
namespace logtool {
    Logcat::Logcat(QString profile, QObject *parent) : QObject(parent) {
        utils::FQLog::getInstance().info("", "*************** START *****************");
        utils::FQLog::getInstance().setLevel(utils::LOG::INFO);
        m_process = new QProcess(this);
        m_profile = profile;
        utils::FileReader fileReader;
        m_blacklist.append(fileReader.read(m_profile));
        m_collapseLevel = 0;

        m_filewatch = new utils::FileWatcher;
        m_filewatch->addPath(QString("%1/%2").arg(QDir::homePath()).arg("log_profiles"));
        connect(m_filewatch, SIGNAL(fileCloseWrite(QString)), this, SLOT(profileUpdated(QString)));

        //highlighted msg
        m_searchkeys.append(fileReader.read(
                QString("%1/%2").arg(QDir::homePath()).arg(keyWordFile))); ///@todo add this path to configfile

        m_printer = new utils::OutputPrinter(m_searchkeys);
        connect(m_process, SIGNAL(readyReadStandardOutput()), this, SLOT(gotData()));
#if QT_VERSION >= 0x050600
        connect(m_process, SIGNAL(errorOccurred(QProcess::error)), this, SLOT(gotError(QProcess::error)));
#endif
        connect(m_process, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(onExit(int, QProcess::ExitStatus)));
        connectAdb();
    }

    Logcat::~Logcat() {
        m_process->close();
        delete m_printer;
        delete m_filewatch;
    }

    void Logcat::gotData() {
        QByteArray byte = m_process->readAllStandardOutput();
        blacklistOutput(QString(byte));
    }

    /**
     * @todo move this code to another class...
     */
    void Logcat::blacklistOutput(const QString &data){
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

    void Logcat::gotError(QProcess::ProcessError err) {
        qDebug() << "gotError: " << err;
    }

    void Logcat::onExit(int exitCode, QProcess::ExitStatus exitStatus) {
        qDebug() << "Exit code; " << exitCode << " exit status: " << exitStatus;
        connectAdb();
    }

    void Logcat::blackListChanged(const QString &file) {
        utils::FileReader fileReader;
        m_blacklist.clear();
        m_blacklist.append(fileReader.read(m_profile));
        qDebug() << "BACKLIST NEW SIZE" << m_blacklist.length();
    }

    void Logcat::connectAdb() {
        m_process->start("adb logcat"); ///@todo add path to adb in configfile
    }

    void Logcat::profileUpdated(const QString &file) {
        if (file == m_profile) {
            blackListChanged(file);
        }
    }
}//namespace
