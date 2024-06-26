# ATmega32 Drivers implementation

- [Description](#Description)
- [Note⛔](#Note⛔)
- [HAL](#HAL)
  - [Keypad](#Keypad)
  - [LCD](#LCD)
  - [NTC](#NTC)
  - [LM35](#LM35)
  - [Servo](#servo)
  - [LED](#LED)
  - [SevenSegment](#SevenSegment)
  - [ULTRASONIC](#ULTRASONIC)
  - [Button](#Button)
  - [EXT-EEPROM](#EXT-EEPROM)
  - [Infrared-Remote-Control](#Infrared-Remote-Control)
- [MCAL](#MCAL)
  - [GPIO](#GPIO)
  - [EXT-INT](#EXT-INT)
  - [Timer0](#Timer0)
  - [Timer1](#Timer1)
  - [ADC](#ADC)
  - [USART](#USART)
  - [SPI](#SPI)
  - [I2C](#I2C)
- [Service](#Service)
  - [Common-Macros](#Common-Macros)
  - [Standrad-Types](#Standrad-Types)
  - [IVT](#IVT)



## Description
<p>Here I implement drivers to be independent on any built in drivers and apply some concepts like</p>
<p>1.modularity</p>
<p>2.save hierarchy</p>
<p>3.easy configurability</p>

## Note⛔
<p>Don't forget for any module Driver go to ModuleName_config.h and read it carefully and edit or configure depend on your need and configure  ModuleName_config.c if exist </p>
<p>Read ModuleName_interface.h to know each function what can do and what can't Do</p>
<p>Don't Ignore any <Strong>Note ⛔🙆‍♂️</Strong> in ModuleName_interface.h OR ModuleName_config.h</p>

## HAL
<p>Here will find all Drivers for external hardware devices that ready to use with ATmega32</p>

### Keypad
<p>Here will find driver for this module and able to config with keypad 4*4 or 4*3 </p>

### LCD
<p>Here will find implementation for LCD LM016L 2*16 and find most of features and add New character to CGRAM</p>

### NTC
<p>Here will find implementation for Negative Temeperature Coffecient </p>

### LM35
<p>Here will find implementation for LM35 </p>

### Servo
<p>Here will find Implement  of Servo Motor That depend on exist of Timer 1 using ICR1 as Top value</p>




## MCAL
<p>Here will find All drivers for MCU specefic and deal direct with it</p>

### GPIO
<p>Here deal with Digital input / output for MCU  </p>

### EXT-INT
<p>Here will find implementation of INT0 , INT1 and INT2 with full configuration </p>

### Timer0
<p>Here will find implementation for Timer0 Module available with all modes 1.OVF(Polling & Interrupt) 2.CTC(Polling & Interrupt & waveform Generation) 3.Fast PWM  4.Phase correct PWM</p>

### Timer1
<p>Here will find implementation for Timer0 Module available with all modes 1.OVF(Polling & Interrupt & ICU) 2.CTC(Polling & Interrupt & waveform Generation) 3.Fast PWM  4.Phase correct PWM</p>

### ADC
<p>Here will find implementation for ADC Module availble with 3 modes (Signle Conversion , Free Running , Auto Trigger)</p>


## Service 
<p>Here will find some service header file used to facilitate dealing</p>

### Common-Macros
<p>Here will find function like macros that help in change bits in register easly without make stack context switch</p>

### Standrad-Types
<p>Here will find standard data types that don't depend on architecture
  bits size</p>

### IVT
<p>Here will find Header file for ALL ISR to Be able to use it</p>

