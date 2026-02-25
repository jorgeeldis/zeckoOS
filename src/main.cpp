#include "unihiker_k10.h"
#include "math.h"
#include <ctime>
#include <Wire.h>
#include "AIRecognition.h"
#include "asr.h"

// Source - https://stackoverflow.com/a/7748079
// Posted by Mysticial, modified by community. See post 'Timeline' for change history
// Retrieved 2026-02-23, License - CC BY-SA 3.0

void onButtonAPressed();
void onButtonBPressed();
void onButtonABPressed();
void startup();
void menu();
void camera();
void musicplayer();
void workout();
void zeckoai();
void weather();
void airecognition();
void animalrecognition();
void journal();

volatile uint8_t step = 0;
volatile uint8_t sets = 0;
volatile uint8_t reps = 0;
volatile int sec = 0;
volatile int minute = 0;
volatile int pressA = 0;
volatile int pressB = 0;
UNIHIKER_K10 k10;
uint8_t screen_dir = 2;
Music music;
AHT20 aht20;
int randomNumber = random(10000);
String filename = "S:/photo" + String(randomNumber) + ".bmp";
String voicerecord = "S:/sound" + String(randomNumber) + ".wav";

void setup()
{
    Wire.begin();
    k10.begin();
    k10.initScreen(screen_dir);
    k10.creatCanvas();
    k10.setScreenBackground(0x000000);
    k10.buttonA->setPressedCallback(onButtonAPressed);
    k10.buttonB->setPressedCallback(onButtonBPressed);
    k10.buttonAB->setPressedCallback(onButtonABPressed);
    k10.canvas->canvasClear();
    startup();
    delay(2000);
    menu();
}

void loop()
{
    k10.rgb->brightness(round(5));
    k10.rgb->write(-1, 0x008000);
    if (pressA == 4000 && pressB == 4000)
    {
        weather();
    }
    if (pressA == 7001)
    {
        k10.canvas->canvasClear();
        k10.canvas->canvasRectangle(1, 1, 239, 319, 0x1F51FF, 0x1F51FF, false);
        k10.canvas->canvasText("Recording", 10, 10, 0x008000, k10.canvas->eCNAndENFont24, 10, false);
        k10.canvas->updateCanvas();
        music.recordSaveToTFCard(voicerecord, 60);
        k10.canvas->canvasClear();
        k10.canvas->canvasRectangle(1, 1, 239, 319, 0x1F51FF, 0x1F51FF, false);
        k10.canvas->canvasText("Record complete", 10, 10, 0x008000, k10.canvas->eCNAndENFont24, 16, false);
        k10.canvas->updateCanvas();
        pressA = 7500;
    }
    if ((pressA >= 2000 && pressA <= 2999) && (pressB >= 2000 && pressB <= 2999))
    {
        workout();
    }
}

void startup()
{
    k10.canvas->canvasRectangle(1, 1, 239, 319, 0x1F51FF, 0x1F51FF, false);
    k10.canvas->canvasText("hi! this is zecko!", 20, 160, 0x008000, Canvas::eCNAndENFont24, 19, false);
    k10.canvas->updateCanvas();
}

void menu()
{
    k10.canvas->canvasClear();
    k10.canvas->canvasRectangle(1, 1, 239, 319, 0x1F51FF, 0x1F51FF, false);
    k10.canvas->canvasText("menu", 10, 10, 0x008000, Canvas::eCNAndENFont24, 5, false);
    k10.canvas->canvasText("camera", 10, 50, 0x008000, Canvas::eCNAndENFont24, 7, false);
    k10.canvas->canvasText("music player", 10, 80, 0x008000, Canvas::eCNAndENFont24, 13, false);
    k10.canvas->canvasText("workout", 10, 110, 0x008000, Canvas::eCNAndENFont24, 8, false);
    k10.canvas->canvasText("zecko ai", 10, 140, 0x008000, Canvas::eCNAndENFont24, 9, false);
    k10.canvas->canvasText("weather", 10, 170, 0x008000, Canvas::eCNAndENFont24, 8, false);
    k10.canvas->canvasText("ai recognition", 10, 200, 0x008000, Canvas::eCNAndENFont24, 15, false);
    k10.canvas->canvasText("animal recognition", 10, 230, 0x008000, Canvas::eCNAndENFont24, 19, false);
    k10.canvas->canvasText("journal", 10, 260, 0x008000, Canvas::eCNAndENFont24, 19, false);
    k10.canvas->updateCanvas();
}

