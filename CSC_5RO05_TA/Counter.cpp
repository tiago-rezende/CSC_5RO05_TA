#include "Counter.h"

Counter::Counter(bool protect) : m_value(0.0), p_mutex(nullptr) {
    if (protect) {
        p_mutex = new Mutex();
        incrementFunc = &Counter::incrProtect;
    } else {
        incrementFunc = &Counter::incrNoProtect;
    }
}

Counter::~Counter() {
    delete p_mutex;
}

double Counter::incrProtect() {
    Mutex::Lock lock(*p_mutex);
    return ++m_value;
}

double Counter::incrNoProtect() {
    return ++m_value;
}

double Counter::increment() {
    return (this->*incrementFunc)();
}

double Counter::value() const {
    return m_value;
}

bool Counter::isProtected() const {
    return p_mutex != nullptr;
}