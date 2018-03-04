#include <a_samp>
#include <download>


public OnFilterScriptInit() {
    new artfolder[64];
    GetServerArtworkFolder(artfolder);
    printf("UseArtwork: %i | Pasta: %s", IsServerUseArtwork(), artfolder);
    return print("Download Test: Carregado");
}

public OnPlayerFinishedDownloading(playerid, virtualworld) 
{ 
    new Msg[144]; 
    format(Msg, sizeof(Msg), "OnPlayerFinishedDownloading(playerid %i, virtualworld %i)", playerid, virtualworld); 
    SendClientMessage(playerid, -1, Msg); 
     
    if(IsPlayerDownloading(playerid)) { // Se o jogador realizou downloads realmente
		format(Msg, sizeof(Msg), "[Beta] Você realizou %i downloads (%i modelos e %i texturas) durante %i segundos.", GetPlayerDownloadedFiles(playerid), GetPlayerDownloadedModels(playerid), GetPlayerDownloadedTextures(playerid), GetPlayerDownloadTime(playerid));
		SendClientMessage(playerid, -1, Msg);
	}
    return 1; 
} 
public OnPlayerRequestDownload(playerid, type, crc) 
{
    new Msg[144];
    format(Msg, sizeof(Msg), "~w~Progresso: ~g~%3.2f%%~n~~w~(%i bytes / %i kb / %i mb)", GetPlayerDownloadProgress(playerid), GetPlayerDownloadedBytes(playerid), GetPlayerDownloadedBytes(playerid)/1024, (GetPlayerDownloadedBytes(playerid)/1024)/1024);
    GameTextForPlayer(playerid, Msg, 60000, 4);
    return 1;
}
public OnPlayerStartedDownloading(playerid, virtualworld) {
	SendClientMessage(playerid, 0xFFFF00FF, "[Beta] O download foi iniciado. Aguarde o término para continuar jogando!");
	return 1;
}

