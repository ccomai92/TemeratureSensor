#include <math.h>

double V_IN = 5.0;             // V_in = 5v
double RESISTANCE_1 = 10000.0; // R1 = 10k ohm
double A = -1.491749559e-3;    // calculated Steinhart-Hart model coefficient
double B = 5.185511356e-4;     // calculated Steinhart-Hart model coefficient
double C = -7.367418029e-7;    // calculated Steinhart-Hart model coefficient
unsigned int UINT_MAX = 65535;

unsigned int timerCounter;
double rawADC;
bool isRawADCRead;
unsigned int timeStamp;

void setup()
{
    // initialize serial port
    Serial.begin(9600);

    // set timer interrupt
    SetTimerInterrupt();

    // initialize global variables
    timerCounter = 0;
    isRawADCRead = false;
    timeStamp = 0;
}

void loop()
{
    if (isRawADCRead)
    {
        cli();
        // Convert analog Value to resistance
        double r2 = RESISTANCE_1 / (1023 / rawADC - 1);
        isRawADCRead = false;
        sei();

        Serial.print("TimeStamp [");
        Serial.print(timeStamp);
        Serial.print("]: ");
        // Serial.print("resistance Value: ");
        // Serial.println(r2);

        double tempKelvin = 1 / (A + (B * log(r2)) + (C * pow(log(r2), 3)));
        Serial.println(1.8 * (tempKelvin - 273.15) + 32);
        // Serial.print("Temperature (K): ");
        // Serial.println(tempKelvin);
        // Serial.print("Temperature (C): ");
        // Serial.println(tempKelvin - 273.15);
        // Serial.print("Temperature (F): ");

        timeStamp %= UINT_MAX; // to prevent overflow
        timeStamp++;
    }
}

void SetTimerInterrupt()
{
    Serial.println("Set TimerInterrupt");
    cli();                      // stop interrupts
    TCCR1A = 0;                 // set entire TCCR0A register to 0
    TCCR1B = 0;                 // set entire TCCR0B register to 0
    TCNT1 = 0;                  // initialize counter value to 0

    OCR1A = 15624;              // (16*10^6) / (1024 * 1Hz) - 1 =  (must be <65536)

    TCCR1B |= B00000101;        // set 1024 prescalar
    TIMSK1 |= B00000010;        // set OCIE1A to 1 so we enable compare match A
    sei();                      // enbale back the interrupts
}

ISR(TIMER1_COMPA_vect)
{
    TCNT1 = 0;
    if (timerCounter == 10)
    {
        rawADC = analogRead(0);
        isRawADCRead = true;
        timerCounter = 0;
    }
    else
    {
        timerCounter++;
    }
    // Serial.println(timerCounter);
}
