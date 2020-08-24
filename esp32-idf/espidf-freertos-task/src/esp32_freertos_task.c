#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "sdkconfig.h"
#include <stdio.h>

#define BLINK_GPIO CONFIG_BLINK_GPIO

void task_create(void);

void app_main()
{
  /* 此处delay是等待系统启动起来 */
  vTaskDelay(1000 / portTICK_PERIOD_MS);

  //创建任务
  task_create();

  /* main 函数中如果不加入下面的死循环，main函数就直接返回，留下2个task单独运行，加入下面的死循环是3个task在运行 */

  //for (;;); //这里加入死循环就会出发wdt

  /* 启动调度器，任务开始执行 */
  //vTaskStartScheduler();  //不能使用此函数
}

void ATaskFunction(void *pvParameters)
{
  /* 可以像普通函数一样定义变量。用这个函数创建的每个任务实例都有一个属于自己的iVarialbleExample变量。
  但如果iVariableExample被定义为static，这一点则不成立, 这种情况下只存在一个变量，所有的任务实例将会共享这个变量。 */

  printf("ATaskFunction start\n");

  /* 任务通常实现在一个死循环中。 */
  while (1)
  {
    /* 完成任务功能的代码将放在这里。 */
    printf("task-1 - running iVariableExample\n");
    vTaskDelay(1000 / portTICK_PERIOD_MS);  //没有此delay 无法被正常调度
  }

  /* 如果任务的具体实现会跳出上面的死循环，则此任务必须在函数运行完之前删除。传入NULL参数表示删除的是当前任务 */
  vTaskDelete(NULL);

  printf("ATaskFunction end\n");
}

void ATaskFunction1(void *pvParameters)
{
  /* 可以像普通函数一样定义变量。用这个函数创建的每个任务实例都有一个属于自己的iVarialbleExample变量。
  但如果iVariableExample被定义为static，这一点则不成立, 这种情况下只存在一个变量，所有的任务实例将会共享这个变量。 */

  printf("ATaskFunction1 start\n");

  gpio_pad_select_gpio(BLINK_GPIO);
  /* Set the GPIO as a push/pull output */
  gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);

  /* 任务通常实现在一个死循环中。 */
  while (1)
  {
    printf("Turning off the LED\n");
    gpio_set_level(BLINK_GPIO, 0);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    printf("Turning on the LED\n");
    gpio_set_level(BLINK_GPIO, 1);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
  /* 如果任务的具体实现会跳出上面的死循环，则此任务必须在函数运行完之前删除。传入NULL参数表示删除的是当前任务 */
  vTaskDelete(NULL);

  printf("ATaskFunction1 end\n");
}

void task_create(void)
{
  printf("task_create start\n");

  /* 如果2个任务里面的死循环都不用delay，且任务优先级一致，是由时间片来实现调度，速度由 portTICK_PERIOD_MS 决定 */
  xTaskCreate(ATaskFunction, "task-1", 2048, NULL, 1, NULL);  //512会重启 必须是1024的倍数
  xTaskCreate(ATaskFunction1, "task-2", 2048, NULL, 1, NULL); //tskIDLE_PRIORITY

  /* vTaskStartScheduler()函数使用会导致重启，vTaskStartScheduler这个函数的用法搞不清楚 
  错误如下：
  ATaskFuncGuru Meditation Error: Core  0 panic'ed (InstrFetchProhibited). Exception was unhandled.
  Core 0 register dump:
  PC      : 0x3ffb4eb5  PS      : 0x00050f33  A0      : 0x3ffb4eb5  A1      : 0x3ffb4de0  
  A2      : 0x0000000f  A3      : 0x00000000  A4      : 0xfffffffc  A5      : 0x40088374  
  A6      : 0x00000000  A7      : 0x00000000  A8      : 0x3ffae920  A9      : 0x3ffb3f5c  
  A10     : 0x00000012  A11     : 0x00060f20  A12     : 0x3ffb3f04  A13     : 0x800d4860  
  A14     : 0x3ffb4e50  A15     : 0x3ffb504c  SAR     : 0x0000003a  EXCCAUSE: 0x00000014  
  EXCVADDR: 0x3ffb4eb4  LBEG    : 0x00000000  LEND    : 0x00000001  LCOUNT  : 0x3f4021b0  
  */
  //vTaskStartScheduler();

  printf("task_create end\n");
}
