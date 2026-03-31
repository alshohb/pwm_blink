#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/pwm.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(pwm_blink, LOG_LEVEL_INF);

#define PWM_LED_NODE DT_ALIAS(pwm_led0)
#define PWM_PERIOD   PWM_MSEC(20U)
#define STEP_COUNT   100
#define STEP_DELAY   10

static const struct pwm_dt_spec pwm_led = PWM_DT_SPEC_GET(PWM_LED_NODE);

int main(void)
{
    if (!pwm_is_ready_dt(&pwm_led)) {
        LOG_ERR("PWM device not ready");
        return -1;
    }

    LOG_INF("PWM breathing effect starting...");

    uint32_t pulse;

    while (1) {
        for (int i = 0; i <= STEP_COUNT; i++) {
            pulse = (PWM_PERIOD / STEP_COUNT) * i;
            pwm_set_dt(&pwm_led, PWM_PERIOD, pulse);
            k_msleep(STEP_DELAY);
        }

        for (int i = STEP_COUNT; i >= 0; i--) {
            pulse = (PWM_PERIOD / STEP_COUNT) * i;
            pwm_set_dt(&pwm_led, PWM_PERIOD, pulse);
            k_msleep(STEP_DELAY);
        }
    }

    return 0;
}