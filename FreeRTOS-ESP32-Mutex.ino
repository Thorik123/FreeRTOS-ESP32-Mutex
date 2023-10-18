#if CONFIG_FREERTOS_UNICORE
#define ARDUINO_RUNNING_CORE 0
#else
#define ARDUINO_RUNNING_CORE 1
#endif

SemaphoreHandle_t mutex;

int glbvar = 0;

void task1(void *pvParameters) {
  while (1) {
    if (xSemaphoreTake(mutex, portMAX_DELAY) == pdTRUE) {
      Serial.println("Task 1: Mutex Acquired");
      glbvar++;
      Serial.print("Task 1 - ");
      Serial.println(glbvar);
      vTaskDelay(1000 / portTICK_PERIOD_MS);
      xSemaphoreGive(mutex);
      Serial.println("Task 1: Mutex Released");
      Serial.println("");
    }
  }
}

void task2(void *pvParameters) {
  while (1) {
    if (xSemaphoreTake(mutex, portMAX_DELAY) == pdTRUE) {
      Serial.println("Task 2: Mutex Acquired");
      glbvar++;
      Serial.print("Task 2 - ");
      Serial.println(glbvar);
      vTaskDelay(1000 / portTICK_PERIOD_MS);
      xSemaphoreGive(mutex);
      Serial.println("Task 2: Mutex Released");
      Serial.println("");
    }
  }
}

void setup() {
  Serial.begin(115200);
  mutex = xSemaphoreCreateMutex();
  xTaskCreatePinnedToCore(task1, "Task 1", 1024, NULL, 1, NULL, ARDUINO_RUNNING_CORE);
  xTaskCreatePinnedToCore(task2, "Task 2", 1024, NULL, 1, NULL, ARDUINO_RUNNING_CORE);
}

void loop() {}