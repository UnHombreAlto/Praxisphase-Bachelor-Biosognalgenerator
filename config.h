#pragma once
#include <Arduino.h>
#include <Arduino_GFX_Library.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// ================= DAC / ADC =================
const int dacPin = A0;
const int adcPin = A1;
const int DAC_MAX = 4095;
const float baseline = 2048.0f;


const uint32_t samplePeriodUs = 30;


const uint16_t SIGNAL_TABLE_SIZE = 1024;
const uint32_t SAMPLE_RATE_HZ = 1000000UL / samplePeriodUs;

// ================= Display Pins =================
#define TFT_CS    10
#define TFT_DC     9
#define TFT_RST   -1
#define TFT_SCK   13
#define TFT_MOSI  11

// ================= Touch Pins =================
#define TOUCH_CS   5
#define TOUCH_CLK  4
#define TOUCH_DIN  6
#define TOUCH_OUT  7

// ================= Touch Calibration =================
const int idleX = 0;
const int idleY = 2047;
const int touchThresholdX = 80;
const int touchThresholdY = 80;

const int rawXTop = 1850;
const int rawXBottom = 185;
const int rawYLeft = 1902;
const int rawYRight = 145;

// ================= Farben =================
extern uint16_t black;
extern uint16_t neonGreen;
extern uint16_t dimGreen;

// ================= Display Objects =================
extern Arduino_DataBus *bus;
extern Arduino_GFX *gfx;

// ================= Waveforms =================

enum WaveformType {
  WAVE_EKG = 0,
  WAVE_EMG,
  WAVE_EEG,
  WAVE_SINE,
  WAVE_WOBBLE,
  WAVE_SQUARE,
  WAVE_CUSTOM1,
  WAVE_CUSTOM2,
  WAVE_CUSTOM3,
  WAVE_CUSTOM4,
  WAVE_CUSTOM5,
  WAVE_CUSTOM6,
  WAVE_CUSTOM7,
  WAVE_CUSTOM8,
  WAVE_CUSTOM9,
  WAVE_CUSTOM10,
  WAVE_CUSTOM11,
  WAVE_CUSTOM12,
  WAVE_COUNT
};


#define WAVE_EKG_ALT WAVE_CUSTOM1

static const char* waveformNames[WAVE_COUNT] = {
  "EKG",
  "EMG",
  "EEG",
  "SINUS",
  "WOBBLE",
  "RECHTECK",
  "EKG_alt",
  "CUSTOM 2",
  "CUSTOM 3",
  "CUSTOM 4",
  "CUSTOM 5",
  "CUSTOM 6",
  "CUSTOM 7",
  "CUSTOM 8",
  "CUSTOM 9",
  "CUSTOM 10",
  "CUSTOM 11",
  "CUSTOM 12"
};

enum ScreenType {
  SCREEN_MAIN_MENU,
  SCREEN_WAVE_MENU,
  SCREEN_PARAM_MENU,
  SCREEN_HELP_MENU,
  SCREEN_AMP_SETUP,
  SCREEN_AMP_PLOT,
  SCREEN_NUMPAD
};

extern ScreenType currentScreen;
extern ScreenType previousScreen;
extern WaveformType selectedWaveform;

extern int waveformPage;
extern int helpPage;

struct RectButton {
  int x;
  int y;
  int w;
  int h;
  const char* label;
};

struct ArrowButton {
  int x;
  int y;
  int w;
  int h;
  bool rightDirection;
};

enum HoldAction {
  HOLD_NONE,
  HOLD_AMP_MINUS,
  HOLD_AMP_PLUS,
  HOLD_FREQ_MINUS,
  HOLD_FREQ_PLUS,
  HOLD_WOB_AMP_MINUS,
  HOLD_WOB_AMP_PLUS,
  HOLD_WOB_START_MINUS,
  HOLD_WOB_START_PLUS,
  HOLD_WOB_STOP_MINUS,
  HOLD_WOB_STOP_PLUS,
  HOLD_WOB_TIME_MINUS,
  HOLD_WOB_TIME_PLUS
};

enum NumericTarget {
  NUM_NONE,
  NUM_AMP_START,
  NUM_AMP_STOP,
  NUM_AMP_STEP,
  NUM_AMP_DRIVE,
  NUM_AMP_SETTLE,
  NUM_AMP_AVG
};

extern NumericTarget numpadTarget;
extern char numpadBuffer[20];

// ================= Global Parameters =================
extern bool waveformIsBpm[WAVE_COUNT];
extern float waveformFreq[WAVE_COUNT];
extern float waveformAmp[WAVE_COUNT];

extern float wobbleStartHz;
extern float wobbleStopHz;
extern float wobbleSweepTimeSec;
extern float wobbleAmplitude;

// ================= Amplitudengang =================
const int MAX_AMP_POINTS = 120;
extern float ampSweepStartHz;
extern float ampSweepStopHz;
extern float ampSweepStepHz;
extern float ampSweepDriveAmp;
extern float ampSweepSettleMs;
extern int ampSweepAverages;

extern float ampFreqPoints[MAX_AMP_POINTS];
extern float ampDbPoints[MAX_AMP_POINTS];
extern int ampPointCount;
extern bool ampDataValid;
extern int ampMarkerIndex;

// ================= Preview Box =================
const int previewX = 250;
const int previewY = 185;
const int previewW = 190;
const int previewH = 115;

// ================= Layout Constants =================
const int waveformsPerPage = 6;
const int waveformPageCount = (WAVE_COUNT + waveformsPerPage - 1) / waveformsPerPage;
const int helpPageCount = 4;