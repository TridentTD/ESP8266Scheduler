#include "ESP8266Scheduler.h"

extern "C" {
    #include "cont.h"

    void yield();
}

ESP8266SchedulerClass Scheduler;

Task ESP8266SchedulerClass::main;
Task *ESP8266SchedulerClass::current = &ESP8266SchedulerClass::main;

ESP8266SchedulerClass::ESP8266SchedulerClass() {
    main.next = &main;
    main.prev = &main;
}

void ESP8266SchedulerClass::start(Task *task) {
    task->next = &main;
    task->prev = main.prev;

    main.prev->next = task;
    main.prev = task;
}

void ESP8266SchedulerClass::begin() {
    while (1) {
        if (current->shouldRun())
            cont_run(&current->context, task_tramponline);

        yield();

        current = current->next;
    }
}

void task_tramponline() {
    ESP8266SchedulerClass::current->loopWrapper();
}
