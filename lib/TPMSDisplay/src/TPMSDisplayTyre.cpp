#ifdef ENABLE_TPMS_DISPLAY

#include "TPMSDisplayTyre.h"

#include "RC3Conv.h"

double TPMSDisplay::Tyre::lastFLP(0.0);
double TPMSDisplay::Tyre::lastFLT(0.0);
double TPMSDisplay::Tyre::lastFRP(0.0);
double TPMSDisplay::Tyre::lastFRT(0.0);
double TPMSDisplay::Tyre::lastRLP(0.0);
double TPMSDisplay::Tyre::lastRLT(0.0);
double TPMSDisplay::Tyre::lastRRP(0.0);
double TPMSDisplay::Tyre::lastRRT(0.0);

bool TPMSDisplay::Tyre::areDiff(const double value1, const double value2) {
    return (!isnan(value1) && value1 != value2) ||
        (isnan(value1) && !isnan(value2));
}

unsigned int TPMSDisplay::Tyre::pressureColor(const double value) {
    return value < 2.0 ? TFT_BLUE : TFT_GREEN;
}

unsigned int TPMSDisplay::Tyre::temperatureColor(const double value) {
    return value < 25.0 ? TFT_BLUE : TFT_GREEN;
}

void TPMSDisplay::Tyre::renderFL(const double pressure, const double temperature)
{
    bool changeTyreColor(false);

    if (TPMSDisplay::Tyre::areDiff(pressure, TPMSDisplay::Tyre::lastFLP))
    {
        tft.fillRect(55, 5, 50, 26, TFT_BLACK);
        tft.setTextColor(TPMSDisplay::Tyre::pressureColor(pressure), TFT_BLACK);
        std::string FLP((isnan(pressure) ? "-" : RC3::toFixed(pressure, 0)) + " k");
        tft.drawString(FLP.c_str(), 55, 5, 4);

        TPMSDisplay::Tyre::lastFLP = pressure;
        changeTyreColor = true;
    }
    if (TPMSDisplay::Tyre::areDiff(temperature, TPMSDisplay::Tyre::lastFLT))
    {
        tft.fillRect(55, 39, 50, 26, TFT_BLACK);
        tft.setTextColor(TPMSDisplay::Tyre::temperatureColor(temperature), TFT_BLACK);
        std::string FLT((isnan(temperature) ? "-" : RC3::toFixed(temperature, 0)) + " C");
        tft.drawString(FLT.c_str(), 55, 38, 4);

        TPMSDisplay::Tyre::lastFLT = pressure;
        changeTyreColor = true;
    }

    if (changeTyreColor)
    {
        tft.fillRoundRect(5, 5, 40, 57, 10, TPMSDisplay::Tyre::temperatureColor(temperature));
        tft.setTextColor(temperature < 30.0 ? TFT_WHITE : TFT_BLACK, TPMSDisplay::Tyre::temperatureColor(temperature));
        tft.drawString("FL", 10, 23, 4);
    }
}

void TPMSDisplay::Tyre::renderFR(const double pressure, const double temperature)
{
    bool changeTyreColor(false);

    if (TPMSDisplay::Tyre::areDiff(pressure, TPMSDisplay::Tyre::lastFRP))
    {
        tft.fillRect(125, 5, 50, 26, TFT_BLACK);
        tft.setTextColor(TPMSDisplay::Tyre::pressureColor(pressure), TFT_BLACK);
        std::string FRP((isnan(pressure) ? "-" : RC3::toFixed(pressure, 0)) + " k");
        tft.drawString(FRP.c_str(), 125, 5, 4);

        TPMSDisplay::Tyre::lastFRP = pressure;
        changeTyreColor = true;
    }
    if (TPMSDisplay::Tyre::areDiff(temperature, TPMSDisplay::Tyre::lastFRT))
    {
        tft.fillRect(125, 38, 50, 26, TFT_BLACK);
        tft.setTextColor(TPMSDisplay::Tyre::temperatureColor(temperature), TFT_BLACK);
        std::string FRT((isnan(temperature) ? "-" : RC3::toFixed(temperature, 0)) + " C");
        tft.drawString(FRT.c_str(), 125, 38, 4);

        TPMSDisplay::Tyre::lastFRT = pressure;
        changeTyreColor = true;
    }

    if (changeTyreColor)
    {
        tft.fillRoundRect(195, 5, 40, 57, 10, TPMSDisplay::Tyre::temperatureColor(temperature));
        tft.setTextColor(temperature < 30.0 ? TFT_WHITE : TFT_BLACK, TPMSDisplay::Tyre::temperatureColor(temperature));
        tft.drawString("FR", 200, 23, 4);
    }
}

