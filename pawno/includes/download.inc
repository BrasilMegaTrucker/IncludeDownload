#if !defined _samp_included
    #error "Defina a include SA-MP
#else
    #if !defined OnPlayerFinishedDownloading
        #error "SA-MP 0.3.8 Requerido"
    #endif
#endif

#define _samp_downloading

enum _down {
	bool:_Started,
	_TimeCount,
	_VirtualWorld,
	_FilesTXD,
	_FilesDFF
};
static PlayerDownload[MAX_PLAYERS][_down];



public OnPlayerDisconnect(playerid, reason) {
	for(new _down:e; e < _down; e++)
		PlayerDownload[playerid][e] = 0;
	return CallLocalFunction("d_OnPlayerDisconnect", "ii", playerid, reason);
}
forward d_OnPlayerDisconnect(playerid, reason);
#if defined _ALS_OnPlayerDisconnect
	#undef OnPlayerDisconnect
#else
	#define _ALS_OnPlayerDisconnect
#endif
#define OnPlayerDisconnect d_OnPlayerDisconnect

public OnPlayerRequestDownload(playerid, type, crc) {
	if(!PlayerDownload[playerid][_Started]) {
		PlayerDownload[playerid][_Started] = true;
		PlayerDownload[playerid][_TimeCount] = gettime();
		PlayerDownload[playerid][_VirtualWorld] = GetPlayerVirtualWorld(playerid);
		CallLocalFunction("OnPlayerStartedDownload", "dd", playerid, PlayerDownload[playerid][_VirtualWorld]);
	}
	switch(type) {
		case DOWNLOAD_REQUEST_TEXTURE_FILE: PlayerDownload[playerid][_FilesTXD]++;
		case DOWNLOAD_REQUEST_MODEL_FILE: PlayerDownload[playerid][_FilesDFF]++;
	}
	return CallLocalFunction("d_OnPlayerRequestDownload", "iii", playerid, type, crc);
}
forward d_OnPlayerRequestDownload(playerid, type, crc);

#if defined _ALS_OnPlayerRequestDownload
	#undef OnPlayerRequestDownload
#else
	#define _ALS_OnPlayerRequestDownload
#endif
#define OnPlayerRequestDownload d_OnPlayerRequestDownload


public OnPlayerFinishedDownloading(playerid, virtualworld)
{
    CallLocalFunction("d_OnPlayerFinishDownload", "ii", playerid, virtualworld);
	SetTimerEx("FlushDownloadInfo", 1000, false, "d", playerid);
	return 1;
}
forward d_OnPlayerFinishDownload(playerid, virtualworld);

#if defined _ALS_OnPlayerFinishDownload
    #undef OnPlayerFinishedDownloading
#else
    #define _ALS_OnPlayerFinishDownload
#endif
#define OnPlayerFinishedDownloading d_OnPlayerFinishDownload

forward FlushDownloadInfo(playerid);
public FlushDownloadInfo(playerid) {
	PlayerDownload[playerid][_Started] = false;
	PlayerDownload[playerid][_TimeCount] = PlayerDownload[playerid][_VirtualWorld] = 0;
	return 1;
}


/*
				Funções
	native IsPlayerDownloading(playerid);
	native IsPlayerDownloadTime(playerid);
	native IsPlayerDownloadedFiles(playerid);
	native IsPlayerDownloadedTextures(playerid);
	native IsPlayerDownloadedModels(playerid);
	native IsPlayerDownloadVirtualWorld(playerid);	
*/
stock IsPlayerDownloading(playerid) return PlayerDownload[playerid][_Started];
stock IsPlayerDownloadTime(playerid) return (PlayerDownload[playerid][_Started] ? (gettime()-PlayerDownload[playerid][_TimeCount]) : 0);
stock IsPlayerDownloadedFiles(playerid) return (PlayerDownload[playerid][_FilesTXD] + PlayerDownload[playerid][_FilesDFF]);
stock IsPlayerDownloadedTextures(playerid) return PlayerDownload[playerid][_FilesTXD];
stock IsPlayerDownloadedModels(playerid) return PlayerDownload[playerid][_FilesDFF];
stock IsPlayerDownloadVirtualWorld(playerid) return PlayerDownload[playerid][_VirtualWorld];

// Callback
forward OnPlayerStartedDownload(playerid, virtualworld);


/*
	Include criada por Locky
	www.brasilmegatrucker.com
*/
