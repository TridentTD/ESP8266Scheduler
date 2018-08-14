#ifndef ESP8266SCHEDULER_H
#define ESP8266SCHEDULER_H

// #include <Arduino.h>
#include "Task.h"

extern "C" void loop();
extern void task_tramponline();

class ESP8266SchedulerClass {
public:
    ESP8266SchedulerClass();

    static void start(Task *task);

    static void begin();

private:
    friend void task_tramponline();

    // class MainTask : public Task {};

    static Task main;
    static Task *current;
};

extern ESP8266SchedulerClass Scheduler;

#endif