void onButtonAPressed()
{
    pressA += 1;

    if (pressA == 1) // Select camera
    {
        music.playTone(220, 2000);
        k10.canvas->canvasText("camera", 10, 50, 0x1F51FF, Canvas::eCNAndENFont24, 7, false);
        k10.canvas->updateCanvas();
    }
    else if (pressA == 2) // Select music player
    {
        music.playTone(220, 2000);
        k10.canvas->canvasText("camera", 10, 50, 0x008000, Canvas::eCNAndENFont24, 7, false);
        k10.canvas->updateCanvas();
        k10.canvas->canvasText("music player", 10, 80, 0x1F51FF, Canvas::eCNAndENFont24, 13, false);
        k10.canvas->updateCanvas();
    }
    else if (pressA == 3) // Select workout
    {
        music.playTone(220, 2000);
        k10.canvas->canvasText("music player", 10, 80, 0x008000, Canvas::eCNAndENFont24, 13, false);
        k10.canvas->updateCanvas();
        k10.canvas->canvasText("workout", 10, 110, 0x1F51FF, Canvas::eCNAndENFont24, 8, false);
        k10.canvas->updateCanvas();
    }
    else if (pressA == 4) // Select zecko ai
    {
        music.playTone(220, 2000);
        k10.canvas->canvasText("workout", 10, 110, 0x008000, Canvas::eCNAndENFont24, 8, false);
        k10.canvas->updateCanvas();
        k10.canvas->canvasText("zecko ai", 10, 140, 0x1F51FF, Canvas::eCNAndENFont24, 9, false);
        k10.canvas->updateCanvas();
    }
    else if (pressA == 5) // Select weather
    {
        music.playTone(220, 2000);
        k10.canvas->canvasText("zecko ai", 10, 140, 0x008000, Canvas::eCNAndENFont24, 9, false);
        k10.canvas->updateCanvas();
        k10.canvas->canvasText("weather", 10, 170, 0x1F51FF, Canvas::eCNAndENFont24, 8, false);
        k10.canvas->updateCanvas();
    }
    else if (pressA == 6) // Select ai recognition
    {
        music.playTone(220, 2000);
        k10.canvas->canvasText("weather", 10, 170, 0x008000, Canvas::eCNAndENFont24, 8, false);
        k10.canvas->updateCanvas();
        k10.canvas->canvasText("ai recognition", 10, 200, 0x1F51FF, Canvas::eCNAndENFont24, 15, false);
        k10.canvas->updateCanvas();
    }
    else if (pressA == 7) // Select animal recognition
    {
        music.playTone(220, 2000);
        k10.canvas->canvasText("ai recognition", 10, 200, 0x008000, Canvas::eCNAndENFont24, 15, false);
        k10.canvas->updateCanvas();
        k10.canvas->canvasText("animal recognition", 10, 230, 0x1F51FF, Canvas::eCNAndENFont24, 19, false);
        k10.canvas->updateCanvas();
    }
    else if (pressA == 8) // Select journal
    {
        music.playTone(220, 2000);
        k10.canvas->canvasText("animal recognition", 10, 230, 0x008000, Canvas::eCNAndENFont24, 19, false);
        k10.canvas->updateCanvas();
        k10.canvas->canvasText("journal", 10, 260, 0x1F51FF, Canvas::eCNAndENFont24, 8, false);
        k10.canvas->updateCanvas();
    }
    else if (pressA == 9) // Select camera
    {
        music.playTone(220, 2000);
        k10.canvas->canvasText("journal", 10, 260, 0x008000, Canvas::eCNAndENFont24, 8, false);
        k10.canvas->updateCanvas();
        k10.canvas->canvasText("camera", 10, 50, 0x1F51FF, Canvas::eCNAndENFont24, 7, false);
        k10.canvas->updateCanvas();
        pressA = 1;
    }
    else if (pressA == 101)
    {
        k10.photoSaveToTFCard(filename);
    }
    else if (pressA == 1001)
    {
        k10.canvas->canvasClear();
        k10.canvas->canvasRectangle(1, 1, 239, 319, 0x1F51FF, 0x1F51FF, false);
        k10.canvas->canvasText("Playing...", 10, 10, 0x008000, Canvas::eCNAndENFont24, 20, false);
        k10.canvas->updateCanvas();
        music.playTFCardAudio("S:/car-horn.wav");
    }
    else if (pressA >= 2001 && pressA <= 2800)
    {
        sets++;
        reps = 0;
    }
}

