# espidf-freertos-task

## 概述

目的：充分了解下列标题  

- 在应用程序中，FreeRTOS如何为各任务分配处理时间
- 在任意给定时刻，FreeRTOS如何选择任务投入运行
- 任务优先级如何影响系统行为
- 任务存在哪些状态
- 如何实现一个任务
- 如何创建一个或多个任务的实例
- 如何使用任务参数
- 如何改变一个任务的优先级
- 如何删除任务
- 如何实现周期性处理
- 空闲任务何时运行，可以用来干什么

## 任务函数

- 任务是由 C 语言函数实现的。唯一特别的只是任务的函数原型，其必须返回 void，而且带有一个 void 指针参数  

  - 任务函数必须返回void  
  - 参数必须有和void的指针参数  

```code
void ATaskFunction( void *pvParameters );
```

- 任务函数要求：
  - 每个任务都是在自己权限范围内的一个小程序
  - 其具有程序入口，通常会运行在一个死循环中，也不会退出
  - FreeRTOS任务不允许以任何方式从实现函数中返回。它们绝不能有一条”return”语句，也不能执行到函数末尾。
  - 如果一个任务不再需要，可以显式地将其删除。
  - 一个任务函数可以用来创建若干个任务——创建出的任务均是独立的执行实例。拥有属于自己的栈空间，以及属于自己的自动变量(栈变量)，即任务函数本身定义的变量

```code
void ATaskFunction( void *pvParameters )
{
    /* 可以像普通函数一样定义变量。用这个函数创建的每个任务实例都有一个属于自己的iVarialbleExample变
    量。但如果iVariableExample被定义为static，这一点则不成立 – 这种情况下只存在一个变量，所有的任务实
    例将会共享这个变量。 */
    int iVariableExample = 0;
    /* 任务通常实现在一个死循环中。 */
    for( ;; )
    {
        /* 完成任务功能的代码将放在这里。 */
    }
    /* 如果任务的具体实现会跳出上面的死循环，则此任务必须在函数运行完之前删除。传入NULL参数表示删除
    的是当前任务 */
    vTaskDelete( NULL );
}
```

- 顶层任务状态
略

- 创建任务
  xTaskCreate()  

```code
portBASE_TYPE xTaskCreate(
                          pdTASK_CODE pvTaskCode,
                          const signed portCHAR * const pcName,
                          unsigned portSHORT usStackDepth,
                          void *pvParameters,
                          unsigned portBASE_TYPE uxPriority,
                          xTaskHandle *pxCreatedTask
                          );

1. 返回值
pdTRUE 表明任务创建成功。
errCOULD_NOT_ALLOCATE_REQUIRED_MEMORY 由于内存堆空间不足，FreeRTOS 无法分配足够的空间来保存任务结构数据和任务栈，因此无法创建任务。

2. pvTaskCode
任务只是永不退出的C函数，实现常通常是一个死循环。参数pvTaskCode只一个指向任务的实现函数的指针(效果上仅仅是函数名)

3. pcName
具有描述性的任务名。这个参数不会被 FreeRTOS 使用。其只是单纯地用于辅助调试。识别一个具有可读性的名字总是比通过句柄来识别容易得多。
通过定义常量 config_MAX_TASK_NAME_LEN 来定义任务名的最大长度——包括’\0’结束符。
如果传入的字符串长度超过了这个最大值，字符串将会自动被截断。

4. usStackDepth
当任务创建时，内核会分为每个任务分配属于任务自己的唯一状态,usStackDepth值用于告诉内核为它分配多大的栈空间。
这个值指定的是栈空间可以保存多少个字(word)，而不是多少个字节(byte)。
比如说，如果是 32 位宽的栈空间，传入的 usStackDepth值为 100，则将会分配 400 字节的栈空间(100 * 4bytes)。
栈深度乘以栈宽度的结果千万不能超过一个 size_t 类型变量所能表达的最大值。
应用程序通过定义常量 configMINIMAL_STACK_SIZE 来决定空闲任务任用的栈空间大小。
在 FreeRTOS 为微控制器架构提供的Demo 应用程序中，赋予此常量的值是对所有任务的最小建议值。如果你的任务会使用大量栈空间，那么你应当赋予一个更大的值。
没有任何简单的方法可以决定一个任务到底需要多大的栈空间。计算出来虽然是可能的，但大多数用户会先简单地赋予一个自认为合理的值，
然后利用 FreeRTOS 提供的特性来确证分配的空间既不欠缺也不浪费。可以知道如何去查询任务使用了多少栈空间

5. pvParameters
任务函数接受一个指向 void 的指针(void*)。pvParameters 的值即是传递到任务中的值

6. uxPriority
指定任务执行的优先级。优先级的取值范围可以从最低优先级 0 到 最高优先级(configMAX_PRIORITIES – 1)。
configMAX_PRIORITIES 是一个由用户定义的常量。优先级号并没有上限(除了受限于采用的数据类型和系统的有效内存空间)，
但最好使用实际需要的最小数值以避免内存浪费。
如果 uxPriority 的值超过了(configMAX_PRIORITIES – 1)，将会导致实际赋给任务的优先级被自动封顶到最大合法值。

7. pxCreatedTask
pxCreatedTask 用于 传出 任务的句柄。这个句柄将在 API 调用中对该创建出来的任务进行引用，比如改变任务优先级，或者删除任务。
如果应用程序中不会用到这个任务的句柄，则 pxCreatedTask 可以被设为 NULL。
```

