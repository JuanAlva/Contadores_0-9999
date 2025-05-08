# Contador con Display de 7 Segmentos - PFR 003

Este proyecto implementa un **contador digital** usando un microcontrolador **PIC16F628A** y un display de **4 dígitos de 7 segmentos**. El sistema cuenta pulsos de entrada recibidos por el pin **RB0** y muestra el resultado en tiempo real en el display.

## 🛠️ Características

- Conteo desde 0 hasta 9999  
- Incremento del conteo al detectar un **flanco de bajada** en RB0  
- Filtro por software para validar pulsos reales (mínimo 5 ms activos)  
- Multiplexación de 4 dígitos en un display de 7 segmentos  
- Reinicio automático del conteo al superar 9999  

## 📦 Hardware

- **Microcontrolador**: PIC16F628A  
- **Oscilador**: Cristal de 16 MHz  
- **Display**: 4 dígitos, ánodo común  
- **Entradas/Salidas**:
  - `RB0`: Entrada de pulsos  
  - `RB1 - RB7`: Segmentos del display (a-g)  
  - `RA0 - RA3`: Activación de los 4 dígitos del display  

## ⚙️ Configuración de Fuses


## 📋 Descripción del Código

El programa principal realiza las siguientes funciones:

- Lee el estado de RB0 para detectar pulsos.
- Aplica una verificación por software para asegurar que la señal es válida.
- Incrementa el contador cuando se confirma un pulso.
- Actualiza los dígitos del display con la nueva cuenta.
- Realiza la multiplexación periódica para mostrar los 4 dígitos.

## Principales funciones

- display_update(): Convierte el número en dígitos individuales.
- display_refresh(): Activa los dígitos uno por uno con su correspondiente valor segmentado.
- main(): Lazo principal que verifica pulsos y actualiza el display.

## 🧠 Lógica de Conteo

El sistema detecta un flanco de bajada en RB0 y luego valida que la señal permanezca baja por al menos 5 ms antes de incrementar el conteo. Esto actúa como antirebote por software.

## 🖥️ Diagrama Lógico de Conexiones (resumen)
Pin PIC16F628A	Función
RA0 - RA3	Selección de dígito (1 por dígito)
RB1 - RB7	Segmentos del display (a-g)
RB0	Entrada de pulso externo

## 📜 Creditos
Desarrollado por Juan Alva
