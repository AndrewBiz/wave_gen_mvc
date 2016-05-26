/*
    AD9850 DDS based wave generator built on MVC pattern
    Andrew Bizyaev (ANB) github.com/andrewbiz
*/
#include "include/wave_gen.hpp"
#include "include/model_wg.hpp"

// Global variables
ModelWG * model;

void setup()
{
    Log.Init(LOGLEVEL, 38400L, LOG_PRINT_TS, LOG_AUTO_LN);
    Log.Info(F("Starting DDS " DDS_DEVICE " Wave_Gen, version " WAVE_GEN_VERSION));

    model = new ModelWG;
} // setup

void loop()
{
    Serial.println(model->get_freq());
    delay(1000);

    Serial.println(model->get_tword());
    delay(1000);

    Serial.println(model->get_clock());
    delay(1000);

    Serial.println(sizeof(*model));
    delay(1000);

} // function loop
