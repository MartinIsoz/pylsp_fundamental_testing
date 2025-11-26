import pylsp


def get(case):
    laserBeam = case.laserBeam

    headerString = '\
FoamFile\n\
{\n\
    version     2.0;\n\
    format      ascii;\n\
    class       dictionary;\n\
    location    "constant";\n\
    object      laserBeamProperties;\n\
}\n\n'

    square  = laserBeam.spaceProfile.square[0] * laserBeam.spaceProfile.square[0]
    square += laserBeam.spaceProfile.square[1] * laserBeam.spaceProfile.square[1]
    square += laserBeam.spaceProfile.square[2] * laserBeam.spaceProfile.square[2]

    squareString  = 'square ( '
    squareString += str(laserBeam.spaceProfile.square[0]) + ' '
    squareString += str(laserBeam.spaceProfile.square[1]) + ' '
    squareString += str(laserBeam.spaceProfile.square[2])
    squareString += ' );\n'

    if isinstance(laserBeam.spaceProfile, pylsp.PiecewiseLinearLaserSpaceProfile):
        squareString += 'pureSquareRadius ' + str(laserBeam.spaceProfile.pureSquareRadius) + ';\n'
    elif isinstance(laserBeam.spaceProfile, pylsp.ExponentialLaserSpaceProfile):
        squareString += 'pureSquareRadius ' + str(laserBeam.spaceProfile.radius) + ';\n'
        squareString += 'a ' + str(laserBeam.spaceProfile.a) + ';\n'
        squareString += 'c ' + str(laserBeam.spaceProfile.c) + ';\n'
        squareString += 'n ' + str(laserBeam.spaceProfile.n) + ';\n'
        if laserBeam.spaceProfile.modified:
            squareString += 'modified true;\n'
        else:
            squareString += 'modified false;\n'

    spotType = 'spotType "'
    if isinstance(laserBeam.spaceProfile, pylsp.PiecewiseLinearLaserSpaceProfile):
        if square > 0.0:
            spotType += 'PIECEWISE_LINEAR_SQUARE_LASER_SPOT'
        else:
            spotType += 'PIECEWISE_LINEAR_CIRCLE_LASER_SPOT'
    elif isinstance(laserBeam.spaceProfile, pylsp.ExponentialLaserSpaceProfile):
        if square > 0.0:
            spotType += 'EXP_SQUARE_LASER_SPOT'
        else:
            spotType += 'EXP_CIRCLE_LASER_SPOT'
    else:
        spotType += 'NONE'
    spotType += '";\n\n'

    startPoint = 'startPoint ( ' +  str(laserBeam.startPoint.x) + ' ' + str(laserBeam.startPoint.y) + ' ' + str(laserBeam.startPoint.z) + ' );\n\n'
    endPoint = 'endPoint ( ' +  str(laserBeam.endPoint.x) + ' ' + str(laserBeam.endPoint.y) + ' ' + str(laserBeam.endPoint.z) + ' );\n\n'

    timeProfileString = 'timeProfile ( '
    t = []
    for T in laserBeam.timeProfile.time:
        t.append(T + case.startTime)
    i = 0
    for pressure in laserBeam.timeProfile.pressure:
        timeProfileString = timeProfileString + '('
        timeProfileString = timeProfileString + str(t[i])
        timeProfileString = timeProfileString + ' '
        timeProfileString = timeProfileString + str(pressure)
        timeProfileString = timeProfileString + ') '
        i = i + 1
    timeProfileString = timeProfileString + '(' + str(1.0001 * t[-1]) + ' 0)'
    timeProfileString = timeProfileString + ' );\n\n'

    spaceProfileString = ''
    if isinstance(laserBeam.spaceProfile, pylsp.PiecewiseLinearLaserSpaceProfile):
        spaceProfileString = 'spaceProfile ( '
        for i in range(0, len(laserBeam.spaceProfile.radius)):
            spaceProfileString = spaceProfileString + '('
            spaceProfileString = spaceProfileString + str(laserBeam.spaceProfile.radius[i])
            spaceProfileString = spaceProfileString + ' '
            spaceProfileString = spaceProfileString + str(laserBeam.spaceProfile.mult[i])
            spaceProfileString = spaceProfileString + ') '
            i = i + 1
        spaceProfileString += '(' + str(1.0001 * laserBeam.spaceProfile.radius[-1]) + ' 0) );\n'

    if laserBeam.spaceProfile.considerFaceNormal:
        spaceProfileString += 'considerFaceNormal true;\n'
    else:
        spaceProfileString += 'considerFaceNormal false;\n\n'

    return headerString + spotType + startPoint + endPoint + timeProfileString + spaceProfileString + squareString