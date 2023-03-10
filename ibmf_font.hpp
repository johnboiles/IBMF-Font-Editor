#pragma once

#include <cinttypes>
#include <cstring>
#include <vector>

#include <QChar>

// These are the corresponding Unicode value for each of the 174 characters that are part of
// an IBMF Font;
const QChar characterCodes[] = {
    QChar(0x0060), // `
    QChar(0x00B4), // ´
    QChar(0x02C6), // ˆ
    QChar(0x02DC), // ˜
    QChar(0x00A8), // ¨
    QChar(0x02DD), // ˝
    QChar(0x02DA), // ˚
    QChar(0x02C7), // ˇ
    QChar(0x02D8), // ˘
    QChar(0x00AF), // ¯
    QChar(0x02D9), // ˙
    QChar(0x00B8), // ¸
    QChar(0x02DB), // ˛
    QChar(0x201A), // ‚
    QChar(0x2039), // ‹
    QChar(0x203A), // ›
    
    QChar(0x201C), // “
    QChar(0x201D), // ”
    QChar(0x201E), // „
    QChar(0x00AB), // «
    QChar(0x00BB), // »
    QChar(0x2013), // –
    QChar(0x2014), // —
    QChar(0x00BF), // ¿
    QChar(0x2080), // ₀
    QChar(0x0131), // ı
    QChar(0x0237), // ȷ
    QChar(0xFB00), // ﬀ
    QChar(0xFB01), // ﬁ
    QChar(0xFB02), // ﬂ
    QChar(0xFB03), // ﬃ
    QChar(0xFB04), // ﬄ
    
    QChar(0x00A1), // ¡
    QChar(0x0021), // !
    QChar(0x0022), // "
    QChar(0x0023), // #
    QChar(0x0024), // $
    QChar(0x0025), // %
    QChar(0x0026), // &
    QChar(0x2019), // ’
    QChar(0x0028), // (
    QChar(0x0029), // )
    QChar(0x002A), // *
    QChar(0x002B), // +
    QChar(0x002C), // ,
    QChar(0x002D), // .
    QChar(0x002E), // -
    QChar(0x002F), // /
    
    QChar(0x0030), // 0
    QChar(0x0031), // 1
    QChar(0x0032), // 2
    QChar(0x0033), // 3
    QChar(0x0034), // 4
    QChar(0x0035), // 5
    QChar(0x0036), // 6
    QChar(0x0037), // 7
    QChar(0x0038), // 8
    QChar(0x0039), // 9
    QChar(0x003A), // :
    QChar(0x003B), // ;
    QChar(0x003C), // <
    QChar(0x003D), // =
    QChar(0x003E), // >
    QChar(0x003F), // ?
    
    QChar(0x0040), // @
    QChar(0x0041), // A
    QChar(0x0042), // B
    QChar(0x0043), // C
    QChar(0x0044), // D
    QChar(0x0045), // E
    QChar(0x0046), // F
    QChar(0x0047), // G
    QChar(0x0048), // H
    QChar(0x0049), // I
    QChar(0x004A), // J
    QChar(0x004B), // K
    QChar(0x004C), // L
    QChar(0x004D), // M
    QChar(0x004E), // N
    QChar(0x004F), // O

    QChar(0x0050), // P
    QChar(0x0051), // Q
    QChar(0x0052), // R
    QChar(0x0053), // S
    QChar(0x0054), // T
    QChar(0x0055), // U
    QChar(0x0056), // V
    QChar(0x0057), // W
    QChar(0x0058), // X
    QChar(0x0059), // Y
    QChar(0x005A), // Z
    QChar(0x005B), // [
    QChar(0x005C), // \ .
    QChar(0x005D), // ]
    QChar(0x005E), // ^
    QChar(0x005F), // _

    QChar(0x2018), // ‘
    QChar(0x0061), // a
    QChar(0x0062), // b
    QChar(0x0063), // c
    QChar(0x0064), // d
    QChar(0x0065), // e
    QChar(0x0066), // f
    QChar(0x0067), // g
    QChar(0x0068), // h
    QChar(0x0069), // i
    QChar(0x006A), // j
    QChar(0x006B), // k
    QChar(0x006C), // l
    QChar(0x006D), // m
    QChar(0x006E), // n
    QChar(0x006F), // o

    QChar(0x0070), // p
    QChar(0x0071), // q
    QChar(0x0072), // r
    QChar(0x0073), // s
    QChar(0x0074), // t
    QChar(0x0075), // u
    QChar(0x0076), // v
    QChar(0x0077), // w
    QChar(0x0078), // x
    QChar(0x0079), // y
    QChar(0x007A), // z
    QChar(0x007B), // {
    QChar(0x007C), // |
    QChar(0x007D), // }
    QChar(0x007E), // ~
    QChar(0x013D), // Ľ

    QChar(0x0141), // Ł
    QChar(0x014A), // Ŋ
    QChar(0x0132), // Ĳ
    QChar(0x0111), // đ
    QChar(0x00A7), // §
    QChar(0x010F), // ď
    QChar(0x013E), // ľ
    QChar(0x0142), // ł
    QChar(0x014B), // ŋ
    QChar(0x0165), // ť
    QChar(0x0133), // ĳ
    QChar(0x00A3), // £
    QChar(0x00C6), // Æ
    QChar(0x00D0), // Ð
    QChar(0x0152), // Œ
    QChar(0x00D8), // Ø

    QChar(0x00DE), // Þ
    QChar(0x1E9E), // ẞ
    QChar(0x00E6), // æ
    QChar(0x00F0), // ð
    QChar(0x0153), // œ
    QChar(0x00F8), // ø
    QChar(0x00FE), // þ
    QChar(0x00DF), // ß
    QChar(0x00A2), // ¢
    QChar(0x00A4), // ¤
    QChar(0x00A5), // ¥
    QChar(0x00A6), // ¦
    QChar(0x00A9), // ©
    QChar(0x00AA), // ª
    QChar(0x00AC), // ¬
    QChar(0x00AE), // ®

    QChar(0x00B1), // ±
    QChar(0x00B2), // ²
    QChar(0x00B3), // ³
    QChar(0x00B5), // µ
    QChar(0x00B6), // ¶
    QChar(0x00B7), // ·
    QChar(0x00B9), // ¹
    QChar(0x00BA), // º
    QChar(0x00D7), // ×
    QChar(0x00BC), // ¼
    QChar(0x00BD), // ½
    QChar(0x00BE), // ¾
    QChar(0x00F7), // ÷
    QChar(0x20AC)  // €
};
 
