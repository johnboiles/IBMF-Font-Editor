#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
  initialized = false;
  ui->setupUi(this);
  currentFilename = "";
  fontChanged = false;
  glyphChanged = false;
  faceChanged = false;
  setWindowTitle("IBMF Font Editor");

  bitmapRenderer = new BitmapRenderer;
  ui->bitmapFrame->layout()->addWidget(bitmapRenderer);

  QObject::connect(bitmapRenderer, &BitmapRenderer::bitmapHasChanged , this, &MainWindow::bitmapChanged);

  smallGlyph = new BitmapRenderer;
  smallGlyph->setPixelSize(2);
  ui->smallGlyphPreview->layout()->addWidget(smallGlyph);
  smallGlyph->connect_to(bitmapRenderer);

  largeGlyph = new BitmapRenderer;
  largeGlyph->setPixelSize(4);
  ui->largeGlyphPreview->layout()->addWidget(largeGlyph);
  largeGlyph->connect_to(bitmapRenderer);

  ibmf_font = nullptr;
  ibmf_glyph_code = 0;

  // All captions in the tables are not editable
  for (int row = 0; row < ui->fontHeader->rowCount(); row++) {
    this->clearEditable(ui->fontHeader, row, 0);
  }

  for (int row = 0; row < ui->faceHeader->rowCount(); row++) {
    this->clearEditable(ui->faceHeader, row, 0);
  }

  for (int row = 0; row < ui->characterMetrics->rowCount(); row++) {
    this->clearEditable(ui->characterMetrics, row, 0);
  }

  // Initialize the characters table
  ui->charactersList->setColumnCount(5);
  ui->charactersList->setRowCount((174 + 4) / 5);

  for (int col = 0; col < 5; col++) {
    ui->charactersList->setColumnWidth(col, 40);
  }

  int idx = 0;
  for (int row = 0; row < ui->charactersList->rowCount(); row++) {
    ui->charactersList->setRowHeight(row, 50);
    for (int col = 0; col < 5; col++) {
      auto item = new QTableWidgetItem;
      item->setFlags(item->flags() & ~ Qt::ItemIsEditable);
      item->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);
      if (idx < 174) {
          item->setData(Qt::EditRole, characterCodes[idx]);
          item->setToolTip(QString::number(idx));
      }
      else {
          item->setFlags(Qt::NoItemFlags);
      }
      ui->charactersList->setItem(row, col, item);
      idx += 1;
    }
  }

  // Set tables columns widths
  ui->fontHeader->setColumnWidth(0, 120);
  ui->faceHeader->setColumnWidth(0, 120);
  ui->characterMetrics->setColumnWidth(0, 120);
  ui->fontHeader->setColumnWidth(1, 100);
  ui->faceHeader->setColumnWidth(1, 100);
  ui->characterMetrics->setColumnWidth(1, 100);

  // clear all data
  this->clearAll();

  initialized = true;
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
  if (!checkFontChanged()) event->ignore();
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
  bitmapRenderer->setPixelSize(ui->pixelSize->value());
}

void MainWindow::bitmapChanged(uint8_t * bitmap, Dim dim)
{
  if (ibmf_font != nullptr) {
    fontChanged = true;
    glyphChanged = true;
  }
}

bool MainWindow::checkFontChanged()
{
  if (fontChanged) {
    saveGlyph();
    QMessageBox::StandardButton button = QMessageBox::question(
            this, "File Changed", "File was changed. Do you want to save it ?",
            QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel);
    if (button == QMessageBox::Yes) {
      QMessageBox::information(this, "Saving....", "Saving the file...");
    }
    else {
      return button != QMessageBox::Cancel;
    }

    fontChanged = false;
    currentFilename = "";
    setWindowTitle("IBMF Font Editor");
  }
  return true;
}

void MainWindow::on_actionOpen_triggered()
{
  if (!checkFontChanged()) return;

  QString filename = QFileDialog::getOpenFileName(this, "Open IBMF Font File");
  file.setFileName(filename);
  currentFilename = filename;
  fontChanged = false;

  if (!file.open(QIODevice::ReadOnly)) {
    QMessageBox::warning(this, "Warning", "Unable to open file " + file.errorString());
  }
  else {
    if (loadFont()) {
      setWindowTitle("IBMF Font Editor - " + filename);
    }
    else {
      QMessageBox::warning(this, "Warning", "Unable to load IBMF file " + currentFilename);
    }
    file.close();
  }
}

void MainWindow::clearAll()
{
  ui->faceIndex->clear();
  bitmapRenderer->clear(); // Will clear other renderers through signaling
}

