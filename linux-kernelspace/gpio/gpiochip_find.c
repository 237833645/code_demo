#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/gpio.h>
#include <linux/delay.h>

struct gpio_chip *gpiochip = NULL;

#define LED_PIN 17  //gpio 0

#if 0
static inline struct gpio_chip *gpio_to_chip(unsigned gpio)
获取相应GPIO的的gpio_chip结构体
#endif

static int chip_match_name(struct gpio_chip *chip, void *data)
{
    return !strcmp(chip->label, data);
}

static __init int gpiochip_find_init(void)
{
    pr_info("gpiochip_find! init\n");

    gpiochip = gpiochip_find("pinctrl-bcm2835", chip_match_name);
    //gpiochip = gpio_to_chip(LED_PIN);
    if (gpiochip == NULL) {
        pr_err("%s %d, error gpiochip == NULL\n",__func__,__LINE__);
        return 0;
    }

    gpiochip->direction_output(gpiochip, LED_PIN, 1);
    gpiochip->set(gpiochip, LED_PIN, 1);

    pr_info("information: gpiochip->label=%s, gpiochip->base=%d, gpiochip->ngpio=%d\n",gpiochip->label, gpiochip->base, gpiochip->ngpio);
    //  information: gpiochip->label=pinctrl-bcm2835, gpiochip->base=0, gpiochip->ngpio=54

    return 0;
}

static __exit void gpiochip_find_exit(void)
{
    if (gpiochip != NULL) {
        gpiochip->set(gpiochip, LED_PIN, 0);
        gpio_free(LED_PIN);
    }

    pr_info("gpiochip_find! exit\n");
}

module_init(gpiochip_find_init);
module_exit(gpiochip_find_exit);

MODULE_AUTHOR("wangfeng");
MODULE_DESCRIPTION("Linux gpiochip_find module");
MODULE_LICENSE("Dual BSD/GPL");
