
/*
 *    --- ANALISADOR DE ENERGIA TCC ---
 *    
 *  (com chip ATM90E36 usando comunicação SPI com ESP8266)
 *  
 *  Autor: Matheus J. Colhyêr
 *  
 *  Licença: Uso restrito. 
 *  
 *  CONTROLE DE VERSÃO:
 *    
 *  RESULTADO: 
 * 
 *  Desenvolvido para a placa ESP8266 NodeMCU
 * 
 */


#include <ESP8266WiFi.h>
#include <ATM90E36.h>                                                         // BIBLIOTECA ATM90E36

#define ESP8266                                                               // DEFINIÇÃO NECESSÁRIA PARA A BIBLIOTECA ATM90E36
#define cs_pin  16                                                            // DEFINIÇÃO DE LOCALIZAÇÃO DE PINO: CS           - 16 (D0_ESP)
#define SCK     14                                                            // DEFINIÇÃO DE LOCALIZAÇÃO DE PINO: SCK          - 14 (D5_ESP)
#define MISO    12                                                            // DEFINIÇÃO DE LOCALIZAÇÃO DE PINO: MISO (DOUT)  - 12 (D6_ESP)
#define MOSI    13                                                            // DEFINIÇÃO DE LOCALIZAÇÃO DE PINO: MOSI (DIN)   - 13 (D7_ESP)

double voltageA;                                                              // DECLARAÇÃO DE VARIÁVEL GLOBAL: TENSÃO RMS FASE A
double voltageB;                                                              // DECLARAÇÃO DE VARIÁVEL GLOBAL: TENSÃO RMS FASE B
double voltageC;                                                              // DECLARAÇÃO DE VARIÁVEL GLOBAL: TENSÃO RMS FASE C

double currentA;                                                              // DECLARAÇÃO DE VARIÁVEL GLOBAL: CORRENTE RMS FASE A 
double currentB;                                                              // DECLARAÇÃO DE VARIÁVEL GLOBAL: CORRENTE RMS FASE B  
double currentC;                                                              // DECLARAÇÃO DE VARIÁVEL GLOBAL: CORRENTE RMS FASE C  

double Frequencia;                                                            // DECLARAÇÃO DE VARIÁVEL GLOBAL: FREQUÊNCIA DE FASE

double TAPower;                                                               // DECLARAÇÃO DE VARIÁVEL GLOBAL: POTÊNCIA ATIVA TOTAL
double AAPower;                                                               // DECLARAÇÃO DE VARIÁVEL GLOBAL: POTÊNCIA ATIVA FASE A
double BAPower;                                                               // DECLARAÇÃO DE VARIÁVEL GLOBAL: POTÊNCIA ATIVA FASE B
double CAPower;                                                               // DECLARAÇÃO DE VARIÁVEL GLOBAL: POTÊNCIA ATIVA FASE C

double THAPower;                                                               // DECLARAÇÃO DE VARIÁVEL GLOBAL: POTÊNCIA HARMÔNICA ATIVA TOTAL
double AHAPower;                                                               // DECLARAÇÃO DE VARIÁVEL GLOBAL: POTÊNCIA HARMÔNICA ATIVA FASE A
double BHAPower;                                                               // DECLARAÇÃO DE VARIÁVEL GLOBAL: POTÊNCIA HARMÔNICA ATIVA FASE B
double CHAPower;                                                               // DECLARAÇÃO DE VARIÁVEL GLOBAL: POTÊNCIA HARMÔNICA ATIVA FASE C

double TRPower;                                                               // DECLARAÇÃO DE VARIÁVEL GLOBAL: POTÊNCIA REATIVA TOTAL
double ARPower;                                                               // DECLARAÇÃO DE VARIÁVEL GLOBAL: POTÊNCIA REATIVA FASE A
double BRPower;                                                               // DECLARAÇÃO DE VARIÁVEL GLOBAL: POTÊNCIA REATIVA FASE B
double CRPower;                                                               // DECLARAÇÃO DE VARIÁVEL GLOBAL: POTÊNCIA REATIVA FASE C

