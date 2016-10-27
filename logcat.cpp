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

Logcat::Logcat(QString profile, QObject *parent) : QObject(parent){
    utils::FQLog::getInstance().info("","*************** START *****************");
    utils::FQLog::getInstance().setLevel(utils::LOG::INFO);
    m_process = new QProcess(this);
    m_profile = profile;
    utils::FileReader fileReader;
    m_blacklist.append(fileReader.read(m_profile));
    m_collapseLevel = 0;

    m_filewatch = new FileWatcher;
    m_filewatch->addPath(QString("%1/%2").arg(QDir::homePath()).arg("log_profiles"));
    connect(m_filewatch, SIGNAL(fileCloseWrite(QString)), this, SLOT(profileUpdated(QString)));

    //highlighted msg
    m_searchkeys.append(fileReader.read(QString("%1/%2").arg(QDir::homePath()).arg(keyWordFile))); ///@todo add this path to configfile
    //fileWatch.addPath(m_profile);
    //connect(&fileWatch, SIGNAL(fileChanged(QString)), this, SLOT(blackListChanged(QString)));

    connect(m_process, SIGNAL(readyReadStandardOutput()),this, SLOT(gotData()));
#if QT_VERSION >= 0x050600
    connect(m_process, SIGNAL(errorOccurred(QProcess::error)), this, SLOT(gotError(QProcess::error)));
#endif
    connect(m_process, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(onExit(int,QProcess::ExitStatus)));
    connectAdb();
}

Logcat::~Logcat(){
    m_process->close();
    delete m_filewatch;
}

void Logcat::gotData(){
    bool blacklisted = false;
    QByteArray byte = m_process->readAllStandardOutput();
    QStringList lines = QString(byte).split("\n");
    foreach(QString line, lines){
        foreach(QString key, m_blacklist){
            if(line.contains(key)){
                blacklisted = true;
                break;
            }
        }
        if(line.size() > 1 && !blacklisted){
            foreach(QString key, m_searchkeys ){
                QString firstchar = line.mid(0,1);
                std::string colorcode = Color::Format::Reset;
                if(firstchar.toLower() == "e"){ ///@todo remove hardcoded value, this print android system exceptions with red
                    colorcode = Color::Text::Red;
                }else if(line.contains("INFO:CONSOLE")){ ///@todo remove hardcoded value
                     colorcode=Color::Text::LightBlue;
                }
                if(line.contains(key)){
                    std::cout << colorcode << Color::Format::Bold << line.trimmed().toStdString() << Color::Format::Reset << std::endl;
                }else{
                    if(m_collapseLevel != 1){
                        std::cout << colorcode << line.trimmed().toStdString() << Color::Format::Reset << std::endl;
                    }
                }
                utils::FQLog::getInstance().info("",line.trimmed());
            }
        }
        blacklisted = false;
    }
}

void Logcat::gotError(QProcess::ProcessError err){
    qDebug() << "gotError: " << err;
}

void Logcat::onExit(int exitCode, QProcess::ExitStatus exitStatus){
    qDebug() << "Exit code; " << exitCode << " exit status: " << exitStatus;
    connectAdb();
}

void Logcat::blackListChanged(QString file){
    qDebug() << "blackListChanged " << file;
    utils::FileReader fileReader;
    m_blacklist.clear();
    m_blacklist.append(fileReader.read(m_profile));
    qDebug() << "BACKLIST NEW SIZE" << m_blacklist.length();
}

void Logcat::connectAdb(){
    m_process->start("adb logcat"); ///@todo add path to adb in configfile
}

void Logcat::profileUpdated(const QString &file) {
    qDebug() << "Logcat::profileUpdated: " << file;
    if(file == m_profile){
        blackListChanged(file);
    }else{
        //do something fun...
    }
}
