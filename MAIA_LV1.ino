//--------------------------------------------------------------------------------------------------------------------------------------------------------------//
//                                                                                                                                                              //
//                                                            MAIA - MOBILE AWARE INTERMODAL ASSISTANT                                                          //
//                                                    DELL LEAD - RESEARCH, DEVELOPMENT AND INNOVATION CENTER                                                   //
//                                                                                                                                                              //
//--------------------------------------------------------------------------------------------------------------------------------------------------------------//

/////////////////////////////////////////////////////////////////////////// LIBRARIES ////////////////////////////////////////////////////////////////////////////

#include <SoftwareSerial.h>
#include <HamShield.h> 

////////////////////////////////////////////////////////////////////////// DEFINITIONS ///////////////////////////////////////////////////////////////////////////

#define MIC_PIN        3  // Pin responsible for sending audios in the raw format (It won't be used because the audios will be sent through the TRRS jack cable)
#define RESET_PIN     A3  // Reset pin
#define SWITCH_PIN     2  // Pin responsible for alternating between transmit and receive modes (switch)
#define ARDUINO_RX     5  // It has to be connected to the TX pin of the MP3 module
#define ARDUINO_TX     6  // It has to be connected to the RX pin of the MP3 module
#define RADIO_FLAG     7  // Transmission operation indicator LED 
#define CMD_SEL_DEV 0X09  // Selects the storage device for the TF card --> Require complement (00 00)
#define DEV_TF      0X02

//////////////////////////////////////////////////////////////////////////// OBJECTS ////////////////////////////////////////////////////////////////////////////

HamShield radio;
SoftwareSerial mp3(ARDUINO_RX, ARDUINO_TX);

/////////////////////////////////////////////////////////////////////////// VARIABLES ///////////////////////////////////////////////////////////////////////////

static int8_t send_buf[8] = {0};  // Buffer to storage commands to be sent
uint32_t freq;                     // It will keep the radio frequency
char requests[50];
String leader = "";
String line = "";
String area = "";
int8_t audio1_index = 0;
int8_t audio2_index = 0;
int8_t audio3_index = 0;
char aux = ' ';                  // Used to help in the data reception during the serial communication
byte i;

/////////////////////////////////////////////////// FREQUENCIES (IN MHz) OF THE CHANNELS USED INSIDE THE FACTORY ////////////////////////////////////////////////

