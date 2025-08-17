#ifndef DEBUG_H
#define DEBUG_H

#undef DEBUG

#ifdef DEBUG
    #define DEBUG_ENTRY(name)    Serial.print("DEBUG: "); Serial.print(logno++); Serial.print(".."); Serial.print(name); Serial.print( " Entered\n"); 
    #define DEBUG_EXIT(name)     Serial.print("DEBUG: "); Serial.print(logno++); Serial.print(".."); Serial.print(name); Serial.print( " Completed\n"); 
    #define DEBUG_PRINT(str)     Serial.print("DEBUG: "); Serial.print(logno++); Serial.print(".."); Serial.print(str);
    #define DEBUG_PRINTLN(str)   Serial.print("DEBUG: "); Serial.print(logno++); Serial.print(".."); Serial.println(str);
    #define SERIAL_PRINT(str)    Serial.print(str);
    #define SERIAL_PRINTLN(str)  Serial.println(str);

#else
    #define DEBUG_ENTRY(name)   // name
    #define DEBUG_EXIT(name)    // name
    #define DEBUG_PRINT(str)    // str
    #define DEBUG_PRINTLN(str)  // str
    #define SERIAL_PRINT(str)   // str
    #define SERIAL_PRINTLN(str) // str
#endif

#endif