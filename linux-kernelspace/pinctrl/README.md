# PINCTRL子系统使用

CONFIG_PINCTRL=y

头文件列表：
\include\linux\pinctrl\consumer.h
\include\linux\pinctrl\devinfo.h
\include\linux\pinctrl\machine.h
\include\linux\pinctrl\pinconf.h
\include\linux\pinctrl\pinconf-generic.h
\include\linux\pinctrl\pinctrl.h
\include\linux\pinctrl\pinctrl-state.h
\include\linux\pinctrl\pinmux.h

## 简介

## API使用

extern bool pinctrl_gpio_can_use_line(unsigned gpio);
extern int pinctrl_gpio_request(unsigned gpio);
extern void pinctrl_gpio_free(unsigned gpio);
extern int pinctrl_gpio_direction_input(unsigned gpio);
extern int pinctrl_gpio_direction_output(unsigned gpio);
extern int pinctrl_gpio_set_config(unsigned gpio, unsigned long config);

extern struct pinctrl * __must_check pinctrl_get(struct device *dev);
extern void pinctrl_put(struct pinctrl *p);
extern struct pinctrl_state * __must_check pinctrl_lookup_state(
							struct pinctrl *p,
							const char *name);
extern int pinctrl_select_state(struct pinctrl *p, struct pinctrl_state *s);

extern struct pinctrl * __must_check devm_pinctrl_get(struct device *dev);
extern void devm_pinctrl_put(struct pinctrl *p);
extern int pinctrl_select_default_state(struct device *dev);

#ifdef CONFIG_PM
extern int pinctrl_pm_select_default_state(struct device *dev);
extern int pinctrl_pm_select_sleep_state(struct device *dev);
extern int pinctrl_pm_select_idle_state(struct device *dev);
#else