# 🔒 SA-MP Security System (Anti VPN / Proxy / GeoIP / Ping)

Sistema híbrido de segurança para servidores SA-MP, focado na detecção de **VPN, Proxy, Hosting, localização (GeoIP)** e **ping alto**, utilizando lógica baseada em **pontuação (score system)** para reduzir falsos positivos.

---

## 📦 Funcionalidades

- 🌍 Detecção de país via GeoIP  
- 🚫 Detecção de VPN / Proxy  
- 🖥️ Identificação de conexões de Hosting (datacenter)  
- 📶 Verificação de ping do jogador  
- 🧠 Sistema inteligente baseado em pontuação  
- ⏱️ Proteção contra falhas de API (timeout safe)  

---

## ⚙️ Como funciona

O sistema utiliza a API:

http://ip-api.com

Cada jogador recebe uma **pontuação de risco** com base nas informações coletadas:

| Evento                     | Pontos |
|--------------------------|--------|
| VPN / Proxy detectado    | +2     |
| Hosting detectado        | +1     |
| País diferente do Brasil | +1     |
| Ping alto                | +1     |

---

### 🚨 Regra de decisão

- **Score ≥ 2** → Jogador é kickado  
- **Score < 2** → Jogador é liberado  

---

## 📥 Requisitos

- SA-MP Server  
- Plugin: a_http  
- Include: sscanf2  
- Include: YSI (y_hooks)  

---

## 📌 Instalação

1. Adicione os includes no seu gamemode:

#include <YSI/YSI_Coding/y_hooks>
#include <a_http>
#include <sscanf2>

2. Insira o código do sistema no seu gamemode ou em um .inc.

3. Compile normalmente.

---

## 🔧 Configuração

#define MAX_PING 250
#define MAX_SCORE 2

- MAX_PING: Limite máximo de ping permitido  
- MAX_SCORE: Pontuação necessária para bloquear o jogador  

---

## 📊 Logs

Exemplo de saída no console:

[SECURITY] ID:3 | Brazil | Score:1  
[SECURITY] Player 3 liberado (Score:1 | Ping:120)

---

## ⚠️ Observações importantes

- Nenhum sistema anti-VPN é 100% preciso  
- APIs externas podem falhar ou ter rate limit  
- Algumas operadoras podem retornar dados incorretos  

👉 Por isso, o sistema utiliza validação híbrida para evitar kicks injustos.

---

## 🚀 Melhorias opcionais

- Integração com múltiplas APIs (fallback)  
- Cache de IP para reduzir requisições  
- Logs avançados (ASN, ISP, etc.)  
- Sistema de whitelist (IPs confiáveis)  
- Detecção avançada de datacenter  

---

## 📜 Licença

Uso livre para servidores SA-MP.  
Modificações são permitidas.

---

## 🤝 Suporte

Em caso de problemas:

- Verifique os logs do servidor  
- Confirme se a API está respondendo corretamente  
- Ajuste os valores de configuração se necessário  
