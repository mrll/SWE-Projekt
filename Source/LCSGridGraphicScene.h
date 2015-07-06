//
// Created by Matthias Röll on 20.05.15.
//
// Original aus dem Tutorial von: http://tufangorel.blogspot.de/2011/08/draw-grid-on-qgraphicsscene.html

#ifndef LCSGRIDGRAPHICSCENE_H
#define LCSGRIDGRAPHICSCENE_H

#include <QGraphicsScene>

/* ---------------------------------------------------------------------------------------------------------------- */
/* Abgeleitete QGraphicScene inkl. Grid                                                                             */
/* ---------------------------------------------------------------------------------------------------------------- */

class LCSGridGraphicScene : public QGraphicsScene {
public:
    LCSGridGraphicScene(QObject *parent);

protected:
    /**
     * Hintergrund Zeichen Methode
     *
     * Die Methode wird hier überschrieben,
     * um ein Grid auf der GraphicScene darzutellen.
     *
     * @see QGraphicScene::drawBackground
     */
    void drawBackground(QPainter * painter, const QRectF & rect );
};


#endif //LCGRIDGRAPHICSCENE_H
