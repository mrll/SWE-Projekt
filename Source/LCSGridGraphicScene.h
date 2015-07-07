//
// Created by Matthias Röll, Marc Wüst
//
// Original aus dem Tutorial von: http://tufangorel.blogspot.de/2011/08/draw-grid-on-qgraphicsscene.html

#ifndef LCSGRIDGRAPHICSCENE_H
#define LCSGRIDGRAPHICSCENE_H

#include <QGraphicsScene>

/* ---------------------------------------------------------------------------------------------------------------- */
/* Abgeleitete QGraphicScene inkl. Grid                                                                             */
/* ---------------------------------------------------------------------------------------------------------------- */

/**
 * @brief Grid Graphic View
 *
 * Die Klasse zeichnet ein Karomuster im Hintergrund der GraphicView.
 *
 * Die Klasse stammt ursprünglich aus dem Blogeintrag:
 *  http://tufangorel.blogspot.de/2011/08/draw-grid-on-qgraphicsscene.html
 * wurde aber um die Möglichkeit erweitert, die Karogröße einzustellen.
 */
class LCSGridGraphicScene : public QGraphicsScene {
public:
    LCSGridGraphicScene(QObject *parent);

    int getGridStep();
    void setGridStep(int size);

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

private:
    int _gridStep;
};


#endif //LCGRIDGRAPHICSCENE_H