void MainWindow::on_actionExit_triggered()
{
  if (checkFontChanged()) QApplication::exit();
}

void MainWindow::clearEditable(QTableWidget * w, int row, int col )
{
  auto item = w->item(row, col);
  item->setFlags(item->flags() & ~ Qt::ItemIsEditable);
}

void MainWindow::putValue(QTableWidget * w, int row, int col, QVariant value, bool editable)
{
  auto item = new QTableWidgetItem();
  item->setData(Qt::EditRole, value);
  if (!editable) item->setFlags(item->flags() & ~ Qt::ItemIsEditable);
  w->setItem(row, col, item);
}

void MainWindow::putFix16Value(QTableWidget * w, int row, int col, QVariant value, bool editable)
{
  auto item = new QTableWidgetItem();
  item->setData(Qt::EditRole, value);
  if (!editable) item->setFlags(item->flags() & ~ Qt::ItemIsEditable);
  w->setItem(row, col, item);
  w->setItemDelegateForRow(row, new Fix16Delegate);
}

QVariant MainWindow::getValue(QTableWidget * w, int row, int col)
{
  return w->item(row, col)->data(Qt::DisplayRole);
}

bool MainWindow::loadFont()
{
  QByteArray content = file.readAll();
  file.close();
  if (ibmf_font != nullptr) {
    delete ibmf_font;
    ibmf_font = nullptr;
  }
  ibmf_font = new IBMFFont((uint8_t *) content.data(), content.size());
  if (ibmf_font->is_initialized()) {
    ibmf_preamble = ibmf_font->get_preample();

    char marker[5];
    memcpy(marker, ibmf_preamble->marker, 4);
    marker[4] = 0;

    putValue(ui->fontHeader, 0, 1, marker,                       false);
    putValue(ui->fontHeader, 1, 1, ibmf_preamble->face_count,    false);
    putValue(ui->fontHeader, 2, 1, ibmf_preamble->bits.version,  false);
    putValue(ui->fontHeader, 3, 1, ibmf_preamble->bits.char_set, false);

    for (int i = 0; i < ibmf_preamble->face_count; i++) {
      IBMFFont::FaceHeader * face_header = ibmf_font->get_face_header(i);
      ui->faceIndex->addItem(QString::number(face_header->point_size).append(" pts"));
    }

    loadFace(0);

    fontChanged = false;
    faceChanged = false;
    glyphChanged = false;
  }
  return ibmf_font->is_initialized();
}

void MainWindow::saveFace()
{
  if ((ibmf_font != nullptr) && ibmf_font->is_initialized() && faceChanged) {
    IBMFFont::FaceHeader face_header;

    face_header.point_size         = getValue(ui->faceHeader,  0, 1).toUInt();
    face_header.line_height        = getValue(ui->faceHeader,  1, 1).toUInt();
    face_header.dpi                = getValue(ui->faceHeader,  2, 1).toUInt();
    face_header.x_height           = getValue(ui->faceHeader,  3, 1).toFloat() * 64.0;
    face_header.em_size            = getValue(ui->faceHeader,  4, 1).toFloat() * 64.0;
    face_header.slant_correction   = getValue(ui->faceHeader,  5, 1).toFloat() * 64.0;
    face_header.descender_height   = getValue(ui->faceHeader,  6, 1).toUInt();
    face_header.space_size         = getValue(ui->faceHeader,  7, 1).toUInt();
    face_header.glyph_count        = getValue(ui->faceHeader,  8, 1).toUInt();
    face_header.lig_kern_pgm_count = getValue(ui->faceHeader,  9, 1).toUInt();
    face_header.kern_count         = getValue(ui->faceHeader, 10, 1).toUInt();

    ibmf_font->save_face_header(ibmf_face_idx, &face_header);
    faceChanged = false;
  }
}

