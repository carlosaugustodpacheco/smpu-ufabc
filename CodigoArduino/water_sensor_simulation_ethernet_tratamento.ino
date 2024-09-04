//  SISTEMA DE MONITORAMENTO PLUVIAL URBANO - TCC UFABC - CARLOS PACHECO
// VERSÃO 1 - Regra de negócio tratando valores captados por sensor e enviando aviso para um Web Server via Ethernet.
// SMPU MODELO PARA (CIDADE:SÃO PAULO/ REGIÃO: 1 / MÓDULO SMPU: 1 )

#include <LiquidCrystal.h>
#include <EtherCard.h>

//inicializa pins de valores do LCD
LiquidCrystal lcd(7, 6, 5, 4, 3, 2); 
 
int resval = 0;  // armazena valor da resistencia gerada por sensor de nivel de agua
int respin = A3; // pin do sensor de nivel de água

// Configuração de IP Estatico
static byte myip[] = { 169, 254, 199, 140 }; // IP do Web Server (169.254.199.140) - usar no navegador para acessar Web Server
static byte gwip[] = { 169, 254, 229, 192 }; // IP do Módulo Ethernet (169.254.229.192) - usar para configurar Módulo no Simulador Proteus

// MAC address do Arduino
static byte mymac[] = { 0x74, 0x69, 0x69, 0x2D, 0x30, 0x31 };


// tamanho do buffer da Ethernet
byte Ethernet::buffer[700];

// Pagina HTML para Situação Normal(armazenada na variavel PROGMEM)
const char situacaoNormal[] PROGMEM =
  "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nConnection: close\r\n\r\n"
                        "<html>\r\n"
                        "<head>\r\n"
                        "<meta http-equiv='refresh' content='3'>\r\n"
                        "</head>\r\n"
                        "<body>\r\n"
                        "estado:sp;cidade:sao_paulo;regiao:1;smpu:1;nivel_da_agua:situacao_normal;\r\n"
                        "</body>\r\n"
                        "</html>\r\n";

// Pagina HTML para Alerta Leve(armazenada na variavel PROGMEM)
const char alertaLeve[] PROGMEM =
  "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nConnection: close\r\n\r\n"
                        "<html>\r\n"
                        "<head>\r\n"
                        "<meta http-equiv='refresh' content='3'>\r\n"
                        "</head>\r\n"
                        "<body>\r\n"
                        "estado:sp;cidade:sao_paulo;regiao:1;smpu:1;nivel_da_agua:alerta_leve;\r\n"
                        "</body>\r\n"
                        "</html>\r\n";

// Pagina HTML para Alerta Moderado(armazenada na variavel PROGMEM)
const char alertaModerado[] PROGMEM =
  "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nConnection: close\r\n\r\n"
                        "<html>\r\n"
                        "<head>\r\n"
                        "<meta http-equiv='refresh' content='3'>\r\n"
                        "</head>\r\n"
                        "<body>\r\n"
                        "estado:sp;cidade:sao_paulo;regiao:1;smpu:1;nivel_da_agua:alerta_moderado;\r\n"
                        "</body>\r\n"
                        "</html>\r\n";

// Pagina HTML para Alerta Grave(armazenada na variavel PROGMEM)
const char alertaGrave[] PROGMEM =
  "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nConnection: close\r\n\r\n"
                        "<html>\r\n"
                        "<head>\r\n"
                        "<meta http-equiv='refresh' content='3'>\r\n"
                        "</head>\r\n"
                        "<body>\r\n"
                        "estado:sp;cidade:sao_paulo;regiao:1;smpu:1;nivel_da_agua:alerta_grave;\r\n"
                        "</body>\r\n"
                        "</html>\r\n";

void setup() { 
 
  // configura numero de colunas e linhas do LCD
  lcd.begin(16, 2); 
  // printa mensagem fixa no LCD. 
  lcd.print("NIVEL DA AGUA:  "); 
  // Comeca comunicação com Ethenert pelo tamanho do buffer e MAC address
  ether.begin(sizeof Ethernet::buffer, mymac, SS);
  // Configura IP estatico e gateway IP
  ether.staticSetup(myip, gwip);
} 
  
void loop() { 
  // Seta cursor para coluna 0 e linha 1
  lcd.setCursor(0, 1); 
  resval = analogRead(respin); //Le o dado do pin3 e armazena na variavel resval
  // Maneja pacotes Ethernet e pega a posicionamento do dado
  word pos = ether.packetLoop(ether.packetReceive());
   
  // REGRAS DE NEGOCIO
  // Menor que 150ohm/Menor de 15cm = SITUACAO NORMAL
  if (resval<=150) { 
    // printa mensagem variavel no LCD. 
    lcd.println("SITUACAO NORMAL");
    if (pos) {
      // Extrai o dado do buffer da Ethernet
      char *data = (char *)Ethernet::buffer + pos;
      // copia HTML da situacao normal
      memcpy_P(ether.tcpOffset(), situacaoNormal, sizeof situacaoNormal);
      // Envia informacao via HTTP para Web Server
      ether.httpServerReply(sizeof situacaoNormal - 1);
    } 
  } 
  // Entre 151ohm e 300ohm/ Entre 16cm e 30cm = ALERTA LEVE
  else if (resval>150 && resval<=300){ 
    // printa mensagem variavel no LCD. 
    lcd.println("ALERTA LEVE    ");
    if (pos) {
    // Extrai o dado do buffer da Ethernet
    char *data = (char *)Ethernet::buffer + pos;
    // copia HTML da situacao normal
    memcpy_P(ether.tcpOffset(), alertaLeve, sizeof alertaLeve);
    // Envia informacao via HTTP para Web Server
    ether.httpServerReply(sizeof alertaLeve - 1);
    } 
  }
  // Entre 301ohm e 600ohm/ Entre 31cm e 60cm = ALERTA MODERADO
  else if (resval>300 && resval<=600){ 
    // printa mensagem variavel no LCD.
    lcd.println("ALERTA MODERADO");
    if (pos) {
    // Extrai o dado do buffer da Ethernet
    char *data = (char *)Ethernet::buffer + pos;
    // copia HTML da situacao normal
    memcpy_P(ether.tcpOffset(), alertaModerado, sizeof alertaModerado);
    // Envia informacao via HTTP para Web Server
    ether.httpServerReply(sizeof alertaModerado - 1);
    }
   } 
   // Acima de 601ohm/ Acima de 61cm = ALERTA GRAVE
  else if (resval>600){ 
    // printa mensagem variavel no LCD.
    lcd.println("ALERTA GRAVE     ");
    if (pos) {
    // Extrai o dado do buffer da Ethernet
    char *data = (char *)Ethernet::buffer + pos;
    // copia HTML da situacao normal
    memcpy_P(ether.tcpOffset(), alertaGrave, sizeof alertaGrave);
    // Envia informacao via HTTP para Web Server
    ether.httpServerReply(sizeof alertaGrave - 1);
    }
   }
   // Seta delay de mensagem para 100ms
  delay(100);  
}
