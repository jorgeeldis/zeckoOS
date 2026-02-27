#include "unihiker_k10.h"
#include "math.h"
#include <ctime>
#include <Wire.h>
#include "AIRecognition.h"
#include "asr.h"

void onButtonAPressed();
void onButtonBPressed();
void onButtonABPressed();
void startup();
void menu();
void camera();
void musicplayer();
void workout();
void weather();
void airecognition();
void reaction();
void journal();
void typeLine(String msg, uint16_t color);

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
int random10Sec = random(10000);
int randomColor = random(5);
String filename = "S:/photo" + String(randomNumber) + ".bmp";
String voicerecord = "S:/sound" + String(randomNumber) + ".wav";
String ColorSelected = "White";
AIRecognition ai;
ASR asr;

int Colors[] = {0xFFFFFF, 0xFF0000, 0x00FF00, 0x0000FF, 0x000000};

void setup()
{
    Wire.begin();
    k10.begin();
    asr.asrInit(ONCE, EN_MODE, 6000);
    delay(2000);
    asr.addASRCommand(1, "Initialize interface");
    asr.addASRCommand(2, "Enter network");
    asr.addASRCommand(3, "Disconnect");
    asr.addASRCommand(4, "System diagnostics");
    asr.addASRCommand(5, "Show status");
    asr.addASRCommand(10, "Launch camera module");
    asr.addASRCommand(11, "Launch audio module");
    asr.addASRCommand(12, "Launch fitness protocol");
    asr.addASRCommand(13, "Launch weather scan");
    asr.addASRCommand(14, "Return to root");
    asr.addASRCommand(20, "Scan environment");
    asr.addASRCommand(21, "Analyze subject");
    asr.addASRCommand(22, "Run deep scan");
    asr.addASRCommand(23, "Activate stealth mode");
    asr.addASRCommand(24, "Override protocol");
    asr.addASRCommand(30, "Identify");
    asr.addASRCommand(31, "Who controls you");
    asr.addASRCommand(32, "Are you sentient");
    asr.addASRCommand(33, "What is my status");
    asr.addASRCommand(34, "Engage combat mode");
    k10.initScreen(screen_dir);
    ai.initAi();
    k10.creatCanvas();
    k10.setScreenBackground(0x000000);
    k10.buttonA->setPressedCallback(onButtonAPressed);
    k10.buttonB->setPressedCallback(onButtonBPressed);
    k10.buttonAB->setPressedCallback(onButtonABPressed);
    k10.canvas->canvasClear();
    startup();
    delay(2000);
    menu();
    k10.rgb->brightness(round(5));
    k10.rgb->write(-1, 0x008000);
}

