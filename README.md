# Include Download #
Funções extras e leve correção do sistema de Download de Modelos do SA-MP 0.3.8

## Funções [Player]: ##
IsPlayerDownloading(playerid)
- Retorna se um jogador está realizando download.

GetPlayerDownloadTime(playerid)
- Retorna o tempo de download de um jogador (em segundos) caso esteja realizando download.

GetPlayerDownloadedFiles(playerid)
- Retorna o número total de arquivos baixados.

GetPlayerDownloadedTextures(playerid)
- Retorna o número total de texturas baixadas.

GetPlayerDownloadedModels(playerid)
- Retorna o número total de modelos baixados.

GetPlayerDownloadVirtualWorld(playerid)
- Retorna o mundo virtual da qual o jogador está realizando os downloads.

## Funções [Server]: ##
IsServerUseArtwork()
- Retorna se o servidor está emitindo downloads de modelos.

GetServerArtworkFolder(folder[])
- Retorna o diretório onde os modelos serão lidos e distribuídos.

## Callback: ##
OnPlayerStartedDownload(playerid, virtualworld)
- É chamada quando o jogador inicia o procedimento de downloads.


Em breve poderá existir mais funções. O retorno continua sendo chamado para a callback OnPlayerFinishedDownloading.
