#!/usr/bin/python3

from pylsp.bash import runBashCommand
from pylsp.utils import infoRawH2

def runFOAMapp(FOAM, app, cwd, outputFile=None):
    commands = [FOAM, app]
    ret = runBashCommand(cwd, commands, outputFile)
    if ret != 0:
        infoRawH2('OpenFOAM app error', app, newLine=True, bold=True)
        #exit() #problem with bitbucket
