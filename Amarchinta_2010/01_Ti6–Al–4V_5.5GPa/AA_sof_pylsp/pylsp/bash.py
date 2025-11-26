#!/usr/bin/python3

from os import environ
import subprocess


def _runBashCommand(cwd, commands, outputFile=None):
    ret = None
    command = ''
    for comm in commands:
        command += comm + ' ;'

    if outputFile is None:
        ret = subprocess.call(command, shell=True, executable='/bin/bash', cwd=cwd)
    else:
        ret = subprocess.call(command, shell=True, executable='/bin/bash', stdout=outputFile, cwd=cwd)

    return ret

def runBashCommand(cwd, commands, outputFilePath=None):
    ret = None
    if outputFilePath is not None:
        outputFile = open(outputFilePath, 'w')
        ret = _runBashCommand(cwd, commands, outputFile=outputFile)
        outputFile.close()
    else:
        ret = _runBashCommand(cwd, commands)

    return ret
