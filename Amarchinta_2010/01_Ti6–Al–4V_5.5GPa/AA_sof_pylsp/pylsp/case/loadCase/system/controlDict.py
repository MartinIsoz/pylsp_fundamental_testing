def get(case):
    return '\
FoamFile\n\
{\n\
    version     2.0;\n\
    format      ascii;\n\
    class       dictionary;\n\
    location    "system";\n\
    object      controlDict;\n\
}\n\
\n\
application       lspfoam;\n\
startFrom         startTime;\n\
startTime         ' + str(case.startTime) + ';\n\
stopAt            endTime;\n\
endTime           ' + str(case.endTime) + ';\n\
deltaT            ' + str(case.endTime - case.startTime) + ';\n\
maxCo             1;\n\
writeInterval     1;\n\
writeControl      timeStep;\n\
purgeWrite        0;\n\
writeFormat       ascii;\n\
writePrecision    7;\n\
writeCompression  off;\n\
timeFormat        general;\n\
timePrecision     10;\n\
runTimeModifiable yes;\n\
\n\
InfoSwitches\n\
{\n\
    allowSystemOperations 1;\n\
}'