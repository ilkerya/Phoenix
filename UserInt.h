
void UpdateDisplayBuffer(void){  
    Display_Line1 = String(Str_Date) + "   " + String(Str_Time);
    UpdateSD_LogTime();// Line2
    UpdateFileSize();// Line3
    UpdateProperLine(DispRollIndex[0], 4); // Line 4
    UpdateProperLine(DispRollIndex[1], 5); // Line 5
    UpdateProperLine(DispRollIndex[2], 6); // Line 6
    UpdateProperLine(DispRollIndex[3], 7); // Line 7
    // DisplayFullSensors();   
    UpdateDisplayMenu(); // Line8    
}

void UpdateFileSize(){
    String str;unsigned long Remain;unsigned long Remain2;
    str = "    "; //4
    if( FileSize.Total == 0) str += " ";//10
    
      if(FileSize.Total < 100000000)str += ' ';   // 100 Mb     
      if(FileSize.Total < 10000000)str += ' ';   // 10 Mb    
      if(FileSize.Total < 1000000)str += ' ';   // 1 Mb
      if(FileSize.Total < 100000)str += ' ';   // 100 kb
      if(FileSize.Total < 10000)str += ' ';   // 10 kb      
      if(FileSize.Total < 1000)str += ' ';   // 1 kb
      if(FileSize.Total < 100)str += ' ';   // 100 byte
      if(FileSize.Total < 10)str += ' ';   // 10  byte  
      if(FileSize.Total >= 1000000){  // 1 mb   // find out the 1millions dot place and remaining leading zeros
        str += String(FileSize.Total / 1000000);  // 9 digit 
        str +='.';  // 9 digit 
        Remain = FileSize.Total % 1000000;        
        if(Remain < 100000)str += '0'; //  _50000
        if(Remain < 10000)str += '0';  //  __5000
        if(Remain < 1000)str += '0';  //  ___500
      
        if(Remain  >= 1000){
          Remain2 = Remain % 1000;
          str += String(Remain / 1000);  // 9 digit 
          str +='.';   // 9 digit
          if(Remain2 < 100)str += '0';
          if(Remain2 < 10)str += '0';
          str += String(Remain2);  // 9 digit       
        }  
      }
      else if(FileSize.Total >= 1000){ // find out the 1000s dot place and remaining leading zeros
        Remain = FileSize.Total % 1000;
        str += String(FileSize.Total / 1000);  // 9 digit 
        str +='.';   // 9 digit 
        if(Remain < 100)str += '0';
        if(Remain < 10)str += '0';
        str += String(Remain);  // 9 digit 
      }
      else str += String(FileSize.Total); // less than 1000 
             
      str += String(" Bytes"); //9 digit  total 15   
      Display_Line3 = str;
}