double TAPPower;                                                              // DECLARAÇÃO DE VARIÁVEL GLOBAL: POTÊNCIA APARENTE TOTAL
double AAPPower;                                                              // DECLARAÇÃO DE VARIÁVEL GLOBAL: POTÊNCIA APARENTE FASE A
double BAPPower;                                                              // DECLARAÇÃO DE VARIÁVEL GLOBAL: POTÊNCIA APARENTE FASE B
double CAPPower;                                                              // DECLARAÇÃO DE VARIÁVEL GLOBAL: POTÊNCIA APARENTE FASE C

double TPowerFactor;                                                          // DECLARAÇÃO DE VARIÁVEL GLOBAL: FATOR DE POTÊNCIA TOTAL
double APowerFactor;                                                          // DECLARAÇÃO DE VARIÁVEL GLOBAL: FATOR DE POTÊNCIA FASE A
double BPowerFactor;                                                          // DECLARAÇÃO DE VARIÁVEL GLOBAL: FATOR DE POTÊNCIA FASE B
double CPowerFactor;                                                          // DECLARAÇÃO DE VARIÁVEL GLOBAL: FATOR DE POTÊNCIA FASE C

ATM90E36 analisador(cs_pin);                                                  // DECLARAÇÃO DO ANALISADOR

/*------------------------------------ CONFIGURAÇÃO WIFI -----------------------------------------------------------------------------------------------------------------------------------*/

const char* ssid     = "Ap 402 ";
const char* password = "jm190792";
const char* host = "analisadordosmonitor.000webhostapp.com";                      

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

void setup(){

  Serial.begin(9600);  
  delay(100);
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password); 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP()); 
  Serial.print("Netmask: ");
  Serial.println(WiFi.subnetMask());
  Serial.print("Gateway: ");
  Serial.println(WiFi.gatewayIP());
  
  pinMode(cs_pin,OUTPUT);                                                                     // DECLARAÇÃO DE SAÍDA: CS
  pinMode(SCK, INPUT);                                                                        // DECLARAÇÃO DE SAÍDA: SCK
  pinMode(MISO, INPUT);                                                                       // DECLARAÇÃO DE SAÍDA: MISO
  pinMode(MOSI, INPUT);                                                                       // DECLARAÇÃO DE SAÍDA: MOSI            
                                                                               
  Serial.println("Start ATM90E36");                                                           // INICIALIZA O ANALISADOR
  analisador.begin();                                                                         // INICIALIZA O ATM90E36 + SPI
  
}

