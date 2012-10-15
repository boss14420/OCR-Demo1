
/************************************************************************
        charactersbar.cc

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

#include "charactersbar.hh"
#include "strokescene.hh"
#include "stroke.hh"
#include <QPainter>
#include <QDebug>

CharactersBar::CharactersBar (StrokeScene *scene, QWidget *parent)
    : QWidget (parent), scene (scene)
{
    buffer = new QImage (scene->width(), 50, QImage::Format_Mono);
    setMinimumSize (buffer->size());
    setMaximumSize (buffer->size());
    resize (buffer->size());

    connect (scene, SIGNAL (strokeChanged()), SLOT (updateChars()));
}

CharactersBar::~CharactersBar()
{
    delete buffer;
}

void CharactersBar::updateChars() 
{
    static const int CHAR_WIDTH = 20;
    static const int CHAR_HEIGHT = 28;

    buffer->fill (Qt::color1);


    int x = CHAR_WIDTH / 2;
    int y = CHAR_HEIGHT / 7;

    static struct ItemBefore {
        bool operator() (QGraphicsItem const *i1, QGraphicsItem const *i2)
        {
            auto rect1 = i1->boundingRect();
            auto rect2 = i2->boundingRect();
            
            return (rect1.y() + rect1.height() < rect2.y()) 
                    || ((rect1.y() < rect2.y() + rect2.height()) 
                        && (rect1.x() < rect2.x()));
        }
    } itemBefore;
    
    auto itemList = scene->items();
    qSort (itemList.begin(), itemList.end(), itemBefore);

    QPainter painter (buffer);
    painter.setPen (QPen (Qt::color0));
    for (auto item : itemList) {
        scene->render (&painter, QRectF (x, y, CHAR_WIDTH, CHAR_HEIGHT),
                       item->boundingRect().adjusted(-2,-2,2,2), 
                       Qt::KeepAspectRatio);

        x += CHAR_WIDTH * 7 / 5;
    }
    
    repaint();
}

void CharactersBar::paintEvent (QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawImage (0, 0, *buffer);
}
