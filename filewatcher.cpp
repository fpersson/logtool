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


#include <error.h>
#include <QtCore/QString>
#include <QtCore/QArgument>
#include <QtCore/QtGlobal>
#include <QtCore/QtCore>
#include <QtCore/QThread>
#include "filewatcher.h"


/**
 * @brief FileWatchDemo::FileWatchDemo for testing purpose, we use $HOME/watchdir/
 * @param file
 */
FileWatcher::FileWatcher(const QString &file){
    addPath(file);
}

/**
 * path to dir to watch.
 * @param path
 */
void FileWatcher::addPath(const QString &path) {
    QThread* thread = new QThread;
    LinuxFileWatcher* lfw = new LinuxFileWatcher;
    lfw->addPath(path);
    lfw->moveToThread(thread);

    connect(lfw, SIGNAL(fileCreate(const QString)), this, SLOT(fileCreated(const QString)));
    connect(lfw, SIGNAL(fileDelete(const QString)), this, SLOT(fileDeleted(const QString)));
    connect(lfw, SIGNAL(fileCloseWrite(const QString)), this, SLOT(fileClosedWrite(const QString)));
    connect(lfw, SIGNAL(fileMove(const QString)), this, SLOT(fileMoved(const QString)));

    connect(lfw, SIGNAL(dirCreate(const QString)), this, SLOT(dirCreated(const QString)));
    connect(lfw, SIGNAL(dirDelete(const QString)), this, SLOT(dirDeleted(const QString)));
    connect(lfw, SIGNAL(dirCloseWrite(const QString)), this, SLOT(dirClosedWrite(const QString)));
    connect(lfw, SIGNAL(dirMove(const QString)), this, SLOT(dirMoved(const QString)));

    connect(lfw, SIGNAL(error(const QString)), this, SLOT(gotError(const QString)));

    connect(thread, SIGNAL(started()), lfw, SLOT(startWatch()));
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    thread->start();
}

void FileWatcher::fileCreated(const QString &file){
    ///@todo implement
}

void FileWatcher::fileDeleted(const QString &file) {
    ///@todo implement
}

void FileWatcher::fileMoved(const QString &file) {
    ///@todo implement
}

void FileWatcher::fileClosedWrite(const QString &file) {
    emit fileCloseWrite(file);
}

void FileWatcher::dirDeleted(const QString &dir) {
    ///@todo implement
}

void FileWatcher::dirCreated(const QString &dir) {
    ///@todo implement
}

void FileWatcher::dirMoved(const QString &dir) {
    ///@todo implement
}

void FileWatcher::dirClosedWrite(const QString &dir) {
    ///@todo implement
}

void FileWatcher::gotError(const QString &msg) {
    ///@todo implement
}

FileWatcher::~FileWatcher(){
    ///@todo implement
}