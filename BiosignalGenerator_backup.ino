#include <Arduino.h>
#include <Arduino_GFX_Library.h>

#include "config.h"
#include "touch_input.h"
#include "signal_engine.h"
#include "ui.h"

// ================= Display Objekte =================
Arduino_DataBus *bus = new Arduino_SWSPI(
  TFT_DC,
  TFT_CS,
  TFT_SCK,
  TFT_MOSI,
  GFX_NOT_DEFINED
);

Arduino_GFX *gfx = new Arduino_ILI9488_18bit(bus, TFT_RST, 1, false);

// ================= Farben =================
uint16_t black;
uint16_t neonGreen;
uint16_t dimGreen;


ScreenType currentScreen = SCREEN_MAIN_MENU;
ScreenType previousScreen = SCREEN_MAIN_MENU;

WaveformType selectedWaveform = WAVE_EKG;

int waveformPage = 0;
int helpPage = 0;

// ================= Kurven-Parameter =================
bool waveformIsBpm[WAVE_COUNT] = {
  true, false, false, false, false, false,
  true, false, false, false, false, false,
  false, false, false, false, false, false
};

float waveformFreq[WAVE_COUNT] = {
  60.0f,   // EKG BPM
  90.0f,   // EMG Hz
  10.0f,   // EEG Hz
  5.0f,    // Sinus Hz
  5.0f,    // Wobble Platzhalter
  5.0f,    // Rechteck Hz

  60.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f,
  5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f
};

float waveformAmp[WAVE_COUNT] = {
  1.0f,    // EKG
  0.35f,   // EMG
  0.20f,   // EEG
  0.50f,   // Sinus
  0.50f,   // Wobble 
  0.50f,   // Rechteck

  1.0f, 0.50f, 0.50f, 0.50f, 0.50f, 0.50f,
  0.50f, 0.50f, 0.50f, 0.50f, 0.50f, 0.50f
};

// ================= Wobble-Parameter =================
float wobbleStartHz = 5.0f;
float wobbleStopHz = 50.0f;
float wobbleSweepTimeSec = 5.0f;
float wobbleAmplitude = 0.50f;

// ================= Amplitudengang-Parameter =================
float ampSweepStartHz = 10.0f;
float ampSweepStopHz = 1000.0f;
float ampSweepStepHz = 10.0f;
float ampSweepDriveAmp = 0.50f;
float ampSweepSettleMs = 200.0f;
int ampSweepAverages = 2;

float ampFreqPoints[MAX_AMP_POINTS];
float ampDbPoints[MAX_AMP_POINTS];
int ampPointCount = 0;
bool ampDataValid = false;
int ampMarkerIndex = -1;

// ================= Numpad =================
NumericTarget numpadTarget = NUM_NONE;
char numpadBuffer[20] = "";

// ================= Setup =================
void setup() {
  analogWriteResolution(12);
  analogReadResolution(12);

  pinMode(TOUCH_CS, OUTPUT);
  pinMode(TOUCH_CLK, OUTPUT);
  pinMode(TOUCH_DIN, OUTPUT);
  pinMode(TOUCH_OUT, INPUT);

  digitalWrite(TOUCH_CS, HIGH);
  digitalWrite(TOUCH_CLK, LOW);
  digitalWrite(TOUCH_DIN, LOW);

  gfx->begin();

  black = gfx->color565(0, 0, 0);
  neonGreen = gfx->color565(0, 255, 80);
  dimGreen = gfx->color565(0, 120, 40);

  clampAllParameters();
  rebuildSignalTable();

  
  drawMainMenu();
}

// ================= Loop =================
void loop() {
  updateSignalOutput();
  handleTouchUi();
  handleSignalRebuild();
}