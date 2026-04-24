#include <YSI/YSI_Coding/y_hooks>
#include <a_http>
#include <sscanf2>

#define MAX_PING 250
#define MAX_SCORE 2

new PlayerCountry[MAX_PLAYERS][35];
new bool:PlayerChecked[MAX_PLAYERS];
new PlayerScore[MAX_PLAYERS];

hook OnPlayerConnect(playerid)
{
    new ip[24], url[256];
    GetPlayerIp(playerid, ip, sizeof(ip));

    format(url, sizeof(url), "http://ip-api.com/csv/%s?fields=country,proxy,hosting", ip);
    HTTP(playerid, HTTP_GET, url, "", "HTTP_GEO");

    PlayerChecked[playerid] = false;
    PlayerScore[playerid] = 0;

    SetTimerEx("CheckPlayerSecurity", 7000, false, "i", playerid);
    return Y_HOOKS_CONTINUE_RETURN_1;
}

forward HTTP_GEO(playerid, response_code, data[]);
public HTTP_GEO(playerid, response_code, data[])
{
    if(response_code != 200) return 1;

    new country[35], proxy[6], hosting[6];
    sscanf(data, "p<,>s[35]s[6]s[6]", country, proxy, hosting);

    // limpa \n
    if(strlen(country) > 0 && country[strlen(country)-1] == '\n')
        country[strlen(country)-1] = '\0';

    format(PlayerCountry[playerid], sizeof(PlayerCountry[]), "%s", country);

    // score sistema
    if(!strcmp(proxy, "true", true)) PlayerScore[playerid] += 2;
    if(!strcmp(hosting, "true", true)) PlayerScore[playerid] += 1;
    if(strcmp(country, "Brazil", true) != 0) PlayerScore[playerid] += 1;

    PlayerChecked[playerid] = true;

    printf("[SECURITY] ID:%d | %s | Score:%d", playerid, country, PlayerScore[playerid]);
    return 1;
}

forward CheckPlayerSecurity(playerid);
public CheckPlayerSecurity(playerid)
{
    if(!IsPlayerConnected(playerid)) return 1;

    // se API falhou → ignora
    if(!PlayerChecked[playerid])
    {
        printf("[SECURITY] Player %d ignorado (API falhou)", playerid);
        return 1;
    }

    new ping = GetPlayerPing(playerid);

    if(ping > MAX_PING)
        PlayerScore[playerid] += 1;

    // 🔥 decisão final
    if(PlayerScore[playerid] >= MAX_SCORE)
    {
        SendClientMessage(playerid, -1, "Conexao bloqueada (VPN/Proxy/Ping).");
        Kick(playerid);
    }
    else
    {
        printf("[SECURITY] Player %d liberado (Score:%d | Ping:%d)",
            playerid, PlayerScore[playerid], ping);
    }

    return 1;
}