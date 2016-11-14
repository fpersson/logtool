#ifndef LOGTOOL_OUTPUTPRINTER_H
#define LOGTOOL_OUTPUTPRINTER_H
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
#include <iostream>

#include <QStringList>

#include "utils/flog.h"
#include "utils/unix_color.h"

namespace utils {
    class OutputPrinter {
    public:
        explicit OutputPrinter(const QStringList &keywords);
        void updateKeywords(const QStringList &keywords){m_keywords=keywords;}
        void colorizeOutput(const QString &line);
    private:
        QStringList m_keywords;
    };
} //namespace


#endif //LOGTOOL_OUTPUTPRINTER_H
