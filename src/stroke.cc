
/************************************************************************
        stroke.cc

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

#include "stroke.hh"
 
//
// Constructors

Stroke::Stroke (QGraphicsItem *parent) : QGraphicsPathItem (parent) {}

Stroke::Stroke (const QPainterPath &path, QGraphicsItem *parent)
    : QGraphicsPathItem (path, parent)
{}


//
// Methods

void Stroke::unite (Stroke const &stroke)
{
    QPainterPath newPath = path();
    newPath.addPath (stroke.path());
    setPath (newPath);
}


void Stroke::paint (QPainter *painter, 
            const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QGraphicsPathItem::paint (painter, option, widget);
}
