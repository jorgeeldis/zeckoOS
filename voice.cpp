#include "asr.h"
#include "unihiker_k10.h"

UNIHIKER_K10 k10;
ASR asr;

void setup() {
    k10.begin();
    asr.asrInit(CONTINUOUS, EN_MODE, 6000);
    delay(3000);
    asr.addASRCommand(1, "Switch on");
}

void loop() {

    if (asr.isWakeUp()) {
    }

    if (asr.isDetectCmdID(1)) {
        k10.rgb->brightness(round(9));
        k10.rgb->write(-1, 0xFF0000);
    }
}