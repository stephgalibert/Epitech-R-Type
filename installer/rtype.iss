#define MyAppName "R-Type"
#define MyAppVersion "1.0"
#define MyAppPublisher "Epitech"
#define MyAppExeName "rtype.exe"

[Setup]
; NOTE: The value of AppId uniquely identifies this application.
; Do not use the same AppId value in installers for other applications.
; (To generate a new GUID, click Tools | Generate GUID inside the IDE.)
AppId={{A1837576-55A2-49C3-A902-0006212F7AA6}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
;AppVerName={#MyAppName} {#MyAppVersion}
AppPublisher={#MyAppPublisher}
DefaultDirName={pf}\{#MyAppName}
DefaultGroupName={#MyAppName}
AllowNoIcons=yes
OutputDir=rTypeSetup
OutputBaseFilename=rtype_setup
Compression=lzma
SolidCompression=yes
SetupIconFile=icon.ico

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"
Name: "french"; MessagesFile: "compiler:Languages\French.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}";

[Code]
function CreateBatch(): boolean;
var
  fileName : string;
  lines : TArrayOfString;
begin
  Result := true;
  fileName := ExpandConstant('{app}\launcher.bat');
  SetArrayLength(lines, 3);
  lines[0] := 'cd "' + ExpandConstant('{app}') + '"';
  lines[1] := 'start ./rtype "" "%1"';
  Result := SaveStringsToFile(filename,lines,true);
  exit;                                
end;

procedure CurStepChanged(CurStep: TSetupStep);
begin
  if  CurStep=ssPostInstall then
    begin
         CreateBatch();
    end
end;

[UninstallDelete]
Type: files; Name: "{app}\launcher.bat"

[Files]
Source: "C:\Github\R-Type\client\rtype\Release\rtype.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Github\R-Type\client\rtype\Release\rsrc\*"; DestDir: "{app}\rsrc"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "C:\Github\R-Type\client\rtype\Release\monsters\*.dll"; DestDir: "{app}\monsters"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "C:\Github\R-Type\client\rtype\Release\levels\*"; DestDir: "{app}\levels"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "C:\Github\R-Type\client\rtype\Release\Server.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Github\R-Type\client\rtype\Release\config.xml"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Libraries\SFML-2.4.0\bin\sfml-audio-2.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Libraries\SFML-2.4.0\bin\sfml-graphics-2.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Libraries\SFML-2.4.0\bin\sfml-network-2.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Libraries\SFML-2.4.0\bin\sfml-system-2.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Libraries\SFML-2.4.0\bin\sfml-window-2.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Libraries\SFML-2.4.0\bin\openal32.dll"; DestDir: "{app}"; Flags: ignoreversion
; NOTE: Don't use "Flags: ignoreversion" on any shared system files
            
[Registry]
Root: HKCU; Subkey: "Software\Classes\rtype"; Flags: uninsdeletekey; ValueType: none;
Root: HKCU; Subkey: "Software\Classes\rtype"; ValueType: string; ValueData: """URL:rtype Protocol""";
Root: HKCU; Subkey: "Software\Classes\rtype"; ValueType: string; ValueName: URL Protocol; ValueData: """""";
Root: HKCU; Subkey: "Software\Classes\rtype\DefaultIcon"; ValueType: string; ValueData:"""{app}\rtype.exe,0""";
Root: HKCU; Subkey: "Software\Classes\rtype\shell"; Flags: uninsdeletekey; ValueType: none;
Root: HKCU; Subkey: "Software\Classes\rtype\shell\open"; Flags: uninsdeletekey; ValueType: none;
Root: HKCU; Subkey: "Software\Classes\rtype\shell\open\command"; Flags: uninsdeletekey; ValueType: string; ValueData:"""{app}\launcher.bat"" ""%1""";

[Icons]
Name: "{group}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"
Name: "{commondesktop}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: desktopicon

[Run]
Filename: "{app}\{#MyAppExeName}"; Description: "{cm:LaunchProgram,{#StringChange(MyAppName, '&', '&&')}}"; Flags: nowait postinstall skipifsilent

