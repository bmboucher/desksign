#ifndef __DEBOUNCE_H__
#define __DEBOUNCE_H__

#include <stdint.h>

class DebouncedInput {
    public:
        DebouncedInput(int pin, uint32_t debounce);
        bool value(void);
        void update(void);
    private:
        int pin;
        uint32_t debounce;

        uint32_t lastChange = 0;
        bool oldValue = false;
        bool newValue = false;
};

#endif // __DEBOUNCE_H__