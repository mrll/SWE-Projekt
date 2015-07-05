//
// Created by Matthias Röll on 20.05.15.
//
// Original aus dem Tutorial von: http://tufangorel.blogspot.de/2011/08/draw-grid-on-qgraphicsscene.html

#include "LCSGridGraphicScene.h"

#include <QPainter>

static const int GRID_STEP = 25;

inline qreal round(qreal val, int step) {
    int tmp = int(val) + step /2;
    tmp -= tmp % step;
    return qreal(tmp);
}

LCSGridGraphicScene::LCSGridGraphicScene(QObject *parent ) : QGraphicsScene(parent) {

}

void LCSGridGraphicScene::drawBackground(QPainter *painter, const QRectF &rect)
{
    painter->setPen(QPen(Qt::lightGray));

    // draw horizontal grid
    qreal start = round(rect.top(), GRID_STEP);
    if (start > rect.top()) {
        start -= GRID_STEP;
    }
    for (qreal y = start - GRID_STEP; y < rect.bottom(); ) {
        y += GRID_STEP;
        painter->drawLine((int)rect.left(), (int)y, (int)rect.right(), (int)y);
    }

    // now draw vertical grid
    start = round(rect.left(), GRID_STEP);
    if (start > rect.left()) {
        start -= GRID_STEP;
    }
    for (qreal x = start - GRID_STEP; x < rect.right(); ) {
        x += GRID_STEP;
        painter->drawLine((int)x, (int)rect.top(), (int)x, (int)rect.bottom());
    }
}
