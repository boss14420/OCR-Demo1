
/************************************************************************
        stroke.hh

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

#ifndef STROKE_HH
#define STROKE_HH

#include <QGraphicsPathItem>

class Stroke : public QGraphicsPathItem {
public:
    //! Constructor
    Stroke (QGraphicsItem * parent = 0);

    //! Constructor
    Stroke (const QPainterPath & path, QGraphicsItem * parent = 0);

    //
    // Methods

    //! Add line to current stroke
//    void addLine (QLine const &line);

    //! Unite current stroke with another stroke
    void unite (Stroke const &stroke);

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
            QWidget *widget = 0);

};

#endif // STROKE_HH
