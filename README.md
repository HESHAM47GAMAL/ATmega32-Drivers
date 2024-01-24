# ATmega32 Drivers implementation

- [Description](#Description)
- [Note⛔](#Note⛔)
- [HAL](#HAL)
  - [Keypad](#Keypad)
  - [LCD](#LCD)
- [MCAL](#MCAL)
  - [GPIO](#GPIO)
- [Service](#Service)
  - [Common-Macros](#Common-Macros)
  - [Standrad-Types](#Standrad-Types)



## Description
<p>Here I implement drivers to be independent on any built in drivers and apply some concepts like</p>
<p>1.modularity</p>
<p>2.save hierarchy</p>
<p>3.easy configurability</p>

## Note⛔
<p>Don't forget for any module Driver go to ModuleName_config.h and read it carefully and edit or configure depend on your need</p>
<p>Read ModuleName_interface.h to know each function what can do and what can't Do</p>
<p>Don't Ignore any Note ⛔🙆‍♂️ in ModuleName_interface.h OR ModuleName_config.h</p>

## HAL
<p>Here will find all Drivers for external hardware devices that ready to use with ATmega32</p>

### Keypad
<p>Here will find driver for this module and able to config with keypad 4*4 or 4*3 </p>

### LCD
<p>Here will implementation for LCD LM016L 2*16 and find most of features and add New character to CGRAM</p>


## MCAL
<p>Here will find All drivers for MCU specefic and deal direct with it</p>

### GPIO
<p>Here deal with Digital input / output for MCU  </p>


## Service 
<p>Here will find some service header file used to facilitate dealing</p>

### Common-Macros
<p>Here will find function like macros that help in change bits in register easly without make stack context switch</p>

### Standrad-Types
<p>Here will find standard data types that don't depend on architecture
  bits size</p>