void TPMSDisplay::Tyre::renderRL(const double pressure, const double temperature)
{
    bool changeTyreColor(false);

    if (TPMSDisplay::Tyre::areDiff(pressure, TPMSDisplay::Tyre::lastRLP))
    {
        tft.fillRect(55, 72, 50, 26, TFT_BLACK);
        tft.setTextColor(TPMSDisplay::Tyre::pressureColor(pressure), TFT_BLACK);
        std::string RLP((isnan(pressure) ? "-" : RC3::toFixed(pressure, 0)) + " k");
        tft.drawString(RLP.c_str(), 55, 72, 4);

        TPMSDisplay::Tyre::lastRLP = pressure;
        changeTyreColor = true;
    }
    if (TPMSDisplay::Tyre::areDiff(temperature, TPMSDisplay::Tyre::lastRLT))
    {
        tft.fillRect(55, 105, 50, 26, TFT_BLACK);
        tft.setTextColor(TPMSDisplay::Tyre::temperatureColor(temperature), TFT_BLACK);
        std::string RLT((isnan(temperature) ? "-" : RC3::toFixed(temperature, 0)) + " C");
        tft.drawString(RLT.c_str(), 55, 105, 4);

        TPMSDisplay::Tyre::lastRLT = pressure;
        changeTyreColor = true;
    }

    if (changeTyreColor)
    {
        tft.fillRoundRect(5, 72, 40, 57, 10, TPMSDisplay::Tyre::temperatureColor(temperature));
        tft.setTextColor(temperature < 30.0 ? TFT_WHITE : TFT_BLACK, TPMSDisplay::Tyre::temperatureColor(temperature));
        tft.drawString("RL", 10, 90, 4);
    }
}

void TPMSDisplay::Tyre::renderRR(const double pressure, const double temperature)
{
    bool changeTyreColor(false);

    if (TPMSDisplay::Tyre::areDiff(pressure, TPMSDisplay::Tyre::lastRRP))
    {
        tft.fillRect(125, 72, 50, 26, TFT_BLACK);
        tft.setTextColor(TPMSDisplay::Tyre::pressureColor(pressure), TFT_BLACK);
        std::string RRP((isnan(pressure) ? "-" : RC3::toFixed(pressure, 0)) + " k");
        tft.drawString(RRP.c_str(), 125, 72, 4);

        TPMSDisplay::Tyre::lastRRP = pressure;
        changeTyreColor = true;
    }
    if (TPMSDisplay::Tyre::areDiff(temperature, TPMSDisplay::Tyre::lastRRT))
    {
        tft.fillRect(125, 105, 50, 26, TFT_BLACK);
        tft.setTextColor(TPMSDisplay::Tyre::temperatureColor(temperature), TFT_BLACK);
        std::string RRT((isnan(temperature) ? "-" : RC3::toFixed(temperature, 0)) + " C");
        tft.drawString(RRT.c_str(), 125, 105, 4);

        TPMSDisplay::Tyre::lastRRT = pressure;
        changeTyreColor = true;
    }

    if (changeTyreColor)
    {
        tft.fillRoundRect(195, 72, 40, 57, 10, TPMSDisplay::Tyre::temperatureColor(temperature));
        tft.setTextColor(temperature < 25.0 ? TFT_WHITE : TFT_BLACK, TPMSDisplay::Tyre::temperatureColor(temperature));
        tft.drawString("RR", 200, 90, 4);
    }
}

#endif
