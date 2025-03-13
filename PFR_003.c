// PFR 003

// contador pequeño con disipador horizontal
#include <16F628A.h>

#fuses HS,NOWDT,NOPROTECT,NOLVP
#use delay(clock=16000000)

// Mapeo de los segmentos del display
const int8 segment_map[10] = {
   0b1110111, // 0b0111111, //// 0b0111111, // 0
   0b0010001, // 0b0100001, // // 0b0001100, // 1
   0b1101101, // 0b1101110, // // 0b1101011, // 2
   0b0111101, // 0b1101011, // // 0b1101110, // 3
   0b0011011, // 0b1110001, //  // 0b1011100, // 4
   0b0111110, // 0b1011011, // // 0b1110110, // 5
   0b1111110, // 0b1011111, // // 0b1110111, // 6
   0b0010101, // 0b0101001, // // 0b0101100, // 7
   0b1111111, // 0b1111111, // // 0b1111111, // 8
   0b0011111 // 0b1111001 // // 0b1111110  // 9
};

int16 count = 0;       // Variable para almacenar el conteo
int8 digit[4];         // Dígitos individuales para el display
int1 prev_state = 1;   // Estado anterior del pin RB0 (inicializado en 1)

// Tiempo acumulado de la señal activa en milisegundos
unsigned int16 active_time = 0; 

void display_update() {
   digit[2] = count % 10;          // Unidades
   digit[3] = (count / 10) % 10;   // Decenas
   digit[1] = (count / 100) % 10;  // Centenas
   digit[0] = (count / 1000) % 10; // Millar
}

void display_refresh() {
   for (int8 i = 0; i < 4; i++) {
      output_a(1 << i); // Activar el dígito correspondiente
      output_b(segment_map[digit[i]] << 1); // Enviar segmentos a RB1-RB7
      delay_ms(2); // Breve retardo para evitar parpadeos
      output_a(0); // Apagar el dígito
   }
}

void main() {
   setup_timer_0(RTCC_INTERNAL); 
   setup_comparator(NC_NC_NC_NC); // Deshabilitar comparadores
   set_tris_a(0xF0);             // RA0-RA3 como salida
   set_tris_b(0x01);             // RB0 como entrada, RB1-RB7 como salida

   display_update(); // Inicializar el display

   while (true) {
      int1 current_state = input(PIN_B0); // Leer el estado actual de RB0

      if (!current_state && prev_state) { // Detectar flanco de bajada
         active_time = 0; // Reiniciar tiempo acumulado
         
         // Esperar 100 ms para validar que la señal es continua
         while (!input(PIN_B0)) {
            delay_ms(1);
            active_time++;
            
            // Validar si la señal se mantiene activa durante al menos 100 ms
            if (active_time >= 5) {
               count++;
               if (count > 9999) {
                  count = 0; // Reiniciar el conteo al alcanzar el límite
               }
               display_update(); // Actualizar los dígitos del display
               break; // Salir del bucle tras un conteo válido
            }
         }
      }

      prev_state = current_state; // Actualizar el estado anterior
      display_refresh();          // Refrescar el display
   }
}