void onButtonBPressed()
{

    if (pressB == 2000)
    {
        reps++;
    }

    switch (pressA)
    {
    case 1:
        pressA = 100;
        pressB = 100;
        music.playTone(220, 2000);
        camera();
        break;
    case 2:
        pressA = 1000;
        pressB = 1000;
        music.playTone(220, 2000);
        musicplayer();
        break;
    case 3:
        pressA = 2000;
        pressB = 2000;
        music.playTone(220, 2000);
        workout();
        break;
    case 4:
        pressA = 3000;
        pressB = 3000;
        music.playTone(220, 2000);
        zeckoai();
        break;
    case 5:
        pressA = 4000;
        pressB = 4000;
        music.playTone(220, 2000);
        weather();
        break;
    case 6:
        pressA = 5000;
        pressB = 5000;
        music.playTone(220, 2000);
        airecognition();
        break;
    case 7:
        pressA = 6000;
        pressB = 6000;
        music.playTone(220, 2000);
        animalrecognition();
        break;
    case 8:
        pressA = 7000;
        pressB = 7000;
        music.playTone(220, 2000);
        journal();
        break;
    }
}

void onButtonABPressed()
{
    menu();
    pressA = 0;
    pressB = 0;
}

void camera()
{
    k10.canvas->canvasClear();
    k10.initBgCamerImage();
    k10.creatCanvas();
    k10.initSDFile();
    k10.setBgCamerImage(true);
}

void musicplayer()
{
    k10.canvas->canvasClear();
    k10.initSDFile();
    k10.canvas->canvasRectangle(1, 1, 239, 319, 0x1F51FF, 0x1F51FF, false);
    k10.canvas->canvasText("Press A to play...", 10, 10, 0x008000, Canvas::eCNAndENFont24, 20, false);
    k10.canvas->updateCanvas();
}

void workout()
{
    if (((k10.getStrength())>1080)) {
        step += 1;
    }
    sec++;
    if (sec == 60)
    {
        minute++;
        sec = 0;
    }
    String StrSets = String(sets);
    String StrReps = String(reps);
    String StrStep = String(step);
    k10.canvas->canvasClear();
    k10.canvas->canvasRectangle(1, 1, 239, 319, 0x1F51FF, 0x1F51FF, false);
    k10.canvas->canvasText("Workout Station", 10, 10, 0x008000, Canvas::eCNAndENFont24, 16, false);
    k10.canvas->canvasText("Step Count: " + StrStep, 10, 50, 0x008000, Canvas::eCNAndENFont24, 16, false);
    k10.canvas->canvasText("Set: " + StrSets, 10, 80, 0x008000, Canvas::eCNAndENFont24, 16, false);
    k10.canvas->canvasText("Reps: " + StrReps, 10, 110, 0x008000, Canvas::eCNAndENFont24, 16, false);
    k10.canvas->canvasText("Time: ", 10, 140, 0x008000, Canvas::eCNAndENFont24, 16, false);
    k10.canvas->canvasText(" " + String(minute) + " : " + String(sec), 90, 220, 0x008000, Canvas::eCNAndENFont24, 16, false);
    k10.canvas->updateCanvas();
    delay(1000);
}

void weather()
{
    float temperatureC = aht20.getData(AHT20::eAHT20TempC) * 0.75;
    float humidity = aht20.getData(AHT20::eAHT20HumiRH) + 25;
    String Noise = String(k10.readMICData());
    String Temp = String(temperatureC);
    String Humid = String(humidity);
    String LAX = String(k10.readALS());
    k10.canvas->canvasClear();
    k10.canvas->canvasRectangle(1, 1, 239, 319, 0x1F51FF, 0x1F51FF, false);
    k10.canvas->canvasText("Weather Station", 10, 10, 0x008000, Canvas::eCNAndENFont24, 16, false);
    k10.canvas->canvasText("Temperature: " + Temp, 10, 50, 0x008000, Canvas::eCNAndENFont24, 20, false);
    k10.canvas->canvasText("Humidity: " + Humid, 10, 80, 0x008000, Canvas::eCNAndENFont24, 15, false);
    k10.canvas->canvasText("Intensity: " + LAX, 10, 110, 0x008000, Canvas::eCNAndENFont24, 18, false);
    k10.canvas->canvasText("Noise: " + Noise, 10, 140, 0x008000, Canvas::eCNAndENFont24, 18, false);
    k10.canvas->updateCanvas();
    delay(1000);
}

void journal()
{
    k10.canvas->canvasClear();
    k10.creatCanvas();
    k10.initSDFile();
    k10.canvas->canvasRectangle(1, 1, 239, 319, 0x1F51FF, 0x1F51FF, false);
    k10.canvas->canvasText("Press A to record.", 10, 10, 0x008000, k10.canvas->eCNAndENFont24, 50, false);
    k10.canvas->updateCanvas();
}

void zeckoai()
{
}

void airecognition()
{
}

void animalrecognition()
{
}