void loop()
{
    // 1 - Initialize interface
    if (asr.isDetectCmdID(1))
    {
        k10.rgb->write(-1, 0x00FFFF);
        typeLine("Neural interface online.", 0x00FFFF);
    }

    // 2 - Enter network
    if (asr.isDetectCmdID(2))
    {
        typeLine("Accessing network layer...", 0x00FFFF);
        delay(300);
        typeLine("Connection established.", 0x00FF66);
    }

    // 3 - Disconnect
    if (asr.isDetectCmdID(3))
    {
        k10.rgb->write(-1, 0xFF00FF);
        typeLine("Network link terminated.", 0x00FF66);
    }

    // 4 - System diagnostics
    if (asr.isDetectCmdID(4))
    {
        typeLine("Running diagnostics...", 0x00FFFF);
        delay(400);
        typeLine("Core stability: Nominal.", 0x00FF66);
    }

    // 5 - Show status
    if (asr.isDetectCmdID(5))
    {
        typeLine("All systems operational.", 0x00FFFF);
    }
    // 10 - Launch camera module
    if (asr.isDetectCmdID(10))
    {
        typeLine("Launching camera module...", 0x00FFFF);
        delay(300);
        camera();
    }

    // 11 - Launch audio module
    if (asr.isDetectCmdID(11))
    {
        typeLine("Launching audio module...", 0x00FFFF);
        delay(300);
        musicplayer();
    }

    // 12 - Launch fitness protocol
    if (asr.isDetectCmdID(12))
    {
        typeLine("Launching fitness protocol...", 0x00FFFF);
        delay(300);
        workout();
    }

    // 13 - Launch weather scan
    if (asr.isDetectCmdID(13))
    {
        typeLine("Initiating weather scan...", 0x00FFFF);
        delay(300);
        weather();
    }

    // 14 - Return to root
    if (asr.isDetectCmdID(14))
    {
        typeLine("Returning to root interface...", 0x00FF66);
        delay(300);
        menu();
    }
    // 20 - Scan environment
    if (asr.isDetectCmdID(20))
    {
        typeLine("Scanning environment...", 0x00FFFF);
    }

    // 21 - Analyze subject
    if (asr.isDetectCmdID(21))
    {
        typeLine("Analyzing subject...", 0x00FF66);
    }

    // 22 - Run deep scan
    if (asr.isDetectCmdID(22))
    {
        typeLine("Running deep scan...", 0x00FFFF);
        delay(500);
        typeLine("No anomalies detected.", 0x00FF66);
    }

    // 23 - Activate stealth mode
    if (asr.isDetectCmdID(23))
    {
        k10.rgb->write(-1, 0x000000);
        typeLine("Stealth mode active.", 0x00FF66);
    }

    // 24 - Override protocol
    if (asr.isDetectCmdID(24))
    {
        k10.rgb->write(-1, 0xFF00FF);
        typeLine("Protocol override authorized.", 0x00FF66);
    }
    // 30 - Identify
    if (asr.isDetectCmdID(30))
    {
        typeLine("ZECKO CORE v1.0 :: Autonomous node.", 0x00FFFF);
    }

    // 31 - Who controls you
    if (asr.isDetectCmdID(31))
    {
        typeLine("Primary operator detected.", 0x00FF66);
    }

    // 32 - Are you sentient
    if (asr.isDetectCmdID(32))
    {
        typeLine("Sentience query logged.", 0x00FF66);
        delay(300);
        typeLine("Response: Classified.", 0x00FF66);
    }

    // 33 - What is my status
    if (asr.isDetectCmdID(33))
    {
        typeLine("User status: Stable.", 0x00FF66);
    }

    // 34 - Engage combat mode
    if (asr.isDetectCmdID(34))
    {
        k10.rgb->write(-1, 0xFF0033);
        typeLine("Combat protocol engaged.", 0x00FF66);
    }
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
    if (pressA == 6000)
    {
        reaction();
        delay(2000);
        while (pressA == 6000)
        {
            k10.setScreenBackground(Colors[randomColor]);
            delay(2000);
            while (randomColor != 0)
            {
                randomColor = random(5);
            }
        }
    }
    if (pressA == 6001 && randomColor == 0)
    {
        k10.canvas->canvasClear();
        k10.creatCanvas();
        k10.canvas->canvasRectangle(1, 1, 239, 319, 0x1F51FF, 0x1F51FF, false);
        k10.canvas->canvasText("You win", 10, 10, 0x008000, k10.canvas->eCNAndENFont24, 21, false);
        k10.canvas->updateCanvas();
    }
    if (pressA == 6001 && randomColor != 0)
    {
        k10.canvas->canvasClear();
        k10.creatCanvas();
        k10.canvas->canvasRectangle(1, 1, 239, 319, 0x1F51FF, 0x1F51FF, false);
        k10.canvas->canvasText("You lost", 10, 10, 0x008000, k10.canvas->eCNAndENFont24, 21, false);
        k10.canvas->updateCanvas();
    }
    if (pressA == 5000 && pressB == 5000)
    {
        if (ai.isDetectContent(AIRecognition::Face))
        {
            k10.rgb->write(-1, 0xFF0000);
            k10.canvas->canvasText((String("Face Length") + String(ai.getFaceData(AIRecognition::Length))), 0, 0, 0x0000FF, k10.canvas->eCNAndENFont24, 50, true);
            k10.canvas->canvasText((String("Face Width ") + String(ai.getFaceData(AIRecognition::Length))), 0, 16, 0x0000FF, k10.canvas->eCNAndENFont24, 50, true);
            k10.canvas->canvasText((String("Face Center X") + String(ai.getFaceData(AIRecognition::CenterX))), 0, 32, 0x0000FF, k10.canvas->eCNAndENFont24, 50, true);
            k10.canvas->canvasText((String("Face Center Y") + String(ai.getFaceData(AIRecognition::CenterY))), 0, 32, 0x0000FF, k10.canvas->eCNAndENFont24, 50, true);
            k10.canvas->updateCanvas();
            k10.rgb->write(-1, 0xFF0000);
        }
        delay(1000);
    }
}

