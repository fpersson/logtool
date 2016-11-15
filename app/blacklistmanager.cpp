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
#include "blacklistmanager.h"
#include "utils/filereader.h"


namespace logtool {

    BlacklistManager::BlacklistManager(const QString &listfile, QObject *parent) : QObject(parent) {
        readListFile(listfile);
    }

    void BlacklistManager::readNewList(const QString &list) {
        readListFile(list);
    }

    void BlacklistManager::readListFile(const QString &file) {
        utils::FileReader fileReader;
        m_blacklist.clear();
        m_blacklist.append(fileReader.read(file));
        emit updated(m_blacklist);
    }

}//namespace