/*
	##########################################################
	##		Manipulação de Downloads		##
	##			   by Locky			##	
	##########################################################


	
		* Funções [Player]
	native IsPlayerDownloading(playerid);
	native GetPlayerDownloadTime(playerid);
	native GetPlayerDownloadedFiles(playerid);
	native GetPlayerDownloadedTextures(playerid);
	native GetPlayerDownloadedModels(playerid);
	native GetPlayerDownloadVirtualWorld(playerid);	
	native GetPlayerDownloadTimeString(playerid);
	
		* Funções [Server]
	native IsServerUseArtwork();
	native GetServerArtworkFolder(folder[]);
	
		* Callback
	OnPlayerStartedDownload(playerid, virtualworld);

*/

#if !defined _samp_included
    #error "Defina a include SA-MP"
#else
    #if !defined OnPlayerFinishedDownloading
        #error "SA-MP 0.3.DL Requerido"
    #endif
#endif
#if defined _samp_downloading
	#endinput
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

public OnPlayerConnect(playerid)
{
	PlayerDownload[playerid][_Started] = false;	
	return CallLocalFunction("d_OnPlayerConnect", "d", playerid);	
}
#if defined _ALS_OnPlayerConnect
	#undef OnPlayerConnect
#else
	#define _ALS_OnPlayerConnect
#endif
#define OnPlayerConnect d_OnPlayerConnect
forward d_OnPlayerConnect(playerid);
public OnPlayerDisconnect(playerid, reason) {	
	for(new _down:e; e < _down; e++)
		PlayerDownload[playerid][e] = 0;
	return CallLocalFunction("d_OnPlayerDisconnect", "dd", playerid, reason);	
}
#if defined _ALS_OnPlayerDisconnect
	#undef OnPlayerDisconnect
#else
	#define _ALS_OnPlayerDisconnect
#endif
#define OnPlayerDisconnect d_OnPlayerDisconnect
forward d_OnPlayerDisconnect(playerid, reason);

public OnPlayerRequestDownload(playerid, type, crc) {
	if(!PlayerDownload[playerid][_Started]) {
		PlayerDownload[playerid][_Started] = true;
		PlayerDownload[playerid][_TimeCount] = gettime();
		PlayerDownload[playerid][_VirtualWorld] = GetPlayerVirtualWorld(playerid);		
		#if defined OnPlayerStartedDownload
			OnPlayerStartedDownload(playerid, PlayerDownload[playerid][_VirtualWorld]);
		#endif
	}
	switch(type) 
	{
		case DOWNLOAD_REQUEST_TEXTURE_FILE: PlayerDownload[playerid][_FilesTXD]++;
		case DOWNLOAD_REQUEST_MODEL_FILE: PlayerDownload[playerid][_FilesDFF]++;
	}	
	if(funcidx("d_OnPlayerRequestDownload") != -1)
		return CallLocalFunction("d_OnPlayerRequestDownload", "ddd", playerid, type, crc);
	else 
		return 1;	
}
#if defined _ALS_OnPlayerRequestDownload
	#undef OnPlayerRequestDownload
#else
	#define _ALS_OnPlayerRequestDownload
#endif
#define OnPlayerRequestDownload d_OnPlayerRequestDownload
forward d_OnPlayerRequestDownload(playerid, type, crc);

public OnPlayerFinishedDownloading(playerid, virtualworld)
{    
	if(funcidx("d_OnPlayerFinishDownload") != -1)
		d_OnPlayerFinishDownload(playerid, virtualworld);	
	SetTimerEx("FlushDownloadInfo", 1000, false, "d", playerid);
	return 1;
}
#if defined _ALS_OnPlayerFinishDownload
    #undef OnPlayerFinishedDownloading
#else
    #define _ALS_OnPlayerFinishDownload
#endif
#define OnPlayerFinishedDownloading d_OnPlayerFinishDownload
forward d_OnPlayerFinishDownload(playerid, virtualworld);

forward FlushDownloadInfo(playerid);
public FlushDownloadInfo(playerid) {
	PlayerDownload[playerid][_Started] = false;
	PlayerDownload[playerid][_TimeCount] = PlayerDownload[playerid][_VirtualWorld] = 0;
	return 1;
}



/////////////////////////////////////////////////////////////////////////////////////////
// Player
stock IsPlayerDownloading(playerid) 
	return PlayerDownload[playerid][_Started];
