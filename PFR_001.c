// PFR 001

// contador largo

#include <16F628A.h>

#fuses HS,NOWDT,NOPROTECT,NOLVP
#use delay(clock=16000000)

// Mapeo de los segmentos del display
const int8 segment_map[10] = {
   0b0111111, // 0
   0b0001100, // 1
   0b1101011, // 2
   0b1101110, // 3
   0b1011100, // 4
   0b1110110, // 5
   0b1110111, // 6
   0b0101100, // 7
   0b1111111, // 8
   0b1111110  // 9
};

int16 count = -1;       // Variable para almacenar el conteo
int8 digit[4];         // D�gitos individuales para el display
int1 prev_state = 1;   // Estado anterior del pin RB0 (inicializado en 1)

// Tiempo acumulado de la se�al activa en milisegundos
unsigned int16 active_time = 0; 

void display_update() {
   digit[2] = count % 10;          // Unidades
   digit[1] = (count / 10) % 10;   // Decenas
   digit[0] = (count / 100) % 10;  // Centenas
   digit[3] = (count / 1000) % 10; // Millar
}

void display_refresh() {
   for (int8 i = 0; i < 4; i++) {
      output_a(1 << i); // Activar el d�gito correspondiente
      output_b(segment_map[digit[i]] << 1); // Enviar segmentos a RB1-RB7
      delay_ms(2); // Breve retardo para evitar parpadeos
      output_a(0); // Apagar el d�gito
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
         
         // Esperar 100 ms para validar que la se�al es continua
         while (!input(PIN_B0)) {
            delay_ms(1);
            active_time++;
            
            // Validar si la se�al se mantiene activa durante al menos 100 ms
            if (active_time >= 10) {
               count++;
               if (count > 9999) {
                  count = 0; // Reiniciar el conteo al alcanzar el l�mite
               }
               display_update(); // Actualizar los d�gitos del display
               break; // Salir del bucle tras un conteo v�lido
            }
         }
      }

      prev_state = current_state; // Actualizar el estado anterior
      display_refresh();          // Refrescar el display
   }
}

