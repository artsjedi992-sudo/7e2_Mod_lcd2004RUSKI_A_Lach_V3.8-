#ifndef RUS_LCD_2004_H
#define RUS_LCD_2004_H

#include <Arduino.h>
#include <LiquidCrystal.h>
#include <avr/pgmspace.h>
#include <Print.h>

// Russian UTF-8 renderer based on the proven TestLCD/RusLCD.ino.
// HD44780 has only 8 CGRAM slots. Latin lookalikes use ASCII;
// other Cyrillic letters use up to 8 custom glyphs per screen.
// Control codes 1..6 from the original project are mapped to ASCII
// so they do not consume CGRAM slots.

#define GLYPH_COUNT 48

const unsigned int GLYPH_CP[GLYPH_COUNT] PROGMEM = {
  0x0401,0x0411,0x0413,0x0414,0x0416,0x0417,0x0418,0x0419,0x041B,0x041F,0x0423,0x0424,0x0426,0x0427,0x0428,0x0429,0x042A,0x042B,0x042C,0x042D,0x042E,0x042F,0x0431,0x0432,0x0433,0x0434,0x0436,0x0437,0x0438,0x0439,0x043A,0x043B,0x043C,0x043D,0x043F,0x0442,0x0444,0x0446,0x0447,0x0448,0x0449,0x044A,0x044B,0x044C,0x044D,0x044E,0x044F,0x0451
};

