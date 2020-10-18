
//--------------------------------------------------------- ROTINA QUE ENVIA 1 DADO EM UMA SOLICITAÇÃO PARA O BANCO DE DADOS: --------------------------------------------------------------------------
void envia_dados(String id,String param,double reg){                    
  ESP.wdtDisable();
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
  String url = "/api/analisador/update.php?id="+id+"&Param="+param+"&Value="+String(reg);
  if (client.connected()) {
    client.print(String("GET ") + url + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close\r\n\r\n");
  }
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
  client.stop();
  ESP.wdtEnable(1000);
}                                                

//--------------------------------------------------------- ROTINA QUE ENVIA 4 DADOS EM UMA SÓ SOLICITAÇÃO PARA O BANCO DE DADOS: ------------------------------------------------------------------------------------------------------------------
void envia_4_dados(String id,String param_1,double reg_1,           
                             String param_2,double reg_2,
                             String param_3,double reg_3,
                             String param_4,double reg_4)
{
  ESP.wdtDisable();
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
  String url = "/api/analisador/update_4.php?id="+id+"&Param_1="+param_1+"&Value_1="+String(reg_1)+
                                                     "&Param_2="+param_2+"&Value_2="+String(reg_2)+
                                                     "&Param_3="+param_3+"&Value_3="+String(reg_3)+
                                                     "&Param_4="+param_4+"&Value_4="+String(reg_4);
  if (client.connected()) {
    client.print(String("GET ") + url + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close\r\n\r\n");
  }
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
  client.stop();
  ESP.wdtEnable(1000);
}

//--------------------------------------------------------- ROTINA QUE ENVIA 6 DADOS EM UMA SÓ SOLICITAÇÃO PARA O BANCO DE DADOS: ------------------------------------------------------------------------------------------------------------------

void envia_6_dados(String id,String param_1,double reg_1,             
                             String param_2,double reg_2,
                             String param_3,double reg_3,
                             String param_4,double reg_4,
                             String param_5,double reg_5,
                             String param_6,double reg_6)
{
  ESP.wdtDisable();
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
  String url = "/api/analisador/update_6.php?id="+id+"&Param_1="+param_1+"&Value_1="+String(reg_1)+
                                                     "&Param_2="+param_2+"&Value_2="+String(reg_2)+
                                                     "&Param_3="+param_3+"&Value_3="+String(reg_3)+
                                                     "&Param_4="+param_4+"&Value_4="+String(reg_4)+
                                                     "&Param_5="+param_5+"&Value_5="+String(reg_5)+
                                                     "&Param_6="+param_6+"&Value_6="+String(reg_6);
  if (client.connected()) {
    client.print(String("GET ") + url + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close\r\n\r\n");
  }
     
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
  client.stop();
  ESP.wdtEnable(1000);
}

//--------------------------------------------------------- ROTINA QUE ENVIA 12 DADOS EM UMA SÓ SOLICITAÇÃO PARA O BANCO DE DADOS: ------------------------------------------------------------------------------------------------------------------

void envia_12_dados(String id,String param_1,double reg_1,               
                              String param_2,double reg_2,
                              String param_3,double reg_3,
                              String param_4,double reg_4,
                              String param_5,double reg_5,
                              String param_6,double reg_6,
                              String param_7,double reg_7,
                              String param_8,double reg_8,
                              String param_9,double reg_9,
                              String param_10,double reg_10,
                              String param_11,double reg_11,
                              String param_12,double reg_12)
{
  ESP.wdtDisable();
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
  String url = "/api/analisador/update_12.php?id="+id+"&Param_1="+param_1+"&Value_1="   +String(reg_1)+
                                                      "&Param_2="+param_2+"&Value_2="   +String(reg_2)+
                                                      "&Param_3="+param_3+"&Value_3="   +String(reg_3)+
                                                      "&Param_4="+param_4+"&Value_4="   +String(reg_4)+
                                                      "&Param_5="+param_5+"&Value_5="   +String(reg_5)+
                                                      "&Param_6="+param_6+"&Value_6="   +String(reg_6)+
                                                      "&Param_7="+param_7+"&Value_7="   +String(reg_7)+
                                                      "&Param_8="+param_8+"&Value_8="   +String(reg_8)+
                                                      "&Param_9="+param_9+"&Value_9="   +String(reg_9)+
                                                      "&Param_10="+param_10+"&Value_10="+String(reg_10)+
                                                      "&Param_11="+param_11+"&Value_11="+String(reg_11)+
                                                      "&Param_12="+param_12+"&Value_12="+String(reg_12);
  if (client.connected()) {
    client.print(String("GET ") + url + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close\r\n\r\n");
  }
     
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
  client.stop();
  ESP.wdtEnable(1000);
}

//--------------------------------------------------------- ROTINA QUE ENVIA 30 DADOS EM UMA SÓ SOLICITAÇÃO PARA O BANCO DE DADOS: ------------------------------------------------------------------------------------------------------------------

void envia_30_dados(String id,String param_1,double reg_1,                //ROTINA QUE ENVIA 30 DADOS EM UMA SÓ SOLICITAÇÃO PARA O BANCO DE DADOS
                              String param_2,double reg_2,          
                              String param_3,double reg_3,
                              String param_4,double reg_4,
                              String param_5,double reg_5,
                              String param_6,double reg_6,
                              String param_7,double reg_7,
                              String param_8,double reg_8,
                              String param_9,double reg_9,
                              String param_10,double reg_10,
                              String param_11,double reg_11,
                              String param_12,double reg_12,
                              String param_13,double reg_13,
                              String param_14,double reg_14,
                              String param_15,double reg_15,
                              String param_16,double reg_16,
                              String param_17,double reg_17,
                              String param_18,double reg_18,
                              String param_19,double reg_19,
                              String param_20,double reg_20,
                              String param_21,double reg_21,
                              String param_22,double reg_22,
                              String param_23,double reg_23,
                              String param_24,double reg_24,
                              String param_25,double reg_25,
                              String param_26,double reg_26,
                              String param_27,double reg_27,
                              String param_28,double reg_28,
                              String param_29,double reg_29,
                              String param_30,double reg_30,
                              String param_31,double reg_31)
{
  ESP.wdtDisable();
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
  String url = "/api/analisador/update_30.php?id="+id+"&Param_1="+param_1+"&Value_1="   +String(reg_1) +
                                                      "&Param_2="+param_2+"&Value_2="   +String(reg_2) +
                                                      "&Param_3="+param_3+"&Value_3="   +String(reg_3) +
                                                      "&Param_4="+param_4+"&Value_4="   +String(reg_4) +
                                                      "&Param_5="+param_5+"&Value_5="   +String(reg_5) +
                                                      "&Param_6="+param_6+"&Value_6="   +String(reg_6) +
                                                      "&Param_7="+param_7+"&Value_7="   +String(reg_7) +
                                                      "&Param_8="+param_8+"&Value_8="   +String(reg_8) +
                                                      "&Param_9="+param_9+"&Value_9="   +String(reg_9) +
                                                      "&Param_10="+param_10+"&Value_10="+String(reg_10)+
                                                      "&Param_11="+param_11+"&Value_11="+String(reg_11)+
                                                      "&Param_12="+param_12+"&Value_12="+String(reg_12)+
                                                      "&Param_13="+param_13+"&Value_13="+String(reg_13)+
                                                      "&Param_14="+param_14+"&Value_14="+String(reg_14)+
                                                      "&Param_15="+param_15+"&Value_15="+String(reg_15)+
                                                      "&Param_16="+param_16+"&Value_16="+String(reg_16)+
                                                      "&Param_17="+param_17+"&Value_17="+String(reg_17)+
                                                      "&Param_18="+param_18+"&Value_18="+String(reg_18)+
                                                      "&Param_19="+param_19+"&Value_19="+String(reg_19)+
                                                      "&Param_20="+param_20+"&Value_20="+String(reg_20)+
                                                      "&Param_21="+param_21+"&Value_21="+String(reg_21)+
                                                      "&Param_22="+param_22+"&Value_22="+String(reg_22)+
                                                      "&Param_23="+param_23+"&Value_23="+String(reg_23)+
                                                      "&Param_24="+param_24+"&Value_24="+String(reg_24)+
                                                      "&Param_25="+param_25+"&Value_25="+String(reg_25)+
                                                      "&Param_26="+param_26+"&Value_26="+String(reg_26)+
                                                      "&Param_27="+param_27+"&Value_27="+String(reg_27)+
                                                      "&Param_28="+param_28+"&Value_28="+String(reg_28)+
                                                      "&Param_29="+param_29+"&Value_29="+String(reg_29)+
                                                      "&Param_30="+param_30+"&Value_30="+String(reg_30)+
                                                      "&Param_31="+param_31+"&Value_31="+String(reg_31);
  if (client.connected()) {
    client.print(String("GET ") + url + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close\r\n\r\n");
  }
     
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
  client.stop();
  ESP.wdtEnable(1000);
}
