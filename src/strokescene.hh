
/************************************************************************
        strokescene.hh

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

#ifndef STROKESCENE_HH
#define STROKESCENE_HH

#include <QGraphicsScene>
#include <QPainterPath>

class Stroke;

class StrokeScene : public QGraphicsScene {
    Q_OBJECT

public:
    //! Constructor 
    StrokeScene (QObject *parent = 0);

signals:
    void strokeChanged();

protected:
    void mousePressEvent (QGraphicsSceneMouseEvent *mouseEvent);
    void mouseMoveEvent (QGraphicsSceneMouseEvent *mouseEvent);
    void mouseReleaseEvent (QGraphicsSceneMouseEvent *mouseEvent); 

private:
    //! was mouse pressed ?
    bool mousePressed;

    //! 
    Stroke *currentStroke;

    //! 
    QPainterPath currentPath;

    //! 
    QPointF lastPos;
};

#endif // STROKESCENE_HH
