#pragma once
#include "config.h"
#include "touch_input.h"
#include "signal_engine.h"

// ================= Buttons =================
static RectButton btnMainSignal = { 120,  55, 240, 45, "SIGNALGENERATOR" };
static RectButton btnMainAmp    = { 120, 125, 240, 45, "AMPLITUDENGANG"  };
static RectButton btnMainHelp   = { 120, 195, 240, 45, "HILFE"           };

static RectButton btnBack       = {  20, 270, 120, 35, "ZURUECK" };
static RectButton btnAmpMinus   = {  20,  90, 100, 40, "AMP -"   };
static RectButton btnAmpPlus    = { 130,  90, 100, 40, "AMP +"   };
static RectButton btnFreqMinus  = {  20, 140, 100, 40, "FREQ -"  };
static RectButton btnFreqPlus   = { 130, 140, 100, 40, "FREQ +"  };

static RectButton btnWobAmpMinus   = {  20,  70, 100, 26, "A -"  };
static RectButton btnWobAmpPlus    = { 130,  70, 100, 26, "A +"  };
static RectButton btnWobStartMinus = {  20, 105, 100, 26, "ST -" };
static RectButton btnWobStartPlus  = { 130, 105, 100, 26, "ST +" };
static RectButton btnWobStopMinus  = {  20, 140, 100, 26, "SP -" };
static RectButton btnWobStopPlus   = { 130, 140, 100, 26, "SP +" };
static RectButton btnWobTimeMinus  = {  20, 175, 100, 26, "TM -" };
static RectButton btnWobTimePlus   = { 130, 175, 100, 26, "TM +" };

static RectButton btnAmpStartField  = {  20,  55, 135, 28, "START"   };
static RectButton btnAmpStopField   = { 165,  55, 135, 28, "STOP"    };
static RectButton btnAmpStepField   = { 310,  55, 135, 28, "STEP"    };
static RectButton btnAmpDriveField  = {  20,  95, 135, 28, "AMP"     };
static RectButton btnAmpSettleField = { 165,  95, 135, 28, "SETTLE"  };
static RectButton btnAmpAvgField    = { 310,  95, 135, 28, "AVG"     };

static RectButton btnAmpRun         = { 160, 270, 120, 35, "MESSEN"  };
static RectButton btnAmpPlot        = { 340, 270, 120, 35, "PLOT"    };

static RectButton waveSlotButtons[6] = {
  {  30,  50, 190, 42, "" },
  { 260,  50, 190, 42, "" },
  {  30, 105, 190, 42, "" },
  { 260, 105, 190, 42, "" },
  {  30, 160, 190, 42, "" },
  { 260, 160, 190, 42, "" }
};

static ArrowButton btnLeftArrow  = { 360, 265, 40, 40, false };
static ArrowButton btnRightArrow = { 420, 265, 40, 40, true  };

static RectButton npBtn1  = { 100,  70, 55, 40, "1" };
static RectButton npBtn2  = { 170,  70, 55, 40, "2" };
static RectButton npBtn3  = { 240,  70, 55, 40, "3" };
static RectButton npBtn4  = { 100, 120, 55, 40, "4" };
static RectButton npBtn5  = { 170, 120, 55, 40, "5" };
static RectButton npBtn6  = { 240, 120, 55, 40, "6" };
static RectButton npBtn7  = { 100, 170, 55, 40, "7" };
static RectButton npBtn8  = { 170, 170, 55, 40, "8" };
static RectButton npBtn9  = { 240, 170, 55, 40, "9" };
static RectButton npBtn0  = { 170, 220, 55, 40, "0" };
static RectButton npBtnDot= { 100, 220, 55, 40, "." };
static RectButton npBtnBk = { 240, 220, 55, 40, "<" };
static RectButton npBtnOk = { 315, 120, 95, 40, "OK" };
static RectButton npBtnX  = { 315, 170, 95, 40, "ABBR" };

inline const char* freqUnitToString(WaveformType wf) {
  return waveformIsBpm[(int)wf] ? "BPM" : "Hz";
}

inline void drawCenteredText(const char* text, int y, int size, uint16_t color) {
  gfx->setTextSize(size);
  gfx->setTextColor(color);
  int textWidth = strlen(text) * 6 * size;
  int x = (480 - textWidth) / 2;
  gfx->setCursor(x, y);
  gfx->print(text);
}

