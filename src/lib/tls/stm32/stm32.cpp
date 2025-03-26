#include <STM32RTC.h>
#include "stm32.h"

/* Get the rtc object */
STM32RTC& rtc = STM32RTC::getInstance();

//#include <TimeLib.h> 
#include "../PPS.h"

bool TlsStm32::init() {
    rtc.begin(); // initialize RTC 24H format
    ready = true;
    return ready;
}

void TlsStm32::set(JulianDate ut1) {
  if (!ready) return;

  GregorianDate greg = calendars.julianDayToGregorian(ut1);

  double f1 = fabs(ut1.hour) + TLS_CLOCK_SKEW;
  int h = floor(f1);
  double m = (f1 - h)*60.0;
  double s = (m - floor(m))*60.0;

  set(greg.year, greg.month, greg.day, h, floor(m), floor(s));
}

void TlsStm32::set(int year, int month, int day, int hour, int minute, int second) {
    rtc.setTime(hour, minute, second);
    rtc.setDate(day, month, year);
}

bool TlsStm32::get(JulianDate &ut1) {
  if (!ready) return false;

  unsigned long rtcTime = rtc.getEpoch(); // get time from Teensy RTC
  //setTime(rtcTime);                           // set system time

  //if (year() >= 0 && year() <= 3000 && month() >= 1 && month() <= 12 && day() >= 1 && day() <= 31 &&
  //    hour() <= 23 && minute() <= 59 && second() <= 59) {
   // GregorianDate greg; greg.year = year(); greg.month = month(); greg.day = day();
  //  ut1 = calendars.gregorianToJulianDay(greg);
  //  ut1.hour = hour() + minute()/60.0 + second()/3600.0;
  //}

  return true;
}
