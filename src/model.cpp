/*
    AD9850 DDS based wave generator built on MVC pattern
    Andrew Bizyaev (ANB) github.com/andrewbiz

    'Model' part pf MVC pattern
*/
#include "include/model.hpp"

Model::Model() :
    _number_observers(0)
{
    for (size_t i = 0; i < MaxObservers; i++) {
        _observer[i] = nullptr;
    };
}

Model::~Model() {
    for (size_t i = 0; i < MaxObservers; i++) {
        _observer[i] = nullptr;
    };
}

void Model::attach_observer(View * v) {
    if (_number_observers < MaxObservers) {
        _observer[_number_observers++] = v;
    };
}

void Model::detach_observer(View * v) {
    if (_number_observers > 0) {
        _observer[--_number_observers] = nullptr;
    };
}

void Model::notify_observers() {
    for (size_t i = 0; i < MaxObservers; i++) {
        if (_observer[i] != nullptr) _observer[i]->update();
    };
}
