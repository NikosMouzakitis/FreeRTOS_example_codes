#include <Arduino_FreeRTOS.h>
#include <task.h>

/// suspend resume tasks 

TaskHandle_t myTask1Handle = NULL;
TaskHandle_t myIntTaskHandle = NULL;

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

void intTask( void *p) {
	while(1) {
		vTaskSuspend(NULL); // suspend itself.
		Serial.println("isr");
	}
}

void myISR_Handler(void) {
	//standart step
	BaseType_t yieldRequired;
	yieldRequired = xTaskResumeFromISR(myIntTaskHandle);

	
	if(yieldRequired == pdTRUE) {
		portYIELD_FROM_ISR(yieldRequired);
	} else
		Serial.println("Unable to resume from ISR\n");

}
void setup() {
	
	pinMode(2, INPUT_PULLUP);	
	
	// initialize serial communication at 9600 bits per second:
	Serial.begin(115200);
	
	while (!Serial) {
		;
	}
	
	// Now set up two tasks to run independently.
	attachInterrupt(digitalPinToInterrupt(2), myISR_Handler, FALLING);
	xTaskCreate( Task1, "task1", 200, (void*)0, tskIDLE_PRIORITY, &myTask1Handle);
	xTaskCreate( intTask, "intTask", 200, (void*)0, tskIDLE_PRIORITY, &myIntTaskHandle);
	vTaskStartScheduler();	
	Serial.println("Scheduler runs");
}

void loop()
{
	// Empty. Things are done in Tasks.
}

