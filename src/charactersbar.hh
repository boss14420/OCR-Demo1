
/************************************************************************
        charactersbar.hh

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

#ifndef CHARACTERSBAR_HH
#define CHARACTERSBAR_HH

#include <QWidget>

class StrokeScene;
class QImage;

class CharactersBar : public QWidget {
    Q_OBJECT

public:
    CharactersBar (StrokeScene *scene, QWidget *parent = 0);
    ~CharactersBar();

protected:
    void paintEvent (QPaintEvent *event)  override;

private slots:
    void updateChars();

private:
    StrokeScene *scene;
    QImage *buffer;
};

#endif // CHARACTERSBAR_HH
