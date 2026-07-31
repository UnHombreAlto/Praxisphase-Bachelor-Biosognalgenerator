#pragma once
#include "config.h"
// ================= EKG_alt-Tabelle =================
const int EKG_ALT_TABLE_SIZE = 512;

static const int16_t ekgAltTable[EKG_ALT_TABLE_SIZE] = {
  0, 0, 1, 1, 1, 1, 0, 0, -1, -1, -1, -2, -2, -2, -3, -4,
  -4, -4, -4, -5, -6, -7, -7, -8, -8, -8, -9, -10, -10, -11, -11, -12,
  -13, -13, -14, -16, -16, -17, -17, -19, -19, -20, -20, -21, -22, -22, -23, -23,
  -23, -25, -25, -26, -26, -26, -26, -28, -28, -28, -29, -29, -29, -30, -31, -31,
  -31, -32, -32, -33, -33, -34, -34, -34, -35, -35, -35, -35, -35, -36, -36, -36,
  -36, -36, -36, -36, -37, -37, -37, -37, -37, -37, -37, -37, -37, -37, -37, -38,
  -38, -38, -38, -38, -38, -39, -38, -38, -38, -38, -39, -38, -37, -34, -30, -27,
  -18, -15, -10, -2, 8, 25, 30, 39, 43, 44, 38, 40, 49, 55, 69, 76,
  86, 94, 97, 106, 113, 130, 136, 143, 158, 169, 189, 199, 217, 223, 222, 216,
  215, 216, 217, 217, 214, 197, 167, 151, 123, 110, 89, 78, 59, 43, 37, 23,
  16, 5, 0, -5, -13, -20, -35, -41, -47, -56, -62, -73, -76, -82, -85, -88,
  -92, -94, -96, -98, -101, -103, -106, -109, -110, -113, -115, -118, -119, -121, -122, -124,
  -127, -127, -128, -129, -131, -132, -133, -134, -132, -126, -122, -108, -87, -74, -45, -30,
  -14, -1, 43, 126, 168, 246, 284, 395, 528, 650, 890, 1033, 1307, 1448, 1685, 1656,
  1490, 975, 750, 523, 459, 266, -4, -154, -439, -547, -692, -730, -726, -655, -605, -494,
  -446, -370, -338, -284, -238, -218, -184, -166, -127, -107, -79, -62, -56, -47, -45, -42,
  -41, -40, -40, -39, -37, -36, -32, -28, -25, -20, -18, -13, -11, -7, -2, 1,
  5, 7, 11, 14, 19, 23, 25, 29, 32, 37, 39, 43, 49, 51, 56, 59,
  64, 67, 72, 77, 80, 86, 89, 96, 99, 104, 111, 115, 121, 124, 130, 134,
  141, 147, 150, 157, 161, 168, 172, 179, 186, 190, 197, 200, 207, 213, 218, 227,
  231, 238, 242, 252, 260, 265, 273, 277, 286, 290, 301, 310, 316, 326, 331, 342,
  348, 359, 371, 376, 388, 394, 407, 413, 425, 439, 446, 460, 466, 480, 487, 501,
  513, 519, 531, 537, 548, 554, 565, 576, 581, 591, 595, 605, 611, 619, 628, 631,
  638, 642, 649, 654, 658, 662, 665, 668, 668, 667, 664, 661, 653, 646, 631, 622,
  603, 580, 566, 539, 524, 495, 480, 448, 416, 401, 370, 354, 325, 311, 283, 256,
  243, 219, 208, 184, 173, 154, 136, 127, 110, 103, 88, 81, 69, 57, 52, 41,
  37, 29, 22, 17, 11, 7, 2, -1, -5, -9, -11, -14, -16, -19, -20, -23,
  -24, -25, -26, -26, -26, -26, -26, -25, -25, -25, -24, -23, -23, -22, -22, -21,
  -20, -19, -18, -17, -17, -16, -15, -13, -13, -12, -11, -10, -8, -7, -5, -4,
  -3, -2, -1, 1, 1, 2, 2, 4, 4, 4, 4, 5, 6, 6, 7, 8,
  8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 7, 7,
  7, 7, 6, 6, 6, 5, 5, 4, 4, 3, 2, 2, 1, 1, 0, 0
};

