#include <stdio.h>
#include "driver/ledc.h"
#include "esp_err.h"

#define BUZZ_TIMER              LEDC_TIMER_0
#define BUZZ_MODE               LEDC_LOW_SPEED_MODE
#define BUZZ_OUTPUT_IO          (5)
#define BUZZ_CHANNEL            LEDC_CHANNEL_0
#define BUZZ_DUTY_RES           LEDC_TIMER_13_BIT
#define BUZZ_DUTY               (4096) // 50%
#define BUZZ_FREQUENCY          (4000)

static void buzzer_init(void)
{
  ledc_timer_config_t ledc_timer = {
    .speed_mode = BUZZ_MODE,
    .duty_resolution = BUZZ_DUTY_RES,
    .timer_num = BUZZ_TIMER,
    .freq_hz = BUZZ_FREQUENCY,
    .clk_cfg = LEDC_AUTO_CLK
  };

  ledc_timer_config(&ledc_timer);

  ledc_channel_config_t ledc_channel = {
    .speed_mode = BUZZ_MODE,
    .channel = BUZZ_CHANNEL,
    .timer_sel = BUZZ_TIMER,
    .intr_type = LEDC_INTR_DISABLE,
    .gpio_num = BUZZ_OUTPUT_IO,
    .duty = 0,
    .hpoint = 0
  };
  ledc_channel_config(&ledc_channel);
}
void app_main(void)
{
  buzzer_init();
  ledc_set_duty(BUZZ_MODE, BUZZ_CHANNEL, BUZZ_DUTY);
  ledc_update_duty(BUZZ_MODE, BUZZ_CHANNEL);
}