// Spidometr — условный статический GUI 320x240 (handoff gui-static-mock)
// Макет: New scale.svg; явные пины Nano (create_default не использовать — GFX пропатчен под Mega)

#include <Arduino_GFX_Library.h>

// Пины TFT (провизорно; как сток Nano в эталоне Arduino_GFX)
#define TFT_DC 8
#define TFT_CS 9
#define TFT_RST 7

Arduino_DataBus *bus = new Arduino_HWSPI(TFT_DC, TFT_CS);
Arduino_GFX *tft = new Arduino_ILI9341(bus, TFT_RST, 1 /* rotation → 320x240 */, false);

// Цвета (RGB565)
#define COL_BG 0x0000
#define COL_GRAY 0x8410
#define COL_WHITE 0xFFFF
#define COL_YELLOW 0xFFE0
#define COL_GREEN 0x07E0
#define COL_RED 0xF800
#define COL_BLACK 0x0000

// Центры шкал после масштаба SVG 397x280 → 320x240
#define SPD_CX 160
#define SPD_CY 207
#define GAS_CX 53
#define GAS_CY 120
#define BAT_CX 267
#define BAT_CY 120

// Перевод угла GFX (0°=восток, CCW) → точка на экране (Y вниз)
static void polarToXY(int16_t cx, int16_t cy, float deg, int16_t r, int16_t *ox, int16_t *oy) {
  float rad = deg * 0.01745329252f;
  *ox = cx + (int16_t)(r * cosf(rad));
  *oy = cy - (int16_t)(r * sinf(rad));
}

// Подпись у дуги (центр текста грубо)
static void drawArcLabel(int16_t cx, int16_t cy, float deg, int16_t r, const char *s) {
  int16_t x, y;
  polarToXY(cx, cy, deg, r, &x, &y);
  tft->setTextColor(COL_BLACK);
  tft->setTextSize(1);
  tft->setCursor(x - 6, y - 4);
  tft->print(s);
}

// Стрелка от центра к углу на радиусе
static void drawNeedle(int16_t cx, int16_t cy, float deg, int16_t rInner, int16_t rOuter, uint16_t color) {
  int16_t x1, y1, x2, y2;
  polarToXY(cx, cy, deg, rInner, &x1, &y1);
  polarToXY(cx, cy, deg, rOuter, &x2, &y2);
  tft->drawLine(x1, y1, x2, y2, color);
}

// Большой спидометр 0…40 (дуга сверху: 180°→0° через 90°)
static void drawSpeedGauge() {
  // серое кольцо
  tft->fillArc(SPD_CX, SPD_CY, 116, 100, 0, 180, COL_GRAY);
  // белая шкала
  tft->fillArc(SPD_CX, SPD_CY, 100, 78, 0, 180, COL_WHITE);

  // метки 0…40 шаг 5 → угол 180…0
  static const char *labs[] = {"0", "5", "10", "15", "20", "25", "30", "35", "40"};
  for (uint8_t i = 0; i < 9; i++) {
    float deg = 180.0f - i * 22.5f;
    drawArcLabel(SPD_CX, SPD_CY, deg, 88, labs[i]);
  }

  drawNeedle(SPD_CX, SPD_CY, 180.0f, 20, 72, COL_YELLOW); // условно на 0

  tft->setTextColor(COL_WHITE);
  tft->setTextSize(2);
  tft->setCursor(SPD_CX - 28, SPD_CY - 36);
  tft->print(F("0"));
  tft->setTextSize(1);
  tft->setCursor(SPD_CX - 20, SPD_CY - 18);
  tft->print(F("km/h"));
}

// Малая шкала: белая дуга + 3 зоны; start/end в градусах GFX
static void drawSideGauge(int16_t cx, int16_t cy, bool gasNotBat) {
  // дуги малых шкал ~150° (углы Arduino_GFX: 0°=восток, CCW)
  float start = gasNotBat ? 125.0f : 305.0f;
  float end = gasNotBat ? 275.0f : 95.0f;

  tft->fillArc(cx, cy, 48, 36, start, end, COL_WHITE);

  // цветные зоны ~по трети дуги (газ: зел→жёлт→красн; заряд: красн→жёлт→зел у «полного»)
  float span = gasNotBat ? (end - start) : (end > start ? end - start : end + 360.0f - start);
  float t1 = start + span * 0.33f;
  float t2 = start + span * 0.66f;
  if (gasNotBat) {
    tft->fillArc(cx, cy, 36, 28, start, t1, COL_GREEN);
    tft->fillArc(cx, cy, 36, 28, t1, t2, COL_YELLOW);
    tft->fillArc(cx, cy, 36, 28, t2, end, COL_RED);
  } else {
    // заряд: у «100» зелёный — ближе к верхней части дуги
    tft->fillArc(cx, cy, 36, 28, start, t1, COL_RED);
    tft->fillArc(cx, cy, 36, 28, t1, t2, COL_YELLOW);
    tft->fillArc(cx, cy, 36, 28, t2, end, COL_GREEN);
  }

  // метки
  if (gasNotBat) {
    drawArcLabel(cx, cy, 140, 42, "0");
    drawArcLabel(cx, cy, 170, 42, "25");
    drawArcLabel(cx, cy, 200, 42, "50");
    drawArcLabel(cx, cy, 230, 42, "75");
    drawArcLabel(cx, cy, 255, 42, "100");
    drawNeedle(cx, cy, 155.0f, 8, 30, COL_YELLOW);
    tft->setTextColor(COL_WHITE);
    tft->setTextSize(1);
    tft->setCursor(cx - 18, cy + 8);
    tft->print(F("TORQUE"));
  } else {
    drawArcLabel(cx, cy, 40, 42, "100");
    drawArcLabel(cx, cy, 10, 42, "75");
    drawArcLabel(cx, cy, 340, 42, "50");
    drawArcLabel(cx, cy, 310, 42, "25");
    drawArcLabel(cx, cy, 280, 42, "0");
    drawNeedle(cx, cy, 300.0f, 8, 30, COL_YELLOW);
    tft->setTextColor(COL_WHITE);
    tft->setTextSize(1);
    tft->setCursor(cx - 10, cy + 8);
    tft->print(F("V"));
  }
}

static void drawStaticGui() {
  tft->fillScreen(COL_BG);
  drawSpeedGauge();
  drawSideGauge(GAS_CX, GAS_CY, true);
  drawSideGauge(BAT_CX, BAT_CY, false);
}

void setup() {
  tft->begin();
  tft->fillScreen(COL_BG);
  drawStaticGui();
}

void loop() {
  // статика; датчики/стрелки — следующие handoff
}
