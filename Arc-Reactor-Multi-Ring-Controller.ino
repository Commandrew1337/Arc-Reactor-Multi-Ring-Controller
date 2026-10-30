// ============================================================================
// SECTION 1: HARDWARE INITIALIZATION AND MEMORY ARCHITECTURE
// Place this at the very top of your sketch to establish configurations.
// ============================================================================
#include <FastLED.h>

#define LED_PIN         6          
#define BUTTON_PIN      2          
#define ONBOARD_LED     13         
#define NUM_LEDS        93         
#define LED_TYPE        WS2812B    
#define COLOR_ORDER     GRB        
#define TOTAL_PATTERNS  15         // Total of 15 pattern modules

CRGB leds[NUM_LEDS];
volatile uint8_t currentPatternIndex = 0; 
volatile bool buttonIsPressed = false;    

// RING BOUNDARY LOOKUP TABLES
// Allows us to instantly treat each ring as an independent, isolated concentric object
const uint8_t NUM_RINGS = 6;
const uint8_t ringSizes[NUM_RINGS]  = {32, 24, 16, 12,  8,  1};
const uint8_t ringStarts[NUM_RINGS] = { 0, 32, 56, 72, 84, 92};

// ============================================================================
// SECTION 2: CORE SETUP ENGINE AND SYSTEM LOOP
// This section configures hardware and routes the active patterns.
// ============================================================================
void setup() {
  delay(500); 
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 5000); 
  FastLED.setBrightness(150); 

  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(ONBOARD_LED, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), handleButtonInterrupt, CHANGE);
}

void loop() {
  digitalWrite(ONBOARD_LED, buttonIsPressed ? HIGH : LOW);

  // Switchboard Engine
  switch (currentPatternIndex) {
    case 0: pattern_concentricSyncPulse(); break; 
    case 1: pattern_radialRainbowWheel();   break; 
    case 2: pattern_tunnelRipple();         break; 
    case 3: pattern_concentricChaser();     break; 
    case 4: pattern_matrixSparkle();        break; 
    case 5: pattern_vortexSpiral();         break; 
    case 6: pattern_pingPongBounce();       break; 
    case 7: pattern_kaleidoSpoke();         break; 
    case 8: pattern_heatWave();             break; 
    case 9: pattern_orbitSplit();           break; 
    
    // Remade Cinematic Arc Reactor Effects (10 - 14)
    case 10: pattern_starkCoreSteady();     break; // Fluid Breathing Plasma Core
    case 11: pattern_ibeamCharge();         break; // Concentric Inward Wave Compression
    case 12: pattern_palladiumDecay();      break; // Swirling Magnetic Heat Discoloration
    case 13: pattern_vibraniumOverload();   break; // High-Density Ring Swarm Accelerator
    case 14: pattern_starkSegmentTest();    break; // Geometric Rotary Scanning Diagnostics
    default: currentPatternIndex = 0; break;
  }
}

// ============================================================================
// SECTION 3: CONCENTRIC AND GEOMETRIC LIGHT PATTERNS (0 - 9)
// Contains your original 5 animations and your second set of geometric ring behaviors.
// ============================================================================

/**
 * 1. Synchronized Concentric Pulse
 */
void pattern_concentricSyncPulse() {
  uint8_t wave = beatsin8(10, 0, 255); 
  for (uint8_t r = 0; r < NUM_RINGS; r++) {
    CRGB ringColor = CHSV((wave + (r * 40)) % 255, 255, 255);
    fill_solid(&(leds[ringStarts[r]]), ringSizes[r], ringColor);
  }
  FastLED.show();
}

/**
 * 2. Radial Rainbow Wheel
 */
void pattern_radialRainbowWheel() {
  static unsigned long lastUpdate = 0;
  static uint8_t motionTracker = 0;
  if (millis() - lastUpdate >= 15) {
    lastUpdate = millis();
    for (uint8_t r = 0; r < NUM_RINGS; r++) {
      uint8_t startIdx = ringStarts[r];
      uint8_t size = ringSizes[r];
      uint8_t hueDelta = 256 / size; 
      for (uint8_t i = 0; i < size; i++) {
        leds[startIdx + i] = CHSV((motionTracker + (i * hueDelta)) % 255, 255, 255);
      }
    }
    FastLED.show();
    motionTracker += 2; 
  }
}

