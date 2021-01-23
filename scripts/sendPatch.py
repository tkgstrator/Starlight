import ftplib
import os
import sys

titleIdLookup = {
    "JP": '01003C700009C000',
    "US": '01003BC0000A0000',
    "EU": '0100F8F0000A2000',
    'EveJP': '0100D070040F8000',
    'EveUS': '01003870040FA000',
    'EveEU': '010086F0040FC000',
    'TrialJP20': '0100998011330000',
    'TrialUS20': '01002120116C4000',
    'TrialEU20': '01009240116CC000',
    'ShowDL': '010000A00218E000'
}


def listdirs(connection,_path):
    file_list, dirs, nondirs = [], [], []
    try:
        connection.cwd(_path)
    except:
        return []

    connection.retrlines('LIST', lambda x: file_list.append(x.split()))
    for info in file_list:
        ls_type, name = info[0], info[-1]
        if ls_type.startswith('d'):
            dirs.append(name)
        else:
            nondirs.append(name)
    return dirs


def ensuredirectory(connection,root,path):
    print(f"Ensuring {os.path.join(root, path)}...", end="")
    if path not in listdirs(connection, root):
        print("not exists")
        connection.mkd(f'{root}/{path}')
    else:
        print("exists")

consoleIP = sys.argv[1]
if '.' not in consoleIP:
    print(sys.argv[0], "ERROR: Please specify with `IP=[Your console's IP]`")
    sys.exit(-1)

consolePort = 5000

if len(sys.argv) < 3:
    romType = 'US'
else:
    romType = sys.argv[2]

if len(sys.argv) < 4:
    version = '310'
else:
    version = sys.argv[3]

curDir = os.curdir
patchDirectories = []

with ftplib.FTP() as ftp:
    try:
        # FTP settings
        ftp.connect(host=consoleIP, port=consolePort, timeout=5)
        # Login
        ftp.login("tkgling", "starlight")
        root, dirs, _ = next(os.walk(curDir))
        for dir in dirs:
            if dir.startswith("starlight_patch_"):
                patchDirectories.append((os.path.join(root, dir), dir))
        
        # starlight_patch
        ensuredirectory(ftp, '/', 'atmosphere')
        ensuredirectory(ftp, '/atmosphere', 'exefs_patches')
        for patchDir in patchDirectories:
            dirPath = patchDir[0]
            dirName = patchDir[1]
            ensuredirectory(ftp, '/atmosphere/exefs_patches', dirName)
            
            _, _, patches = next(os.walk(dirPath))
            for patch in patches:
                fullPath = os.path.join(dirPath, patch)
                if os.path.exists(fullPath):
                    sdPath = f'/atmosphere/exefs_patches/{dirName}/{patch}'
                    with open(fullPath, 'rb') as fp:
                        ftp.storbinary(f'STOR {sdPath}', fp)
        # subsdk0
        ensuredirectory(ftp, '/atmosphere', 'contents')
        ensuredirectory(ftp, '/atmosphere/contents', titleIdLookup[romType])
        ensuredirectory(ftp, f'/atmosphere/contents/{titleIdLookup[romType]}', 'exefs')
        binaryPath = f'{os.path.basename(os.getcwd())}{version}.nso'
        if os.path.isfile(binaryPath):
            sdPath = f'/atmosphere/contents/{titleIdLookup[romType]}/exefs/subsdk0'
            print(f'Sending {sdPath}')
            ftp.storbinary(f'STOR {sdPath}', open(binaryPath, 'rb'))
    except ftplib.all_errors as e:
        print(e)
        sys.exit(1)