void PrintDisplayBuffer(void){
      Serial.println();
      Serial.println();
      Serial.println("   DISPLAY  8x21     ");
      Serial.println(Display_Line1);
      Serial.println(Display_Line2);
      Serial.println(Display_Line3);
      Serial.println(Display_Line4);
      Serial.println(Display_Line5);
      Serial.println(Display_Line6);
      Serial.println(Display_Line7);
      Serial.println(Display_Line8);
      Serial.println();
      Serial.println();   

    // Additionals
    Serial.print("DevId: ");Serial.print(EE_Id_EString);
    Serial.print("    Sensor1: ");Serial.print(Sensor1_Id);
    Serial.print("    Sensor2: ");Serial.print(Sensor2_Id);
    Serial.print("    Sensor3: ");Serial.print(Sensor3_Id);

    Serial.println();   
    //Compiled: Jul 21 2020 15:55:39 7.3.0
    Serial.println( "Compiled: " + FW_Version  + ' ' + __VERSION__);  // 11 1 8
   // Serial.println( "Compiled: " __DATE__ ", " __TIME__ ", " __VERSION__); 

    Serial.print("RELAY 1:");Serial.println(digitalRead(RELAY_OUT_1));
    Serial.print("RELAY 2:");Serial.println(digitalRead(RELAY_OUT_2));   
     
     
    Serial.println();
    Serial.println();     
}
char* UpdateTempHumSensor(byte Que, float Temperature, float Humidity){

 /*
  String s = "geeksforgeeks";   
    int n = s.length();  
    // declaring character array 
    char char_array[n + 1]; 
    // copying the contents of the 
    // string to char array 
    strcpy(char_array, s.c_str()); 
*/
  
  String str;
      switch(Que){
        case 1:str = "1.";
        break;
        case 2:str = "2.";
        break;
        case 3:str = "3.";
        break; 
        default:
        break;                       
      }      
          if (!isnan(Temperature)) {
            str += String(Temperature,1);
            str += " C";   DispExpSens1 = ON;               //  str += '°'; 
          }
          else  str += "------";        
          if (!isnan(Humidity)) {
            str +=" %";
            str += String((int)Humidity); // 
          }
          else   str +="----";         
          str += ' ' + Sensor1_Id;   
        // converting str to char array
       int Length = str.length(); 
        char char_array[Length+ 1]; 
        strcpy(char_array, str.c_str());       
        return &char_array[0];
}
const char* myName() {
  String s = "String";   
  char *name = "Ilker";
  return name;
}
#define MAXNOCHAR 4
void UpdateProperLine(byte Index, byte Line){
    String str = String(Index)+ ".";
    String Tempstr;
    switch(Index){
      case 0: str = "";//// show nothing                 
      break;    
    //  case 1: str += " FW " + FW_Version;  // fw version compile time             
   //   break;
   //   case 2: str += " Dev Id: " + EE_Id_EString;  // device id           
   //   break;
      case 1:   
          if (!isnan(Values.TemperatureSi072_Ch1)) {
            str += String(Values.TemperatureSi072_Ch1,1);
            str += " C";  DispExpSens1 = ON;                           
          }
          else  str += "------";       
          if (!isnan(Values.Humidity_Ch1)) {
            str +=" %";
            str += String((int)Values.Humidity_Ch1); // 10...
          }
          else   str +="----"; 
          str += ' ' + Sensor1_Id;
          
     break;
     case 2: //str = "4."; // temp sensor2
          if (!isnan(Values.TemperatureSi072_Ch2)) {
            str += String(Values.TemperatureSi072_Ch2,1);
            str += " C";   DispExpSens2 = ON;               //  str += '°'; 
          }
          else  str += "------";        
          if (!isnan(Values.Humidity_Ch2)) {
            str +=" %";
            str += String((int)Values.Humidity_Ch2); // 
          }
          else   str +="----";
          str += ' ' + Sensor2_Id;              
     break;
     case 3: //str = "5."; // temp sensor3
         if (!isnan(Values.TemperatureSi072_Ch3)) {
            str += String(Values.TemperatureSi072_Ch3,1);
            str += " C";    DispExpSens3 = ON;
        }
        else  str += "------";  
        if (!isnan(Values.Humidity_Ch3)) {
          str +=" %";
          str += String((int)Values.Humidity_Ch3); // 
        }
        else   str +="----";   // 10 lines
        str += ' ' + Sensor3_Id;             
     break;
     case 4:       
              #ifdef VOLTAGE_MEASURE_EXISTS
               // str += " " + String(Mains_Volt) + "V ";  
                str += " " + String(Mains_Volt) + "V ";  
             #endif
             #ifdef LEM_CURRENT_EXISTS               
                str += String(Current_Mains_Rms) + "A ";  
            #endif

             #ifdef AD9153_PROTOTYPE 
              str += " " +String(Values.Current)+ "A "; // 3/4/2
              str +=String((unsigned int)Values.Voltage)+ "V "; //4/2  
              if(Values.Voltage > 32) {
               // str += String((byte)pqVals.FrequencyValue)+ "Hz"; //4
                str += String(Values.Frequency)+ "Hz"; //4
              }
              else  str += "--Hz"; //4
            #endif 
     break;      
     case 5:    

             #ifdef AD9153_PROTOTYPE 
          //   str += "7. " + String(powerVals.ActivePowerValue/1000)+ " w "; // 3/4/3
              str += " " + String(Values.ActivePower)+ " w "; // 3/4/3
              str += "PF " + String(Values.PowerFactor)+ " ";  // 3/4/1 
               
            #endif 
     break; 
     case 6:   
            #ifdef PM25_DUST_SENSOR_EXISTS  
            
            str += " PM2.5: ";
              //  str += "7. PM2.5: ";
                  if(Values.PM25 < 100.00)str +=  String(Values.PM25,1);
                  else str += String(Values.PM25,0);
            #endif 
                 
     break;  
     case 7:  
          str += "R1:" +String(digitalRead(RELAY_OUT_1))+ " "; //7 + 1     
         // str +=  String((unsigned int)RL1Min) +   RLlVal  +  String((unsigned int)RL1Max);
          for(int i = 0; i < MAXNOCHAR; i++){
            str += RlStr2[i];  // Limit Str length to 4 20.4 // 124. // 1378
          }      
          str += " " +  RLlVal + " ";   
          for(int i = 0; i < MAXNOCHAR; i++){
            str += RlStr4[i];
          }  
      break;  
      case 8:    
          str += "R2:" +String(digitalRead(RELAY_OUT_2))+ " "; //7 + 1
          for(int i = 0; i < MAXNOCHAR; i++){
            str += RlStr6[i];  // Limit Str length to 4 20.4 // 124. // 1378
          }      
          str += " " +  RL2Val + " "; 
          for(int i = 0; i < MAXNOCHAR; i++){
            str += RlStr8[i];
          }  
      break;       
             
    default: str = "default";
    break; 
    }     
    switch(Line){
      case 4: Display_Line4 = str;                  
      break; 
      case 5: Display_Line5 = str;             
      break;
      case 6:Display_Line6 = str;
      break;
      case 7:Display_Line7 = str;     
      break;
      default:              // 
      break;
    }        
}