inline void drawButtonFrame(const RectButton& b, bool highlighted) {
  if (highlighted) {
    gfx->fillRect(b.x, b.y, b.w, b.h, neonGreen);
    gfx->drawRect(b.x, b.y, b.w, b.h, black);
    gfx->setTextColor(black);
  } else {
    gfx->fillRect(b.x, b.y, b.w, b.h, black);
    gfx->drawRect(b.x, b.y, b.w, b.h, neonGreen);
    gfx->setTextColor(neonGreen);
  }

  int size = (b.h < 30) ? 1 : 2;
  gfx->setTextSize(size);
  int textWidth = strlen(b.label) * 6 * size;
  int tx = b.x + (b.w - textWidth) / 2;
  int ty = b.y + (b.h - 8 * size) / 2 + 1;
  gfx->setCursor(tx, ty);
  gfx->print(b.label);
  gfx->setTextColor(neonGreen);
}

inline void drawArrowButton(const ArrowButton& b, bool highlighted) {
  uint16_t fillColor = highlighted ? neonGreen : black;
  uint16_t lineColor = highlighted ? black : neonGreen;

  gfx->fillRect(b.x, b.y, b.w, b.h, black);
  gfx->drawRect(b.x, b.y, b.w, b.h, neonGreen);

  if (highlighted) {
    gfx->fillRect(b.x + 1, b.y + 1, b.w - 2, b.h - 2, neonGreen);
  }

  int cx = b.x + b.w / 2;
  int cy = b.y + b.h / 2;

  if (b.rightDirection) {
    gfx->fillTriangle(cx - 8, cy - 10, cx - 8, cy + 10, cx + 10, cy, fillColor);
    gfx->drawTriangle(cx - 8, cy - 10, cx - 8, cy + 10, cx + 10, cy, lineColor);
  } else {
    gfx->fillTriangle(cx + 8, cy - 10, cx + 8, cy + 10, cx - 10, cy, fillColor);
    gfx->drawTriangle(cx + 8, cy - 10, cx + 8, cy + 10, cx - 10, cy, lineColor);
  }
}

inline void animateButton(const RectButton& b) {
  
  drawButtonFrame(b, true);
  drawButtonFrame(b, false);
}

inline void animateArrow(const ArrowButton& b) {
  
  drawArrowButton(b, true);
  drawArrowButton(b, false);
}

inline void drawPreviewFrame() {
  gfx->drawRect(previewX, previewY, previewW, previewH, neonGreen);
  gfx->drawLine(previewX + 5, previewY + previewH / 2, previewX + previewW - 6, previewY + previewH / 2, neonGreen);

  gfx->setTextColor(neonGreen);
  gfx->setTextSize(1);
  gfx->setCursor(previewX + 4, previewY - 10);
  gfx->print("SIGNAL-VORSCHAU");
}

inline void drawSignalPreview(WaveformType wf) {
  gfx->fillRect(previewX + 1, previewY + 1, previewW - 2, previewH - 2, black);
  drawPreviewFrame();

  float tSpan = 1.0f;
  if (wf == WAVE_EKG) {
    tSpan = 60.0f / waveformFreq[WAVE_EKG];
  } else if (wf == WAVE_WOBBLE) {
    tSpan = wobbleSweepTimeSec;
  }

  int prevX = previewX + 4;
  int prevY = previewY + previewH / 2;

  for (int i = 0; i < previewW - 8; i++) {
    float t = ((float)i / (float)(previewW - 8 - 1)) * tSpan;
    float yVal = generateSignalForWaveform(wf, t);
    float centered = yVal - baseline;

    float scaleDenom = 1.0f;
    if (wf == WAVE_EKG) scaleDenom = 1400.0f;
    else if (wf == WAVE_EMG) scaleDenom = 1400.0f;
    else if (wf == WAVE_EEG) scaleDenom = 500.0f;
    else scaleDenom = 2200.0f;

    float norm = centered / scaleDenom;
    if (norm > 1.0f) norm = 1.0f;
    if (norm < -1.0f) norm = -1.0f;

    int sx = previewX + 4 + i;
    int sy = previewY + previewH / 2 - (int)(norm * (previewH / 2 - 8));

    if (i > 0) gfx->drawLine(prevX, prevY, sx, sy, neonGreen);

    prevX = sx;
    prevY = sy;
  }
}

inline void drawSplashScreen() {
  gfx->fillScreen(black);
  drawCenteredText("Biosignalgenerator", 120, 3, neonGreen);
  drawCenteredText("Praxisprojekt HTWK", 170, 2, neonGreen);

  uint32_t splashStart = millis();
  while ((uint32_t)(millis() - splashStart) < 5000UL) {
    handleSignalRebuild();
    updateSignalOutput();
  }
}

inline void drawMainMenu() {
  currentScreen = SCREEN_MAIN_MENU;
  gfx->fillScreen(black);
  drawCenteredText("HAUPTMENUE", 15, 2, neonGreen);
  drawButtonFrame(btnMainSignal, false);
  drawButtonFrame(btnMainAmp, false);
  drawButtonFrame(btnMainHelp, false);
}