struct Dim {
    int16_t width;
    int16_t height;
    Dim(int16_t w, int16_t h) {
      width  = w;
      height = h;
    }
    Dim() {}
};

struct Pos {
    int16_t x;
    int16_t y;
    Pos(int16_t xpos, int16_t ypos) {
      x = xpos;
      y = ypos;
    }
    Pos() {}
};


/**
 * @brief Access to a IBMF font.
 * 
 * This is a class to allow acces to a IBMF font generated from METAFONT
 * 
 */
class IBMFFont
{
  public:
    typedef int16_t FIX16;

    struct GlyphKernStep {
      unsigned int next_char_code;
      FIX16 kern;
    };

    struct GlyphLigStep {
      unsigned int next_char_code;
      unsigned int char_code;
    };

    struct GlyphLigKern {
      std::vector<GlyphLigStep>  lig_steps;
      std::vector<GlyphKernStep> kern_steps;
    };

    #pragma pack(push, 1)
      struct LigKernStep {
        unsigned int next_char_code:8;
        union {
          unsigned int char_code:8;
          unsigned int kern_idx:8;  // Ligature: replacement char code, kern: displacement
        } u;
        unsigned int tag:1;         // 0 = Ligature, 1 = Kern
        unsigned int stop:1;
        unsigned int filler:6;
      };

      struct GlyphMetric {
        unsigned int          dyn_f:4;
        unsigned int first_is_black:1;
        unsigned int         filler:3;
      };

      struct GlyphInfo {
        uint8_t     bitmap_width;
        uint8_t     bitmap_height;
        int8_t      horizontal_offset;
        int8_t      vertical_offset;
        uint16_t    lig_kern_pgm_index; // = 65535 if none
        uint16_t    packet_length;
        FIX16       advance;
        GlyphMetric glyph_metric;
        uint8_t     char_code;
      };