void SDCard_or_File(){

    switch(DisplayValueTimer){
      case 0:
      case 2:
      case 4:       
           if(SDCard.Status = SD1_TYPE)      Display_Line2 = "SD1 ";         
           else if(SDCard.Status = SD2_TYPE) Display_Line2 = "SD2 ";           
           else if(SDCard.Status = SDHC_TYPE)Display_Line2 = "SDH ";
           Display_Line2 += String(SD_Volume) + "Gb " ;   // 4+5+3
         break;
      case 1:
      case 3: 
           Display_Line2 = String(LOG_FILE) ; // 12
         break;
   //   case 4:
   //      break;
         default:
         break;  
    }      
}
void UpdateSD_LogTime(){
    if(SDCard.PauseTimer){
      Display_Line2 = "SD Error   Retry-> "; //18
      Display_Line2 += String(SDCard.PauseTimer);//13
     // " Try in"  //7
      return;     
  }
  
    if(SDCard.Status != SD_NOT_Present){
      SDCard_or_File();           
      Display_Line2 += "   "; // 3    
      switch(SampleTime){
       case TASK_500MSEC:Display_Line2 += "0.5Sec"; //5 
          break;        
        case TASK_1SEC : Display_Line2 += "  1Sec";//5
          break; 
        case TASK_2SEC : Display_Line2 += "  2Sec";
          break;        
        case TASK_5SEC : Display_Line2 += "  5Sec";
          break;  
        case TASK_10SEC :Display_Line2 += " 10Sec";
          break; 
        case TASK_20SEC :Display_Line2 += " 20Sec";
          break;            
        case TASK_60SEC :Display_Line2 += " 60Sec";
          break;     
      }     
    }
    else Display_Line2 = "SD Error             ";

}