inline void drawWaveMenuPage() {
  currentScreen = SCREEN_WAVE_MENU;
  gfx->fillScreen(black);
  drawCenteredText("KURVENFORM WAHL", 10, 2, neonGreen);

  int startIdx = waveformPage * waveformsPerPage;
  for (int i = 0; i < 6; i++) {
    RectButton b = waveSlotButtons[i];
    int wfIdx = startIdx + i;

    if (wfIdx < WAVE_COUNT) {
      b.label = waveformNames[wfIdx];
      drawButtonFrame(b, false);
    } else {
      gfx->fillRect(b.x, b.y, b.w, b.h, black);
      gfx->drawRect(b.x, b.y, b.w, b.h, neonGreen);
    }
  }

  drawButtonFrame(btnBack, false);
  drawArrowButton(btnLeftArrow, false);
  drawArrowButton(btnRightArrow, false);

  gfx->setTextColor(neonGreen);
  gfx->setTextSize(2);
  gfx->setCursor(150, 278);
  gfx->print("SEITE ");
  gfx->print(waveformPage + 1);
  gfx->print("/");
  gfx->print(waveformPageCount);
}

inline void drawParamValues() {
  gfx->fillRect(20, 45, 220, 60, black);

  gfx->setTextColor(neonGreen);
  gfx->setTextSize(2);

  if (selectedWaveform == WAVE_WOBBLE) {
    gfx->setCursor(20, 45);
    gfx->print("WOBBLE");
  } else {
    gfx->setCursor(20, 45);
    gfx->print("FREQ:");
    gfx->print(waveformFreq[(int)selectedWaveform], 1);
    gfx->print(" ");
    gfx->print(freqUnitToString(selectedWaveform));

    gfx->setCursor(20, 70);
    gfx->print("AMP :");
    gfx->print(waveformAmp[(int)selectedWaveform], 2);
  }
}

inline void drawWobbleValues() {
  gfx->fillRect(20, 45, 220, 145, black);
  gfx->setTextColor(neonGreen);
  gfx->setTextSize(1);

  gfx->setCursor(20, 45);  gfx->print("AMP:   "); gfx->print(wobbleAmplitude, 2);
  gfx->setCursor(20, 58);  gfx->print("START: "); gfx->print(wobbleStartHz, 1); gfx->print(" Hz");
  gfx->setCursor(20, 71);  gfx->print("STOP:  "); gfx->print(wobbleStopHz, 1);  gfx->print(" Hz");
  gfx->setCursor(20, 84);  gfx->print("TIME:  "); gfx->print(wobbleSweepTimeSec, 1); gfx->print(" s");
}

inline void drawParamMenu() {
  currentScreen = SCREEN_PARAM_MENU;
  gfx->fillScreen(black);

  gfx->setTextColor(neonGreen);
  gfx->setTextSize(2);
  gfx->setCursor(20, 10);
  gfx->print("PARAMETER: ");
  gfx->println(waveformNames[(int)selectedWaveform]);

  drawButtonFrame(btnBack, false);

  if (selectedWaveform == WAVE_WOBBLE) {
    drawButtonFrame(btnWobAmpMinus, false);
    drawButtonFrame(btnWobAmpPlus, false);
    drawButtonFrame(btnWobStartMinus, false);
    drawButtonFrame(btnWobStartPlus, false);
    drawButtonFrame(btnWobStopMinus, false);
    drawButtonFrame(btnWobStopPlus, false);
    drawButtonFrame(btnWobTimeMinus, false);
    drawButtonFrame(btnWobTimePlus, false);
    drawWobbleValues();
  } else {
    drawParamValues();
    drawButtonFrame(btnAmpMinus, false);
    drawButtonFrame(btnAmpPlus, false);
    drawButtonFrame(btnFreqMinus, false);
    drawButtonFrame(btnFreqPlus, false);
  }

  drawSignalPreview(selectedWaveform);
}

inline void drawAmpSweepValues() {
  gfx->fillRect(20, 135, 440, 45, black);

  gfx->setTextColor(neonGreen);
  gfx->setTextSize(1);

  gfx->setCursor(22, 138);  gfx->print("START: ");  gfx->print(ampSweepStartHz, 1);
  gfx->setCursor(110, 138); gfx->print("STOP: ");   gfx->print(ampSweepStopHz, 1);
  gfx->setCursor(198, 138); gfx->print("STEP: ");   gfx->print(ampSweepStepHz, 1);
  gfx->setCursor(286, 138); gfx->print("AMP: ");    gfx->print(ampSweepDriveAmp, 2);

  gfx->setCursor(22, 154);  gfx->print("SETTLE: "); gfx->print(ampSweepSettleMs, 0); gfx->print(" ms");
  gfx->setCursor(180, 154); gfx->print("AVG: ");    gfx->print(ampSweepAverages);
}

