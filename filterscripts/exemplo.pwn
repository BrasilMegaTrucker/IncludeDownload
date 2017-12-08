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
public OnPlayerStartedDownload(playerid, virtualworld) {
	SendClientMessage(playerid, 0xFFFF00FF, "[Beta] O download foi iniciado. Aguarde o término para continuar jogando!");
	return 1;
}