const byte GLYPH_BMP[GLYPH_COUNT][8] PROGMEM = {
  {0b01010,0b11111,0b10000,0b11110,0b10000,0b10000,0b11111,0b00000}, // Ё
  {0b11111,0b10000,0b10000,0b11110,0b10001,0b10001,0b11110,0b00000}, // Б
  {0b11111,0b10000,0b10000,0b10000,0b10000,0b10000,0b10000,0b00000}, // Г
  {0b00111,0b01001,0b01001,0b01001,0b01001,0b11111,0b10001,0b00000}, // Д
  {0b10101,0b10101,0b10101,0b01110,0b10101,0b10101,0b10101,0b00000}, // Ж
  {0b01110,0b10001,0b00001,0b00110,0b00001,0b10001,0b01110,0b00000}, // З
  {0b10001,0b10001,0b10011,0b10101,0b11001,0b10001,0b10001,0b00000}, // И
  {0b01010,0b10001,0b10001,0b10011,0b10101,0b11001,0b10001,0b00000}, // Й
  {0b00111,0b01001,0b01001,0b01001,0b01001,0b01001,0b10001,0b00000}, // Л
  {0b11111,0b10001,0b10001,0b10001,0b10001,0b10001,0b10001,0b00000}, // П
  {0b10001,0b10001,0b10001,0b01111,0b00001,0b10001,0b01110,0b00000}, // У
  {0b00100,0b01110,0b10101,0b10101,0b10101,0b01110,0b00100,0b00000}, // Ф
  {0b10010,0b10010,0b10010,0b10010,0b10010,0b11111,0b00001,0b00000}, // Ц
  {0b10001,0b10001,0b10001,0b01111,0b00001,0b00001,0b00001,0b00000}, // Ч
  {0b10101,0b10101,0b10101,0b10101,0b10101,0b10101,0b11111,0b00000}, // Ш
  {0b10101,0b10101,0b10101,0b10101,0b10101,0b11111,0b00001,0b00000}, // Щ
  {0b11000,0b01000,0b01000,0b01110,0b01001,0b01001,0b01110,0b00000}, // Ъ
  {0b10001,0b10001,0b10001,0b11001,0b10101,0b10101,0b11001,0b00000}, // Ы
  {0b10000,0b10000,0b10000,0b11110,0b10001,0b10001,0b11110,0b00000}, // Ь
  {0b01110,0b10001,0b00001,0b00111,0b00001,0b10001,0b01110,0b00000}, // Э
  {0b10010,0b10101,0b10101,0b11101,0b10101,0b10101,0b10010,0b00000}, // Ю
  {0b01111,0b10001,0b10001,0b01111,0b00101,0b01001,0b10001,0b00000}, // Я
  {0b00110,0b01000,0b10000,0b11110,0b10001,0b10001,0b01110,0b00000}, // б
  {0b00000,0b00000,0b11100,0b10010,0b11100,0b10010,0b11100,0b00000}, // в
  {0b00000,0b00000,0b11110,0b10000,0b10000,0b10000,0b10000,0b00000}, // г
  {0b00000,0b00000,0b00111,0b01001,0b01001,0b11111,0b10001,0b00000}, // д
  {0b00000,0b00000,0b10101,0b10101,0b01110,0b10101,0b10101,0b00000}, // ж
  {0b00000,0b00000,0b01110,0b00001,0b00110,0b00001,0b01110,0b00000}, // з
  {0b00000,0b00000,0b10001,0b10011,0b10101,0b11001,0b10001,0b00000}, // и
  {0b01010,0b00100,0b10001,0b10011,0b10101,0b11001,0b10001,0b00000}, // й
  {0b00000,0b00000,0b10010,0b10100,0b11000,0b10100,0b10010,0b00000}, // к
  {0b00000,0b00000,0b00111,0b01001,0b01001,0b01001,0b10001,0b00000}, // л
  {0b00000,0b00000,0b10001,0b11011,0b10101,0b10001,0b10001,0b00000}, // м
  {0b00000,0b00000,0b10001,0b10001,0b11111,0b10001,0b10001,0b00000}, // н
  {0b00000,0b00000,0b11111,0b10001,0b10001,0b10001,0b10001,0b00000}, // п
  {0b00000,0b00000,0b11111,0b00100,0b00100,0b00100,0b00100,0b00000}, // т
  {0b00100,0b00100,0b01110,0b10101,0b10101,0b01110,0b00100,0b00100}, // ф
  {0b00000,0b00000,0b10010,0b10010,0b10010,0b11111,0b00001,0b00000}, // ц
  {0b00000,0b00000,0b10001,0b10001,0b01111,0b00001,0b00001,0b00000}, // ч
  {0b00000,0b00000,0b10101,0b10101,0b10101,0b10101,0b11111,0b00000}, // ш
  {0b00000,0b00000,0b10101,0b10101,0b10101,0b11111,0b00001,0b00000}, // щ
  {0b00000,0b00000,0b11000,0b01000,0b01110,0b01001,0b01110,0b00000}, // ъ
  {0b00000,0b00000,0b10001,0b10001,0b11001,0b10101,0b11001,0b00000}, // ы
  {0b00000,0b00000,0b10000,0b10000,0b11110,0b10001,0b11110,0b00000}, // ь
  {0b00000,0b00000,0b01110,0b00001,0b00111,0b00001,0b01110,0b00000}, // э
  {0b00000,0b00000,0b10010,0b10101,0b11101,0b10101,0b10010,0b00000}, // ю
  {0b00000,0b00000,0b01111,0b10001,0b01111,0b00101,0b01001,0b00000}, // я
  {0b01010,0b00000,0b01110,0b10001,0b11111,0b10000,0b01110,0b00000}, // ё
};

class RusLCD2004 : public Print {
public:
  RusLCD2004(uint8_t rs, uint8_t enable, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7)
    : hw(rs, enable, d4, d5, d6, d7), cols(20), rows(4), cursorX(0), cursorY(0),
      utfValue(0), utfRemaining(0) {
    clearBuffer();
  }

  void begin(uint8_t columns, uint8_t lines) {
    cols = (columns > 20) ? 20 : columns;
    rows = (lines > 4) ? 4 : lines;
    hw.begin(columns, lines);
    clear();
  }

  void clear() {
    clearBuffer();
    cursorX = 0;
    cursorY = 0;
    utfValue = 0;
    utfRemaining = 0;
    hw.clear();
  }

  void setCursor(uint8_t column, uint8_t row) {
    cursorX = (column < cols) ? column : (cols ? cols - 1 : 0);
    cursorY = (row < rows) ? row : (rows ? rows - 1 : 0);
  }

  void flush() {
    if (utfRemaining) {
      putCodepoint('?');
      utfRemaining = 0;
      utfValue = 0;
    }
    render();
  }

