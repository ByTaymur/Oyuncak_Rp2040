# Oyuncak_RP2040 / Toy_RP2040

## English

This project is built for the Raspberry Pi Pico RP2040, combining audio playback, LED animation, and button interactions. It features an Adafruit NeoPixel LED strip, an SD card for storing audio files, and PWM audio playback. The project is designed to create interactive sound and light displays, responding to button presses with various animations and sound effects.

### Features

- **LED Control:** WS2812 LEDs are controlled using the Adafruit_NeoPixel library to create various light effects.
- **Audio Playback:** Plays audio files (in WAV format) from an SD card using PWM.
- **Button Interactions:** 5 buttons control which audio and LED effects are triggered.
- **Multicore Support:** The program uses both cores of the RP2040 for efficient operation, with one core handling LED animations and the other handling audio playback.

### Pin Configuration

- **NeoPixel (WS2812) LED Strip**
  - Pin: GPIO 3
  - Number of LEDs: 16

- **SD Card (SPI0)**
  - MISO (Master In Slave Out): GPIO 4
  - MOSI (Master Out Slave In): GPIO 7
  - CS (Chip Select): GPIO 5
  - SCK (Clock): GPIO 6

- **Button Pins**
  - Button 1: GPIO 13
  - Button 2: GPIO 10
  - Button 3: GPIO 11
  - Button 4: GPIO 8
  - Button 5: GPIO 9

- **PWM Audio Pin**
  - PWM Audio Output: GPIO 2 (for playing WAV files)

### Required Libraries

- Adafruit_NeoPixel
- SD
- SPI
- PWMAudio

### How It Works

- **LED Animations:** Different animations such as rainbow cycles, color wipes, and white pulses are played depending on the button pressed.
- **Audio Playback:** Corresponding audio files stored on the SD card are played via PWM output when a button is pressed.
- **Multicore Execution:** One core handles the LED animation, while the other core reads and plays the audio files in sync.

### Setup Instructions

1. Connect your NeoPixel strip to GPIO 3.
2. Set up an SD card with WAV files. The supported files are listed in the code as `fileNames[]`.
3. Attach buttons to the GPIO pins as defined above.
4. Compile and upload the code to the RP2040 using the Arduino IDE. The program will read button inputs and respond with both audio and LED animations.

### License

This project is open-source and licensed under the MIT License.

## Türkçe / Turkish

Bu proje, ses çalma, LED animasyonu ve buton etkileşimlerini birleştiren Raspberry Pi Pico RP2040 için tasarlanmıştır. Proje, Adafruit NeoPixel LED şeridi, SD kart ile ses dosyalarını saklama ve PWM ile ses oynatma özelliklerini içerir. Etkileşimli ses ve ışık sistemleri oluşturmak için kullanılır.

### Özellikler

- **LED Kontrolü:** WS2812 LED'ler, Adafruit_NeoPixel kütüphanesi kullanılarak kontrol edilir ve çeşitli ışık efektleri oluşturulur.
- **Ses Oynatma:** WAV formatındaki ses dosyaları, SD karttan PWM ile çalınır.
- **Buton Etkileşimleri:** 5 buton, hangi ses ve LED efektlerinin tetikleneceğini kontrol eder.
- **Çok Çekirdek Desteği:** Program, RP2040'ın her iki çekirdeğini kullanarak LED animasyonları ve ses çalma eşzamanlı olarak gerçekleştirir.

### Pin Konfigürasyonu

- **NeoPixel (WS2812) LED Şerit**
  - Pin: GPIO 3
  - LED Sayısı: 16

- **SD Kart (SPI0)**
  - MISO (Master In Slave Out): GPIO 4
  - MOSI (Master Out Slave In): GPIO 7
  - CS (Chip Select): GPIO 5
  - SCK (Saat Sinyali): GPIO 6

- **Buton Pinleri**
  - Buton 1: GPIO 13
  - Buton 2: GPIO 10
  - Buton 3: GPIO 11
  - Buton 4: GPIO 8
  - Buton 5: GPIO 9

- **PWM Ses Pini**
  - PWM Ses Çıkışı: GPIO 2 (WAV dosyalarını çalmak için)

### Gerekli Kütüphaneler

- Adafruit_NeoPixel
- SD
- SPI
- PWMAudio

### Çalışma Prensibi

- **LED Animasyonları:** Butonlara basıldığında gökkuşağı döngüsü, renk silme, beyaz darbe gibi animasyonlar oynatılır.
- **Ses Oynatma:** Butonlara basıldığında, SD kartta depolanan ses dosyaları PWM çıkışı üzerinden çalınır.
- **Çok Çekirdekli Yürütme:** Bir çekirdek LED animasyonlarını kontrol ederken, diğer çekirdek ses dosyalarını okur ve oynatır.

### Kurulum Talimatları

1. NeoPixel şeridini GPIO 3'e bağlayın.
2. SD kartınıza WAV dosyalarını yükleyin. Desteklenen dosyalar, `fileNames[]` dizisinde listelenmiştir.
3. Butonları yukarıda tanımlanan GPIO pinlerine bağlayın.
4. Arduino IDE'yi kullanarak kodu RP2040'a yükleyin. Program, buton girişlerini okur ve hem ses hem de LED animasyonlarıyla yanıt verir.

### Lisans

Bu proje ByTaymur Lisansı altında açık kaynaklıdır.