bool MainWindow::loadFace(uint8_t face_idx)
{
  saveFace();
  if ((ibmf_font != nullptr) && (ibmf_font->is_initialized()) && (face_idx < ibmf_preamble->face_count)) {
    ibmf_face_header = ibmf_font->get_face_header(face_idx);

    putValue(ui->faceHeader,  0, 1, ibmf_face_header->point_size,                       false);
    putValue(ui->faceHeader,  1, 1, ibmf_face_header->line_height);
    putValue(ui->faceHeader,  2, 1, ibmf_face_header->dpi);
    putFix16Value(ui->faceHeader,  3, 1, (float) ibmf_face_header->x_height / 64.0);
    putFix16Value(ui->faceHeader,  4, 1, (float) ibmf_face_header->em_size / 64.0);
    putFix16Value(ui->faceHeader,  5, 1, (float) ibmf_face_header->slant_correction / 64.0);
    putValue(ui->faceHeader,  6, 1, ibmf_face_header->descender_height);
    putValue(ui->faceHeader,  7, 1, ibmf_face_header->space_size);
    putValue(ui->faceHeader,  8, 1, ibmf_face_header->glyph_count,                      false);
    putValue(ui->faceHeader,  9, 1, ibmf_face_header->lig_kern_pgm_count,               false);
    putValue(ui->faceHeader, 10, 1, ibmf_face_header->kern_count,                       false);

    ibmf_face_idx = face_idx;

    loadGlyph(ibmf_glyph_code);
  }
  else {
    return false;
  }

  return true;
}

void MainWindow::saveGlyph()
{
  if ((ibmf_font != nullptr) && ibmf_font->is_initialized() && glyphChanged) {
    uint8_t * theBitmap;
    Dim theDim;
    IBMFFont::GlyphInfo glyph_info;
    if (bitmapRenderer->retrieveBitmap(&theBitmap, &theDim)) {

      glyph_info.char_code                   = getValue(ui->characterMetrics,  0, 1).toUInt();
      glyph_info.bitmap_width                = theDim.width;
      glyph_info.bitmap_height               = theDim.height;
      glyph_info.horizontal_offset           = getValue(ui->characterMetrics,  3, 1).toInt();
      glyph_info.vertical_offset             = getValue(ui->characterMetrics,  4, 1).toInt();
      glyph_info.lig_kern_pgm_index          = getValue(ui->characterMetrics,  5, 1).toUInt();
      glyph_info.packet_length               = getValue(ui->characterMetrics,  6, 1).toUInt();
      glyph_info.advance                     = getValue(ui->characterMetrics,  7, 1).toFloat() * 64.0;
      glyph_info.glyph_metric.dyn_f          = getValue(ui->characterMetrics,  8, 1).toUInt();
      glyph_info.glyph_metric.first_is_black = getValue(ui->characterMetrics,  9, 1).toUInt();

      ibmf_font->save_glyph(ibmf_face_idx, ibmf_glyph_code, &glyph_info, theBitmap);
      glyphChanged = false;
    }
  }
}

bool MainWindow::loadGlyph(uint16_t glyph_code)
{
  saveGlyph();
  if ((ibmf_font != nullptr) &&
      (ibmf_font->is_initialized()) &&
      (ibmf_face_idx < ibmf_preamble->face_count) &&
      (glyph_code < ibmf_face_header->glyph_count)) {

    if (ibmf_font->get_glyph(ibmf_face_idx, glyph_code, &ibmf_glyph_info, &ibmf_glyph_bitmap)) {
      ibmf_glyph_code = glyph_code;

      glyphChanged = false;

      putValue(ui->characterMetrics,  0, 1, ibmf_glyph_info->char_code,                   false);
      putValue(ui->characterMetrics,  1, 1, ibmf_glyph_info->bitmap_width,                false);
      putValue(ui->characterMetrics,  2, 1, ibmf_glyph_info->bitmap_height,               false);
      putValue(ui->characterMetrics,  3, 1, ibmf_glyph_info->horizontal_offset);
      putValue(ui->characterMetrics,  4, 1, ibmf_glyph_info->vertical_offset);
      putValue(ui->characterMetrics,  5, 1, ibmf_glyph_info->lig_kern_pgm_index,          false);
      putValue(ui->characterMetrics,  6, 1, ibmf_glyph_info->packet_length,               false);
      putFix16Value(ui->characterMetrics,  7, 1, (float) ibmf_glyph_info->advance / 64.0);
      putValue(ui->characterMetrics,  8, 1, ibmf_glyph_info->glyph_metric.dyn_f,          false);
      putValue(ui->characterMetrics,  9, 1, ibmf_glyph_info->glyph_metric.first_is_black, false);

      bitmapRenderer->loadBitmap(ibmf_glyph_bitmap, Dim(ibmf_glyph_info->bitmap_width, ibmf_glyph_info->bitmap_height));
      smallGlyph->loadBitmap(ibmf_glyph_bitmap, Dim(ibmf_glyph_info->bitmap_width, ibmf_glyph_info->bitmap_height));
      largeGlyph->loadBitmap(ibmf_glyph_bitmap, Dim(ibmf_glyph_info->bitmap_width, ibmf_glyph_info->bitmap_height));

      ui->ligTable->clearContents();
      ui->kernTable->clearContents();

// TBD: Lig/Kern formatting issue
//
//      if (ibmf_font->get_glyph_lig_kern(ibmf_face_idx, ibmf_glyph_code, &ibmf_lig_kerns)) {
//        ui->ligTable->setRowCount(ibmf_lig_kerns->lig_steps.size());
//        for (int i = 0; i < ibmf_lig_kerns->lig_steps.size(); i++) {
//          putValue(ui->ligTable, i, 0, ibmf_lig_kerns->lig_steps[i].next_char_code);
//          putValue(ui->ligTable, i, 1, ibmf_lig_kerns->lig_steps[i].char_code);
//          ui->ligTable->item(i, 0)->setToolTip(QChar(characterCodes[ibmf_lig_kerns->lig_steps[i].next_char_code]));
//          ui->ligTable->item(i, 1)->setToolTip(QChar(characterCodes[ibmf_lig_kerns->lig_steps[i].char_code]));
//        }
//        ui->kernTable->setRowCount(ibmf_lig_kerns->kern_steps.size());
//        for (int i = 0; i < ibmf_lig_kerns->kern_steps.size(); i++) {
//          putValue(ui->kernTable, i, 0, ibmf_lig_kerns->kern_steps[i].next_char_code);
//          putFix16Value(ui->kernTable, i, 1, (float) ibmf_lig_kerns->kern_steps[i].kern / 64.0);
//          ui->kernTable->item(i, 0)->setToolTip(QChar(characterCodes[ibmf_lig_kerns->kern_steps[i].next_char_code]));
//        }
//      }

      ui->charactersList->setCurrentCell(glyph_code / 5, glyph_code % 5);
    }
    else {
      return false;
    }
  }
  else {
    return false;
  }

  return true;
}

