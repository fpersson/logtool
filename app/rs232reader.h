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

#ifndef LOGTOOL_RS232READER_H
#define LOGTOOL_RS232READER_H

#include <QDebug>
#include <QObject>
#include <QByteArray>
#include <QtSerialPort/QSerialPort>

namespace logtool {

    struct SerialSettings{
        QString port;
        int baudrate;
    };

    class Rs232Reader : public QObject {
        Q_OBJECT
    public:
        explicit Rs232Reader(const QString &settings, QObject *parent=0);
        ~Rs232Reader();

    signals:
        void dataAvailable(const QString &data);

    private slots:
        void gotData();

    private:
        QSerialPort *m_serial;
        SerialSettings m_settings;
    };

} //namespace


#endif //LOGTOOL_RS232READER_H
