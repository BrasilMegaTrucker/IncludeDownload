# Include Download #
Funções extras e leve correção do sistema de Download de Modelos do SA-MP 0.3.8

## Funções [Player]: ##
IsPlayerDownloading(playerid)
- Retorna se um jogador está realizando download.

GetPlayerDownloadTime(playerid)
- Retorna o tempo de download de um jogador (em segundos) caso esteja realizando download.

GetPlayerDownloadedFiles(playerid, virtualworld=0)
- Retorna o número total de arquivos baixados.

GetPlayerDownloadedTextures(playerid, virtualworld=0)
- Retorna o número total de texturas baixadas.

GetPlayerDownloadedModels(playerid, virtualworld=0)
- Retorna o número total de modelos baixados.

GetPlayerDownloadVirtualWorld(playerid)
- Retorna o mundo virtual da qual o jogador está realizando os downloads.

Float:GetPlayerDownloadProgress(playerid)
- Retorna o valor do progresso de download (Nota: Isto é baseado sempre como se nunca tivesse baixado os arquivos).

GetPlayerDownloadedBytes(playerid)
- Retorna o valor em Bytes do conteúdo baixado (Nota: Isto só é funcional caso o download esteja sendo feito sem redirecionamento, e há uma compressão utilizada pelo servidor SA-MP, então não poderá retornar o tamanho exato no diretório).

IsPlayerUseRedirectDownload(playerid)
- Retorna se está sendo feito o download pelo método de redirecionamento.

## Funções [Server]: ##
IsServerUseArtwork()
- Retorna se o servidor está emitindo downloads de modelos.

GetServerArtworkFolder(folder[])
- Retorna o diretório onde os modelos serão lidos e distribuídos.

GetArtworkGlobalSimpleModels()
- Retorna o número de objetos adicionados.

GetArtworkGlobalCharModels()
- Retorna o número de skins adicionados.

GetArtworksModelFiles()
- Retorna o número de arquivos de modelo adicionados (dff).

GetArtworksTextureFiles()
- Retorna o número de arquivos de texturas adicionados (txd).
	
GetArtworkModelFilesInVW(virtualworld)
- Retorna o valor de modelos no mundo virtual citado.

GetArtworkTextureFilesInVW(virtualworld)
- Retorna o valor de texturas no mundo virtual citado.

GetArtworkSimpleModelInVW(virtualworld)	
- Retorna o valor de objetos no mundo virtual citado.

## Callback: ##
OnPlayerStartedDownloading(playerid, virtualworld)
- É chamada quando o jogador inicia o procedimento de downloads.


Em breve poderá existir mais funções. O retorno continua sendo chamado para a callback OnPlayerFinishedDownloading.
