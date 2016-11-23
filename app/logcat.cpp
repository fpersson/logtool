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
    Logcat::Logcat(QObject *parent) : QObject(parent) {
        m_process = new QProcess(this);
        connect(m_process, SIGNAL(readyReadStandardOutput()), this, SLOT(gotData()));
#if QT_VERSION >= 0x050600
        connect(m_process, SIGNAL(errorOccurred(QProcess::error)), this, SLOT(gotError(QProcess::error)));
#endif
        connect(m_process, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(onExit(int, QProcess::ExitStatus)));
        connectAdb();
    }

    Logcat::~Logcat() {
        m_process->close();
    }

    void Logcat::gotData() {
        QByteArray byte = m_process->readAllStandardOutput();
        emit dataAvailable(QString(byte));
    }

    void Logcat::gotError(QProcess::ProcessError err) {
        qDebug() << "gotError: " << err;
    }

    void Logcat::onExit(int exitCode, QProcess::ExitStatus exitStatus) {
        qDebug() << "Exit code; " << exitCode << " exit status: " << exitStatus;
        connectAdb();
    }

    void Logcat::connectAdb() {
        m_process->start("adb logcat"); ///@todo add path to adb in configfile
    }
}//namespace
