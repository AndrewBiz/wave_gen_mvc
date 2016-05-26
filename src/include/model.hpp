/*
    AD9850 DDS based wave generator built on MVC pattern
    Andrew Bizyaev (ANB) github.com/andrewbiz

    'Model' part pf MVC pattern
*/
#ifndef MODEL_HPP
#define MODEL_HPP

#include "view.hpp"
#include <stddef.h>

class Model {
public:
    virtual ~Model();
    void attach_observer(View *);
    void detach_observer(View *);
    void notify_observers();
protected:
    Model();
    static const size_t MaxObservers = 1;
private:
    View * _observer[MaxObservers];
    size_t _number_observers;
};

#endif
