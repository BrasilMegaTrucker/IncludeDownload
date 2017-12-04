# Include Download
Funções extras e leve correção do sistema de Download de Modelos do SA-MP 0.3.8

Funções:
IsPlayerDownloading(playerid)
- Retorna se um jogador está realizando download.

IsPlayerDownloadTime(playerid)
- Retorna o tempo de download de um jogador (em segundos) caso esteja realizando download.

IsPlayerDownloadedFiles(playerid)
- Retorna o número total de arquivos baixados.

IsPlayerDownloadedTextures(playerid)
- Retorna o número total de texturas baixadas.

IsPlayerDownloadedModels(playerid)
- Retorna o número total de modelos baixados.

IsPlayerDownloadVirtualWorld(playerid)
- Retorna o mundo virtual da qual o jogador está realizando os downloads.

Callback:
OnPlayerStartedDownload
- É chamada quando o jogador inicia o procedimento de downloads.


Em breve poderá existir mais funções. O retorno continua sendo chamado para a callback OnPlayerFinishedDownloading.
