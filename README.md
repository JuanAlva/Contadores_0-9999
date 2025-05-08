/*
 * ============================================================================
 * Archivo: readme.h
 * Proyecto: Contador con Display de 7 segmentos - PFR 003
 * Autor: [Tu Nombre]
 * Microcontrolador: PIC16F628A
 * Frecuencia del oscilador: 16 MHz
 * Fecha: [Fecha actual]
 * ============================================================================
 *
 * DESCRIPCIÓN:
 * --------------
 * Este proyecto implementa un contador de pulsos simple utilizando un 
 * microcontrolador PIC16F628A. El sistema cuenta pulsos de entrada recibidos 
 * en el pin RB0 y muestra el valor actual en un display de 4 dígitos de 7 
 * segmentos mediante multiplexación.
 *
 * FUNCIONALIDAD PRINCIPAL:
 * -------------------------
 * - Cada vez que se detecta un flanco de bajada en RB0 y la señal permanece 
 *   activa por al menos 5 ms, el contador incrementa su valor en uno.
 * - El conteo se muestra en un display de 4 dígitos.
 * - El conteo se reinicia a 0 cuando supera 9999.
 *
 * CONFIGURACIÓN DE FUSES:
 * ------------------------
 * - HS: Oscilador de alta velocidad.
 * - NOWDT: Watchdog Timer desactivado.
 * - NOPROTECT: Protección de código desactivada.
 * - NOLVP: Programación en baja tensión desactivada.
 *
 * PINOUT:
 * --------
 * - RB0: Entrada del pulso a contar.
 * - RB1 - RB7: Salidas para segmentos del display (a través de una máscara de desplazamiento).
 * - RA0 - RA3: Control de activación de los dígitos (multiplexado).
 *
 * FUNCIONES CLAVE:
 * -----------------
 * - `display_update()`: Calcula los 4 dígitos del valor actual del contador.
 * - `display_refresh()`: Multiplexa los 4 dígitos para el display.
 * - `main()`: Contiene el bucle principal, donde se detectan los pulsos y se actualiza el display.
 *
 * NOTAS:
 * ------
 * - El sistema incluye un filtro por software que requiere que el pulso sea 
 *   sostenido durante al menos 5 ms (anti-rebote por software).
 * - El sistema utiliza temporización por retardo (`delay_ms`) y no interrupciones.
 *
 * LICENCIA:
 * ----------
 * Código de libre uso para fines educativos y no comerciales.
 *
 * ============================================================================
 */