inline void drawAmpGraphFrame() {
  gfx->drawRect(20, 185, 440, 70, neonGreen);
  gfx->drawLine(32, 245, 448, 245, neonGreen);
  gfx->drawLine(32, 193, 32, 245, neonGreen);

  gfx->setTextColor(neonGreen);
  gfx->setTextSize(1);
  gfx->setCursor(24, 176);
  gfx->print("PLOT (dB, log f)");
}

inline void drawAmpGraph() {
  gfx->fillRect(21, 186, 438, 68, black);
  drawAmpGraphFrame();

  if (!ampDataValid || ampPointCount < 2) {
    gfx->setTextColor(neonGreen);
    gfx->setTextSize(1);
    gfx->setCursor(160, 215);
    gfx->print("NOCH KEINE MESSDATEN");
    return;
  }

  float minDb = ampDbPoints[0];
  float maxDb = ampDbPoints[0];

  for (int i = 1; i < ampPointCount; i++) {
    if (ampDbPoints[i] < minDb) minDb = ampDbPoints[i];
    if (ampDbPoints[i] > maxDb) maxDb = ampDbPoints[i];
  }

  if (fabs(maxDb - minDb) < 1.0f) {
    maxDb += 0.5f;
    minDb -= 0.5f;
  }

  float startHz = ampFreqPoints[0];
  float stopHz  = ampFreqPoints[ampPointCount - 1];
  if (startHz < 1.0f) startHz = 1.0f;
  if (stopHz <= startHz) stopHz = startHz + 1.0f;

  float logStart = log10f(startHz);
  float logStop  = log10f(stopHz);

  int prevX = 0;
  int prevY = 0;

  for (int i = 0; i < ampPointCount; i++) {
    float lx = log10f(ampFreqPoints[i]);
    int x = 32 + (int)(((lx - logStart) / (logStop - logStart)) * (448 - 32));
    int y = 243 - (int)(((ampDbPoints[i] - minDb) / (maxDb - minDb)) * 46.0f);

    if (i > 0) gfx->drawLine(prevX, prevY, x, y, neonGreen);

    gfx->fillCircle(x, y, 2, neonGreen);
    prevX = x;
    prevY = y;
  }

  gfx->setTextColor(neonGreen);
  gfx->setTextSize(1);
  gfx->setCursor(34, 247);  gfx->print(startHz, 0);
  gfx->setCursor(408, 247); gfx->print(stopHz, 0);
  gfx->setCursor(2, 194);   gfx->print(maxDb, 0);
  gfx->setCursor(2, 238);   gfx->print(minDb, 0);

  if (ampMarkerIndex >= 0 && ampMarkerIndex < ampPointCount) {
    float lx = log10f(ampFreqPoints[ampMarkerIndex]);
    int mx = 32 + (int)(((lx - logStart) / (logStop - logStart)) * (448 - 32));
    int my = 243 - (int)(((ampDbPoints[ampMarkerIndex] - minDb) / (maxDb - minDb)) * 46.0f);

    gfx->drawLine(mx, 193, mx, 245, neonGreen);
    gfx->fillCircle(mx, my, 3, neonGreen);

    gfx->fillRect(250, 260, 200, 18, black);
    gfx->setCursor(250, 262);
    gfx->print("f=");
    gfx->print(ampFreqPoints[ampMarkerIndex], 1);
    gfx->print(" Hz  dB=");
    gfx->print(ampDbPoints[ampMarkerIndex], 2);
  }
}

inline void drawAmpSetupMenu() {
  currentScreen = SCREEN_AMP_SETUP;
  gfx->fillScreen(black);

  drawCenteredText("AMPLITUDENGANG SETUP", 10, 2, neonGreen);

  drawButtonFrame(btnAmpStartField, false);
  drawButtonFrame(btnAmpStopField, false);
  drawButtonFrame(btnAmpStepField, false);
  drawButtonFrame(btnAmpDriveField, false);
  drawButtonFrame(btnAmpSettleField, false);
  drawButtonFrame(btnAmpAvgField, false);

  drawButtonFrame(btnBack, false);
  drawButtonFrame(btnAmpRun, false);
  drawButtonFrame(btnAmpPlot, false);

  drawAmpSweepValues();
  drawAmpGraph();
}

