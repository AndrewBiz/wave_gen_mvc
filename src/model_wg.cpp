/*
    AD9850 DDS based wave generator built on MVC pattern
    Andrew Bizyaev (ANB) github.com/andrewbiz

    'Model' part pf MVC pattern
*/

#include "include/model_wg.hpp"

ModelWG::ModelWG() :
    _freq(DefFreq),
    _step_level_index_f(DefStepLevelIndexF),
    _tword(DefTword),
    _step_level_index_t(DefStepLevelIndexT),
    _clock(DefClock),
    _step_level_index_c(DefStepLevelIndexC)
{
    initialize();
}

constexpr uint32_t ModelWG::StepLevel[];

void ModelWG::initialize() {
    _calculate_tword();
}

void ModelWG::save_to_memory(int memory_slot) {
};

void ModelWG::load_from_memory(int memory_slot) {
};

void ModelWG::_calculate_freq() {
    _freq = ((uint64_t)_tword * (uint64_t)_clock) >> 32;
};

void ModelWG::_calculate_tword() {
    _tword = ((uint64_t)_freq << 32) / _clock;
};

void ModelWG::change_freq(int8_t steps) {
    int32_t delta = get_step_level_f() * steps;
    if (delta < 0) {
        _freq = (_freq >= uint32_t(-delta)) ? _freq + delta : _freq;
    } else {
        _freq = (_freq + delta <= MaxFreq) ? _freq + delta : _freq;
    }
    _calculate_tword();
    notify_observers();
    // TODO send to DDS
}

void ModelWG::next_step_level_f() {
    _step_level_index_f = (_step_level_index_f + 1 >= MaxStepLevelsF) ? MaxStepLevelsF - 1 : _step_level_index_f + 1;
    notify_observers();
}

void ModelWG::prev_step_level_f() {
    _step_level_index_f = (_step_level_index_f - 1 < 0) ? 0 : _step_level_index_f - 1;
    notify_observers();
}

uint32_t ModelWG::get_freq() {
    return _freq;
}

uint32_t ModelWG::get_step_level_f() {
    return StepLevel[_step_level_index_f];
}

void ModelWG::change_tword(int8_t steps) {
    int32_t delta = get_step_level_t() * steps;
    if (delta < 0) {
        _tword = (_tword >= uint32_t(-delta)) ? _tword + delta : _tword;
    } else {
        _tword = (_tword + delta <= MaxTword) ? _tword + delta : _tword;
    }
    _calculate_freq();
    notify_observers();
    // TODO send to DDS
}

void ModelWG::next_step_level_t() {
    _step_level_index_t = (_step_level_index_t + 1 >= MaxStepLevelsT) ? MaxStepLevelsT - 1 : _step_level_index_t + 1;
    notify_observers();
}

void ModelWG::prev_step_level_t() {
    _step_level_index_t = (_step_level_index_t - 1 < 0) ? 0 : _step_level_index_t - 1;
    notify_observers();
}

uint32_t ModelWG::get_tword() {
    return _tword;
}

uint32_t ModelWG::get_step_level_t() {
    return StepLevel[_step_level_index_t];
}

void ModelWG::change_clock(int8_t steps) {
    int32_t delta = get_step_level_c() * steps;
    if (delta < 0) {
        _clock = (_clock + delta >= DefClock - ThresholdClock) ? _clock + delta : _clock;
    } else {
        _clock = (_clock + delta <= DefClock + ThresholdClock) ? _clock + delta : _clock;
    }
    _calculate_tword();
    notify_observers();
    // TODO send to DDS
}

void ModelWG::next_step_level_c() {
    _step_level_index_c = (_step_level_index_c + 1 >= MaxStepLevelsC) ? MaxStepLevelsC - 1 : _step_level_index_c + 1;
    notify_observers();
}

void ModelWG::prev_step_level_c() {
    _step_level_index_c = (_step_level_index_c - 1 < 0) ? 0 : _step_level_index_c - 1;
    notify_observers();
}

uint32_t ModelWG::get_clock() {
    return _clock;
}

uint32_t ModelWG::get_step_level_c() {
    return StepLevel[_step_level_index_c];
}
