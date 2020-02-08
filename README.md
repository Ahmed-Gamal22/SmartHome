# SmartHome
Smart Home system using modules: (ATmega128, Ultrasonic Sensor, LM35 Sensor, Keypad, LCD, Servo Motor, ADC, External EEPROM, UART and I2C)
HomeGenius.c is our main application:
First: at the beginning the application wouldn't run unless the user is at short distance < 50 CM to our application 
,so the ultrasonic sensor can detect and lcd and keypad start working.
some options in the main :
                            1- change Password and save it to externa EEProm.
                            2- open the door with servo motor driver.
ALSO, fire alarm system connected with LM35 to LCD and Buzzer.
UART control for Air condtioning and lighting system. 
finally, our system has A locked system if you entered wrong password at any stage of the above one.
