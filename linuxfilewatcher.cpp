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

#include "linuxfilewatcher.h"

LinuxFileWatcher::LinuxFileWatcher(QObject *parent) : QObject(parent){;}

void LinuxFileWatcher::startWatch() {
    if(m_path != "") {
        QFile file(m_path);
        if (file.exists()) {
            m_filedescriptor = inotify_init();
            if (m_filedescriptor < 0) {
                emit error("No filedescriptor.");
            } else {
                watch();
            }
        } else {
            emit error(QString("Watchdir is not set: %1 %2").arg(m_path).arg("does not exist."));
        }
    }else{
        emit error("Watchdir is not set");
    }
}

LinuxFileWatcher::~LinuxFileWatcher(){
    inotify_rm_watch(m_filedescriptor, m_filewatch);
    close(m_filedescriptor);
}

void LinuxFileWatcher::watch(){
    bool running = true;
    m_filewatch = inotify_add_watch(m_filedescriptor, m_path.toLocal8Bit(), IN_CREATE | IN_DELETE | IN_CLOSE_WRITE | IN_MOVE);
    while(running){
        int length = 0;
        int i = 0;
        char buffer[EVENT_BUF_LEN];

        int flags = fcntl(m_filedescriptor, F_GETFL, 0);
        fcntl(m_filedescriptor, F_SETFL, flags | O_NONBLOCK);
        length = read(m_filedescriptor, buffer, EVENT_BUF_LEN);

        while(i<length){
            struct inotify_event *event = (struct inotify_event * ) &buffer[i];
            if(event->len){
                if(event->mask & IN_CREATE ){
                    if(event->mask & IN_ISDIR){
                        emit dirCreate(QString("%1/%2").arg(m_path).arg(event->name));
                    }else{
                        emit fileCreate(QString("%1/%2").arg(m_path).arg(event->name));
                    }
                }else if(event->mask & IN_DELETE ){
                    if(event->mask & IN_ISDIR){
                        emit dirDelete(QString("%1/%2").arg(m_path).arg(event->name));
                    }else{
                        emit fileDelete(QString("%1/%2").arg(m_path).arg(event->name));
                    }
                }else if(event->mask & IN_CLOSE_WRITE){
                    if(event->mask & IN_ISDIR){
                        emit dirCloseWrite(QString("%1/%2").arg(m_path).arg(event->name));
                    }else{
                        emit fileCloseWrite(QString("%1/%2").arg(m_path).arg(event->name));
                    }
                }else if(event->mask & IN_MOVE){
                    if(event->mask & IN_ISDIR){
                        emit dirMove(QString("%1/%2").arg(m_path).arg(event->name));
                    }else{
                        emit fileMove(QString("%1/%2").arg(m_path).arg(event->name));
                    }
                }
            }
            i += EVENT_SIZE + event->len;
        }
    }
}