// ================= Ausgabetabelle =================
static uint16_t signalTable[SIGNAL_TABLE_SIZE];

static volatile bool signalNeedsRebuild = true;
static volatile bool signalOutputEnabled = false;

static uint32_t phaseAcc = 0;
static uint32_t phaseInc = 1;
static uint32_t lastSampleMicros = 0;
static uint32_t signalStartMicros = 0;
static uint32_t lastWobbleUpdateMs = 0;


const uint8_t DDS_FRAC_BITS = 16;
const uint32_t DDS_FRAC_SCALE = 65536UL;

inline float clampf(float v, float lo, float hi) {
  if (v < lo) return lo;
  if (v > hi) return hi;
  return v;
}

inline uint16_t clampToDac(float y) {
  if (y < 0.0f) y = 0.0f;
  if (y > DAC_MAX) y = DAC_MAX;
  return (uint16_t)(y + 0.5f);
}

inline void clampAllParameters() {
  for (int i = 0; i < WAVE_COUNT; i++) {
    waveformAmp[i] = clampf(waveformAmp[i], 0.05f, 5.0f);

    if (waveformIsBpm[i]) {
      waveformFreq[i] = clampf(waveformFreq[i], 20.0f, 220.0f);
    } else {
      waveformFreq[i] = clampf(waveformFreq[i], 1.0f, 300.0f);
    }
  }

  wobbleStartHz = clampf(wobbleStartHz, 1.0f, 300.0f);
  wobbleStopHz = clampf(wobbleStopHz, 1.0f, 300.0f);
  wobbleSweepTimeSec = clampf(wobbleSweepTimeSec, 0.5f, 30.0f);
  wobbleAmplitude = clampf(wobbleAmplitude, 0.05f, 5.0f);

  ampSweepStartHz = clampf(ampSweepStartHz, 1.0f, 3000.0f);
  ampSweepStopHz = clampf(ampSweepStopHz, 1.0f, 3000.0f);
  ampSweepStepHz = clampf(ampSweepStepHz, 1.0f, 500.0f);
  ampSweepDriveAmp = clampf(ampSweepDriveAmp, 0.05f, 5.0f);
  ampSweepSettleMs = clampf(ampSweepSettleMs, 10.0f, 5000.0f);

  if (ampSweepAverages < 1) ampSweepAverages = 1;
  if (ampSweepAverages > 20) ampSweepAverages = 20;
}

inline float gauss(float t, float mu, float sigma, float amplitude) {
  float x = (t - mu) / sigma;
  return amplitude * expf(-0.5f * x * x);
}

inline float pseudoNoise(float t) {
  return
      0.55f * sinf(2.0f * PI * 73.0f * t + 0.31f) +
      0.30f * sinf(2.0f * PI * 127.0f * t + 1.17f) +
      0.15f * sinf(2.0f * PI * 211.0f * t + 2.41f);
}

inline float getCurrentWobbleFrequency(float t) {
  float startHz = wobbleStartHz;
  float stopHz = wobbleStopHz;

  if (startHz > stopHz) {
    float tmp = startHz;
    startHz = stopHz;
    stopHz = tmp;
  }

  float cycle = 2.0f * wobbleSweepTimeSec;
  float phase = fmodf(t, cycle);

  if (phase <= wobbleSweepTimeSec) {
    float k = phase / wobbleSweepTimeSec;
    return startHz + (stopHz - startHz) * k;
  } else {
    float k = (phase - wobbleSweepTimeSec) / wobbleSweepTimeSec;
    return stopHz - (stopHz - startHz) * k;
  }
}

inline float ekgValueFromPhase(float phase) {
  const float pPos = 0.18f;
  const float qPos = 0.36f;
  const float rPos = 0.40f;
  const float sPos = 0.43f;
  const float tPos = 0.68f;

  const float pWidth = 0.025f;
  const float qWidth = 0.008f;
  const float rWidth = 0.010f;
  const float sWidth = 0.012f;
  const float tWidth = 0.060f;

  float a = waveformAmp[WAVE_EKG];

  float y = baseline;
  y += gauss(phase, pPos, pWidth,  180.0f * a);
  y += gauss(phase, qPos, qWidth, -220.0f * a);
  y += gauss(phase, rPos, rWidth, 1200.0f * a);
  y += gauss(phase, sPos, sWidth, -320.0f * a);
  y += gauss(phase, tPos, tWidth,  320.0f * a);

  return y;
}

