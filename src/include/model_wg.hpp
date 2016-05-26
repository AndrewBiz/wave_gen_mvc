/*
    AD9850 DDS based wave generator built on MVC pattern
    Andrew Bizyaev (ANB) github.com/andrewbiz

    'Model' part pf MVC pattern
*/

#ifndef MODEL_WG_HPP
#define MODEL_WG_HPP

#define DDS_DEVICE "AD9850"

#include "model.hpp"
#include <stdint.h>

class ModelWG : public Model {
public:
    ModelWG();
    void initialize();
    void save_to_memory(int memory_slot);
    void load_from_memory(int memory_slot);

    void change_freq(int8_t steps);
    uint32_t get_freq();
    uint32_t get_step_level_f();
    void next_step_level_f();
    void prev_step_level_f();

    void change_tword(int8_t steps);
    uint32_t get_tword();
    uint32_t get_step_level_t();
    void next_step_level_t();
    void prev_step_level_t();

    void change_clock(int8_t steps);
    uint32_t get_clock();
    uint32_t get_step_level_c();
    void next_step_level_c();
    void prev_step_level_c();

protected:
    static constexpr uint32_t StepLevel[] = { 1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000 };

    static const uint32_t DefFreq = 1000;
    static const uint32_t MaxFreq = 20000000;
    static const uint32_t MinFreq = 0;
    static const uint8_t MaxStepLevelsF = 7;
    static const uint8_t DefStepLevelIndexF = 3;

    static const uint32_t DefTword = 1000;
    static const uint32_t MaxTword = 690000000;
    static const uint32_t MinTword = 0;
    static const uint8_t MaxStepLevelsT = 9;
    static const uint8_t DefStepLevelIndexT = 4;

    static const uint32_t DefClock = 125000000;
    static const uint32_t ThresholdClock = 20000000;
    static const uint8_t MaxStepLevelsC = 5;
    static const uint8_t DefStepLevelIndexC = 0;
private:
    uint32_t _freq;    //  Frequency expected from DDS output
    uint8_t _step_level_index_f;

    uint32_t _tword;   // TWORD to set into DDS chip
    uint8_t _step_level_index_t;

    uint32_t _clock;   // Clock of DD chip
    uint8_t _step_level_index_c;

    void _calculate_freq();
    void _calculate_tword();
};
#endif