/**
 * 3. Tunnel Ripple
 */
void pattern_tunnelRipple() {
  static unsigned long lastUpdate = 0;
  static int currentStep = 0;
  if (millis() - lastUpdate >= 120) {
    lastUpdate = millis();
    fill_solid(leds, NUM_LEDS, CRGB::Black);
    if (currentStep < NUM_RINGS) {
      fill_solid(&(leds[ringStarts[currentStep]]), ringSizes[currentStep], CRGB::DeepSkyBlue);
    }
    FastLED.show();
    currentStep++;
    if (currentStep >= NUM_RINGS + 2) currentStep = 0;
  }
}

/**
 * 4. Concentric Sync-Chaser
 */
void pattern_concentricChaser() {
  static unsigned long lastUpdate = 0;
  static uint16_t frameCount = 0;
  if (millis() - lastUpdate >= 50) {
    lastUpdate = millis();
    fill_solid(leds, NUM_LEDS, CRGB::Black);
    for (uint8_t r = 0; r < NUM_RINGS - 1; r++) { 
      uint8_t startIdx = ringStarts[r];
      uint8_t size = ringSizes[r];
      uint8_t dotPos = frameCount % size;
      leds[startIdx + dotPos] = CRGB::Fuchsia;
      uint8_t tailPos = (dotPos + size - 1) % size;
      leds[startIdx + tailPos] = CRGB(100, 0, 100);
    }
    leds[92] = CRGB::White; 
    FastLED.show();
    frameCount++;
  }
}

/**
 * 5. Matrix Shimmer Sparkle
 */
void pattern_matrixSparkle() {
  static unsigned long lastUpdate = 0;
  if (millis() - lastUpdate >= 25) {
    lastUpdate = millis();
    fadeToBlackBy(leds, NUM_LEDS, 40);
    uint8_t randomRing = random8(0, NUM_RINGS);
    uint8_t randomPixelOffset = random8(0, ringSizes[randomRing]);
    uint16_t targetGlobalPixel = ringStarts[randomRing] + randomPixelOffset;
    leds[targetGlobalPixel] = CHSV(random8(120, 180), 200, 255); 
    FastLED.show();
  }
}

/**
 * 6. Vortex Spiral
 */
void pattern_vortexSpiral() {
  static unsigned long lastUpdate = 0;
  static uint8_t spinTracker = 0;
  if (millis() - lastUpdate >= 20) {
    lastUpdate = millis();
    fill_solid(leds, NUM_LEDS, CRGB::Black);
    for (uint8_t r = 0; r < NUM_RINGS; r++) {
      uint8_t size = ringSizes[r];
      uint8_t startIdx = ringStarts[r];
      uint8_t targetPixel = (spinTracker + (r * 3)) % size;
      leds[startIdx + targetPixel] = CHSV((spinTracker * 2) + (r * 25), 255, 255);
    }
    FastLED.show();
    spinTracker++;
  }
}

/**
 * 7. Ping Pong Bounce
 */
void pattern_pingPongBounce() {
  static unsigned long lastUpdate = 0;
  static int currentRing = 0;
  static int direction = 1; 
  if (millis() - lastUpdate >= 100) {
    lastUpdate = millis();
    fill_solid(leds, NUM_LEDS, CRGB::Black);
    fill_solid(&(leds[ringStarts[currentRing]]), ringSizes[currentRing], CRGB::LimeGreen);
    FastLED.show();
    currentRing += direction;
    if (currentRing >= NUM_RINGS - 1 || currentRing <= 0) direction = -direction; 
  }
}

/**
 * 8. Kaleido Spoke
 */
void pattern_kaleidoSpoke() {
  static unsigned long lastUpdate = 0;
  static uint8_t sectorTracker = 0;
  if (millis() - lastUpdate >= 60) {
    lastUpdate = millis();
    fill_solid(leds, NUM_LEDS, CRGB::Black);
    for (uint8_t r = 0; r < NUM_RINGS - 1; r++) {
      uint8_t size = ringSizes[r];
      uint8_t startIdx = ringStarts[r];
      for (uint8_t s = 0; s < 4; s++) {
        uint8_t localOffset = (sectorTracker + (s * (size / 4))) % size;
        leds[startIdx + localOffset] = CHSV(sectorTracker * 3, 230, 255);
      }
    }
    leds[92] = CRGB::Gold; 
    FastLED.show();
    sectorTracker++;
  }
}

