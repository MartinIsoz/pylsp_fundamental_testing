#!/usr/bin/env python

"""The setup script."""

from genericpath import isdir
from shutil import move
from setuptools import setup, find_packages
import urllib.request
from os import error, listdir, makedirs, path, chmod, stat
import stat as Stat
import urllib.request
import sysconfig

#####################################
lspfoamReqVer = 16
URL = 'https://bitbucket.org/it-cas/pub_foam/downloads/'
reqs = []
reqs.append([URL + 'subsetMesh', 'subsetMesh'])
reqs.append([URL + 'initCase',   'initCase'])
reqs.append([URL + 'createMaps', 'createMaps'])
reqs.append([URL + 'sub2mesh',   'sub2mesh'])
reqs.append([URL + 'lspfoam',    'lspfoam'])
reqs.append([URL + 'patch2cell', 'patch2cell'])
#reqs.append([URL + 'postprocessing', 'postprocessing'])
#####################################

lspfoamVer = None
urls    = [ x[0] for x in reqs]
targets = [ x[1] for x in reqs]

sitePackagesPath = sysconfig.get_path('purelib')
lspfoamDir = path.join(sitePackagesPath, 'lspfoam')
# ~ lspfoamDir = "/home/kovarnoa/sof_pylsp/foam/build"

logFile = open(path.join(sitePackagesPath, 'pylsp_setup.log'), "w")
logFile.write('sitePackagesPath: ' + sitePackagesPath + '\n')
logFile.writelines('lspfoamDir: ' + lspfoamDir + '\n')
logFile.close()

lspfoamInstalled = False
if path.exists(lspfoamDir):
    files = listdir(lspfoamDir)
    for file in files:
        if file.startswith('version_'):
            lspfoamVer = int(file.split('_')[-1])
            if lspfoamVer == lspfoamReqVer:
                if all(x in files for x in targets):
                    lspfoamInstalled = True

if not lspfoamInstalled:
    if lspfoamVer is None:
        message = 'lspFOAM has to be installed\n'
    else:
        if lspfoamVer == lspfoamReqVer:
            message = 'lspFOAM (' + str(lspfoamVer) + ') has to be repaired.\n'
        else:    
            message = 'lspFOAM has to be updated (' + str(lspfoamVer) + ' -> ' +  str(lspfoamReqVer) + ') \n'

    if not isdir(lspfoamDir):
        try:
            makedirs(lspfoamDir)
        except:
            raise SystemError ('It is not possible to make directory ' + lspfoamDir)

    res = 'Permission denied!'

    for req in reqs:
        url = req[0]
        target = path.join(lspfoamDir, req[1])
        print (url + ' -> ' + target)
        try:
            res = urllib.request.urlretrieve(url, target)
            st = stat(target)
            chmod(target, st.st_mode | Stat.S_IEXEC)
        except:
            raise SystemError (res)
        print(res[0] + ' updated.')
else:
    print("lspFoam already installed")

try:
    move(path.join(lspfoamDir, 'version_' + str(lspfoamVer)), path.join(lspfoamDir, 'version_' + str(lspfoamReqVer)))
except:
    versionFile = open(path.join(lspfoamDir, 'version_' + str(lspfoamReqVer)), 'w')
    versionFile.close()

requirements = [ ]

test_requirements = ['pytest>=3', ]

setup(
    author="Pavel Gruber",
    author_email='gruber.pavel@gmail.com',
    python_requires='>=3.6',
    classifiers=[
        'Development Status :: 2 - Pre-Alpha',
        'Intended Audience :: Developers',
        'Natural Language :: English',
        'Programming Language :: Python :: 3',
        'Programming Language :: Python :: 3.6',
        'Programming Language :: Python :: 3.7',
        'Programming Language :: Python :: 3.8',
    ],
    description="Python Laser Shock Peening (PyLSP) analysis based on Finite Volume Method (FVM) implemented in OpenFOAM and solids4Foam",
    include_package_data=True,
    keywords='pylsp',
    name='pylsp',
    packages=find_packages(include=['pylsp', 'pylsp.*']),
    test_suite='tests',
    tests_require=test_requirements,
    url='https://github.com/grubepav/pylsp',
    version='0.4.1',
    zip_safe=False
)
