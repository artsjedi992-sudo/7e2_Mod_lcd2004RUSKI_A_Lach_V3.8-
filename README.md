digital_feed_7e2 электронная гитара

LCD2004 Russian text:
- The project now uses RusLCD2004.h, adapted from the working TestLCD/RusLCD.ino.
- Russian UTF-8 text is rendered using custom 5x8 glyphs stored in the LCD controller CGRAM.
- Latin-lookalike Cyrillic letters are printed as Latin characters, as in the reference test.
- Original project control characters 1..6 are mapped to ASCII symbols so they do not consume CGRAM slots.
- HD44780 has only 8 custom glyph slots. If a screen needs more than 8 different non-lookalike Russian letters at once, extra letters are shown as '?' (same limitation documented by the reference test).
- The controller and motion logic were not intentionally changed. The display renderer buffers the complete 20x4 screen and renders it on lcd.flush().
- Compilation and physical LCD2004 testing are still required.