inline void drawAmpPlotMenu() {
  currentScreen = SCREEN_AMP_PLOT;
  gfx->fillScreen(black);

  drawCenteredText("AMPLITUDENGANG PLOT", 10, 2, neonGreen);

  drawButtonFrame(btnBack, false);
  drawButtonFrame(btnAmpRun, false);
  drawButtonFrame(btnAmpPlot, false);

  drawAmpGraph();
}

inline void drawHelpPage() {

  currentScreen = SCREEN_HELP_MENU;

  gfx->fillScreen(black);

  drawCenteredText("HILFE", 10, 2, neonGreen);

  gfx->setTextColor(neonGreen);
  gfx->setTextSize(2);

  // ================= Seite 1 =================
  if (helpPage == 0) {

    gfx->setCursor(20, 55);
    gfx->println("Signalgenerator:");

    gfx->setCursor(20, 90);
    gfx->println("Waehlen Sie diese");

    gfx->setCursor(20, 115);
    gfx->println("Option, um eine der");

    gfx->setCursor(20, 140);
    gfx->println("vorgefertigten");

    gfx->setCursor(20, 165);
    gfx->println("Kurvenformen oder");
  }

  // ================= Seite 2 =================
  else if (helpPage == 1) {

    gfx->setCursor(20, 55);
    gfx->println("eine selbst");

    gfx->setCursor(20, 80);
    gfx->println("programmierte");

    gfx->setCursor(20, 105);
    gfx->println("Kurvenform");

    gfx->setCursor(20, 130);
    gfx->println("darzustellen.");

    gfx->setCursor(20, 165);
    gfx->println("Im Folgemenue");
  }

  // ================= Seite 3 =================
  else if (helpPage == 2) {

    gfx->setCursor(20, 55);
    gfx->println("koennen Sie die");

    gfx->setCursor(20, 80);
    gfx->println("Kurvenform");

    gfx->setCursor(20, 105);
    gfx->println("parametrisieren.");

    gfx->setCursor(20, 150);
    gfx->println("Wobblefunktion");

    gfx->setCursor(20, 175);
    gfx->println("noch in Arbeit!");
  }

  // ================= Seite 4 =================
  else if (helpPage == 3) {

    gfx->setCursor(20, 55);
    gfx->println("Amplitudengang:");

    gfx->setCursor(20, 95);
    gfx->println("Noch in Arbeit,");

    gfx->setCursor(20, 120);
    gfx->println("Funktion nicht");

    gfx->setCursor(20, 145);
    gfx->println("ausreichend");

    gfx->setCursor(20, 170);
    gfx->println("getestet!");
  }

  // ================= Buttons =================

  drawButtonFrame(btnBack, false);

  drawArrowButton(btnLeftArrow, false);
  drawArrowButton(btnRightArrow, false);

  // ================= Seitenanzeige =================

  gfx->setCursor(150, 278);

  gfx->print("SEITE ");
  gfx->print(helpPage + 1);
  gfx->print("/");
  gfx->print(helpPageCount);
}


inline void updateNumpadValueDisplay() {
  gfx->fillRect(21, 271, 438, 28, black);
  gfx->setTextColor(neonGreen);
  gfx->setTextSize(2);
  gfx->setCursor(25, 278);
  gfx->print(numpadBuffer);
}

inline const char* numericTargetName() {
  switch (numpadTarget) {
    case NUM_AMP_START:  return "START";
    case NUM_AMP_STOP:   return "STOP";
    case NUM_AMP_STEP:   return "STEP";
    case NUM_AMP_DRIVE:  return "AMP";
    case NUM_AMP_SETTLE: return "SETTLE";
    case NUM_AMP_AVG:    return "AVG";
    default:             return "VALUE";
  }
}

inline void openNumpad(NumericTarget target, float currentValue, bool integerOnly) {
  previousScreen = currentScreen;
  currentScreen = SCREEN_NUMPAD;
  numpadTarget = target;

  if (integerOnly) {
    snprintf(numpadBuffer, sizeof(numpadBuffer), "%d", (int)currentValue);
  } else {
    dtostrf(currentValue, 0, 2, numpadBuffer);
  }

  gfx->fillScreen(black);
  drawCenteredText("WERTEINGABE", 15, 2, neonGreen);

  gfx->setTextColor(neonGreen);
  gfx->setTextSize(2);
  gfx->setCursor(20, 40);
  gfx->print(numericTargetName());

  drawButtonFrame(npBtn1, false);
  drawButtonFrame(npBtn2, false);
  drawButtonFrame(npBtn3, false);
  drawButtonFrame(npBtn4, false);
  drawButtonFrame(npBtn5, false);
  drawButtonFrame(npBtn6, false);
  drawButtonFrame(npBtn7, false);
  drawButtonFrame(npBtn8, false);
  drawButtonFrame(npBtn9, false);
  drawButtonFrame(npBtn0, false);
  drawButtonFrame(npBtnDot, false);
  drawButtonFrame(npBtnBk, false);
  drawButtonFrame(npBtnOk, false);
  drawButtonFrame(npBtnX, false);

  gfx->drawRect(20, 270, 440, 30, neonGreen);
  updateNumpadValueDisplay();
}

