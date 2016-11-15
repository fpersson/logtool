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

#ifndef LOGTOOL_BLACKLISTMANAGER_H
#define LOGTOOL_BLACKLISTMANAGER_H

#include <QObject>
namespace logtool {
    class BlacklistManager : public QObject {
    Q_OBJECT
    public:
        explicit BlacklistManager(const QString &listfile, QObject *parent=0);
        QStringList getList() const {return m_blacklist;} //cstor don't emit the initial blacklist fix this later

    signals:
        void updated(const QStringList &blacklist);

    public slots:
        void readNewList(const QString &list);

    private:
        QStringList m_blacklist;
        void readListFile(const QString &file);
    };
} //namespace


#endif //LOGTOOL_BLACKLISTMANAGER_H
