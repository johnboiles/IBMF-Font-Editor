#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include <QByteArray>
#include <QTableWidgetItem>
#include <QStyledItemDelegate>
#include <QDoubleSpinBox>

#include "bitmapRenderer.h"
#include "ibmf_font.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

protected:
  void closeEvent(QCloseEvent *event);
  void resizeEvent(QResizeEvent *event);

private slots:
  void on_actionOpen_triggered();
  void on_actionExit_triggered();
  void on_leftButton_clicked();
  void on_rightButton_clicked();
  void on_faceIndex_currentIndexChanged(int index);
  void on_pixelSize_valueChanged(int value);
  void on_charactersList_cellClicked(int row, int column);
  void on_characterMetrics_cellChanged(int row, int column);
  void on_faceHeader_cellChanged(int row, int column);
  void on_glyphForgetButton_clicked();
  void on_faceForgetButton_clicked();

  void bitmapChanged(uint8_t * bitmap, Dim dim);

private:
  Ui::MainWindow *ui;
  QString currentFilename;
  QFile file;

  bool fontChanged;
  bool faceChanged;
  bool glyphChanged;
  bool initialized;
  bool glyphReloading;
  bool faceReloading;

  BitmapRenderer * bitmapRenderer;
  BitmapRenderer * smallGlyph;
  BitmapRenderer * largeGlyph;

  IBMFFont             * ibmfFont;
  IBMFFont::Preamble   * ibmfPreamble;
  IBMFFont::FaceHeader * ibmfFaceHeader;
  IBMFFont::GlyphInfo  * ibmfGlyphInfo;
  uint8_t              * ibmfGlyphBitmap;

  IBMFFont::GlyphLigKern * ibmfLigKerns;

  int ibmfFaceIdx;
  int ibmfGlyphCode;

  bool checkFontChanged();
  bool loadFont();
  bool loadFace(uint8_t face_idx);
  void saveFace();
  void saveGlyph();
  bool loadGlyph(uint16_t glyph_code);
  void clearAll();
  void putValue(QTableWidget * w, int row, int col, QVariant value, bool editable = true);
  void putFix16Value(QTableWidget * w, int row, int col, QVariant value, bool editable = true);
  QVariant getValue(QTableWidget * w, int row, int col);
  void clearEditable(QTableWidget * w, int row, int col);
};

// The following is to support Fix16 fields editing in QTableWidgets
class Fix16Delegate : public QStyledItemDelegate
{
  QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& style, const QModelIndex& index) const
  {
    QDoubleSpinBox* box = new QDoubleSpinBox(parent);

    box->setDecimals(4);

    // you can also set these
    box->setSingleStep(0.01);
    box->setMinimum(0);
    box->setMaximum(1000);

    return box;
  }
};

#endif // MAINWINDOW_H