inline float ekgModel(float t) {
  float bpm = waveformFreq[WAVE_EKG];
  float beatPeriod = 60.0f / bpm;
  float phaseSeconds = fmodf(t, beatPeriod);
  float phase = phaseSeconds / beatPeriod;
  return ekgValueFromPhase(phase);
}

inline float ekgAltValueFromPhase(float phase) {
  float tablePos = phase * EKG_ALT_TABLE_SIZE;
  int i0 = (int)tablePos;
  float frac = tablePos - i0;

  if (i0 < 0) i0 = 0;
  if (i0 >= EKG_ALT_TABLE_SIZE) i0 = 0;

  int i1 = i0 + 1;
  if (i1 >= EKG_ALT_TABLE_SIZE) i1 = 0;

  float y0 = (float)ekgAltTable[i0];
  float y1 = (float)ekgAltTable[i1];
  float centered = y0 + (y1 - y0) * frac;

  return baseline + waveformAmp[WAVE_EKG_ALT] * centered;
}

inline float ekgAltModel(float t) {
  float bpm = waveformFreq[WAVE_EKG_ALT];
  float beatPeriod = 60.0f / bpm;
  float phaseSeconds = fmodf(t, beatPeriod);
  float phase = phaseSeconds / beatPeriod;
  return ekgAltValueFromPhase(phase);
}

inline float eegModel(float t) {
  float f = waveformFreq[WAVE_EEG];

  float s1 = sinf(2.0f * PI * f * t);
  float s2 = 0.45f * sinf(2.0f * PI * (0.5f * f) * t + 0.9f);
  float s3 = 0.25f * sinf(2.0f * PI * (1.8f * f) * t + 2.1f);
  float s4 = 0.12f * sinf(2.0f * PI * (3.2f * f) * t + 1.4f);

  float envelope = 0.85f + 0.15f * sinf(2.0f * PI * 0.25f * t);

  return baseline + 220.0f * waveformAmp[WAVE_EEG] * envelope * (s1 + s2 + s3 + s4);
}

inline float emgModel(float t) {
  float f = waveformFreq[WAVE_EMG];

  float burst =
      0.45f +
      0.35f * sinf(2.0f * PI * 1.2f * t + 0.6f) +
      0.20f * sinf(2.0f * PI * 2.7f * t + 1.8f);

  if (burst < 0.0f) burst = 0.0f;

  float c1 = sinf(2.0f * PI * f * t);
  float c2 = 0.65f * sinf(2.0f * PI * (1.7f * f) * t + 1.1f);
  float c3 = 0.40f * sinf(2.0f * PI * (2.4f * f) * t + 2.3f);
  float c4 = 0.22f * sinf(2.0f * PI * (3.1f * f) * t + 0.4f);

  return baseline + 420.0f * waveformAmp[WAVE_EMG] *
         burst * (c1 + c2 + c3 + c4 + 0.55f * pseudoNoise(t));
}

inline float sineValueFromPhase(float phase, float ampScale) {
  return baseline + 1800.0f * ampScale * sinf(2.0f * PI * phase);
}

inline float sineLikeModel(float t, float freq, float ampScale) {
  return baseline + 1800.0f * ampScale * sinf(2.0f * PI * freq * t);
}

inline float squareValueFromPhase(float phase) {
  float a = 1800.0f * waveformAmp[WAVE_SQUARE];
  return (phase < 0.5f) ? (baseline + a) : (baseline - a);
}

inline float squareModel(float t) {
  float a = 1800.0f * waveformAmp[WAVE_SQUARE];
  float s = sinf(2.0f * PI * waveformFreq[WAVE_SQUARE] * t);
  return (s >= 0.0f) ? (baseline + a) : (baseline - a);
}

