#include <Adafruit_NeoPixel.h>
#include <SPI.h>
#include <SD.h>
#include <PWMAudio.h>
#include <pico/multicore.h>

#define PIN 3          // WS2812 LED strip pin
#define NUMPIXELS 16   // Number of LEDs

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

// SD card pins for SPI0
const int _MISO = 4;  
const int _MOSI = 7;
const int _CS = 5;
const int _SCK = 6;

const int buttonPins[] = {13, 10, 11, 8, 9};
const int S = 10240; // Number of samples to read in block
uint8_t buffer[S]; 
const int16_t *start = (const int16_t *)buffer;
const int16_t *p = start;

const int numButtons = 5;

// Audio file names
const char* fileNames[] = {
  "AF.wav", "A.wav", "B.wav", "C.wav", "D.wav", "E.wav", "F.wav", "G.wav", "H.wav", "I.wav", "J.wav", "K.wav", "L.wav", 
  "M.wav", "N.wav", "O.wav", "P.wav", "Q.wav", "R.wav", "S.wav", "T.wav", "U.wav", "V.wav", "W.wav", "X.wav", "Y.wav", 
  "Z.wav", "AA.wav", "AB.wav", "AC.wav", "AD.wav", "AE.wav", "AF.wav"
};

int ButSanraki = 0;
PWMAudio pwm(2);

unsigned int count = 0;
void cb() {
  while (pwm.availableForWrite()) {
    int16_t sample = *p++;
    sample = sample * 2 > INT16_MAX ? INT16_MAX : sample * 2;
    pwm.write(sample);
    count += 2;
    if (count >= sizeof(buffer)) {
      count = 0;
      p = start;
    }
    for (int i = 0; i < numButtons; i++) {
      if (digitalRead(buttonPins[i]) == LOW) {
        ButSanraki = i + 1;
        break;
      }
    }
  }
}

void WavOpen() {
  File root = SD.open(fileNames[ButSanraki]);
  if (!root) {
    Serial.println("Ses dosyası açılamadı!");
    return;
  }
  Serial.println(fileNames[ButSanraki]);
  while (root.available()) {
    root.read(buffer, sizeof(buffer));
  }
}

void setup() {
  for (int i = 0; i < numButtons; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
  }
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);

  Serial.begin(115200);
  pwm.onTransmit(cb);
  pwm.begin(96000);

  Serial.println("\nInitializing SD card...");

  bool sdInitialized = false;
  if (_MISO == 0 || _MISO == 4 || _MISO == 16) {
    SPI.setRX(_MISO);
    SPI.setTX(_MOSI);
    SPI.setSCK(_SCK);
    sdInitialized = SD.begin(_CS);
  } else if (_MISO == 8 || _MISO == 12) {
    SPI1.setRX(_MISO);
    SPI1.setTX(_MOSI);
    SPI1.setSCK(_SCK);
    sdInitialized = SD.begin(_CS, SPI1);
  } else {
    Serial.println(F("ERROR: Unknown SPI Configuration"));
    return;
  }

  strip.begin();
  strip.show(); // Initialize all pixels to 'off'

  multicore_launch_core1(core1Loop);
}

void core1Loop() {
  while (true) {
    switch(ButSanraki) {
      case 1:
        rainbowCycle(20);
        break;
      case 2:
        theaterChaseRainbow(50);
        break;
      case 3:
        colorWipe(strip.Color(255, 0, 0), 50);  // Kırmızı
        colorWipe(strip.Color(0, 255, 0), 50);  // Yeşil
        colorWipe(strip.Color(0, 0, 255), 50);  // Mavi
        break;
      case 4:
        pulseWhite(5);
        break;
      case 5:
        rainbowWave(10);
        break;
      default:
        colorAll(strip.Color(255, 255, 255));  // Tüm LEDler beyaz
        delay(1000);
    }
  }
}

void rainbowCycle(uint8_t wait) {
  for(uint16_t j=0; j<256*5; j++) {
    for(uint16_t i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, Wheel( (i+j) % 255));
      }
      strip.show();
      delay(wait);
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);
      }
    }
  }
}

void colorWipe(uint32_t color, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, color);
    strip.show();
    delay(wait);
  }
}

void pulseWhite(uint8_t wait) {
  for(int j = 0; j < 256; j++) {
    for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, strip.Color(j,j,j));
    }
    strip.show();
    delay(wait);
  }
  for(int j = 255; j >= 0; j--) {
    for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, strip.Color(j,j,j));
    }
    strip.show();
    delay(wait);
  }
}

void rainbowWave(uint8_t wait) {
  for(uint16_t j=0; j<256*5; j++) {
    for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

void colorAll(uint32_t color) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, color);
  }
  strip.show();
}

uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

void loop() {
  WavOpen();
}