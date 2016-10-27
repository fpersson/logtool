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

#include "filewatcher.h"
#include <QtCore/QString>
#include <QtCore/QArgument>
#include <QtCore/QtGlobal>
#include <QtCore/QtCore>
#include <QtCore/QThread>

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

    connect(lfw, SIGNAL(fileCreate(QString)), this, SLOT(fileCreated(QString)));
    connect(lfw, SIGNAL(fileDelete(QString)), this, SLOT(fileDeleted(QString)));
    connect(lfw, SIGNAL(fileCloseWrite(QString)), this, SLOT(fileClosedWrite(QString)));
    connect(lfw, SIGNAL(fileMove(QString)), this, SLOT(fileMoved(QString)));

    connect(lfw, SIGNAL(dirCreate(QString)), this, SLOT(dirCreated(QString)));
    connect(lfw, SIGNAL(dirDelete(QString)), this, SLOT(dirDeleted(QString)));
    connect(lfw, SIGNAL(dirCloseWrite(QString)), this, SLOT(dirClosedWrite(QString)));
    connect(lfw, SIGNAL(dirMove(QString)), this, SLOT(dirMoved(QString)));

    connect(lfw, SIGNAL(error(QString)), this, SLOT(gotError(QString)));

    connect(thread, SIGNAL(started()), lfw, SLOT(startWatch()));
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    thread->start();
}

void FileWatcher::fileCreated(const QString &file){
    emit fileCreate(file);
}

void FileWatcher::fileDeleted(const QString &file) {
    emit fileDelete(file);
}

void FileWatcher::fileMoved(const QString &file) {
    emit fileMove(file);
}

void FileWatcher::fileClosedWrite(const QString &file) {
    emit fileCloseWrite(file);
}

void FileWatcher::dirDeleted(const QString &dir) {
    emit dirDelete(dir);
}

void FileWatcher::dirCreated(const QString &dir) {
    emit dirCreate(dir);
}

void FileWatcher::dirMoved(const QString &dir) {
    emit dirMove(dir);
}

void FileWatcher::dirClosedWrite(const QString &dir) {
    emit dirCloseWrite(dir);
}

void FileWatcher::gotError(const QString &msg) {
    emit error(msg);
}

FileWatcher::~FileWatcher(){
    ///@todo implement
}
