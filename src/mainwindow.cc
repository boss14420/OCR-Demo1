
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
#include "stroke.hh"
#include "charactersbar.hh"
#include <QGraphicsView>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QFile>
#include <QTextStream>
#include <QDebug>

#include <opencv2/ml/ml.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

MainWindow::MainWindow()
{
    //
    // Init interface

    scene = new StrokeScene (this);
    scene->setSceneRect (0, 0, 500, 800);
    connect (scene, SIGNAL (strokeChanged()), SLOT (updateStroke()));

    view = new QGraphicsView(scene);

    clearButton = new QPushButton ("Clear", this);
    connect (clearButton, SIGNAL (pressed()), scene, SLOT (clear()));

    charactersBar = new CharactersBar (scene, this);

    predictResult = new QLabel (this);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget (view);
    layout->addWidget (clearButton);
    layout->addWidget (charactersBar);
    layout->addWidget (predictResult);

    QWidget *widget = new QWidget;
    widget->setLayout(layout);

    setCentralWidget(widget);


    //
    // Init ann

    cv::Mat_<int> layerSize (1, 3);
    layerSize << INPUT_SIZE, (INPUT_SIZE+OUTPUT_SIZE)/2, OUTPUT_SIZE;
    ann.create (layerSize, CvANN_MLP::SIGMOID_SYM, 1.0f, 1.0f);

    train();
}


void MainWindow::updateStroke()
{
    QImage image (CHAR_WIDTH, CHAR_HEIGHT, QImage::Format_Mono);

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

    cv::Mat_<float> inputs (0, INPUT_SIZE), inp (1, INPUT_SIZE);

    QPainter painter (&image);
    painter.setPen (QPen (Qt::color0));

    std::cerr << "--------------------------------------------------\n";
    for (auto item : itemList) {

        image.fill (Qt::color1);
        scene->render (&painter, QRectF (0, 0, CHAR_WIDTH, CHAR_HEIGHT),
                       item->boundingRect(), //.adjusted(-2,-2,2,2), 
                       Qt::IgnoreAspectRatio);

        image.save ("char.png");

        for (int y = 0; y != CHAR_HEIGHT; ++y)
            for (int x = 0; x != CHAR_WIDTH; ++x) {
                inp (0, y*CHAR_WIDTH+x) = 
                    (image.pixel (x, y) == 0xffffffff) ? 0.0f : 1.0f;
            }
        inputs.push_back (inp);

        std::cerr << "char:\n";
        for (int y = 0; y != CHAR_HEIGHT; ++y) {
            for (int x = 0; x != CHAR_WIDTH; ++x) {
                std::cerr << inp (0, y*CHAR_WIDTH+x);
//                std::cerr << std::ios::hex << image.pixel (x, y) << ' ';
            }
            std::cerr << '\n';
        }
        std::cerr << '\n';


    }
    
    predict (inputs);
}


void MainWindow::predict (cv::Mat_<float> const &inputs) 
{
    using cv::Mat_;

    QString digitalText;
    
    int inputCount = inputs.size().height;

    cv::Mat_<float> outputs (OUTPUT_SIZE, inputCount);  
    ann.predict (inputs, outputs);

    for (int r = 0; r != inputCount; ++r) {
        
        for (int i = 0; i != OUTPUT_SIZE; ++i)
            std::cerr << outputs (r, i) << ' ';
        std::cerr << '\n';

        float maxFitted = 0.0;
        int lastResult = -1;
        for (int c = 0; c != OUTPUT_SIZE; ++c)
            if (outputs(r, c) > maxFitted) {
                maxFitted = outputs (r, c);
                lastResult = c;
            }

//        digitalText += QString::number (lastResult);
        digitalText += (lastResult + 'A');
    }

    predictResult->setText (digitalText);
}

void MainWindow::learn() {
}

void MainWindow::train() {
    cv::Mat_<float> inputs (0, INPUT_SIZE), outputs (0, OUTPUT_SIZE);
    initTrainingSet (inputs, outputs);

    CvANN_MLP_TrainParams trainParam(
            cvTermCriteria(CV_TERMCRIT_EPS, 10000, 0.001f),
            CvANN_MLP_TrainParams::BACKPROP,
            0.1f, 0.4f
            );

    ann.train(inputs, outputs, cv::Mat(), cv::Mat(), trainParam);
}


void 
MainWindow::initTrainingSet (cv::Mat_<float> &inputs, cv::Mat_<float> &outputs)
{
    const QString trainingFile = "sample.dat";
    QFile file (trainingFile);
    file.open (QFile::ReadOnly | QFile::Text);
    QTextStream stream (&file);

    char res;
    
    cv::Mat_<float> inp (1, INPUT_SIZE), out (1, OUTPUT_SIZE);
    while ( !(stream >> res).atEnd() ) {
        res -= 'A';
        // set output
        for (int i = 0; i < res; ++i) out (0, i) = 0.0f;
        for (int i = res+1; i < OUTPUT_SIZE; ++i) out (0, i) = 0.0f;
        out (0, res) = 1.0f;
        outputs.push_back (out);

        // set input
        char pixel;
        for (int i = 0; i != INPUT_SIZE; ++i) {
            stream >> pixel;
            inp (0, i) = (pixel - '0');
        }
        stream >> pixel; // ignore newline
        inputs.push_back (inp);
    }

    file.close();
}
