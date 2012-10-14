
/************************************************************************
        strokescene.cc

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

#include "strokescene.hh"
#include "stroke.hh"

#include <QGraphicsSceneMouseEvent>
#include <QDebug>

//! Constructor
StrokeScene::StrokeScene (QObject *parent)
    : QGraphicsScene (parent)
{
    mousePressed = false;
    currentStroke = nullptr;
}

//
// Event handlers


//! Mouse press event
void StrokeScene::mousePressEvent (QGraphicsSceneMouseEvent *mouseEvent)
{
    mousePressed = true;
//    lastPos = mouseEvent->scenePos();
    currentPath = QPainterPath (mouseEvent->scenePos());
    currentStroke = new Stroke (currentPath);
    addItem (currentStroke);

    QGraphicsScene::mousePressEvent (mouseEvent);
}


//! Mouse move event
void StrokeScene::mouseMoveEvent (QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mousePressed) {
        currentPath.lineTo (mouseEvent->scenePos());
        currentStroke->setPath (currentPath);
//        addLine (QLineF (lastPos, mouseEvent->scenePos()))
//        lastPos = mouseEvent->scenePos();
    }

    QGraphicsScene::mouseMoveEvent (mouseEvent);
}


//! Mouse release event
void StrokeScene::mouseReleaseEvent (QGraphicsSceneMouseEvent *mouseEvent)
{
    mousePressed = false;
    
    if (!currentPath.isEmpty()) {
        for (auto stroke : currentStroke->collidingItems()) {
            currentStroke->unite (*qgraphicsitem_cast<Stroke*>(stroke));
            removeItem (stroke);
            delete stroke;
        }

//        for (auto stroke : items()) {
//            if ( (currentStroke->boundingRect().adjusted (-2,-2,2,2)
//                            .intersects (stroke->boundingRect()) ) 
//                    && (stroke != currentStroke) )
//            {
//                currentStroke->unite (*qgraphicsitem_cast<Stroke*>(stroke));
//                removeItem (stroke);
//                delete stroke;
//            }
//        }

        emit strokeChanged();
        
    } else {
        removeItem (currentStroke);
        delete currentStroke;
    }

    QGraphicsScene::mouseReleaseEvent (mouseEvent);

//    qDebug() << items().size();
}