inline float customValueFromPhase(WaveformType wf, float phase) {
  int idx = (int)wf - (int)WAVE_CUSTOM2;
  if (idx < 0) idx = 0;

  float a = waveformAmp[(int)wf];
  float base = sinf(2.0f * PI * phase);
  float harm = 0.20f * sinf(2.0f * PI * (1.0f + 0.1f * idx) * phase + 0.3f * idx);

  return baseline + 1600.0f * a * (base + harm);
}

inline float customModel(WaveformType wf, float t) {
  float f = waveformFreq[(int)wf];
  float phase = fmodf(t * f, 1.0f);
  return customValueFromPhase(wf, phase);
}

inline float generateSignalForWaveform(WaveformType wf, float t) {
  switch (wf) {
    case WAVE_EKG:
      return ekgModel(t);

    case WAVE_EMG:
      return emgModel(t);

    case WAVE_EEG:
      return eegModel(t);

    case WAVE_SINE:
      return sineLikeModel(t, waveformFreq[WAVE_SINE], waveformAmp[WAVE_SINE]);

    case WAVE_WOBBLE:
      return sineLikeModel(t, getCurrentWobbleFrequency(t), wobbleAmplitude);

    case WAVE_SQUARE:
      return squareModel(t);

    case WAVE_EKG_ALT:
      return ekgAltModel(t);

    default:
      if ((int)wf >= (int)WAVE_CUSTOM2 && (int)wf <= (int)WAVE_CUSTOM12) {
        return customModel(wf, t);
      }
      return baseline;
  }
}


inline float getPlaybackFrequencyHzForSelectedWaveform() {
  if (selectedWaveform == WAVE_EKG || selectedWaveform == WAVE_EKG_ALT) {
    return waveformFreq[(int)selectedWaveform] / 60.0f;  // BPM -> Hz
  }

  if (selectedWaveform == WAVE_WOBBLE) {
    return wobbleStartHz;
  }

  if (selectedWaveform == WAVE_EEG || selectedWaveform == WAVE_EMG) {
    return 1.0f;
  }

  return waveformFreq[(int)selectedWaveform];
}

inline void setPhaseIncrementFromHz(float fHz) {
  if (fHz < 0.001f) fHz = 0.001f;

  float inc = (fHz * (float)SIGNAL_TABLE_SIZE * (float)DDS_FRAC_SCALE) / (float)SAMPLE_RATE_HZ;

  if (inc < 1.0f) inc = 1.0f;
  if (inc > 4294960000.0f) inc = 4294960000.0f;

  phaseInc = (uint32_t)(inc + 0.5f);
}

inline void requestSignalRebuild() {
  signalOutputEnabled = false;
  signalNeedsRebuild = true;
}

inline float buildTableValueForIndex(int i) {
  float phase = (float)i / (float)SIGNAL_TABLE_SIZE;

  switch (selectedWaveform) {
    case WAVE_EKG:
      return ekgValueFromPhase(phase);

    case WAVE_EKG_ALT:
      return ekgAltValueFromPhase(phase);

    case WAVE_SINE:
      return sineValueFromPhase(phase, waveformAmp[WAVE_SINE]);

    case WAVE_WOBBLE:
      return sineValueFromPhase(phase, wobbleAmplitude);

    case WAVE_SQUARE:
      return squareValueFromPhase(phase);

    case WAVE_EEG: {
      float t = phase;      
      return eegModel(t);
    }

    case WAVE_EMG: {
      float t = phase;      
      return emgModel(t);
    }

    default:
      if ((int)selectedWaveform >= (int)WAVE_CUSTOM2 && (int)selectedWaveform <= (int)WAVE_CUSTOM12) {
        return customValueFromPhase(selectedWaveform, phase);
      }
      return baseline;
  }
}

inline void rebuildSignalTable() {
  signalOutputEnabled = false;
  clampAllParameters();

  for (int i = 0; i < SIGNAL_TABLE_SIZE; i++) {
    float y = buildTableValueForIndex(i);
    signalTable[i] = clampToDac(y);
  }

  phaseAcc = 0;
  lastSampleMicros = micros();
  signalStartMicros = micros();
  lastWobbleUpdateMs = millis();

  setPhaseIncrementFromHz(getPlaybackFrequencyHzForSelectedWaveform());

  signalNeedsRebuild = false;
  signalOutputEnabled = true;
}

