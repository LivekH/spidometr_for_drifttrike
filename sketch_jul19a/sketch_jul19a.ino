// Spidometr — статический GUI из GUI Draw Master (handoff gui-from-draw-master)
// Arduino_GFX, явные пины Nano (не create_default — глобальная GFX может быть под Mega)

#include <Arduino_GFX_Library.h>

#define TFT_DC 8
#define TFT_CS 9
#define TFT_RST 7

Arduino_DataBus *bus = new Arduino_HWSPI(TFT_DC, TFT_CS);
Arduino_GFX *gfx = new Arduino_ILI9341(bus, TFT_RST, 1 /* 320x240 */, false);

// Экспорт GUI Draw Master — Arduino_GFX, 320x240, альбом
void drawGui() {
  gfx->setRotation(1);
  gfx->fillScreen(0x0000);

  // внутренний круг спидометра
  gfx->drawArc(106, 120, 100, 90, 0, 360, 0x001F);

  // внешняя окантовка
  gfx->drawCircle(106, 120, 104, 0x4D5E);

  // Шкала спидометра 0…40
  gfx->drawArc(106, 120, 76, 74, 150, 30, 0xCE9B);
  gfx->drawLine(40, 158, 50, 153, 0xEF7E);
  gfx->drawLine(37, 152, 43, 150, 0x6BB1);
  gfx->drawLine(35, 146, 40, 144, 0x6BB1);
  gfx->drawLine(33, 140, 38, 138, 0x6BB1);
  gfx->drawLine(31, 133, 37, 132, 0x6BB1);
  gfx->drawLine(30, 127, 36, 126, 0x6BB1);
  gfx->drawLine(30, 120, 41, 120, 0xEF7E);
  gfx->drawLine(30, 113, 36, 114, 0x6BB1);
  gfx->drawLine(31, 107, 37, 108, 0x6BB1);
  gfx->drawLine(33, 100, 38, 102, 0x6BB1);
  gfx->drawLine(35, 94, 40, 96, 0x6BB1);
  gfx->drawLine(37, 88, 43, 90, 0x6BB1);
  gfx->drawLine(40, 82, 50, 88, 0xEF7E);
  gfx->drawLine(44, 76, 49, 80, 0x6BB1);
  gfx->drawLine(48, 71, 52, 75, 0x6BB1);
  gfx->drawLine(52, 66, 57, 71, 0x6BB1);
  gfx->drawLine(57, 62, 61, 66, 0x6BB1);
  gfx->drawLine(62, 58, 66, 63, 0x6BB1);
  gfx->drawLine(68, 54, 74, 64, 0xEF7E);
  gfx->drawLine(74, 51, 76, 57, 0x6BB1);
  gfx->drawLine(80, 49, 82, 54, 0x6BB1);
  gfx->drawLine(86, 47, 88, 52, 0x6BB1);
  gfx->drawLine(93, 45, 94, 51, 0x6BB1);
  gfx->drawLine(99, 44, 100, 50, 0x6BB1);
  gfx->drawLine(106, 44, 106, 55, 0xEF7E);
  gfx->drawLine(113, 44, 112, 50, 0x6BB1);
  gfx->drawLine(119, 45, 118, 51, 0x6BB1);
  gfx->drawLine(126, 47, 124, 52, 0x6BB1);
  gfx->drawLine(132, 49, 130, 54, 0x6BB1);
  gfx->drawLine(138, 51, 136, 57, 0x6BB1);
  gfx->drawLine(144, 54, 139, 64, 0xEF7E);
  gfx->drawLine(150, 58, 146, 63, 0x6BB1);
  gfx->drawLine(155, 62, 151, 66, 0x6BB1);
  gfx->drawLine(160, 66, 155, 71, 0x6BB1);
  gfx->drawLine(164, 71, 160, 75, 0x6BB1);
  gfx->drawLine(168, 76, 163, 80, 0x6BB1);
  gfx->drawLine(172, 82, 162, 88, 0xEF7E);
  gfx->drawLine(175, 88, 169, 90, 0x6BB1);
  gfx->drawLine(177, 94, 172, 96, 0x6BB1);
  gfx->drawLine(179, 100, 174, 102, 0x6BB1);
  gfx->drawLine(181, 107, 175, 108, 0x6BB1);
  gfx->drawLine(182, 113, 176, 114, 0x6BB1);
  gfx->drawLine(182, 120, 171, 120, 0xEF7E);
  gfx->drawLine(182, 127, 176, 126, 0x6BB1);
  gfx->drawLine(181, 133, 175, 132, 0x6BB1);
  gfx->drawLine(179, 140, 174, 138, 0x6BB1);
  gfx->drawLine(177, 146, 172, 144, 0x6BB1);
  gfx->drawLine(175, 152, 169, 150, 0x6BB1);
  gfx->drawLine(172, 158, 162, 153, 0xEF7E);
  gfx->setTextColor(0xEF7E);
  gfx->setTextSize(2);
  gfx->setCursor(25, 156);
  gfx->print(F("0"));
  gfx->setTextColor(0xEF7E);
  gfx->setTextSize(2);
  gfx->setCursor(13, 112);
  gfx->print(F("5"));
  gfx->setTextColor(0xEF7E);
  gfx->setTextSize(2);
  gfx->setCursor(19, 69);
  gfx->print(F("10"));
  gfx->setTextColor(0xEF7E);
  gfx->setTextSize(2);
  gfx->setCursor(51, 37);
  gfx->print(F("15"));
  gfx->setTextColor(0xEF7E);
  gfx->setTextSize(2);
  gfx->setCursor(94, 25);
  gfx->print(F("20"));
  gfx->setTextColor(0xEF7E);
  gfx->setTextSize(2);
  gfx->setCursor(138, 37);
  gfx->print(F("25"));
  gfx->setTextColor(0xEF7E);
  gfx->setTextSize(2);
  gfx->setCursor(169, 69);
  gfx->print(F("30"));
  gfx->setTextColor(0xEF7E);
  gfx->setTextSize(2);
  gfx->setCursor(181, 112);
  gfx->print(F("35"));
  gfx->setTextColor(0xEF7E);
  gfx->setTextSize(2);
  gfx->setCursor(169, 156);
  gfx->print(F("40"));

  // синяя окантовка второго прибора
  gfx->drawArc(239, 120, 74, 59, 232, 128, 0x001F);

  // белая окантовка второго прибора
  gfx->drawArc(239, 120, 80, 79, 232, 128, 0xFFFF);

  // красный / жёлтый / зелёный сектор вольтметра
  gfx->drawArc(239, 120, 63, 57, 235, 270, 0xF800);
  gfx->drawArc(239, 120, 63, 57, 270, 305, 0xFFE0);
  gfx->drawArc(239, 120, 63, 57, 305, 340, 0x07E0);

  // Шкала вольтметра
  gfx->drawArc(239, 120, 59, 57, 239, 337, 0xCE9B);
  gfx->drawLine(209, 69, 211, 74, 0xEF7E);
  gfx->drawLine(227, 62, 228, 67, 0xEF7E);
  gfx->drawLine(247, 62, 247, 67, 0xEF7E);
  gfx->drawLine(267, 68, 264, 72, 0xEF7E);
  gfx->drawLine(282, 80, 279, 83, 0xEF7E);
  gfx->drawLine(293, 97, 289, 99, 0xEF7E);
  gfx->setTextColor(0xFFFF);
  gfx->setTextSize(1);
  gfx->setCursor(196, 55);
  gfx->print(F("20"));
  gfx->setTextColor(0xFFFF);
  gfx->setTextSize(1);
  gfx->setCursor(219, 46);
  gfx->print(F("22"));
  gfx->setTextColor(0xFFFF);
  gfx->setTextSize(1);
  gfx->setCursor(243, 46);
  gfx->print(F("24"));
  gfx->setTextColor(0xFFFF);
  gfx->setTextSize(1);
  gfx->setCursor(266, 53);
  gfx->print(F("26"));
  gfx->setTextColor(0xFFFF);
  gfx->setTextSize(1);
  gfx->setCursor(285, 68);
  gfx->print(F("28"));
  gfx->setTextColor(0xFFFF);
  gfx->setTextSize(1);
  gfx->setCursor(298, 88);
  gfx->print(F("30"));

  // газ: зелёный / жёлтый / красный (0% слева → 100% справа)
  gfx->drawArc(239, 120, 63, 57, 90, 125, 0x07E0);
  gfx->drawArc(239, 120, 63, 57, 55, 90, 0xFFE0);
  gfx->drawArc(239, 120, 63, 57, 20, 55, 0xF800);

  // Шкала положения ручки газа
  gfx->drawArc(239, 120, 59, 57, 23, 121, 0xCE9B);
  gfx->drawLine(293, 143, 289, 141, 0xEF7E);
  gfx->drawLine(279, 163, 275, 160, 0xEF7E);
  gfx->drawLine(257, 176, 256, 171, 0xEF7E);
  gfx->drawLine(232, 179, 233, 174, 0xEF7E);
  gfx->drawLine(209, 171, 211, 166, 0xEF7E);
  gfx->setTextColor(0xEF7E);
  gfx->setTextSize(1);
  gfx->setCursor(295, 144);
  gfx->print(F("100"));
  gfx->setTextColor(0xEF7E);
  gfx->setTextSize(1);
  gfx->setCursor(281, 168);
  gfx->print(F("75"));
  gfx->setTextColor(0xEF7E);
  gfx->setTextSize(1);
  gfx->setCursor(255, 184);
  gfx->print(F("50"));
  gfx->setTextColor(0xEF7E);
  gfx->setTextSize(1);
  gfx->setCursor(225, 187);
  gfx->print(F("25"));
  gfx->setTextColor(0xEF7E);
  gfx->setTextSize(1);
  gfx->setCursor(199, 177);
  gfx->print(F("0"));

  // рамка окна под стрелкой спидометра (контент — позже)
  gfx->drawLine(53, 159, 159, 159, 0xFFFF);
  gfx->drawArc(106, 120, 91, 90, 53, 125, 0xFFFF);
  gfx->drawLine(53, 159, 53, 194, 0xEF7E);
  gfx->drawLine(160, 159, 160, 193, 0xEF7E);
}

void setup() {
  gfx->begin();
  drawGui();
}

void loop() {
  // статика; стрелки / датчики — следующие handoff
}