void loop() {
  
/*------------------------------------------------------------------------- Banco de Dados -----------------------------------------------------------------------------------------------------------------------------------*/
        
  envia_12_dados("2","VARms",                           analisador.GetLineVoltageA(),             //
                     "VBRms",                           analisador.GetLineVoltageB(),             //
                     "VCRms",                           analisador.GetLineVoltageC(),             //
                     "IARms",                           analisador.GetLineCurrentA(),             //
                     "IBRms",                           analisador.GetLineCurrentB(),             //
                     "ICRms",                           analisador.GetLineCurrentC(),             //
                     "Potencia_Reativa_FASE_B",         analisador.GetReactivePowerB(),           //
                     "Potencia_Reativa_FASE_C",         analisador.GetReactivePowerC(),           //
                     "Potencia_Aparente_Total",         analisador.GetTotalApparentPower(),       //
                     "Potencia_Aparente_FASE_A",        analisador.GetApparentPowerA(),           //
                     "Potencia_Aparente_FASE_B",        analisador.GetApparentPowerB(),           //
                     "Potencia_Aparente_FASE_C",        analisador.GetApparentPowerC()            //
                     );          
                  
  envia_12_dados("2","PFA",                             analisador.GetPowerFactorA(),                          
                     "PFB",                             analisador.GetPowerFactorB(),
                     "PFC",                             analisador.GetPowerFactorC(),
                     "Potencia_Harmonica_Ativa_Fase_A", analisador.GetHarmonicPowerA(),
                     "Potencia_Harmonica_Ativa_Fase_B", analisador.GetHarmonicPowerB(),
                     "Potencia_Harmonica_Ativa_Fase_C", analisador.GetHarmonicPowerC(),
                     "Potencia_Ativa_Total",            analisador.GetTotalActivePower(),
                     "Potencia_Ativa_FASE_A",           analisador.GetActivePowerA(),
                     "Potencia_Ativa_FASE_B",           analisador.GetActivePowerB(),
                     "Potencia_Ativa_FASE_C",           analisador.GetActivePowerC(),
                     "Potencia_Reativa_Total",          analisador.GetTotalReactivePower(),
                     "Potencia_Reativa_FASE_A",         analisador.GetReactivePowerA()
                     );   
                     
  envia_6_dados("2","PFTotal",                 analisador.GetTotalPowerFactor(),
                     "Freq",                   analisador.GetFrequency(),
                     "sys0",                   analisador.GetSysStatus0(),  
                     "sys1",                   analisador.GetSysStatus1(),
                     "en0",                    analisador.GetMeterStatus0(),
                     "en1",                    analisador.GetMeterStatus1()
                     ); 
                     

  envia_12_dados("2","Total_Forward_Active",   analisador.GetValueRegister(APenergyT)/163.84,
                     "A_Forward_Active",       analisador.GetValueRegister(APenergyA)/163.84,
                     "B_Forward_Active",       analisador.GetValueRegister(APenergyB)/163.84,
                     "C_Forward_Active",       analisador.GetValueRegister(APenergyC)/163.84,
                     "Total_Reverse_Active",   analisador.GetValueRegister(RPenergyT)/163.84,
                     "A_Reverse_Active",       analisador.GetValueRegister(RPenergyA)/163.84,
                     "B_Reverse_Active",       analisador.GetValueRegister(RPenergyB)/163.84,
                     "C_Reverse_Active",       analisador.GetValueRegister(RPenergyC)/163.84,
                     "Forward_Reactive",       analisador.GetValueRegister(SAenergyT)/163.84,
                     "A_Forward_Reactive",     analisador.GetValueRegister(SenergyA)/163.84,
                     "B_Forward_Reactive",     analisador.GetValueRegister(SenergyB)/163.84,
                     "C_Forward_Reactive",     analisador.GetValueRegister(SenergyC)/163.84
                     ); 
              
  envia_4_dados("2","Total_Reverse_Reactive",  analisador.GetValueRegister(RNenergyT)/163.84,
                    "A_Reverse_Reactive",      analisador.GetValueRegister(RNenergyA)/163.84,
                    "B_Reverse_Reactive",      analisador.GetValueRegister(RNenergyB)/163.84,
                    "C_Reverse_Reactive",      analisador.GetValueRegister(RNenergyC)/163.84
                    );
                     
  envia_4_dados("2","Total_Apparent_Energy",   analisador.GetValueRegister(SAenergyT)/163.84,
                    "A_Apparent_Energy",       analisador.GetValueRegister(SenergyA)/163.84,
                    "B_Apparent_Energy",       analisador.GetValueRegister(SenergyB)/163.84,
                    "C_Apparent_Energy",       analisador.GetValueRegister(SenergyC)/163.84
                    );
                     
  envia_30_dados("2","Volt_H_R_Fase_A_2",  analisador.GetValueRegister(AV_HR2)/163.84,
                     "Volt_H_R_Fase_A_3",  analisador.GetValueRegister(AV_HR3)/163.84,
                     "Volt_H_R_Fase_A_4",  analisador.GetValueRegister(AV_HR4)/163.84,
                     "Volt_H_R_Fase_A_5",  analisador.GetValueRegister(AV_HR5)/163.84,
                     "Volt_H_R_Fase_A_6",  analisador.GetValueRegister(AV_HR6)/163.84,
                     "Volt_H_R_Fase_A_7",  analisador.GetValueRegister(AV_HR7)/163.84,
                     "Volt_H_R_Fase_A_8",  analisador.GetValueRegister(AV_HR8)/163.84,
                     "Volt_H_R_Fase_A_9",  analisador.GetValueRegister(AV_HR9)/163.84,
                     "Volt_H_R_Fase_A_10", analisador.GetValueRegister(AV_HR10)/163.84,
                     "Volt_H_R_Fase_A_11", analisador.GetValueRegister(AV_HR11)/163.84,
                     "Volt_H_R_Fase_A_12", analisador.GetValueRegister(AV_HR12)/163.84,
                     "Volt_H_R_Fase_A_13", analisador.GetValueRegister(AV_HR13)/163.84,
                     "Volt_H_R_Fase_A_14", analisador.GetValueRegister(AV_HR14)/163.84,
                     "Volt_H_R_Fase_A_15", analisador.GetValueRegister(AV_HR15)/163.84,
                     "Volt_H_R_Fase_A_16", analisador.GetValueRegister(AV_HR16)/163.84,
                     "Volt_H_R_Fase_A_17", analisador.GetValueRegister(AV_HR17)/163.84,
                     "Volt_H_R_Fase_A_18", analisador.GetValueRegister(AV_HR18)/163.84,
                     "Volt_H_R_Fase_A_19", analisador.GetValueRegister(AV_HR19)/163.84,
                     "Volt_H_R_Fase_A_20", analisador.GetValueRegister(AV_HR20)/163.84,
                     "Volt_H_R_Fase_A_21", analisador.GetValueRegister(AV_HR21)/163.84,
                     "Volt_H_R_Fase_A_22", analisador.GetValueRegister(AV_HR22)/163.84,
                     "Volt_H_R_Fase_A_23", analisador.GetValueRegister(AV_HR23)/163.84,
                     "Volt_H_R_Fase_A_24", analisador.GetValueRegister(AV_HR24)/163.84,
                     "Volt_H_R_Fase_A_25", analisador.GetValueRegister(AV_HR25)/163.84,
                     "Volt_H_R_Fase_A_26", analisador.GetValueRegister(AV_HR26)/163.84,
                     "Volt_H_R_Fase_A_27", analisador.GetValueRegister(AV_HR27)/163.84,
                     "Volt_H_R_Fase_A_28", analisador.GetValueRegister(AV_HR28)/163.84,
                     "Volt_H_R_Fase_A_29", analisador.GetValueRegister(AV_HR29)/163.84,
                     "Volt_H_R_Fase_A_30", analisador.GetValueRegister(AV_HR30)/163.84,
                     "Volt_H_R_Fase_A_31", analisador.GetValueRegister(AV_HR31)/163.84,
                     "Volt_H_R_Fase_A_32", analisador.GetValueRegister(AV_HR32)/163.84
                     );
                    
  envia_30_dados("2","Volt_H_R_Fase_B_2",  analisador.GetValueRegister(BV_HR2)/163.84,
                     "Volt_H_R_Fase_B_3",  analisador.GetValueRegister(BV_HR3)/163.84,
                     "Volt_H_R_Fase_B_4",  analisador.GetValueRegister(BV_HR4)/163.84,
                     "Volt_H_R_Fase_B_5",  analisador.GetValueRegister(BV_HR5)/163.84,
                     "Volt_H_R_Fase_B_6",  analisador.GetValueRegister(BV_HR6)/163.84,
                     "Volt_H_R_Fase_B_7",  analisador.GetValueRegister(BV_HR7)/163.84,
                     "Volt_H_R_Fase_B_8",  analisador.GetValueRegister(BV_HR8)/163.84,
                     "Volt_H_R_Fase_B_9",  analisador.GetValueRegister(BV_HR9)/163.84,
                     "Volt_H_R_Fase_B_10", analisador.GetValueRegister(BV_HR10)/163.84,
                     "Volt_H_R_Fase_B_11", analisador.GetValueRegister(BV_HR11)/163.84,
                     "Volt_H_R_Fase_B_12", analisador.GetValueRegister(BV_HR12)/163.84,
                     "Volt_H_R_Fase_B_13", analisador.GetValueRegister(BV_HR13)/163.84,
                     "Volt_H_R_Fase_B_14", analisador.GetValueRegister(BV_HR14)/163.84,
                     "Volt_H_R_Fase_B_15", analisador.GetValueRegister(BV_HR15)/163.84,
                     "Volt_H_R_Fase_B_16", analisador.GetValueRegister(BV_HR16)/163.84,
                     "Volt_H_R_Fase_B_17", analisador.GetValueRegister(BV_HR17)/163.84,
                     "Volt_H_R_Fase_B_18", analisador.GetValueRegister(BV_HR18)/163.84,
                     "Volt_H_R_Fase_B_19", analisador.GetValueRegister(BV_HR19)/163.84,
                     "Volt_H_R_Fase_B_20", analisador.GetValueRegister(BV_HR20)/163.84,
                     "Volt_H_R_Fase_B_21", analisador.GetValueRegister(BV_HR21)/163.84,
                     "Volt_H_R_Fase_B_22", analisador.GetValueRegister(BV_HR22)/163.84,
                     "Volt_H_R_Fase_B_23", analisador.GetValueRegister(BV_HR23)/163.84,
                     "Volt_H_R_Fase_B_24", analisador.GetValueRegister(BV_HR24)/163.84,
                     "Volt_H_R_Fase_B_25", analisador.GetValueRegister(BV_HR25)/163.84,
                     "Volt_H_R_Fase_B_26", analisador.GetValueRegister(BV_HR26)/163.84,
                     "Volt_H_R_Fase_B_27", analisador.GetValueRegister(BV_HR27)/163.84,
                     "Volt_H_R_Fase_B_28", analisador.GetValueRegister(BV_HR28)/163.84,
                     "Volt_H_R_Fase_B_29", analisador.GetValueRegister(BV_HR29)/163.84,
                     "Volt_H_R_Fase_B_30", analisador.GetValueRegister(BV_HR30)/163.84,
                     "Volt_H_R_Fase_B_31", analisador.GetValueRegister(BV_HR31)/163.84,
                     "Volt_H_R_Fase_B_32", analisador.GetValueRegister(BV_HR32)/163.84
                     );
                    
  envia_30_dados("2","Volt_H_R_Fase_C_2",  analisador.GetValueRegister(CV_HR2)/163.84,
                     "Volt_H_R_Fase_C_3",  analisador.GetValueRegister(CV_HR3)/163.84,
                     "Volt_H_R_Fase_C_4",  analisador.GetValueRegister(CV_HR4)/163.84,
                     "Volt_H_R_Fase_C_5",  analisador.GetValueRegister(CV_HR5)/163.84,
                     "Volt_H_R_Fase_C_6",  analisador.GetValueRegister(CV_HR6)/163.84,
                     "Volt_H_R_Fase_C_7",  analisador.GetValueRegister(CV_HR7)/163.84,
                     "Volt_H_R_Fase_C_8",  analisador.GetValueRegister(CV_HR8)/163.84,
                     "Volt_H_R_Fase_C_9",  analisador.GetValueRegister(CV_HR9)/163.84,
                     "Volt_H_R_Fase_C_10", analisador.GetValueRegister(CV_HR10)/163.84,
                     "Volt_H_R_Fase_C_11", analisador.GetValueRegister(CV_HR11)/163.84,
                     "Volt_H_R_Fase_C_12", analisador.GetValueRegister(CV_HR12)/163.84,
                     "Volt_H_R_Fase_C_13", analisador.GetValueRegister(CV_HR13)/163.84,
                     "Volt_H_R_Fase_C_14", analisador.GetValueRegister(CV_HR14)/163.84,
                     "Volt_H_R_Fase_C_15", analisador.GetValueRegister(CV_HR15)/163.84,
                     "Volt_H_R_Fase_C_16", analisador.GetValueRegister(CV_HR16)/163.84,
                     "Volt_H_R_Fase_C_17", analisador.GetValueRegister(CV_HR17)/163.84,
                     "Volt_H_R_Fase_C_18", analisador.GetValueRegister(CV_HR18)/163.84,
                     "Volt_H_R_Fase_C_19", analisador.GetValueRegister(CV_HR19)/163.84,
                     "Volt_H_R_Fase_C_20", analisador.GetValueRegister(CV_HR20)/163.84,
                     "Volt_H_R_Fase_C_21", analisador.GetValueRegister(CV_HR21)/163.84,
                     "Volt_H_R_Fase_C_22", analisador.GetValueRegister(CV_HR22)/163.84,
                     "Volt_H_R_Fase_C_23", analisador.GetValueRegister(CV_HR23)/163.84,
                     "Volt_H_R_Fase_C_24", analisador.GetValueRegister(CV_HR24)/163.84,
                     "Volt_H_R_Fase_C_25", analisador.GetValueRegister(CV_HR25)/163.84,
                     "Volt_H_R_Fase_C_26", analisador.GetValueRegister(CV_HR26)/163.84,
                     "Volt_H_R_Fase_C_27", analisador.GetValueRegister(CV_HR27)/163.84,
                     "Volt_H_R_Fase_C_28", analisador.GetValueRegister(CV_HR28)/163.84,
                     "Volt_H_R_Fase_C_29", analisador.GetValueRegister(CV_HR29)/163.84,
                     "Volt_H_R_Fase_C_30", analisador.GetValueRegister(CV_HR30)/163.84,
                     "Volt_H_R_Fase_C_31", analisador.GetValueRegister(CV_HR31)/163.84,
                     "Volt_H_R_Fase_C_32", analisador.GetValueRegister(CV_HR32)/163.84
                     );
                    
  envia_30_dados("2","CURR_H_R_Fase_A_2",  analisador.GetValueRegister(AI_HR2)/163.84,
                     "CURR_H_R_Fase_A_3",  analisador.GetValueRegister(AI_HR3)/163.84,
                     "CURR_H_R_Fase_A_4",  analisador.GetValueRegister(AI_HR4)/163.84,
                     "CURR_H_R_Fase_A_5",  analisador.GetValueRegister(AI_HR5)/163.84,
                     "CURR_H_R_Fase_A_6",  analisador.GetValueRegister(AI_HR6)/163.84,
                     "CURR_H_R_Fase_A_7",  analisador.GetValueRegister(AI_HR7)/163.84,
                     "CURR_H_R_Fase_A_8",  analisador.GetValueRegister(AI_HR8)/163.84,
                     "CURR_H_R_Fase_A_9",  analisador.GetValueRegister(AI_HR9)/163.84,
                     "CURR_H_R_Fase_A_10", analisador.GetValueRegister(AI_HR10)/163.84,
                     "CURR_H_R_Fase_A_11", analisador.GetValueRegister(AI_HR11)/163.84,
                     "CURR_H_R_Fase_A_12", analisador.GetValueRegister(AI_HR12)/163.84,
                     "CURR_H_R_Fase_A_13", analisador.GetValueRegister(AI_HR13)/163.84,
                     "CURR_H_R_Fase_A_14", analisador.GetValueRegister(AI_HR14)/163.84,
                     "CURR_H_R_Fase_A_15", analisador.GetValueRegister(AI_HR15)/163.84,
                     "CURR_H_R_Fase_A_16", analisador.GetValueRegister(AI_HR16)/163.84,
                     "CURR_H_R_Fase_A_17", analisador.GetValueRegister(AI_HR17)/163.84,
                     "CURR_H_R_Fase_A_18", analisador.GetValueRegister(AI_HR18)/163.84,
                     "CURR_H_R_Fase_A_19", analisador.GetValueRegister(AI_HR19)/163.84,
                     "CURR_H_R_Fase_A_20", analisador.GetValueRegister(AI_HR20)/163.84,
                     "CURR_H_R_Fase_A_21", analisador.GetValueRegister(AI_HR21)/163.84,
                     "CURR_H_R_Fase_A_22", analisador.GetValueRegister(AI_HR22)/163.84,
                     "CURR_H_R_Fase_A_23", analisador.GetValueRegister(AI_HR23)/163.84,
                     "CURR_H_R_Fase_A_24", analisador.GetValueRegister(AI_HR24)/163.84,
                     "CURR_H_R_Fase_A_25", analisador.GetValueRegister(AI_HR25)/163.84,
                     "CURR_H_R_Fase_A_26", analisador.GetValueRegister(AI_HR26)/163.84,
                     "CURR_H_R_Fase_A_27", analisador.GetValueRegister(AI_HR27)/163.84,
                     "CURR_H_R_Fase_A_28", analisador.GetValueRegister(AI_HR28)/163.84,
                     "CURR_H_R_Fase_A_29", analisador.GetValueRegister(AI_HR29)/163.84,
                     "CURR_H_R_Fase_A_30", analisador.GetValueRegister(AI_HR30)/163.84,
                     "CURR_H_R_Fase_A_31", analisador.GetValueRegister(AI_HR31)/163.84
                     "CURR_H_R_Fase_A_32", analisador.GetValueRegister(AI_HR32)/163.84
                     );
                    
  envia_30_dados("2","CURR_H_R_Fase_B_2",  analisador.GetValueRegister(BI_HR2)/163.84,
                     "CURR_H_R_Fase_B_3", analisador.GetValueRegister(BI_HR3)/163.84,
                     "CURR_H_R_Fase_B_4", analisador.GetValueRegister(BI_HR4)/163.84,
                     "CURR_H_R_Fase_B_5", analisador.GetValueRegister(BI_HR5)/163.84,
                     "CURR_H_R_Fase_B_6", analisador.GetValueRegister(BI_HR6)/163.84,
                     "CURR_H_R_Fase_B_7", analisador.GetValueRegister(BI_HR7)/163.84,
                     "CURR_H_R_Fase_B_8", analisador.GetValueRegister(BI_HR8)/163.84,
                     "CURR_H_R_Fase_B_9", analisador.GetValueRegister(BI_HR9)/163.84,
                     "CURR_H_R_Fase_B_10", analisador.GetValueRegister(BI_HR10)/163.84,
                     "CURR_H_R_Fase_B_11", analisador.GetValueRegister(BI_HR11)/163.84,
                     "CURR_H_R_Fase_B_12", analisador.GetValueRegister(BI_HR12)/163.84,
                     "CURR_H_R_Fase_B_13", analisador.GetValueRegister(BI_HR13)/163.84,
                     "CURR_H_R_Fase_B_14", analisador.GetValueRegister(BI_HR14)/163.84,
                     "CURR_H_R_Fase_B_15", analisador.GetValueRegister(BI_HR15)/163.84,
                     "CURR_H_R_Fase_B_16", analisador.GetValueRegister(BI_HR16)/163.84,
                     "CURR_H_R_Fase_B_17", analisador.GetValueRegister(BI_HR17)/163.84,
                     "CURR_H_R_Fase_B_18", analisador.GetValueRegister(BI_HR18)/163.84,
                     "CURR_H_R_Fase_B_19", analisador.GetValueRegister(BI_HR19)/163.84,
                     "CURR_H_R_Fase_B_20", analisador.GetValueRegister(BI_HR20)/163.84,
                     "CURR_H_R_Fase_B_21", analisador.GetValueRegister(BI_HR21)/163.84,
                     "CURR_H_R_Fase_B_22", analisador.GetValueRegister(BI_HR22)/163.84,
                     "CURR_H_R_Fase_B_23", analisador.GetValueRegister(BI_HR23)/163.84,
                     "CURR_H_R_Fase_B_24", analisador.GetValueRegister(BI_HR24)/163.84,
                     "CURR_H_R_Fase_B_25", analisador.GetValueRegister(BI_HR25)/163.84,
                     "CURR_H_R_Fase_B_26", analisador.GetValueRegister(BI_HR26)/163.84,
                     "CURR_H_R_Fase_B_27", analisador.GetValueRegister(BI_HR27)/163.84,
                     "CURR_H_R_Fase_B_28", analisador.GetValueRegister(BI_HR28)/163.84,
                     "CURR_H_R_Fase_B_29", analisador.GetValueRegister(BI_HR29)/163.84,
                     "CURR_H_R_Fase_B_30", analisador.GetValueRegister(BI_HR30)/163.84,
                     "CURR_H_R_Fase_B_31", analisador.GetValueRegister(BI_HR31)/163.84,
                     "CURR_H_R_Fase_B_32", analisador.GetValueRegister(BI_HR32)/163.84
                     ); 
                    
  envia_30_dados("2","CURR_H_R_Fase_C_2",  analisador.GetValueRegister(CI_HR2)/163.84,
                     "CURR_H_R_Fase_C_3",  analisador.GetValueRegister(CI_HR3)/163.84,
                     "CURR_H_R_Fase_C_4",  analisador.GetValueRegister(CI_HR4)/163.84,
                     "CURR_H_R_Fase_C_5",  analisador.GetValueRegister(CI_HR5)/163.84,
                     "CURR_H_R_Fase_C_6",  analisador.GetValueRegister(CI_HR6)/163.84,
                     "CURR_H_R_Fase_C_7",  analisador.GetValueRegister(CI_HR7)/163.84,
                     "CURR_H_R_Fase_C_8",  analisador.GetValueRegister(CI_HR8)/163.84,
                     "CURR_H_R_Fase_C_9",  analisador.GetValueRegister(CI_HR9)/163.84,
                     "CURR_H_R_Fase_C_10", analisador.GetValueRegister(CI_HR10)/163.84,
                     "CURR_H_R_Fase_C_11", analisador.GetValueRegister(CI_HR11)/163.84,
                     "CURR_H_R_Fase_C_12", analisador.GetValueRegister(CI_HR12)/163.84,
                     "CURR_H_R_Fase_C_13", analisador.GetValueRegister(CI_HR13)/163.84,
                     "CURR_H_R_Fase_C_14", analisador.GetValueRegister(CI_HR14)/163.84,
                     "CURR_H_R_Fase_C_15", analisador.GetValueRegister(CI_HR15)/163.84,
                     "CURR_H_R_Fase_C_16", analisador.GetValueRegister(CI_HR16)/163.84,
                     "CURR_H_R_Fase_C_17", analisador.GetValueRegister(CI_HR17)/163.84,
                     "CURR_H_R_Fase_C_18", analisador.GetValueRegister(CI_HR18)/163.84,
                     "CURR_H_R_Fase_C_19", analisador.GetValueRegister(CI_HR19)/163.84,
                     "CURR_H_R_Fase_C_20", analisador.GetValueRegister(CI_HR20)/163.84,
                     "CURR_H_R_Fase_C_21", analisador.GetValueRegister(CI_HR21)/163.84,
                     "CURR_H_R_Fase_C_22", analisador.GetValueRegister(CI_HR22)/163.84,
                     "CURR_H_R_Fase_C_23", analisador.GetValueRegister(CI_HR23)/163.84,
                     "CURR_H_R_Fase_C_24", analisador.GetValueRegister(CI_HR24)/163.84,
                     "CURR_H_R_Fase_C_25", analisador.GetValueRegister(CI_HR25)/163.84,
                     "CURR_H_R_Fase_C_26", analisador.GetValueRegister(CI_HR26)/163.84,
                     "CURR_H_R_Fase_C_27", analisador.GetValueRegister(CI_HR27)/163.84,
                     "CURR_H_R_Fase_C_28", analisador.GetValueRegister(CI_HR28)/163.84,
                     "CURR_H_R_Fase_C_29", analisador.GetValueRegister(CI_HR29)/163.84,
                     "CURR_H_R_Fase_C_30", analisador.GetValueRegister(CI_HR30)/163.84,
                     "CURR_H_R_Fase_C_31", analisador.GetValueRegister(CI_HR31)/163.84,
                     "CURR_H_R_Fase_C_32", analisador.GetValueRegister(CI_HR32)/163.84
                     );
}


/*---------------------------------------------------Funções do Analisador de Energia--------------------------------------------------------------------------------------------*/

/*
void Reducoes_Aumentos_Interrupcoes(){
  Serial.println(opcao);
  Serial.println("");
  Serial.println("|****************************************|");
  Serial.println("|**|  Reduções/Aumentos/Interrupções  |**|");
  Serial.println("|****************************************|");
  Serial.println("");
  delay(1000);
  opcao = -1;
  return;
}

void Desequilibrio(){
  Serial.println(opcao);
  Serial.println("");
  Serial.println("|****************************|");
  Serial.println("|**|     Desequilíbrio    |**|");
  Serial.println("|****************************|");
  Serial.println("");
  delay(1000);
  opcao = -1;
  return;
}

void Irrupcao(){
  Serial.println(opcao);
  Serial.println("");
  Serial.println("|****************************|");
  Serial.println("|**|       Irrupção       |**|");
  Serial.println("|****************************|");
  Serial.println("");
  delay(1000);
  opcao = -1;
  return;
}

*/