inline void applyNumpadValue() {
  float v = atof(numpadBuffer);

  switch (numpadTarget) {
    case NUM_AMP_START:  ampSweepStartHz = v; break;
    case NUM_AMP_STOP:   ampSweepStopHz = v; break;
    case NUM_AMP_STEP:   ampSweepStepHz = v; break;
    case NUM_AMP_DRIVE:  ampSweepDriveAmp = v; break;
    case NUM_AMP_SETTLE: ampSweepSettleMs = v; break;
    case NUM_AMP_AVG:    ampSweepAverages = (int)v; break;
    default: break;
  }

  clampAllParameters();

  if (previousScreen == SCREEN_AMP_SETUP) drawAmpSetupMenu();
  else drawAmpPlotMenu();
}


inline HoldAction getParamHoldAction(int x, int y) {
  if (selectedWaveform == WAVE_WOBBLE) {
    if (pointInRect(x, y, btnWobAmpMinus))   return HOLD_WOB_AMP_MINUS;
    if (pointInRect(x, y, btnWobAmpPlus))    return HOLD_WOB_AMP_PLUS;
    if (pointInRect(x, y, btnWobStartMinus)) return HOLD_WOB_START_MINUS;
    if (pointInRect(x, y, btnWobStartPlus))  return HOLD_WOB_START_PLUS;
    if (pointInRect(x, y, btnWobStopMinus))  return HOLD_WOB_STOP_MINUS;
    if (pointInRect(x, y, btnWobStopPlus))   return HOLD_WOB_STOP_PLUS;
    if (pointInRect(x, y, btnWobTimeMinus))  return HOLD_WOB_TIME_MINUS;
    if (pointInRect(x, y, btnWobTimePlus))   return HOLD_WOB_TIME_PLUS;
  } else {
    if (pointInRect(x, y, btnAmpMinus))  return HOLD_AMP_MINUS;
    if (pointInRect(x, y, btnAmpPlus))   return HOLD_AMP_PLUS;
    if (pointInRect(x, y, btnFreqMinus)) return HOLD_FREQ_MINUS;
    if (pointInRect(x, y, btnFreqPlus))  return HOLD_FREQ_PLUS;
  }
  return HOLD_NONE;
}

inline void redrawParamData() {
  if (selectedWaveform == WAVE_WOBBLE) drawWobbleValues();
  else drawParamValues();
  drawSignalPreview(selectedWaveform);
}

inline void applyHoldAction(HoldAction action) {
  int i = (int)selectedWaveform;

  switch (action) {
    case HOLD_AMP_MINUS: waveformAmp[i] -= 0.05f; break;
    case HOLD_AMP_PLUS:  waveformAmp[i] += 0.05f; break;
    case HOLD_FREQ_MINUS: waveformFreq[i] -= 1.0f; break;
    case HOLD_FREQ_PLUS:  waveformFreq[i] += 1.0f; break;

    case HOLD_WOB_AMP_MINUS:   wobbleAmplitude -= 0.05f; break;
    case HOLD_WOB_AMP_PLUS:    wobbleAmplitude += 0.05f; break;
    case HOLD_WOB_START_MINUS: wobbleStartHz -= 1.0f; break;
    case HOLD_WOB_START_PLUS:  wobbleStartHz += 1.0f; break;
    case HOLD_WOB_STOP_MINUS:  wobbleStopHz -= 1.0f; break;
    case HOLD_WOB_STOP_PLUS:   wobbleStopHz += 1.0f; break;
    case HOLD_WOB_TIME_MINUS:  wobbleSweepTimeSec -= 0.5f; break;
    case HOLD_WOB_TIME_PLUS:   wobbleSweepTimeSec += 0.5f; break;
    default: break;
  }

  clampAllParameters();
  requestSignalRebuild();
  redrawParamData();
}


