<h1 align="center">SMPU - Sistema de Monitoramento Pluvial Urbano</h1>

### 💻 Sobre o projeto

O Sistema de Monitoramento Pluvial Urbano (SMPU) é um projeto que integra hardware, software e soluções em nuvem detectar variações no nível da água em regiões com risco de alagamento, proporcionando alertas locais e remotos à população.

### 📄 Monografia

A documentação completa do projeto está disponível na monografia e pode ser acessada
        <a href="https://github.com/carlosaugustodpacheco/smpu-ufabc/blob/main/Monografia/CARLOS_PACHECO-SISTEMA-DE-MONITORAMENTO-PLUVIAL-URBANO-2024.docx%20(5).pdf" target="_blank">aqui</a>!
        A Monografia foi apresentada ao Curso de Tecnologias e Sistemas de Informação na Universidade Federal do ABC, como requisito básico para obtenção do Grau de Especialista em Tecnologias e Sistemas da Informação.
        Orientada pelo Prof. Dr. Mario Gazziro.


### 🧩 Arquitetura do Sistema

O desenvolvimento desse modelo se deu pela seguinte ordem:
1. Criação de um ambiente simulado com sensor de nível de água e tanque para testes;
2. Configuração de um algoritmo embarcado no microcontrolador Arduino para tomada de decisão com base nos níveis de água detectados;
3. Inclusão de um Display Tela de Cristal Líquido (LCD) e um Buzzer para alarmes visuais e sonoros;
4. Criação de um Web Server (ou servidor Web) local utilizando um módulo Ethernet e transferência dos dados para um servidor Web público;
5. Adequação de roles, funções e políticas na conta AWS através do Identity and Access Management (IAM);
6. Configuração de um algoritmo em Python para o tratamento dos dados provenientes do servidor Web público;
7. Armazenamento do algoritmo Python em um bucket do Amazon Simple Storage Service (S3);
8. Implementação do algoritmo no AWS Lambda, com habilitação do CloudWatch;
9. Criação de um cronograma no Amazon EventBridge para acionamento do Lambda a cada minuto;
10. Armazenamento das mudanças do nível da água no banco de dados DynamoDB;
11. Envio de alarmes por e-mail em caso de alagamento para usuários cadastrados via Amazon Simple Notification Service (SNS).

O detalhamento do sistema está ilustrado na figura:
<img src="https://github.com/user-attachments/assets/aad99023-ec47-434d-a7b4-3e001fdc813d" alt="Arquitetura do SMPU" width="500">



### 🛠 Tecnologias

As seguintes linguagens de programação foram usadas na construção do projeto:

- HTML
- C++
- Python

### ✨ Autor

<a href="https://github.com/carlosaugustodpacheco">
 <img style="border-radius: 50%;" src="https://avatars.githubusercontent.com/u/68930974?v=4" width="100px;" alt=""/>
 <br />
 <sub><b>Carlos Augusto Duru Pacheco</b></sub></a> <a href="https://github.com/carlosaugustodpacheco" title="Github">🚀</a>
 
  Entre em contato! 👋
  
   [![Linkedin Badge](https://img.shields.io/badge/-Carlos-blue?style=flat-square&logo=Linkedin&logoColor=white&link=https://www.linkedin.com/in/carlosaugustodpacheco/)](https://www.linkedin.com/in/carlosaugustodpacheco/) 
[![Gmail Badge](https://img.shields.io/badge/-carlosaugustodpacheco@gmail.com-c14438?style=flat-square&logo=Gmail&logoColor=white&link=mailto:carlosaugustodpacheco@gmail.com)](mailto:carlosaugustodpacheco@gmail.com)