  virtual size_t write(uint8_t value) {
    if (utfRemaining) {
      if ((value & 0xC0) == 0x80) {
        utfValue = (utfValue << 6) | (value & 0x3F);
        if (--utfRemaining == 0) putCodepoint(utfValue);
        return 1;
      }
      putCodepoint('?');
      utfRemaining = 0;
      utfValue = 0;
    }

    if (value < 0x80) {
      putCodepoint(value);
    } else if ((value & 0xE0) == 0xC0) {
      utfValue = value & 0x1F;
      utfRemaining = 1;
    } else if ((value & 0xF0) == 0xE0) {
      utfValue = value & 0x0F;
      utfRemaining = 2;
    } else {
      putCodepoint('?');
    }
    return 1;
  }

private:
  LiquidCrystal hw;
  uint8_t cols, rows, cursorX, cursorY;
  uint16_t cells[4][20];
  uint16_t utfValue;
  uint8_t utfRemaining;

  void clearBuffer() {
    for (uint8_t r = 0; r < 4; r++)
      for (uint8_t c = 0; c < 20; c++)
        cells[r][c] = ' ';
  }

  void putCodepoint(uint16_t cp) {
    // Preserve the original project's special-character control codes
    // without occupying one of the eight user glyph slots.
    switch (cp) {
      case 1: cp = '<'; break;  // left
      case 2: cp = '>'; break;  // right
      case 3: cp = '^'; break;  // up
      case 4: cp = 'v'; break;  // down
      case 5: cp = 'o'; break;  // degree
      case 6: cp = 'D'; break;  // diameter
    }
    if (cursorY < rows && cursorX < cols) {
      cells[cursorY][cursorX] = cp;
      if (cursorX + 1 < cols) cursorX++;
      else cursorX = cols;
    }
  }

  char lookalike(uint16_t cp) {
    switch (cp) {
      case 0x0410: return 'A'; case 0x0412: return 'B'; case 0x0415: return 'E';
      case 0x041A: return 'K'; case 0x041C: return 'M'; case 0x041D: return 'H';
      case 0x041E: return 'O'; case 0x0420: return 'P'; case 0x0421: return 'C';
      case 0x0422: return 'T'; case 0x0425: return 'X';
      case 0x0430: return 'a'; case 0x0435: return 'e';
      case 0x043E: return 'o'; case 0x0440: return 'p'; case 0x0441: return 'c';
      case 0x0443: return 'y'; case 0x0445: return 'x';
    }
    return 0;
  }

  int findGlyph(uint16_t cp) {
    for (uint8_t i = 0; i < GLYPH_COUNT; i++)
      if (pgm_read_word(&GLYPH_CP[i]) == cp) return i;
    return -1;
  }

  void render() {
    uint16_t slotCode[8];
    uint8_t slotGlyph[8];
    uint8_t used = 0;
    uint8_t output[4][20];

    // Determine which Russian glyphs are needed on the complete 20x4 screen.
    for (uint8_t r = 0; r < rows; r++) {
      for (uint8_t c = 0; c < cols; c++) {
        uint16_t cp = cells[r][c];
        if (cp < 0x80) {
          output[r][c] = (uint8_t)cp;
          continue;
        }
        char latin = lookalike(cp);
        if (latin) {
          output[r][c] = (uint8_t)latin;
          continue;
        }
        int gi = findGlyph(cp);
        if (gi < 0) {
          output[r][c] = '?';
          continue;
        }
        int slot = -1;
        for (uint8_t i = 0; i < used; i++)
          if (slotCode[i] == cp) { slot = i; break; }
        if (slot < 0 && used < 8) {
          slot = used;
          slotCode[used] = cp;
          slotGlyph[used] = (uint8_t)gi;
          used++;
        }
        output[r][c] = (slot < 0) ? '?' : (uint8_t)slot;
      }
    }

    // Load all selected 5x8 glyphs into CGRAM before drawing the screen.
    for (uint8_t i = 0; i < used; i++) {
      byte bitmap[8];
      for (uint8_t j = 0; j < 8; j++)
        bitmap[j] = pgm_read_byte(&GLYPH_BMP[slotGlyph[i]][j]);
      hw.createChar(i, bitmap);
    }

    for (uint8_t r = 0; r < rows; r++) {
      hw.setCursor(0, r);
      for (uint8_t c = 0; c < cols; c++)
        hw.write(output[r][c]);
    }
  }
};

#endif