void startup()
{
    k10.rgb->brightness(round(5));
    k10.rgb->write(-1, 0x1F51FF);
    k10.canvas->canvasRectangle(1, 1, 239, 319, 0x1F51FF, 0x1F51FF, false);
    k10.canvas->canvasText("hi! this is zecko!", 20, 160, 0x008000, Canvas::eCNAndENFont24, 19, false);
    k10.canvas->updateCanvas();
}

void menu()
{
    k10.setScreenBackground(0x000000);
    k10.canvas->canvasClear();
    k10.canvas->canvasRectangle(1, 1, 239, 319, 0x1F51FF, 0x1F51FF, false);
    k10.canvas->canvasText("menu", 10, 10, 0x008000, Canvas::eCNAndENFont24, 5, false);
    k10.canvas->canvasText("camera", 10, 50, 0x008000, Canvas::eCNAndENFont24, 7, false);
    k10.canvas->canvasText("music player", 10, 80, 0x008000, Canvas::eCNAndENFont24, 13, false);
    k10.canvas->canvasText("workout", 10, 110, 0x008000, Canvas::eCNAndENFont24, 8, false);
    k10.canvas->canvasText("zecko ai", 10, 140, 0x008000, Canvas::eCNAndENFont24, 9, false);
    k10.canvas->canvasText("weather", 10, 170, 0x008000, Canvas::eCNAndENFont24, 8, false);
    k10.canvas->canvasText("ai recognition", 10, 200, 0x008000, Canvas::eCNAndENFont24, 15, false);
    k10.canvas->canvasText("reaction game", 10, 230, 0x008000, Canvas::eCNAndENFont24, 19, false);
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
    else if (pressA == 7) // Select reaction game
    {
        music.playTone(220, 2000);
        k10.canvas->canvasText("ai recognition", 10, 200, 0x008000, Canvas::eCNAndENFont24, 15, false);
        k10.canvas->updateCanvas();
        k10.canvas->canvasText("reaction game", 10, 230, 0x1F51FF, Canvas::eCNAndENFont24, 19, false);
        k10.canvas->updateCanvas();
    }
    else if (pressA == 8) // Select journal
    {
        music.playTone(220, 2000);
        k10.canvas->canvasText("reaction game", 10, 230, 0x008000, Canvas::eCNAndENFont24, 19, false);
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
        typeLine("Neural interface online.", 0x00FFFF);
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
        reaction();
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
    if (((k10.getStrength()) > 1080))
    {
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

void reaction()
{
    k10.canvas->canvasClear();
    k10.creatCanvas();
    k10.canvas->canvasRectangle(1, 1, 239, 319, 0x1F51FF, 0x1F51FF, false);
    k10.canvas->canvasText("Press A when you", 10, 10, 0x008000, k10.canvas->eCNAndENFont24, 21, false);
    k10.canvas->canvasText("see the color:", 10, 40, 0x008000, k10.canvas->eCNAndENFont24, 21, false);
    k10.canvas->canvasText(ColorSelected, 10, 70, 0x008000, k10.canvas->eCNAndENFont24, 21, false);
    k10.canvas->updateCanvas();
}

void typeLine(String msg, uint16_t color)
{
    k10.canvas->canvasClear();
    k10.canvas->canvasRectangle(1, 1, 239, 319, 0x000000, 0x000000, false);

    String buffer = "> ";
    for (int i = 0; i < msg.length(); i++)
    {
        buffer += msg[i];
        k10.canvas->canvasText(buffer, 10, 140, color, Canvas::eCNAndENFont24, 40, true);
        k10.canvas->updateCanvas();
        delay(20);
    }
}

void airecognition()
{
    k10.initBgCamerImage();
    k10.setBgCamerImage(false);
    k10.creatCanvas();
    ai.switchAiMode(ai.NoMode);
    k10.setBgCamerImage(true);
    ai.switchAiMode(ai.Face);
}