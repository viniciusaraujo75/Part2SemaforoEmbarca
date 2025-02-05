# Sequência de LEDs com Botão - Raspberry Pi Pico W

Este projeto aciona uma sequência de LEDs ao pressionar um botão usando o Raspberry Pi Pico W.

## Componentes

- **Raspberry Pi Pico W**
- **LEDs (Azul, Verde e Vermelho)**
- **Resistores de 330 Ω**
- **Botão**

## Como Funciona

1. O código monitora o botão no **GPIO 5**.
2. Quando pressionado, ele inicia a sequência:
   - Acende os três LEDs simultaneamente.
   - Após 3 segundos, apaga o LED **vermelho**.
   - Depois de mais 3 segundos, apaga o LED **verde**.
   - Por fim, após mais 3 segundos, apaga o LED **azul**.
3. A sequência só pode ser iniciada novamente depois que todos os LEDs forem apagados.

## Como Usar

1. **Clonar o repositório**:
* git clone https://github.com/viniciusaraujo75/Part2SemaforoEmbarca

2. **Abrir o projeto no VS Code**.
3. **Simular no Wokwi**:
- Configure o Raspberry Pi Pico W.
- Conecte os LEDs nos GPIOs 11 (Azul), 12 (Verde) e 13 (Vermelho).
- Copie e cole o código no editor do Wokwi.
4. **Inicie a simulação e pressione o botão** para acionar a sequência.

## Observação

- Se os LEDs não acenderem corretamente, verifique as conexões e se o botão está configurado corretamente.