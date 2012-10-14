
/************************************************************************
        main.cc

  Copyright (C) 2012 - BOSS14420

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.

**************************************************************************/

#include <QApplication>
#include "mainwindow.hh"

int main(int argc, char *argv[])
{
    QApplication app (argc, argv);
    MainWindow mw;
    mw.setGeometry (100, 100, 800, 500);
    mw.show();
    return app.exec();
}