void MainWindow::on_leftButton_clicked()
{
  if ((ibmf_font == nullptr) || !ibmf_font->is_initialized()) return;

  uint16_t glyph_code = ibmf_glyph_code;

  if (glyph_code > 0) {
    glyph_code -= 1;
  }
  else {
    glyph_code = ibmf_face_header->glyph_count - 1;
  }
  loadGlyph(glyph_code);
}


void MainWindow::on_rightButton_clicked()
{
  if ((ibmf_font == nullptr) || !ibmf_font->is_initialized()) return;

  uint16_t glyph_code = ibmf_glyph_code;

  if (glyph_code >= ibmf_face_header->glyph_count - 1) {
    glyph_code = 0;
  }
  else {
    glyph_code += 1;
  }
  loadGlyph(glyph_code);
}


void MainWindow::on_faceIndex_currentIndexChanged(int index)
{
  if ((ibmf_font == nullptr) || !ibmf_font->is_initialized()) return;

  loadFace(index);
}

void MainWindow::on_pixelSize_valueChanged(int value)
{
  bitmapRenderer->setPixelSize(ui->pixelSize->value());
}


void MainWindow::on_charactersList_cellClicked(int row, int column)
{
  int idx = (row * 5) + column;
  if (ibmf_font != nullptr) {
    loadGlyph(idx);
  }
  else {
    ibmf_glyph_code = idx; // Retain the selection for when a font will be loaded
  }
}

void MainWindow::on_characterMetrics_cellChanged(int row, int column)
{
  if ((ibmf_font != nullptr) && ibmf_font->is_initialized() && initialized) {
    glyphChanged = true;
  }
}


void MainWindow::on_faceHeader_cellChanged(int row, int column)
{
  if ((ibmf_font != nullptr) && ibmf_font->is_initialized() && initialized) {
    faceChanged = true;
  }

}


void MainWindow::on_glyphForgetButton_clicked()
{
  if (glyphChanged) {
    QMessageBox::StandardButton button = QMessageBox::question(
            this, "Character has been Modified",
            "You will loose all changes to the bitmap and metrics. Are-you sure?",
            QMessageBox::Yes|QMessageBox::No);
    if (button == QMessageBox::Yes) {
      glyphChanged = false;
      loadGlyph(ibmf_glyph_code);
    }
  }
}


void MainWindow::on_faceForgetButton_clicked()
{
  if (faceChanged) {
    QMessageBox::StandardButton button = QMessageBox::question(
            this, "Face Header Modified",
            "You will loose all changes to the Face Header. Are-you sure?",
            QMessageBox::Yes|QMessageBox::No);
    if (button == QMessageBox::Yes) {
      faceChanged = false;
      loadFace(ibmf_face_idx);
    }
  }

}

