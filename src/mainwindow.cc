
/************************************************************************
        mainwindow.cc

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

#include "mainwindow.hh"
#include "strokescene.hh"
#include "charactersbar.hh"
#include <QGraphicsView>
#include <QVBoxLayout>
#include <QDebug>

MainWindow::MainWindow()
{
    scene = new StrokeScene (this);
    scene->setSceneRect (0, 0, 500, 800);
    view = new QGraphicsView(scene);

//    connect (scene, SIGNAL (sceneRectChanged (QRectF const&)),
//             view, SLOT (updateSceneRect (QRectF const&)));
//    connect (scene, SIGNAL (sceneRectChanged (QRectF const&)),
//             scene, SLOT (update (QRectF const&)));

    charactersBar = new CharactersBar (scene, this);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget (view);
    layout->addSpacing (15);
    layout->addWidget (charactersBar);

    QWidget *widget = new QWidget;
    widget->setLayout(layout);

    setCentralWidget(widget);
}