inline void handleTouchUi() {
  static bool lastPressed = false;
  static uint16_t lastRawX = 0;
  static uint16_t lastRawY = 0;

  static HoldAction activeHold = HOLD_NONE;
  static uint32_t holdStartMs = 0;
  static uint32_t lastRepeatMs = 0;
  static uint32_t lastTouchPollMs = 0;

  uint32_t nowMs = millis();


  if ((uint32_t)(nowMs - lastTouchPollMs) < 10UL) return;
  lastTouchPollMs = nowMs;

  uint16_t rawX = readTouchX();
  uint16_t rawY = readTouchY();
  bool pressed = isTouchPressed(rawX, rawY);

  if (pressed) {
    lastRawX = rawX;
    lastRawY = rawY;
    lastPressed = true;

    int x = rawToScreenX(rawY);
    int y = rawToScreenY(rawX);

    if (currentScreen == SCREEN_PARAM_MENU) {
      HoldAction action = getParamHoldAction(x, y);

      if (action != HOLD_NONE) {
        if (activeHold != action) {
          activeHold = action;
          holdStartMs = nowMs;
          lastRepeatMs = nowMs;
          applyHoldAction(action);
        } else {
          uint32_t heldFor = nowMs - holdStartMs;
          uint32_t interval = 220;

          if (heldFor > 1500) interval = 40;
          else if (heldFor > 800) interval = 90;
          else if (heldFor > 350) interval = 160;

          if (nowMs - lastRepeatMs >= interval) {
            lastRepeatMs = nowMs;
            applyHoldAction(action);
          }
        }
      } else {
        activeHold = HOLD_NONE;
      }
    }

    return;
  }

  if (!lastPressed) return;

  lastPressed = false;
  activeHold = HOLD_NONE;

  int x = rawToScreenX(lastRawY);
  int y = rawToScreenY(lastRawX);

  if (currentScreen == SCREEN_MAIN_MENU) {
    if (pointInRect(x, y, btnMainSignal)) {
      requestSignalRebuild();
      animateButton(btnMainSignal);
      drawWaveMenuPage();
    } else if (pointInRect(x, y, btnMainAmp)) {
      requestSignalRebuild();
      animateButton(btnMainAmp);
      drawAmpSetupMenu();
    } else if (pointInRect(x, y, btnMainHelp)) {
      requestSignalRebuild();
      animateButton(btnMainHelp);
      helpPage = 0;
      drawHelpPage();
    }
  }

  else if (currentScreen == SCREEN_WAVE_MENU) {
    if (pointInRect(x, y, btnBack)) {
      requestSignalRebuild();
      animateButton(btnBack);
      drawMainMenu();
    } else if (pointInArrow(x, y, btnLeftArrow)) {
      requestSignalRebuild();
      animateArrow(btnLeftArrow);
      waveformPage--;
      if (waveformPage < 0) waveformPage = waveformPageCount - 1;
      drawWaveMenuPage();
    } else if (pointInArrow(x, y, btnRightArrow)) {
      requestSignalRebuild();
      animateArrow(btnRightArrow);
      waveformPage++;
      if (waveformPage >= waveformPageCount) waveformPage = 0;
      drawWaveMenuPage();
    } else {
      int startIdx = waveformPage * waveformsPerPage;
      for (int i = 0; i < 6; i++) {
        int wfIdx = startIdx + i;
        if (wfIdx < WAVE_COUNT && pointInRect(x, y, waveSlotButtons[i])) {
          RectButton tempBtn = waveSlotButtons[i];
          tempBtn.label = waveformNames[wfIdx];
          animateButton(tempBtn);
          selectedWaveform = (WaveformType)wfIdx;
          requestSignalRebuild();
          drawParamMenu();
          break;
        }
      }
    }
  }

  else if (currentScreen == SCREEN_PARAM_MENU) {
    if (pointInRect(x, y, btnBack)) {
      requestSignalRebuild();
      animateButton(btnBack);
      drawWaveMenuPage();
    }
  }

  else if (currentScreen == SCREEN_HELP_MENU) {
    if (pointInRect(x, y, btnBack)) {
      requestSignalRebuild();
      animateButton(btnBack);
      drawMainMenu();
    } else if (pointInArrow(x, y, btnLeftArrow)) {
      requestSignalRebuild();
      animateArrow(btnLeftArrow);
      helpPage--;
      if (helpPage < 0) helpPage = helpPageCount - 1;
      drawHelpPage();
    } else if (pointInArrow(x, y, btnRightArrow)) {
      requestSignalRebuild();
      animateArrow(btnRightArrow);
      helpPage++;
      if (helpPage >= helpPageCount) helpPage = 0;
      drawHelpPage();
    }
  }

  else if (currentScreen == SCREEN_AMP_SETUP) {
    if (pointInRect(x, y, btnBack)) {
      requestSignalRebuild();
      animateButton(btnBack);
      drawMainMenu();
    } else if (pointInRect(x, y, btnAmpRun)) {
      requestSignalRebuild();
      animateButton(btnAmpRun);
      runAmplitudeSweep();
      drawAmpSetupMenu();
    } else if (pointInRect(x, y, btnAmpPlot)) {
      requestSignalRebuild();
      animateButton(btnAmpPlot);
      drawAmpPlotMenu();
    } else if (pointInRect(x, y, btnAmpStartField)) {
      openNumpad(NUM_AMP_START, ampSweepStartHz, false);
    } else if (pointInRect(x, y, btnAmpStopField)) {
      openNumpad(NUM_AMP_STOP, ampSweepStopHz, false);
    } else if (pointInRect(x, y, btnAmpStepField)) {
      openNumpad(NUM_AMP_STEP, ampSweepStepHz, false);
    } else if (pointInRect(x, y, btnAmpDriveField)) {
      openNumpad(NUM_AMP_DRIVE, ampSweepDriveAmp, false);
    } else if (pointInRect(x, y, btnAmpSettleField)) {
      openNumpad(NUM_AMP_SETTLE, ampSweepSettleMs, false);
    } else if (pointInRect(x, y, btnAmpAvgField)) {
      openNumpad(NUM_AMP_AVG, (float)ampSweepAverages, true);
    }
  }

  else if (currentScreen == SCREEN_AMP_PLOT) {
    if (pointInRect(x, y, btnBack)) {
      requestSignalRebuild();
      animateButton(btnBack);
      drawMainMenu();
    } else if (pointInRect(x, y, btnAmpRun)) {
      requestSignalRebuild();
      animateButton(btnAmpRun);
      runAmplitudeSweep();
      drawAmpPlotMenu();
    } else if (pointInRect(x, y, btnAmpPlot)) {
      requestSignalRebuild();
      animateButton(btnAmpPlot);
      drawAmpSetupMenu();
    } else if (x >= 32 && x <= 448 && y >= 193 && y <= 245 && ampDataValid && ampPointCount > 0) {
      int nearest = 0;
      long bestDist = 1000000;

      float startHz = ampFreqPoints[0];
      float stopHz = ampFreqPoints[ampPointCount - 1];
      float logStart = log10f(startHz < 1.0f ? 1.0f : startHz);
      float logStop = log10f(stopHz <= startHz ? startHz + 1.0f : stopHz);

      for (int i = 0; i < ampPointCount; i++) {
        float lx = log10f(ampFreqPoints[i]);
        int px = 32 + (int)(((lx - logStart) / (logStop - logStart)) * (448 - 32));
        long d = labs(px - x);
        if (d < bestDist) {
          bestDist = d;
          nearest = i;
        }
      }

      ampMarkerIndex = nearest;
      drawAmpPlotMenu();
    }
  }

  else if (currentScreen == SCREEN_NUMPAD) {
    if (pointInRect(x, y, npBtn1)) { strcat(numpadBuffer, "1"); updateNumpadValueDisplay(); }
    else if (pointInRect(x, y, npBtn2)) { strcat(numpadBuffer, "2"); updateNumpadValueDisplay(); }
    else if (pointInRect(x, y, npBtn3)) { strcat(numpadBuffer, "3"); updateNumpadValueDisplay(); }
    else if (pointInRect(x, y, npBtn4)) { strcat(numpadBuffer, "4"); updateNumpadValueDisplay(); }
    else if (pointInRect(x, y, npBtn5)) { strcat(numpadBuffer, "5"); updateNumpadValueDisplay(); }
    else if (pointInRect(x, y, npBtn6)) { strcat(numpadBuffer, "6"); updateNumpadValueDisplay(); }
    else if (pointInRect(x, y, npBtn7)) { strcat(numpadBuffer, "7"); updateNumpadValueDisplay(); }
    else if (pointInRect(x, y, npBtn8)) { strcat(numpadBuffer, "8"); updateNumpadValueDisplay(); }
    else if (pointInRect(x, y, npBtn9)) { strcat(numpadBuffer, "9"); updateNumpadValueDisplay(); }
    else if (pointInRect(x, y, npBtn0)) { strcat(numpadBuffer, "0"); updateNumpadValueDisplay(); }
    else if (pointInRect(x, y, npBtnDot)) {
      if (numpadTarget != NUM_AMP_AVG && strchr(numpadBuffer, '.') == nullptr) {
        strcat(numpadBuffer, ".");
        updateNumpadValueDisplay();
      }
    }
    else if (pointInRect(x, y, npBtnBk)) {
      int len = strlen(numpadBuffer);
      if (len > 0) {
        numpadBuffer[len - 1] = '\0';
        updateNumpadValueDisplay();
      }
    }
    else if (pointInRect(x, y, npBtnOk)) {
      applyNumpadValue();
    }
    else if (pointInRect(x, y, npBtnX)) {
      if (previousScreen == SCREEN_AMP_SETUP) drawAmpSetupMenu();
      else drawAmpPlotMenu();
    }
  }
}