/**
 * 9. Heat Wave (Fire Simulation)
 */
void pattern_heatWave() {
  static unsigned long lastUpdate = 0;
  if (millis() - lastUpdate >= 30) {
    lastUpdate = millis();
    for (uint8_t r = 0; r < NUM_RINGS; r++) {
      uint8_t size = ringSizes[r];
      uint8_t startIdx = ringStarts[r];
      for (uint8_t i = 0; i < size; i++) {
        uint8_t noise = inoise8(startIdx * 10, i * 20 + millis() / 4);
        leds[startIdx + i] = CHSV(scale8(noise, 25), 255, noise);
      }
    }
    FastLED.show();
  }
}

/**
 * 10. Orbit Split
 */
void pattern_orbitSplit() {
  static unsigned long lastUpdate = 0;
  static uint16_t frame = 0;
  if (millis() - lastUpdate >= 40) {
    lastUpdate = millis();
    fill_solid(leds, NUM_LEDS, CRGB::Black);
    for (uint8_t r = 0; r < NUM_RINGS - 1; r++) {
      uint8_t size = ringSizes[r];
      uint8_t startIdx = ringStarts[r];
      uint8_t targetIdx = 0;
      if (r % 2 == 0) targetIdx = frame % size;
      else targetIdx = (size - 1) - (frame % size);
      leds[startIdx + targetIdx] = CRGB::OrangeRed;
      uint8_t splitIdx = (targetIdx + (size / 2)) % size;
      leds[startIdx + splitIdx] = CRGB(0, 150, 255); 
    }
    leds[92] = CRGB::White; 
    FastLED.show();
    frame++;
  }
}

// ============================================================================
// SECTION 4: HIGH-DENSITY STARK INDUSTRIES CINEMATIC PATTERNS (10 - 14)
// Entirely rewritten movie effects focused on fluid color blending.
// ============================================================================

/**
 * 11. Stark Core Steady (Fluid Breathing Plasma Core)
 */
void pattern_starkCoreSteady() {
  static unsigned long lastUpdate = 0;
  if (millis() - lastUpdate >= 15) {
    lastUpdate = millis();
    
    uint8_t pulseWave = beatsin8(14, 110, 255); 
    
    for (uint8_t r = 0; r < NUM_RINGS; r++) {
      uint8_t size = ringSizes[r];
      uint8_t startIdx = ringStarts[r];
      for (uint8_t i = 0; i < size; i++) {
        uint8_t plasma = inoise8(startIdx * 20 + i * 40, millis() / 3);
        uint16_t dynamicBright = (plasma + pulseWave) / 2;
        if (dynamicBright < 100) dynamicBright = 100;
        
        leds[startIdx + i] = CRGB(0, scale8(dynamicBright, 185), dynamicBright);
      }
    }
    FastLED.show();
  }
}

/**
 * 12. Un-Ibeam Energy Charge (Concentric Inward Wave Compression)
 */
void pattern_ibeamCharge() {
  static unsigned long lastUpdate = 0;
  if (millis() - lastUpdate >= 25) {
    lastUpdate = millis();
    
    uint8_t baseWave = beatsin8(30, 70, 130);
    for (uint16_t i = 0; i < NUM_LEDS; i++) {
      leds[i] = CRGB(0, baseWave / 2, baseWave);
    }
    
    uint8_t surgePhase = (millis() / 8) % 255;
    for (uint8_t r = 0; r < NUM_RINGS; r++) {
      uint8_t ringWeight = (surgePhase + (r * 42)) % 255;
      uint8_t flareBrightness = sin8(ringWeight);
      
      if (flareBrightness > 180) {
        uint8_t mixVal = map(flareBrightness, 180, 255, 0, 200);
        CRGB waveColor = CRGB(mixVal / 2, mixVal, 255);
        
        for (uint8_t idx = 0; idx < ringSizes[r]; idx++) {
          leds[ringStarts[r] + idx] |= waveColor;
        }
      }
    }
    FastLED.show();
  }
}

