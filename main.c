#include "pico/stdlib.h"
#include "hardware/gpio.h"

// Definindo os pinos dos LEDs e do botão
#define LED_BLUE 11
#define LED_GREEN 12
#define LED_RED 13
#define BUTTON 5

// Variáveis para monitorar o botão e o estado dos LEDs
volatile bool button_pressed = false; // Indica se o botão foi pressionado
volatile bool in_progress = false;   // Verifica se a sequência dos LEDs está em andamento

// Declaração das funções que serão usadas no código
void button_callback(uint gpio, uint32_t events);
int64_t turn_off_red_callback(alarm_id_t id, void *user_data);
int64_t turn_off_green_callback(alarm_id_t id, void *user_data);
int64_t turn_off_blue_callback(alarm_id_t id, void *user_data);

// Configuração inicial dos LEDs e do botão
void setup() {
    // Configura os LEDs como saída e os inicializa desligados
    gpio_init(LED_BLUE);
    gpio_set_dir(LED_BLUE, GPIO_OUT);
    gpio_put(LED_BLUE, 0);

    gpio_init(LED_GREEN);
    gpio_set_dir(LED_GREEN, GPIO_OUT);
    gpio_put(LED_GREEN, 0);

    gpio_init(LED_RED);
    gpio_set_dir(LED_RED, GPIO_OUT);
    gpio_put(LED_RED, 0);

    // Configura o botão como entrada com resistor pull-up
    gpio_init(BUTTON);
    gpio_set_dir(BUTTON, GPIO_IN);
    gpio_pull_up(BUTTON);

    // Configura o callback para o botão quando for pressionado
    gpio_set_irq_enabled_with_callback(BUTTON, GPIO_IRQ_EDGE_FALL, true, &button_callback);
}

// Callback que é chamado quando o botão é pressionado
void button_callback(uint gpio, uint32_t events) {
    if (gpio == BUTTON && !in_progress) {
        button_pressed = true;
    }
}

// Inicia a sequência dos LEDs
void start_led_sequence() {
    in_progress = true; // Marca que a sequência começou

    // Liga os três LEDs
    gpio_put(LED_BLUE, 1);
    gpio_put(LED_GREEN, 1);
    gpio_put(LED_RED, 1);

    // Configura um temporizador para desligar o LED vermelho depois de 3 segundos
    add_alarm_in_ms(3000, turn_off_red_callback, NULL, false);
}

// Callback que desliga o LED vermelho e prepara o próximo temporizador
int64_t turn_off_red_callback(alarm_id_t id, void *user_data) {
    gpio_put(LED_RED, 0);
    add_alarm_in_ms(3000, turn_off_green_callback, NULL, false);
    return 0; // Necessário para o tipo de retorno
}

// Callback que desliga o LED verde e prepara o próximo temporizador
int64_t turn_off_green_callback(alarm_id_t id, void *user_data) {
    gpio_put(LED_GREEN, 0);
    add_alarm_in_ms(3000, turn_off_blue_callback, NULL, false);
    return 0; // Necessário para o tipo de retorno
}

// Callback que desliga o LED azul e encerra a sequência
int64_t turn_off_blue_callback(alarm_id_t id, void *user_data) {
    gpio_put(LED_BLUE, 0);
    in_progress = false; // Libera para uma nova sequência
    return 0; // Necessário para o tipo de retorno
}

int main() {

    setup(); // Chama a configuração inicial

    while (true) {
        if (button_pressed) {
            button_pressed = false; // Reseta o estado do botão
            start_led_sequence(); // Inicia a sequência
        }
        sleep_ms(10); // Pequena pausa para reduzir uso excessivo da CPU
    }
}
