//
// Created by Matthias Röll on 20.05.15.
//
// Original aus dem Tutorial von: http://tufangorel.blogspot.de/2011/08/draw-grid-on-qgraphicsscene.html

#ifndef LCSGRIDGRAPHICSCENE_H
#define LCSGRIDGRAPHICSCENE_H

#include <QGraphicsScene>

class LCSGridGraphicScene : public QGraphicsScene {
public:
    LCSGridGraphicScene(QObject *parent);

protected:
    void drawBackground(QPainter * painter, const QRectF & rect );
};


#endif //LCGRIDGRAPHICSCENE_H