      struct Preamble {
        char     marker[4];
        uint8_t  face_count;
        struct {
          uint8_t   version:5;
          uint8_t  char_set:3;
        } bits;
      };

      std::vector<uint32_t> face_offsets;

      struct FaceHeader {
        uint8_t    point_size;
        uint8_t    line_height;
        uint16_t   dpi;
        FIX16      x_height;
        FIX16      em_size;
        FIX16      slant_correction;
        uint8_t    descender_height;
        uint8_t    space_size;
        uint16_t   glyph_count;
        uint16_t   lig_kern_pgm_count;
        uint16_t    kern_count;
      };

    #pragma pack(pop)

    struct Face {
      FaceHeader header;
      std::vector<GlyphInfo *> glyphs;
      std::vector<uint8_t *> bitmaps;
      std::vector<LigKernStep *> lig_kern_steps;
      std::vector<FIX16> kerns;
      std::vector<GlyphLigKern *> glyphs_lig_kern;
    };

  private:
    static constexpr char const * TAG = "IBMFFont";
    
    static constexpr uint8_t MAX_GLYPH_COUNT = 254; // Index Value 0xFE and 0xFF are reserved
    static constexpr uint8_t IBMF_VERSION    =   3;

    bool initialized;

    std::vector<Face *> faces;

    uint8_t     * memory;
    uint32_t      memory_length;

    uint8_t     * memory_ptr;
    uint8_t     * memory_end;

    uint32_t      repeat_count;

    Preamble    * preamble;

    static constexpr uint8_t PK_REPEAT_COUNT =   14;
    static constexpr uint8_t PK_REPEAT_ONCE  =   15;

    bool
    getnext8(uint8_t & val)
    {
      if (memory_ptr >= memory_end) return false;  
      val = *memory_ptr++;
      return true;
    }

    uint8_t nybble_flipper = 0xf0U;
    uint8_t nybble_byte;

    bool
    get_nybble(uint8_t & nyb)
    {
      if (nybble_flipper == 0xf0U) {
        if (!getnext8(nybble_byte)) return false;
        nyb = nybble_byte >> 4;
      }
      else {
        nyb = (nybble_byte & 0x0f);
      }
      nybble_flipper ^= 0xffU;
      return true;
    }

    // Pseudo-code:
    //
    // function pk_packed_num: integer;
    // var i,j,k: integer;
    // begin 
    //   i := get_nyb;
    //   if i = 0 then begin 
    //     repeat 
    //       j := getnyb; incr(i);
    //     until j != 0;
    //     while i > 0 do begin 
    //       j := j * 16 + get_nyb; 
    //       decr(i);
    //     end;
    //     pk_packed_num := j - 15 + (13 - dyn_f) * 16 + dyn_f;
    //   end
    //   else if i <= dyn_f then 
    //     pk_packed_num := i
    //   else if i < 14 then 
    //     pk_packed_num := (i - dyn_f - 1) * 16 + get_nyb + dyn_f + 1
    //   else begin 
    //     if repeat_count != 0 then abort('Extra repeat count!');
    //     if i = 14 then
    //        repeat_count := pk_packed_num
    //     else
    //        repeat_count := 1;
    //     send_out(true, repeat_count);
    //     pk_packed_num := pk_packed_num;
    //   end;
    // end;

    bool
    get_packed_number(uint32_t & val, const GlyphInfo & glyph)
    {
      uint8_t  nyb;
      uint32_t i, j;

      uint8_t dyn_f = glyph.glyph_metric.dyn_f;

      while (true) {
        if (!get_nybble(nyb)) return false; 
        i = nyb;
        if (i == 0) {
          do {
            if (!get_nybble(nyb)) return false;
            i++;
          } while (nyb == 0);
          j = nyb;
          while (i-- > 0) {
            if (!get_nybble(nyb)) return false;
            j = (j << 4) + nyb;
          }
          val = j - 15 + ((13 - dyn_f) << 4) + dyn_f;
          break;
        }
        else if (i <= dyn_f) {
          val = i;
          break;
        }
        else if (i < PK_REPEAT_COUNT) {
          if (!get_nybble(nyb)) return false;
          val = ((i - dyn_f - 1) << 4) + nyb + dyn_f + 1;
          break;
        }
        else { 
          if (i == PK_REPEAT_COUNT) {
            if (!get_packed_number(repeat_count, glyph)) return false;
          }
          else { // i == PK_REPEAT_ONCE
            repeat_count = 1;
          }
        }
      }
      return true;
    }