- 创建任务

```code
void vTask1(void *pvParameters)
{
  const char *pcTaskName = "Task 1 is running\r\n";
  volatile unsigned long ul;
  /* 和大多数任务一样，该任务处于一个死循环中。 */
  for (;;)
  {
    /* Print out the name of this task. */
    vPrintString(pcTaskName);
    /* 延迟，以产生一个周期 */
    for (ul = 0; ul < mainDELAY_LOOP_COUNT; ul++)
    {
      /* 这个空循环是最原始的延迟实现方式。在循环中不做任何事情。后面的示例程序将采用
delay/sleep函数代替这个原始空循环。 */
    }
  }
}

void vTask2(void *pvParameters)
{
  const char *pcTaskName = "Task 2 is running\r\n";
  volatile unsigned long ul;
  /* 和大多数任务一样，该任务处于一个死循环中。 */
  for (;;)
  {
    /* Print out the name of this task. */
    vPrintString(pcTaskName);
    /* 延迟，以产生一个周期 */
    for (ul = 0; ul < mainDELAY_LOOP_COUNT; ul++)
    {
      /* 这个空循环是最原始的延迟实现方式。在循环中不做任何事情。后面的示例程序将采用delay/sleep函数代替这个原始空循环。 */
    }
  }
}

int main(void)
{
  /* 创建第一个任务。需要说明的是一个实用的应用程序中应当检测函数xTaskCreate()的返回值，以确保任务创建成功。 */
  xTaskCreate(vTask1,   /* 指向任务函数的指针 */
              "Task 1", /* 任务的文本名字，只会在调试中用到 */
              1000,     /* 栈深度 – 大多数小型微控制器会使用的值会比此值小得多 */
              NULL,     /* 没有任务参数 */
              1,        /* 此任务运行在优先级1上. */
              NULL);    /* 不会用到任务句柄 */

  /* Create the other task in exactly the same way and at the same priority. */
  xTaskCreate(vTask2, "Task 2", 1000, NULL, 1, NULL);
  /* 启动调度器，任务开始执行 */
  vTaskStartScheduler();
  /* 如果一切正常，main()函数不应该会执行到这里。但如果执行到这里，很可能是内存堆空间不足导致空闲任务无法创建。*/
  for (;;)
    ;
}
```

## 小结

esp32-idf开发task注意点：

- 创建任务使用的栈大小必须的1024的倍速，小了或者不是1024的会导致重启
- 任务创建后不能使用 vTaskStartScheduler 函数会导致重启  
- task里面死循环不使用delay就会由系统的时间片来调度，由portTICK_PERIOD_MS决定 100Hz 代表 10 Ms
