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

#include "rs232reader.h"

namespace logtool{
    /**
     * @param settings are json formated, contains port and baudrate
     * (can be expanded in future if needed)
     */
    Rs232Reader::Rs232Reader(const QString &settings, QObject *parent) : QObject(parent) {
        m_serial = new QSerialPort(this);

        //@todo implement json parser settings
        m_settings.port = "/dev/ttyACM0"; //hardcoded for arduino...
        m_settings.baudrate = 9600; //hardcoded for arduino...

        m_serial->setPortName(m_settings.port);

        connect(m_serial, SIGNAL(readyRead()), this, SLOT(gotData()));

        if(m_serial->open(QIODevice::ReadOnly)){
            m_serial->setBaudRate(m_settings.baudrate);
        }else{
            qDebug() << "Could not open rs232: " << m_settings.port;
        }
    }

    Rs232Reader::~Rs232Reader(){
        if(m_serial->isOpen()){
            m_serial->close();
        }
        delete m_serial;
    }

    void Rs232Reader::gotData() {
        if(m_serial->isOpen()){
            if (m_serial->canReadLine()) {
                QByteArray byte = m_serial->readLine();
                emit dataAvailable(QString(byte));
            }
        }
    }

}//namespace
