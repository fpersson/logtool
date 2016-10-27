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
#include "filereader.h"

/**
 * @brief FileReader::FileReader
 */
utils::FileReader::FileReader(){}

/**
 * @brief FileReader::read
 * @param filename as full path
 * @return
 */
QStringList utils::FileReader::read(QString filename){
    QStringList retval;
    QFile file(filename);

    if(file.exists()){
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        QTextStream textStream(&file);
        while(true){
            QString line = textStream.readLine();
            if(line.isNull()){
                break;
            }else{
                retval.append(line.trimmed());
            }
        }
    }else{
        qDebug() << filename << " not found.";
    }
    return retval;
}
