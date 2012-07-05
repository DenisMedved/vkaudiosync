; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

#define MyAppName "VkAudioSync"
#define MyAppVersion "0.12b"
#define MyAppPublisher "Denis Medved"
#define MyAppURL "http://src.mdenis.org/vkaudiosync"
#define MyAppExeName "vkaudiosync.exe"

[Setup]
; NOTE: The value of AppId uniquely identifies this application.
; Do not use the same AppId value in installers for other applications.
; (To generate a new GUID, click Tools | Generate GUID inside the IDE.)
AppId={{EDFC17F6-8403-4FF0-A74E-A19FD5AFBCE9}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
;AppVerName={#MyAppName} {#MyAppVersion}
AppPublisher={#MyAppPublisher}
AppPublisherURL={#MyAppURL}
AppSupportURL={#MyAppURL}
AppUpdatesURL={#MyAppURL}
DefaultDirName={pf}\{#MyAppName}
DefaultGroupName={#MyAppName}
LicenseFile=C:\Users\denis\Documents\vkaudiosync\win\LICENSE.txt
OutputDir=C:\Users\denis\Documents\vkaudiosync\win\setup
OutputBaseFilename=vkaudiosync-setup-{#MyAppVersion}
;Password=debug
Compression=lzma
SolidCompression=yes

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"
Name: "russian"; MessagesFile: "compiler:Languages\Russian.isl"
Name: "ukrainian"; MessagesFile: "compiler:Languages\Ukrainian.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked

[Files]
Source: "C:\Users\denis\Documents\vkaudiosync\win\vkaudiosync.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\denis\Documents\vkaudiosync\win\libeay32.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\denis\Documents\vkaudiosync\win\libgcc_s_sjlj-1.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\denis\Documents\vkaudiosync\win\libpng15-15_.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\denis\Documents\vkaudiosync\win\libz_.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\denis\Documents\vkaudiosync\win\QtCore4.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\denis\Documents\vkaudiosync\win\QtGui4.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\denis\Documents\vkaudiosync\win\QtNetwork4.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\denis\Documents\vkaudiosync\win\QtWebKit4.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\denis\Documents\vkaudiosync\win\QtXml4.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\denis\Documents\vkaudiosync\win\ssleay32.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\denis\Documents\vkaudiosync\win\vkaudiosync.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\denis\Documents\vkaudiosync\win\translations\main_en.qm"; DestDir: "{app}\translations"; Flags: ignoreversion
Source: "C:\Users\denis\Documents\vkaudiosync\win\translations\main_ru.qm"; DestDir: "{app}\translations"; Flags: ignoreversion
; NOTE: Don't use "Flags: ignoreversion" on any shared system files

[Icons]
Name: "{group}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"
Name: "{group}\{cm:ProgramOnTheWeb,{#MyAppName}}"; Filename: "{#MyAppURL}"
Name: "{group}\{cm:UninstallProgram,{#MyAppName}}"; Filename: "{uninstallexe}"
Name: "{commondesktop}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: desktopicon

[Run]
Filename: "{app}\{#MyAppExeName}"; Description: "{cm:LaunchProgram,{#StringChange(MyAppName, '&', '&&')}}"; Flags: nowait postinstall skipifsilent

