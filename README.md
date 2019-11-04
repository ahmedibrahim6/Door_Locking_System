# Door_Locking_System
## Schematic capture by Proteus

![Image of Yaktocat](https://github.com/ahmedibrahim6/Door_Locking_System/blob/master/Images/System.PNG)


## Program states

* State 1 : Running the system for the first time 
  * Creating new password for the system 
  
       ![Image of Yaktocat](https://github.com/ahmedibrahim6/Door_Locking_System/blob/master/Images/newpass.PNG)     
  
       ![Image of Yaktocat](https://github.com/ahmedibrahim6/Door_Locking_System/blob/master/Images/reenterpass.PNG)
       
  * Write the password by the keypad then Hit the ON button to go forward
  * Reenter the password 
  * If the password is matched, it will be saved in the EEPROM
  * If the password doesn't match, State 1 will be repeated
  
  
* State 2 : Main Options
  * Change Password or Open Door
  
       ![Image of Yaktocat](https://github.com/ahmedibrahim6/Door_Locking_System/blob/master/Images/newpass.PNG)
        
        
* State 3 : Change Password 
  * Enter the password
  * If the entered password is matched with the one saved in EEPROM, State 1 will be in action
  * If not matched , State 3 will be repeated 
  * In case entering a wrong password 5 times then State 5 will be in action .
  
  
* State 4 : Open Door 
  * Enter the password
  * If the entered password is matched with the one saved in EEPROM :
    Motor will be rotated Clockwise for 15 seconds ( Door is opening ) then Anti-Clockwise ( Door is closing ) for the same amount of time
  * In case entering a wrong password 5 times then State 5 will be in action .
  
  
* State 5 : Password mismatch

  * Lock the system for 1.5 minutes
  
