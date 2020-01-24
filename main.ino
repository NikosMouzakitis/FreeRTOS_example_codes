#include <Arduino_FreeRTOS.h>
#include <task.h>
/// suspend resume tasks 

TaskHandle_t myTask1Handle = NULL;
TaskHandle_t myTask2Handle = NULL;

void Task1( void *p);
void Task2( void *p);

void Task1( void *p) {

	TickType_t myLastUnblock;
	int count =0;
	myLastUnblock = xTaskGetTickCount();
	
	while(1) {
		Serial.print("Hello"); Serial.println(count++);
		fflush(stdout);
		vTaskDelay(pdMS_TO_TICKS(500)); //1sec delay.
	}
}

void Task2( void *p) {
	int susp_time = 100000;	
	while(1) {
		vTaskDelay( pdMS_TO_TICKS( susp_time)/2 ); 
		vTaskSuspend(myTask1Handle);
		Serial.println("suspend");
		fflush(stdout);
		vTaskDelay(pdMS_TO_TICKS(susp_time)); 
		vTaskResume(myTask1Handle);
		//Serial.println("resume");
		fflush(stdout);
	}
}

void setup() {
	// initialize serial communication at 9600 bits per second:
	Serial.begin(115200);
	while (!Serial) {
		;
	}
	int a = 10;
	// Now set up two tasks to run independently.
	xTaskCreate( Task1, "task1", 200, (void*)a, tskIDLE_PRIORITY, &myTask1Handle);
	xTaskCreate( Task2, "task2", 200, NULL, tskIDLE_PRIORITY, &myTask2Handle);
	vTaskStartScheduler();	
	Serial.println("Scheduler runs");
}

void loop()
{
	// Empty. Things are done in Tasks.
}

