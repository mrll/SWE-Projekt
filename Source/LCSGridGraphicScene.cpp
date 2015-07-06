//
// Created by Matthias Röll on 20.05.15.
//
// Original aus dem Tutorial von: http://tufangorel.blogspot.de/2011/08/draw-grid-on-qgraphicsscene.html

#include "LCSGridGraphicScene.h"

#include <QPainter>

inline qreal round(qreal val, int step) {
    int tmp = int(val) + step /2;
    tmp -= tmp % step;
    return qreal(tmp);
}

LCSGridGraphicScene::LCSGridGraphicScene(QObject *parent ) : QGraphicsScene(parent) {
    _gridStep = 25;
}

void LCSGridGraphicScene::drawBackground(QPainter *painter, const QRectF &rect)
{
    painter->setPen(QPen(Qt::lightGray));

    // draw horizontal grid
    qreal start = round(rect.top(), _gridStep);
    if (start > rect.top()) {
        start -= _gridStep;
    }
    for (qreal y = start - _gridStep; y < rect.bottom(); ) {
        y += _gridStep;
        painter->drawLine((int)rect.left(), (int)y, (int)rect.right(), (int)y);
    }

    // now draw vertical grid
    start = round(rect.left(), _gridStep);
    if (start > rect.left()) {
        start -= _gridStep;
    }
    for (qreal x = start - _gridStep; x < rect.right(); ) {
        x += _gridStep;
        painter->drawLine((int)x, (int)rect.top(), (int)x, (int)rect.bottom());
    }
}

int LCSGridGraphicScene::getGridStep() {
    return _gridStep;
}

void LCSGridGraphicScene::setGridStep(int size) {
    _gridStep = size;
}
