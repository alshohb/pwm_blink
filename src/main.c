#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/pwm.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(pwm_blink, LOG_LEVEL_INF);

#define PWM_LED_NODE DT_ALIAS(pwm_led0)
#define PWM_PERIOD   PWM_SEC(1U)

static const struct pwm_dt_spec pwm_led = PWM_DT_SPEC_GET(PWM_LED_NODE);

int main(void)
{
    if (!pwm_is_ready_dt(&pwm_led)) {
        LOG_ERR("PWM device not ready");
        return -1;
    }

    LOG_INF("PWM blink starting...");

    while (1) {
        pwm_set_dt(&pwm_led, PWM_PERIOD, PWM_PERIOD);
        LOG_INF("LED ON");
        k_sleep(K_SECONDS(1));

        pwm_set_dt(&pwm_led, PWM_PERIOD, 0);
        LOG_INF("LED OFF");
        k_sleep(K_SECONDS(1));
    }

    return 0;
}