    bool
    retrieve_bitmap(uint32_t idx, GlyphInfo * glyph_info, uint8_t * bitmap, Dim dim, Pos offsets)
    {
      // point on the glyphs' bitmap definition
      memory_ptr = &memory[idx];
      uint8_t * rowp;

      uint32_t  row_size = dim.width;
      rowp = bitmap + (offsets.y * row_size);

      repeat_count   = 0;
      nybble_flipper = 0xf0U;

      if (glyph_info->glyph_metric.dyn_f == 14) {  // is a bitmap?
        uint32_t  count = 8;
        uint8_t   data;

        for (uint32_t row = 0;
             row < (glyph_info->bitmap_height);
             row++, rowp += row_size) {
          for (uint32_t col = offsets.x;
               col < (glyph_info->bitmap_width + offsets.x);
               col++) {
            if (count >= 8) {
              if (!getnext8(data)) {
                return false;
              }
              count = 0;
            }
            rowp[col] = (data & (0x80U >> count)) ? 0xFF : 0;
            count++;
          }
        }
      }
      else {
        uint32_t count = 0;

        repeat_count   = 0;
        nybble_flipper = 0xf0U;

        bool black = !(glyph_info->glyph_metric.first_is_black == 1);

        for (uint32_t row = 0;
             row < (glyph_info->bitmap_height);
             row++, rowp += row_size) {
          for (uint32_t col = offsets.x;
               col < (glyph_info->bitmap_width + offsets.x);
               col++) {
            if (count == 0) {
              if (!get_packed_number(count, *glyph_info)) {
                return false;
              }
              black = !black;

            }
            if (black) rowp[col] = 0xFF;
            count--;
          }

          while ((row < dim.height) && (repeat_count-- > 0)) {
            memcpy(rowp + row_size, rowp, row_size);
            row++;
            rowp += row_size;
          }

          repeat_count = 0;
        }
      }

      return true;
    }

    bool
    load()
    {
      preamble = new Preamble;
      memcpy(preamble, memory, sizeof(Preamble));
      if (strncmp("IBMF", preamble->marker, 4) != 0) return false;
      if (preamble->bits.version != IBMF_VERSION) return false;

      int idx = sizeof(Preamble);

      for (int i = 0; i < preamble->face_count; i++) {
        uint32_t offset = *((uint32_t *) &memory[idx]);
        face_offsets.push_back(offset);
        idx += 4;
      }

      for (int i = 0; i < preamble->face_count; i++) {
        uint32_t idx = face_offsets[i];
        Face * face = new Face;
        memcpy(&face->header, &memory[idx], sizeof(FaceHeader));
        idx += sizeof(FaceHeader);

        for (int j = 0; j < face->header.glyph_count; j++) {
          GlyphInfo * glyph_info = new GlyphInfo;
          memcpy(glyph_info, &memory[idx], sizeof(GlyphInfo));
          idx += sizeof(GlyphInfo);

          int bitmap_size = glyph_info->bitmap_height * glyph_info->bitmap_width;
          uint8_t * bitmap = new uint8_t[bitmap_size];
          memset(bitmap, 0, bitmap_size);
          retrieve_bitmap(idx, glyph_info, bitmap, Dim(glyph_info->bitmap_width, glyph_info->bitmap_height), Pos(0,0));
          idx += glyph_info->packet_length;

          face->glyphs.push_back(glyph_info);
          face->bitmaps.push_back(bitmap);
        }

        if (face->header.lig_kern_pgm_count > 0) {
          face->lig_kern_steps.reserve(face->header.lig_kern_pgm_count);
          for (int j = 0; j < face->header.lig_kern_pgm_count; j++) {
            LigKernStep * step = new LigKernStep;
            memcpy(step, &memory[idx], sizeof(LigKernStep));
            idx += sizeof(LigKernStep);
            face->lig_kern_steps.push_back(step);
          }
        }

        if (face->header.kern_count > 0) {
          face->kerns.reserve(face->header.kern_count);
          for (int j = 0; j < face->header.kern_count; j++) {
            FIX16 val;
            memcpy(&val, &memory[idx], sizeof(FIX16));
            idx += sizeof(FIX16);
            face->kerns.push_back(val);
          }
        }

        for (int ch = 0; ch < face->header.glyph_count; ch++) {
          GlyphLigKern * glk = new GlyphLigKern;

// TBD: Lig/Kern formatting issue
//          if (face->glyphs[ch]->lig_kern_pgm_index != 65535) {
//            int lk_idx = face->glyphs[ch]->lig_kern_pgm_index;
//            if (lk_idx < face->header.lig_kern_pgm_count) {
//              do {
//                if (lk_idx >= face->header.lig_kern_pgm_count) break;
//                if (face->lig_kern_steps[lk_idx]->tag == 1) { // 1 = kern, 0 = ligature
//                  GlyphKernStep step;
//                  step.next_char_code = face->lig_kern_steps[lk_idx]->next_char_code;
//                  step.kern = face->kerns[face->lig_kern_steps[lk_idx]->u.kern_idx];
//                  glk->kern_steps.push_back(step);
//                }
//                else {
//                  GlyphLigStep step;
//                  step.next_char_code = face->lig_kern_steps[lk_idx]->next_char_code;
//                  step.char_code = face->lig_kern_steps[lk_idx]->u.char_code;
//                  glk->lig_steps.push_back(step);
//                }
//              } while (face->lig_kern_steps[lk_idx++]->stop == 0);
//            }
//          }
          face->glyphs_lig_kern.push_back(glk);
        }

        faces.push_back(face);
      }

      return true;
    }