inline void handleSignalRebuild() {
  if (signalNeedsRebuild) {
    rebuildSignalTable();
  }
}

inline void updateWobblePhaseIncrementIfNeeded() {
  if (selectedWaveform != WAVE_WOBBLE) return;

  uint32_t nowMs = millis();
  if ((uint32_t)(nowMs - lastWobbleUpdateMs) < 10) return;

  lastWobbleUpdateMs = nowMs;

  float t = (micros() - signalStartMicros) / 1000000.0f;
  float f = getCurrentWobbleFrequency(t);
  setPhaseIncrementFromHz(f);
}



inline void updateSignalOutput() {
  if (!signalOutputEnabled) return;

  updateWobblePhaseIncrementIfNeeded();

  uint32_t nowMicros = micros();

  if ((uint32_t)(nowMicros - lastSampleMicros) >= samplePeriodUs) {
    
    lastSampleMicros = nowMicros;

    uint16_t index = (uint16_t)((phaseAcc >> DDS_FRAC_BITS) % SIGNAL_TABLE_SIZE);
    analogWrite(dacPin, signalTable[index]);

    phaseAcc += phaseInc;
  }
}

inline float measureRmsAtFrequency(float freqHz, float ampScale, float settleMs) {
  const uint32_t sampleWindowMs = 180;

  bool oldOutputState = signalOutputEnabled;
  signalOutputEnabled = false;

  uint32_t startMs = millis();
  uint32_t lastUpdateUs = micros();
  uint32_t t0Us = micros();

  double sum = 0.0;
  double sumSq = 0.0;
  uint32_t count = 0;

  while (millis() - startMs < (uint32_t)(settleMs + sampleWindowMs)) {
    uint32_t nowUs = micros();

    if ((uint32_t)(nowUs - lastUpdateUs) >= samplePeriodUs) {
      lastUpdateUs = nowUs;

      float t = (nowUs - t0Us) / 1000000.0f;
      float y = sineLikeModel(t, freqHz, ampScale);
      analogWrite(dacPin, clampToDac(y));

      if (millis() - startMs >= (uint32_t)settleMs) {
        int v = analogRead(adcPin);
        sum += v;
        sumSq += (double)v * (double)v;
        count++;
      }
    }
  }

  signalOutputEnabled = oldOutputState;

  if (count < 2) return 0.0f;

  double mean = sum / (double)count;
  double meanSq = sumSq / (double)count;
  double variance = meanSq - mean * mean;

  if (variance < 0.0) variance = 0.0;

  return (float)sqrt(variance);
}

inline void runAmplitudeSweep() {
  bool oldOutputState = signalOutputEnabled;
  signalOutputEnabled = false;

  ampPointCount = 0;
  ampDataValid = false;
  ampMarkerIndex = -1;

  float startHz = ampSweepStartHz;
  float stopHz = ampSweepStopHz;

  if (startHz > stopHz) {
    float tmp = startHz;
    startHz = stopHz;
    stopHz = tmp;
  }

  float drivePeak = 1800.0f * ampSweepDriveAmp;
  float driveRms = drivePeak / 1.41421356f;

  if (driveRms < 0.001f) driveRms = 0.001f;

  for (float f = startHz; f <= stopHz + 0.001f && ampPointCount < MAX_AMP_POINTS; f += ampSweepStepHz) {
    float rmsAcc = 0.0f;

    for (int k = 0; k < ampSweepAverages; k++) {
      rmsAcc += measureRmsAtFrequency(f, ampSweepDriveAmp, ampSweepSettleMs);
    }

    float rms = rmsAcc / (float)ampSweepAverages;
    float db = 20.0f * log10f((rms < 0.001f ? 0.001f : rms) / driveRms);

    ampFreqPoints[ampPointCount] = f;
    ampDbPoints[ampPointCount] = db;

    ampPointCount++;
  }

  ampDataValid = (ampPointCount > 1);

  if (ampDataValid) {
    ampMarkerIndex = 0;
  }

  signalOutputEnabled = oldOutputState;
  requestSignalRebuild();
}
