#if !defined _samp_included
    #error "Defina a include SA-MP
#else
    #if !defined OnPlayerFinishedDownloading
        #error "SA-MP 0.3.8 Requerido"
    #endif
#endif

#define _samp_downloading


public OnPlayerConnect(playerid)
{
	SetPVarInt(playerid, "download_time", GetTickCount());
	SetPVarInt(playerid, "download_init", true);
	SetPVarInt(playerid, "download_world", GetPlayerVirtualWorld(playerid));
	return CallLocalFunction("download_OnPlayerConnect", "i", playerid);
}
forward download_OnPlayerConnect(playerid);

#if defined _ALS_OnPlayerConnect
    #undef OnPlayerConnect
#else
    #define _ALS_OnPlayerConnect
#endif
#define OnPlayerConnect download_OnPlayerConnect

stock download_SetPlayerVirtualWorld(playerid, virtualworld) {
    SetPVarInt(playerid, "download_time", GetTickCount());
    SetPVarInt(playerid, "download_init", true);
    SetPVarInt(playerid, "download_world", virtualworld);
    return SetPlayerVirtualWorld(playerid, virtualworld);
}
#if defined _ALS_SetPlayerVirtualWorld
    #undef SetPlayerVirtualWorld
#else
    #define _ALS_SetPlayerVirtualWorld
#endif
#define SetPlayerVirtualWorld download_SetPlayerVirtualWorld

public OnPlayerFinishedDownloading(playerid, virtualworld)
{
	if((GetPVarInt(playerid, "download_world") == virtualworld) && (GetPVarInt(playerid, "download_time") < GetTickCount()-150) && (GetPVarInt(playerid, "download_init"))) {
	    #if defined down_OnPlayerFinishDownload
            CallRemoteFunction("down_OnPlayerFinishDownload", "ii", playerid, virtualworld);
        #endif
    }
    DeletePVar(playerid, "download_world");
    DeletePVar(playerid, "download_time");
    DeletePVar(playerid, "download_init");
    return 1;
}
forward down_OnPlayerFinishDownload(playerid, virtualworld);

#if defined _ALS_OnPlayerFinishDownload
    #undef OnPlayerFinishedDownloading
#else
    #define _ALS_OnPlayerFinishDownload
#endif
#define OnPlayerFinishedDownloading down_OnPlayerFinishDownload



/*
				Funções
	native IsPlayerDownloading(playerid);
	native IsPlayerDownloadTime(playerid);
*/

stock IsPlayerDownloading(playerid) return GetPVarInt(playerid, "download_init");
stock IsPlayerDownloadTime(playerid) return (GetPVarInt(playerid, "download_init") ? ((GetTickCount()-GetPVarInt(playerid, "download_time"))/1000) : 0);


/*
	Include criada por Locky
	www.brasilmegatrucker.com
*/
