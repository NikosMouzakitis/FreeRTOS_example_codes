#include <Arduino_FreeRTOS.h>
#include <task.h>
/// passing parameter into the task
TaskHandle_t myTask1Handle = NULL;
void Task1( void *p);

void Task1( void *p) {

	int count = (int *) p;;
	while(1) {
		Serial.println(count++);
		vTaskDelay(100); //1sec delay.


		if(count == 20) {
			// after this task is deleted.(no more print outs)
			vTaskDelete(myTask1Handle);
		}
	}
}


void setup() {
	// initialize serial communication at 9600 bits per second:
	Serial.begin(115200);
	while (!Serial) {
		;
	}
	int a = 12;
	// Now set up two tasks to run independently.
	xTaskCreate( Task1, "task1", 200, (void*)a, tskIDLE_PRIORITY, &myTask1Handle);
	vTaskStartScheduler();	
	Serial.println("Setup finished");
}

void loop()
{
	// Empty. Things are done in Tasks.
}

