#include "bitmapRenderer.h"
#include "qwidget.h"

BitmapRenderer::BitmapRenderer(QWidget *parent, int pixel_size)
    : QWidget(parent)
{
  setBackgroundRole(QPalette::Base);
  setAutoFillBackground(true);
  bitmapChanged = false;
  pixelSize = pixel_size;
  wasBlack = true;
  editable = true;
}

void BitmapRenderer::connect_to(BitmapRenderer * renderer)
{
  QObject::connect(renderer, &BitmapRenderer::bitmapHasChanged, this, &BitmapRenderer::loadBitmap);
  QObject::connect(renderer, &BitmapRenderer::bitmapCleared,    this, &BitmapRenderer::clear_and_repaint);
  editable = false;
}

void BitmapRenderer::clear_and_repaint()
{
  for (int row = 0; row < BITMAP_HEIGHT; row++) {
    for (int col = 0; col < BITMAP_WIDTH; col++) {
      displayBitmap[col][row] = 0;
    }
  }
  this->repaint();
}

void BitmapRenderer::clear(bool repaint_after)
{
  for (int row = 0; row < BITMAP_HEIGHT; row++) {
    for (int col = 0; col < BITMAP_WIDTH; col++) {
      displayBitmap[col][row] = 0;
    }
  }
  if (repaint_after) this->repaint();
  emit this->bitmapCleared();
}

void BitmapRenderer::setPixelSize(int pixel_size)
{
  uint8_t * bitmap;
  Dim dim;

  pixelSize = pixel_size;
  if (retrieveBitmap(&bitmap, &dim)) {
    loadBitmap(bitmap, dim);
    delete [] bitmap;
  }
  else {
    this->repaint();
  }
}

void BitmapRenderer::setPixel(QPoint pos)
{
  QPainter painter(this);
  QRect rect;

  painter.setPen(QPen(QBrush(QColorConstants::Black), 1));
  painter.setBrush(QBrush(QColorConstants::Black));

  if (pixelSize >= 10) {
    rect = QRect(
      pos.x() * pixelSize + 2,
      pos.y() * pixelSize + 2,
      pixelSize - 4,
      pixelSize - 4);
  }
  else {
    rect = QRect(
      pos.x() * pixelSize,
      pos.y() * pixelSize,
      pixelSize,
      pixelSize);
  }
  painter.drawRect(rect);
}

void BitmapRenderer::paintEvent(QPaintEvent * /* event */)
{
  QPainter painter(this);

  painter.setPen(QPen(QBrush(QColorConstants::Gray), 1));
  painter.setBrush(QBrush(QColorConstants::Red));

  if (pixelSize >= 10) {
    for (int row = pixelSize; row < height(); row += pixelSize) {
      for (int col = pixelSize; col < width(); col += pixelSize) {
        painter.drawLine(QPoint(col, 0), QPoint(col, height()));
        painter.drawLine(QPoint(0, row), QPoint(width(), row));
      }
    }
  }
  for (int row = 0; row < BITMAP_HEIGHT; row ++) {
    for (int col = 0; col < BITMAP_WIDTH; col++) {
      if (displayBitmap[col][row] == 1) { setPixel(QPoint(col, row)); }
    }
  }

}

void BitmapRenderer::mousePressEvent(QMouseEvent *event)
{
  if (editable) {
    lastPos = QPoint(event->pos().x() / pixelSize, event->pos().y() / pixelSize);
    if ((lastPos.x() < BITMAP_WIDTH) && (lastPos.y() < BITMAP_HEIGHT)) {
      if (displayBitmap[lastPos.x()][lastPos.y()] == 1) {
        displayBitmap[lastPos.x()][lastPos.y()] = 0;
        wasBlack = false;
      }
      else {
        displayBitmap[lastPos.x()][lastPos.y()] = 1;
        wasBlack = true;
      }
      this->repaint();

      uint8_t * theBitmap;
      Dim theDim;
      if (retrieveBitmap(&theBitmap, &theDim)) {
        emit bitmapHasChanged(theBitmap, theDim);
      }
      else {
        emit bitmapCleared();
      }
    }
  }
}

