//
// Created by Matthias Röll on 20.05.15.
//

#ifndef SWE_PROJEKT_LCGRIDGRAPHICSCENE_H
#define SWE_PROJEKT_LCGRIDGRAPHICSCENE_H

#include <QGraphicsScene>

class LCGridGraphicScene : public QGraphicsScene {
public:
    LCGridGraphicScene(QObject *parent);

protected:
    void drawBackground(QPainter * painter, const QRectF & rect );
};


#endif //SWE_PROJEKT_LCGRIDGRAPHICSCENE_H