/*
    EMR Team (repair team)          01         (462562 MHz)
    ARB Team                        02         (462587 MHz)
    IT                              03         (462612 MHz)
    PC - Production Control         04         (462637 MHz)
    EHS – Emergency                 05         (462662 MHz)
    CFI                             06         (462687 MHz)
    Control Room / MDT / Office     07         (462712 MHz)
    Process engineering             08         (467562 MHz)
    Manufacture                     09         (467587 MHz)
    Materials                       10         (467612 MHz)
    Maintenance                     14         (467712 MHz)
    Test engineering                15         (462550 MHz)
    NPI                             17         (462600 MHz)
    Quality                         20         (462675 MHz)

    String example: EMR/GL1/QT/ysdh8asd5
*/

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void empty_string(){
  for(i=0;i<50;i++){
    requests[i] = ' ';
  }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// It will define the operation frequency of the radio, according to the leader wanted
void select_leader(String leader){
  if(leader.equals("EMR")){
    freq = 462562;
    configure();
  }
  else{
    if(leader.equals("ARB")){
      freq = 462587;
      configure();
    }
    else{
      if(leader.equals("IT")){
        freq = 462612;
        configure();
      }
      else{
        if(leader.equals("PC")){
          freq = 462637;
          configure();
        }
        else{
          if(leader.equals("EHS")){
            freq = 462662;
            configure();
          }
          else{
            if(leader.equals("CFI")){
              freq = 462687;
              configure();
            }
            else{
              if(leader.equals("MDT")){
                freq = 462712;
                configure();
              }
              else{
                if(leader.equals("EP")){
                  freq = 467562;
                  configure();
                }
                else{
                  if(leader.equals("MFT")){
                    freq = 467587;
                    configure();
                  }
                  else{
                    if(leader.equals("MTR")){
                      freq = 467612;
                      configure();
                    }
                    else{
                      if(leader.equals("MNT")){
                        freq = 467712;
                        configure();
                      }
                      else{
                        if(leader.equals("ET")){
                          freq = 462550;
                          configure();
                        }
                        else{
                          if(leader.equals("NPI")){
                            freq = 462600;
                            configure();
                          }
                          else{
                            if(leader.equals("QLD")){
                              freq = 462675;
                              configure();
                            }                           
                          }
                        }
                      }
                    }
                  }              
                }        
              }
            }
          }
        }
      }
    }
  }
   
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// It will define the first part of the audio (line where the worker is)
void select_line(String line){
  audio1_index = 0;
  if(line.equals("GL1") or line.equals("GL01")){
    audio1_index = 0x01;
  }
  else{
    if(line.equals("GL2") or line.equals("GL02")){
      audio1_index = 0x02;
    }
    else{
      if(line.equals("GL3") or line.equals("GL03")){
        audio1_index = 0x03;
      }
      else{
        if(line.equals("GL4") or line.equals("GL04")){
          audio1_index = 0x04;
        }
        else{
          if(line.equals("GL5") or line.equals("GL05")){
            audio1_index = 0x05;
          }
          else{
            if(line.equals("GL6") or line.equals("GL06")){
              audio1_index = 0x06;
            }
            else{
              if(line.equals("GL7") or line.equals("GL07")){
                audio1_index = 0x07;
              }
              else{
                if(line.equals("GL8") or line.equals("GL08")){
                  audio1_index = 0x08;
                }
                else{
                  if(line.equals("GL9") or line.equals("GL09")){
                    audio1_index = 0x09;
                  }
                  else{
                    if(line.equals("GL10")){
                      audio1_index = 0x0A;
                    }
                    else{
                      if(line.equals("GL11")){
                        audio1_index = 0x0B;
                      }
                      else{
                        if(line.equals("GL12")){
                          audio1_index = 0x0C;
                        }
                        else{
                          if(line.equals("GL13")){
                            audio1_index = 0x0D;
                          }
                          else{
                            if(line.equals("GL14")){
                              audio1_index = 0x0E;
                            }
                            else{
                              if(line.equals("GL15")){
                                audio1_index = 0x0F;
                              }
                              else{
                                if(line.equals("GL16")){
                                  audio1_index = 0x10;
                                }
                                else{
                                  if(line.equals("GL17")){
                                    audio1_index = 0x11;
                                  }
                                  else{
                                    if(line.equals("GL18")){
                                      audio1_index = 0x12;
                                    }
                                    else{
                                      if(line.equals("GL19")){
                                        audio1_index = 0x13;
                                      }
                                      else{
                                        if(line.equals("GL20")){
                                          audio1_index = 0x14;
                                        }
                                        else{
                                          if(line.equals("Burn")){
                                            audio1_index = 0x15;
                                          }
                                          else{
                                            if(line.equals("Boxing")){
                                              audio1_index = 0x16;
                                            }
                                            else{
                                            }
                                          }
                                        }
                                      }
                                    }
                                  }
                                }
                              }
                            }                            
                          }
                        }
                      }
                    }
                  }              
                }        
              }
            }
          }
        }
      }
    }
  }

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// It will define the second part of the audio (area of the line where the worker is)
void select_area(String area){
  audio2_index = 0;
  if(area.equals("QT")){
    audio2_index = 0x01;
  }
  else{
    if(area.equals("EMR")){
      audio2_index = 0x02;
    }
    else{
      if(area.equals("Kitting")){
        audio2_index = 0x03;
      }
      else{
        if(area.equals("Montagem")){
          audio2_index = 0x04;
        }
        else{
          if(area.equals("Desktop")){
            audio2_index = 0x05;
          }
          else{
            if(area.equals("Notebook")){
              audio2_index = 0x06;
            }
            else{
              if(area.equals("Servidor")){
                audio2_index = 0x07;
              }
            }
          }
        }
      }
    }
  }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void separate_string(){
  byte c = 0;
  int j = 0;
  leader = "";
  line = "";
  area = "";
  for(j=0;j<50;j++){
    if(requests[j]!='/'){
      if(requests[j]=='\0'){
        break;
      }
      else{
        if(c==0){
          leader+=requests[j];
        }
        else{
              if(c==1){
                line+=requests[j];
              }
              else{
                if(c==2){
                  area+=requests[j];
                }
                else{
                  if(c==3){
                    break;
                  }
                }
              }
        }
      }
    }
    else{
      c++;
    }
  }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_max_volume(){
  send_command(0x06, 0x1E); 
} // Fim do set_max_volume

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void send_command(int8_t command, int16_t dat){
  delay(20);
  send_buf[0] = 0x7E;   
  send_buf[1] = 0xFF;   
  send_buf[2] = 0x06;   
  send_buf[3] = command;
  send_buf[4] = 0x01;  
  send_buf[5] = (int8_t)(dat >> 8);  
  send_buf[6] = (int8_t)(dat);     
  send_buf[7] = 0xEF; 
  for (uint8_t i = 0; i < 8; i++){
    mp3.write(send_buf[i]) ;
  } // Fim do for
} // Fim do send_command

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void select_audio(int8_t folder, int8_t song){
  delay(20);
  send_buf[0] = 0x7E;   
  send_buf[1] = 0xFF;   
  send_buf[2] = 0x06;   
  send_buf[3] = 0x0F;
  send_buf[4] = 0x01;  
  send_buf[5] = folder;
  send_buf[6] = song;  
  send_buf[7] = 0xEF; 
  for (uint8_t i = 0; i < 8; i++){
    mp3.write(send_buf[i]) ;
  } // Fim do for
} // Fim do select_audio

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void send_message(){
  delay(500);
  select_audio(01, audio1_index);
  delay(3000);
  select_audio(02, audio2_index);
  delay(2000);
} // Fim do send_message

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// This function will prepare the radio to transmit on the right frequency, and then send the audio to the walkie-talkie
void configure(){
  digitalWrite(RADIO_FLAG, HIGH);
  radio.frequency(freq);
  radio.setModeTransmit();
  delay(200);
  radio.setUnmute();
  delay(100);
  radio.setUnmute();
  delay(100);
  send_message();
  radio.setMute();
  delay(1500);
  radio.setUnmute();
  radio.setModeReceive();
  radio.setMute();
  radio.setUnmute();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Gives a feedback to the listener, emtiting a long beep, if 'positive' was understood; or three short beeps, if it was 'negative'
void feedback(){
  if (requests[0] == 'n'){
    audio3_index = 0x01;
  }
  else{
    audio3_index = 0x02;
  }
  
  int j = 2;
  String leader2 = "";
  
  while(requests[j]!='/'){
    leader2+=requests[j++];
    if(requests[j]=='\0'){
      break;
    }
  }
  
  if(leader2.equals("EMR")){
    freq = 462562;
  }
  else{
    if(leader2.equals("ARB")){
      freq = 462587;
    }
    else{
      if(leader2.equals("IT")){
        freq = 462612;
      }
      else{
        if(leader2.equals("PC")){
          freq = 462637;
        }
        else{
          if(leader2.equals("EHS")){
            freq = 462662;
          }
          else{
            if(leader2.equals("CFI")){
              freq = 462687;
            }
            else{
              if(leader2.equals("MDT")){
                freq = 462712;
              }
              else{
                if(leader2.equals("EP")){
                  freq = 467562;
                }
                else{
                  if(leader2.equals("MFT")){
                    freq = 467587;
                  }
                  else{
                    if(leader2.equals("MTR")){
                      freq = 467612;
                    }
                    else{
                      if(leader2.equals("MNT")){
                        freq = 467712;
                      }
                      else{
                        if(leader2.equals("ET")){
                          freq = 462550;
                        }
                        else{
                          if(leader2.equals("NPI")){
                            freq = 462600;
                          }
                          else{
                            if(leader2.equals("QLD")){
                              freq = 462675;
                            }                            
                          }
                        }
                      }
                    }
                  }              
                }        
              }
            }
          }
        }
      }
    }
  }

  radio.frequency(freq);
  radio.setModeTransmit();
  delay(200);
  radio.setUnmute();
  delay(100);
  radio.setUnmute();
  delay(100);
  select_audio(03, audio3_index);
  delay(2000);
  radio.setMute();
  delay(1500);
  radio.setUnmute();
  radio.setModeReceive();
  radio.setMute();
  radio.setUnmute();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void setup() {
  // HamShield configuration
  pinMode(MIC_PIN, OUTPUT);
  digitalWrite(MIC_PIN, LOW);  // Will be kept at low logical level, since PWM will not be used to transmit the audios (we're using the TRRS cable)
  pinMode(RADIO_FLAG, OUTPUT);
  digitalWrite(RADIO_FLAG, LOW);
  pinMode(SWITCH_PIN, INPUT_PULLUP);
  pinMode(RESET_PIN, OUTPUT);
  digitalWrite(RESET_PIN, LOW);
  
  Serial.begin(9600);
  delay(500);
  digitalWrite(RESET_PIN, HIGH);
  delay(5);  // Wait the system to stablish
  radio.initialize();  // Initialize automatically UHF 12.5kHz channel
  freq = 462562;
  radio.dangerMode();
  radio.frequency(freq);
  radio.setModeReceive();
  radio.setSQLoThresh(-90);
  radio.setSQHiThresh(-1);
  radio.setSQOn();
  radio.setRfPower(7);
  radio.setCtcss(66.98);
  radio.enableCtcss();

  // MP3 module configuration
  mp3.begin(9600);
  delay(500);
  //          (  Command  ,  Data )
  send_command(CMD_SEL_DEV, DEV_TF);  // Selects the storage device for the TF card
  delay(100);
  set_max_volume();
  delay(100);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void loop() {
  i = 0;
  if(Serial.available()){
    radio.setUnmute();
    empty_string();
    i = 0;
    aux = ' ';
    while(Serial.available()){
      aux = Serial.read();
      requests[i]=aux;
      delay(20);
      i++;
    }
    if(requests[0] == 'n' || requests[0] == 'p'){
      digitalWrite(RADIO_FLAG, HIGH);
      feedback();
    }
    else{
      separate_string();
      select_line(line);
      select_area(area);
      select_leader(leader);
    }
    digitalWrite(RADIO_FLAG, LOW);
  }  // Global if
}  // loop

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
