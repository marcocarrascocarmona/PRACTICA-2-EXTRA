#include <Arduino.h>

#define LED_PIN 2
#define BTN_UP 18
#define BTN_DOWN 19

hw_timer_t *timer = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

volatile bool ledState = false;
volatile int blinkFrequency = 2;
volatile int counter = 0;

volatile bool lastUpState = HIGH;
volatile bool lastDownState = HIGH;

volatile int debounceUp = 0;
volatile int debounceDown = 0;

const int debounceLimit = 5;

void IRAM_ATTR onTimer() {

    portENTER_CRITICAL_ISR(&timerMux);

    counter++;

    int threshold = 500 / blinkFrequency;

    if (counter >= threshold) {
        ledState = !ledState;
        digitalWrite(LED_PIN, ledState);
        counter = 0;
    }

    bool upState = digitalRead(BTN_UP);
    bool downState = digitalRead(BTN_DOWN);

    if (upState != lastUpState) {
        debounceUp++;
        if (debounceUp >= debounceLimit) {
            if (upState == LOW) {
                blinkFrequency++;
                if (blinkFrequency > 10) blinkFrequency = 10;
            }
            lastUpState = upState;
            debounceUp = 0;
        }
    } else {
        debounceUp = 0;
    }

    if (downState != lastDownState) {
        debounceDown++;
        if (debounceDown >= debounceLimit) {
            if (downState == LOW) {
                blinkFrequency--;
                if (blinkFrequency < 1) blinkFrequency = 1;
            }
            lastDownState = downState;
            debounceDown = 0;
        }
    } else {
        debounceDown = 0;
    }

    portEXIT_CRITICAL_ISR(&timerMux);
}

void setup() {

    pinMode(LED_PIN, OUTPUT);
    pinMode(BTN_UP, INPUT_PULLUP);
    pinMode(BTN_DOWN, INPUT_PULLUP);

    timer = timerBegin(0, 80, true);

    timerAttachInterrupt(timer, &onTimer, true);

    timerAlarmWrite(timer, 1000, true);

    timerAlarmEnable(timer);
}

void loop() {

}