
/************************************************************************
        mainwindow.hh

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

#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>

#include <opencv2/ml/ml.hpp>

class StrokeScene;
class QGraphicsView;
class CharactersBar;
class QPushButton;
class QLabel;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    //! Constructor
    MainWindow ();

private:
    void initTrainingSet (cv::Mat_<float> &, cv::Mat_<float> &);
    void train();
    void predict(cv::Mat_<float> const &);
    void learn();

private slots:
    void updateStroke();

private:
    static const int CHAR_WIDTH = 5;
    static const int CHAR_HEIGHT = 7;
    static const int INPUT_SIZE = CHAR_WIDTH * CHAR_HEIGHT;
    static const int OUTPUT_SIZE = 26;

    StrokeScene *scene;
    QGraphicsView *view;
    CharactersBar *charactersBar;
    QPushButton *clearButton;
    QLabel *predictResult;

    CvANN_MLP ann;
};

#endif // MAINWINDOW_HH
