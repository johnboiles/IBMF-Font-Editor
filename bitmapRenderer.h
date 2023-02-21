#ifndef BITMAPRENDERER_H
#define BITMAPRENDERER_H

#include <QWidget>
#include <QPen>
#include <QPainter>
#include <QPainterPath>
#include <QMouseEvent>
#include <QPoint>

#include "ibmf_font.hpp"

const int BITMAP_WIDTH  = 200;
const int BITMAP_HEIGHT = 200;

class BitmapRenderer : public QWidget
{
    Q_OBJECT

public:

    BitmapRenderer(QWidget *parent = 0, int pixel_size = 20);
    bool retrieveBitmap(uint8_t ** bitmap, Dim * dim);
    void clear(bool repaint_after = false);
    bool changed() { return bitmapChanged; }
    void setPixelSize(int pixel_size);
    void connectTo(BitmapRenderer * renderer);
    void resizing();

public slots:
    void clearAndLoadBitmap(uint8_t * bitmap, Dim dim);
    void clear_and_repaint();

signals:
    void bitmapHasChanged(uint8_t * bitmap, Dim dim);
    void bitmapCleared();

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:
    void setPixel(QPoint pos);
    void loadBitmap(uint8_t * bitmap, Dim dim);
    void clearBitmap();
    Dim  bitmapDim;
    Pos  bitmapPos;
    bool bitmapChanged;
    int  pixelSize;
    char displayBitmap[BITMAP_WIDTH][BITMAP_HEIGHT];
    bool wasBlack;
    bool editable;
    QPoint lastPos;

};

#endif // BITMAPRENDERER_H