  public:

    IBMFFont(uint8_t * memory_font, uint32_t size)
        : memory(memory_font), 
          memory_length(size) {
            
      memory_end = memory + memory_length;
      initialized = load();
    }

   ~IBMFFont() {
      for (auto face : faces) {
        for (auto glyph : face->glyphs) {
          delete glyph;
        }
        for (auto bitmap : face->bitmaps) {
          delete bitmap;
        }
        for (auto lig_kern : face->lig_kern_steps) {
          delete lig_kern;
        }
        face->glyphs.clear();
        face->bitmaps.clear();
        face->lig_kern_steps.clear();
        face->kerns.clear();
      }
      faces.clear();
      face_offsets.clear();
    }

    inline Preamble      * get_preample()             { return preamble;                   }
    inline FaceHeader * get_face_header(int face_idx) { return &faces[face_idx]->header;   }
    inline bool          is_initialized()             { return initialized;                }

    bool get_glyph_lig_kern(int face_index, int glyph_code, GlyphLigKern ** glyph_lig_kern)
    {
      if (face_index >= preamble->face_count) return false;
      if (glyph_code >= faces[face_index]->header.glyph_count) return false;

      *glyph_lig_kern = faces[face_index]->glyphs_lig_kern[glyph_code];

      return true;
    }

    bool
    get_glyph(int face_index, int glyph_code, GlyphInfo ** glyph_info, uint8_t ** bitmap)
    {
      if (face_index >= preamble->face_count) return false;
      if (glyph_code >= faces[face_index]->header.glyph_count) return false;

      *glyph_info = faces[face_index]->glyphs[glyph_code];
      *bitmap = faces[face_index]->bitmaps[glyph_code];
      
      return true;
    }

    bool
    save_face_header(int face_index, FaceHeader * face_header)
    {
      if (face_index < preamble->face_count) {
        faces[face_index]->header = *face_header;
        return true;
      }
      return false;
    }

    bool
    save_glyph(int face_index, int glyph_code, GlyphInfo * new_glyph_info, uint8_t * new_bitmap)
    {
      if ((face_index < preamble->face_count) && (glyph_code < faces[face_index]->header.glyph_count)) {
        *faces[face_index]->glyphs[glyph_code] = *new_glyph_info;
        delete [] faces[face_index]->bitmaps[glyph_code];
        faces[face_index]->bitmaps[glyph_code] = new_bitmap;
        return true;
      }
      return false;
    }
};
