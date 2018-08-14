#include <ESP8266Scheduler.h>

class BlinkTask : public Task {
  uint8_t state;
  void setup() {
    state = HIGH;
    pinMode(2, OUTPUT);
    pinMode(2, state);
  }
  void loop() {
    state = state == HIGH ? LOW : HIGH;
    pinMode(2, state);
    delay(1000);
  }
} blink_task;

class PrintTask : public Task {
  void setup() {}
  void loop()  {
    Serial.println("Print Loop Start");
    delay(5000);
    Serial.println("Print Loop End");
    delay(5000);
  }
} print_task;

class MemTask : public Task {
  void setup() {}
  void loop() {
    Serial.print("Free Heap: ");
    Serial.print(ESP.getFreeHeap());
    Serial.println(" bytes");
    delay(10000);
  }
} mem_task;

void setup() {
  Serial.begin(115200);
  Serial.println("");
  delay(1000);
  Scheduler.start(&blink_task);
  Scheduler.start(&print_task);
  Scheduler.start(&mem_task);
  Scheduler.begin();
}

void loop() {}
