#include <a_samp>
#include <download>
#include <zcmd>

public OnFilterScriptInit() return print("Download Test: Carregado");

public OnPlayerFinishedDownloading(playerid, virtualworld) 
{ 
    new Msg[144]; 
    format(Msg, sizeof(Msg), "OnPlayerFinishedDownloading(playerid %i, virtualworld %i)", playerid, virtualworld); 
    SendClientMessage(playerid, -1, Msg); 
     
    // Downloading 
    format(Msg, sizeof(Msg), "Tempo demorado: %i segundos", IsPlayerDownloadTime(playerid)); 
    SendClientMessage(playerid, -1, Msg); 
    return 1; 
} 
CMD:isdown(playerid) return SendClientMessage(playerid, -1, (IsPlayerDownloading(playerid) ? ("Realizando download") : ("Já realizou os downloads."))); 
CMD:tempodown(playerid) { 
    new Msg[144]; 
    format(Msg, sizeof(Msg), "Tempo de download: %i segundos", IsPlayerDownloadTime(playerid)); 
    return SendClientMessage(playerid, -1, Msg); 
}  
