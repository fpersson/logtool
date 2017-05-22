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

#include "outputprinter.h"

namespace utils{
    OutputPrinter::OutputPrinter(const QStringList &keywords):m_keywords(keywords){}

    void OutputPrinter::colorizeOutput(const QString &line) {
        std::string formated_string = "";
        if (line.size() > 1) {
            foreach(const QString &key, m_keywords) {
                QString firstchar = line.mid(0, 1);
                std::string colorcode = Color::Format::Reset;

                if (firstchar.toLower() == "e") { ///@todo remove hardcoded value, this print android system exceptions with red
                    colorcode = Color::Text::Red;
                } else if (line.contains("INFO:CONSOLE")) { ///@todo remove hardcoded value
                    colorcode = Color::Text::LightBlue;
                }

                formated_string = colorcode+line.trimmed().toStdString()+Color::Format::Reset;

                if (line.contains(key)) {
                    formated_string = colorcode+Color::Format::Bold+line.trimmed().toStdString()+Color::Format::Reset;
                    break;
                }
            }
            utils::FQLog::getInstance().info("", line.trimmed());
            std::cout << formated_string << std::endl;
        }
    }
}