void BitmapRenderer::mouseMoveEvent(QMouseEvent *event)
{
  if (editable) {
    QPoint pos = QPoint(event->pos().x() / pixelSize, event->pos().y() / pixelSize);
    if ((pos.x() < BITMAP_WIDTH) &&
        (pos.y() < BITMAP_HEIGHT) &&
        ((pos.x() != lastPos.x()) ||
         (pos.y() != lastPos.y()))) {
      displayBitmap[pos.x()][pos.y()] = wasBlack ? 1 : 0;

      this->repaint();

      lastPos.setX(pos.x());
      lastPos.setY(pos.y());

      uint8_t * theBitmap;
      Dim theDim;
      if (retrieveBitmap(&theBitmap, &theDim)) {
        emit bitmapHasChanged(theBitmap, theDim);
      }
      else {
        emit bitmapCleared();
      }
    }
  }
}

void BitmapRenderer::loadBitmap(uint8_t * bitmap, Dim dim)
{
  clear();

  Dim screen(width() / pixelSize, height() / pixelSize);
  Pos pos((screen.width - dim.width) / 2, (screen.height - dim.height) / 2);

  if (pos.x < 0) {
    pos.x = 0;
  }
  else if ((pos.x + dim.width) > BITMAP_WIDTH) {
    pos.x = BITMAP_WIDTH - dim.width;
  }

  if (pos.y < 0) {
    pos.y = 0;
  }
  else if ((pos.y + dim.height) > BITMAP_HEIGHT) {
    pos.y = BITMAP_HEIGHT - dim.height;
  }

  int idx = 0;
  for (int row = pos.y; row < pos.y + dim.height; row++) {
    for (int col = pos.x; col < pos.x + dim.width; col++) {
      displayBitmap[col][row] = bitmap[idx] == 0 ? 0 : 1;
      idx += 1;
    }
  }

  bitmapDim = dim;
  bitmapPos = pos;
  bitmapChanged = false;

  this->repaint();
}

bool BitmapRenderer::retrieveBitmap(uint8_t ** bitmap, Dim * dim)
{
  Pos top_left;
  Pos bottom_right;

  int row;
  int col;

  bool stop = false;
  for (row = 0; row < BITMAP_HEIGHT; row++) {
    for (col = 0; col < BITMAP_WIDTH; col++) {
      stop = displayBitmap[col][row] != 0;
      if (stop) break;
    }
    if (stop) break;
  }

  if (row >= BITMAP_HEIGHT) return false; // The bitmap is empty of black pixels

  top_left.y = row;

  stop = false;
  for (row = BITMAP_HEIGHT - 1; row >= 0; row--) {
    for (col = 0; col < BITMAP_WIDTH; col++) {
      stop = displayBitmap[col][row] != 0;
      if (stop) break;
    }
    if (stop) break;
  }
  bottom_right.y = row;

  stop = false;
  for (col = 0; col < BITMAP_WIDTH; col++) {
    for (row = 0; row < BITMAP_HEIGHT; row++) {
      stop = displayBitmap[col][row] != 0;
      if (stop) break;
    }
    if (stop) break;
  }
  top_left.x = col;

  stop = false;
  for (col = BITMAP_WIDTH - 1; col >= 0; col--) {
    for (row = 0; row < BITMAP_HEIGHT; row++) {
        stop = displayBitmap[col][row] != 0;
        if (stop) break;
    }
    if (stop) break;
  }
  bottom_right.x = col;

  Dim theDim = Dim(bottom_right.x - top_left.x + 1, bottom_right.y - top_left.y + 1);
  int size   = theDim.width * theDim.height;
  uint8_t * theBitmap = new uint8_t[size];

  int idx = 0;
  for (row = top_left.y; row <= bottom_right.y; row++) {
    for (col = top_left.x; col <= bottom_right.x; col++) {
      theBitmap[idx] = displayBitmap[col][row] == 0 ? 0 : 0xff;
      idx += 1;
    }
  }

  *bitmap = theBitmap;
  *dim    = theDim;

  return true;
}
