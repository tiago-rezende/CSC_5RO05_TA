#include "Chrono.h"
#include <iostream>  

Chrono::Chrono() {
    restart(); 
}

void Chrono::restart() {
    m_startTime = timespec_now(); 
    m_stopTime = m_startTime;    
    m_isActive = true;           
}

timespec Chrono::stop() {
    if (!m_isActive) {
        std::cerr << "Error: Chronometer is already stopped." << std::endl;
        timespec zero = {0, 0};
        return zero;
    }
    m_stopTime = timespec_now();
    m_isActive = false;         
    return timespec_subtract(m_stopTime, m_startTime); 
}

bool Chrono::isActive() const {
    return m_isActive;
}

timespec Chrono::lap() const {
    if (m_isActive) {
        return timespec_subtract(timespec_now(), m_startTime); 
    } else {
        return timespec_subtract(m_stopTime, m_startTime); 
    }
}

double Chrono::lap_ms() const {
    return timespec_to_ms(lap()); 
}