stock GetPlayerDownloadTime(playerid) 
	return (PlayerDownload[playerid][_Started] ? (gettime()-PlayerDownload[playerid][_TimeCount]) : 0);
stock GetPlayerDownloadedFiles(playerid) 
	return (PlayerDownload[playerid][_FilesTXD] + PlayerDownload[playerid][_FilesDFF]);
stock GetPlayerDownloadedTextures(playerid) 
	return PlayerDownload[playerid][_FilesTXD];
stock GetPlayerDownloadedModels(playerid) 
	return PlayerDownload[playerid][_FilesDFF];
stock GetPlayerDownloadVirtualWorld(playerid) 
	return PlayerDownload[playerid][_VirtualWorld];

stock GetPlayerDownloadTimeString(playerid) {
	new timestr[14], hor, mi, seg = (gettime()-PlayerDownload[playerid][_TimeCount]);
	if(seg >= 3600) {
		hor = seg / 3600;
		seg -= hor * 3600;
	}
	if(seg >= 60) {
		mi = seg / 60;
		seg -= mi * 60;
	}
	format(timestr, sizeof(timestr), "%02d:%02d:%02d", hor, mi, seg);
	return timestr;
}
// Server
stock IsServerUseArtwork() return GetConsoleVarAsBool("useartwork");
stock GetServerArtworkFolder(folder[]) return GetConsoleVarAsString("artpath", folder, 64);

#id defined OnPlayerStartedDownload
	// Callback
	forward OnPlayerStartedDownload(playerid, virtualworld);
#endif

/*
	Include criada por Locky
	www.brasilmegatrucker.com
*/


//Sugestion by RazorGuigo:


#if defined INTERNAL_D_CHARLIMIT
	#define INTERNAL_D_CHARLIMIT 3000
#endif

#define MD_TAG STREAMER_TYPE_OBJECT

#define SetDataDownloads(%0)	Streamer_SetArrayData(MD_TAG,OBJ_MD,E_STREAMER_EXTRA_ID,%0);
#define GetDataDownloads(%0)	Streamer_GetArrayData(MD_TAG,OBJ_MD,E_STREAMER_EXTRA_ID,%0);

static OBJ_MD;						//objeto para armazenar arr 
static _FilesGlobal;



#if defined _ALS_AddSimpleModel
	#undef AddSimpleModel
#else
	#define _ALS_AddSimpleModel
#endif
#define AddSimpleModel d_AddSimpleModel

forward AddSimpleModel(virtualworld, baseid, newid, dffname[], txdname[]);
public AddSimpleModel(virtualworld, baseid, newid, dffname[], txdname[])
{
	new archives[INTERNAL_D_CHARLIMIT], escapedff[32]="",escapetxd[32]="";
	GetDataDownloads(archives);

	strcat(escapetxd, txdname);
	strcat(escapedff, dffname);


	for(new i = strlen(escapedff); i > 0; i--)
	{
		if(escapedff[i]== '/' || escapedff[i] == '\')
		{
			strdel(escapedff, 0, i);
			break;
		}
	}
	for(new i = strlen(escapetxd); i > 0; i--)
	{
		if(escapetxd[i]== '/' || escapetxd[i] == '\')
		{
			strdel(escapetxd, 0, i);
			break;
		}
	}


	if(!strfind(archives,escapedff))
	{
		strcat(archives,escapedff);
		_FilesGlobal++;
	}
	if(!strfind(archives,escapetxd))
	{
		strcat(archives,escapetxd);
		_FilesGlobal++;
	}

	SetDataDownloads(archives);
	return 1;
}

#if defined _ALS_OnGamemodeInit
	#undef OnGamemodeInit
#else
	#define _ALS_OnGamemodeInit
#endif
#define OnGamemodeInit d_OnGamemodeInit

public OnGameModeInit()
{
	OBJ_MD = CreateDynamicObject(18631, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
	return 1;
}

//Server Functions:

stock GetTotalFilesDownload()
	return _FilesGlobal;

//Player Functions:
stock GetRemainingFiles(playerid)
	return GetFilesDownload() - GetPlayerDownloadedFiles(playerid);
stock Float:GetPlayerPercentageFiles(playerid)
	return floatdiv(GetFilesDownload(playerid)*100, GetPlayerDownloadedFiles(playerid));