/**
 * 13. Palladium Decay (Swirling Magnetic Heat Discoloration)
 */
void pattern_palladiumDecay() {
  static unsigned long lastUpdate = 0;
  if (millis() - lastUpdate >= 20) {
    lastUpdate = millis();
    
    uint16_t motionTime = millis() / 2;
    for (uint8_t r = 0; r < NUM_RINGS; r++) {
      uint8_t startIdx = ringStarts[r];
      uint8_t size = ringSizes[r];
      for (uint8_t i = 0; i < size; i++) {
        uint8_t fluidNoise = inoise8(startIdx * 10 + i * 35, motionTime);
        
        if (fluidNoise > 170) {
          leds[startIdx + i] = CRGB(20, 210, 130);
        } else if (fluidNoise > 100) {
          leds[startIdx + i] = CRGB(220, 75, 0);
        } else {
          leds[startIdx + i] = CRGB(0, 90, 180);
        }
      }
    }
    FastLED.show();
  }
}

/**
 * 14. Vibranium Overload (High-Density Ring Swarm Accelerator)
 */
void pattern_vibraniumOverload() {
  static unsigned long lastUpdate = 0;
  static uint16_t particleFrame = 0;
  
  if (millis() - lastUpdate >= 20) {
    lastUpdate = millis();
    
    uint8_t ambientPulse = beatsin8(60, 90, 150);
    for (uint16_t i = 0; i < NUM_LEDS; i++) {
      leds[i] = CRGB(0, ambientPulse / 3, ambientPulse);
    }
    
    for (uint8_t r = 0; r < NUM_RINGS - 1; r++) {
      uint8_t size = ringSizes[r];
      uint8_t start = ringStarts[r];
      
      uint8_t posCW  = particleFrame % size;
      uint8_t posCCW = (size - 1) - (particleFrame % size);
      
      leds[start + posCW] = CRGB(255, 255, 255);
      leds[start + posCCW] = CRGB(0, 235, 255);
      
      if (size >= 16) {
        uint8_t antiPosCW = (posCW + (size / 2)) % size;
        leds[start + antiPosCW] = CRGB(0, 200, 255);
      }
    }
    leds[92] = CRGB::White; 
    FastLED.show();
    particleFrame++;
  }
}

/**
 * 15. Stark Segment Test (Geometric Rotary Scanning Diagnostics)
 */
void pattern_starkSegmentTest() {
  static unsigned long lastUpdate = 0;
  if (millis() - lastUpdate >= 15) {
    lastUpdate = millis();
    
    uint8_t radarAngle = (millis() / 5) % 255;
    
    for (uint8_t r = 0; r < NUM_RINGS; r++) {
      uint8_t startIdx = ringStarts[r];
      uint8_t size = ringSizes[r];
      
      for (uint8_t i = 0; i < size; i++) {
        uint8_t pixelAngle = (i * 256) / size;
        uint8_t deltaAngle = radarAngle - pixelAngle;
        uint8_t trailIntensity = 255 - deltaAngle;
        uint8_t finalGlow = map(trailIntensity, 0, 255, 100, 255);
        
        leds[startIdx + i] = CRGB(scale8(finalGlow, 50), scale8(finalGlow, 200), finalGlow);
      }
    }
    FastLED.show();
  }
}

// ============================================================================
// SECTION 5: HARDWARE INTERRUPT SWITCHBOARD DRIVER
// Manages button debounce and shifts pattern indices instantly.
// ============================================================================
void handleButtonInterrupt() {
  bool pinState = digitalRead(BUTTON_PIN);
  static unsigned long lastDebounceTime = 0;
  unsigned long interruptTime = millis();

  if (pinState == LOW) {
    buttonIsPressed = true;
    if (interruptTime - lastDebounceTime > 250) {
      currentPatternIndex++;
      if (currentPatternIndex >= TOTAL_PATTERNS) {
        currentPatternIndex = 0;
      }
      lastDebounceTime = interruptTime;
    }
  } else {
    buttonIsPressed = false;
  }
}
