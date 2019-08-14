@pause

set CUR_DIR=%~dp0
set CLI_DIR="%CUR_DIR%ChatClient\ChatClient\Data"
set SER_DIR="%CUR_DIR%chat_server\cs"

cd %CLI_DIR%

xcopy %SER_DIR% %CLI_DIR% /s/y

@pause