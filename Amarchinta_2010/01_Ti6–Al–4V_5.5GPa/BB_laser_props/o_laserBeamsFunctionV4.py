import numpy as np
import pylsp

def generateLaserBeamsForMOR(spotRad, overlap, height, width, laserTimeProfile, laserSpaceProfile, angle=1):
    # angle (deg.) > 0 -- goes diagonally against the edge (so far used, probably wrong)
    #   \ ____
    #    |    
    #    |  
    # angle (deg.) < 0 -- goes diagonally the other direction (probably correct)
    #     /____
    #     |
    #     |
    if overlap <= 1.0:
        nSeqs = 2
        initShift = [1, 2]
        nPointsInSeq = [2, 3]
    elif overlap <= 1.33334:
        nSeqs = 3
        initShift = [2, 1, 0]
        nPointsInSeq = [2,2,1]
    else:
        nSeqs = 4
        initShift = [3, 2, 1, 0]
        nPointsInSeq = [2, 2, 2, 1]

    # 1.2 laser beams
    laserBeams = []

    print("spotRad , overlap, H, W = ",spotRad, overlap, height, width)
    print("nSeqs = ", nSeqs)

    sinAn = np.sin(angle*np.pi/180)

    xyz = []
    ######## front; against x-axis ###################################################
    for seq in range(nSeqs):
        # shots on the edge
        ycoord = (height/2) - initShift[seq]*(2-overlap)*spotRad
        for i in range(nPointsInSeq[seq]):
            laserBeams.append(pylsp.LaserBeam(
                startPoint  = pylsp.Point(x=-1., y=ycoord, z=-sinAn),
                endPoint    = pylsp.Point(x= 1., y=ycoord, z= sinAn),
                timeProfile =laserTimeProfile,
                spaceProfile=laserSpaceProfile))

            ycoord += nSeqs*(2-overlap)*spotRad

            x=(laserBeams[-1].startPoint.x+laserBeams[-1].endPoint.x)/2
            y=(laserBeams[-1].startPoint.y+laserBeams[-1].endPoint.y)/2
            z=(laserBeams[-1].startPoint.z+laserBeams[-1].endPoint.z)/2
            
            xyz.append([x,y,z])

        # shots above the shots on the edge (moved by 2r)
        ycoord = (height/2) - initShift[seq]*(2-overlap)*spotRad
        for i in range(nPointsInSeq[seq]):
            laserBeams.append(pylsp.LaserBeam(
                startPoint  = pylsp.Point(x=-1., y=ycoord, z=2*spotRad-sinAn),
                endPoint    = pylsp.Point(x= 1., y=ycoord, z=2*spotRad+sinAn),
                timeProfile =laserTimeProfile,
                spaceProfile=laserSpaceProfile))

            ycoord += nSeqs*(2-overlap)*spotRad

            x=(laserBeams[-1].startPoint.x+laserBeams[-1].endPoint.x)/2
            y=(laserBeams[-1].startPoint.y+laserBeams[-1].endPoint.y)/2
            z=(laserBeams[-1].startPoint.z+laserBeams[-1].endPoint.z)/2

            xyz.append([x,y,z])

    # all the remaining shot-lines in between
    for seq in range(nSeqs):
        ycoord = (height/2) - initShift[seq]*(2-overlap)*spotRad
        for i in range(nPointsInSeq[seq]):
            laserBeams.append(pylsp.LaserBeam(
                startPoint  = pylsp.Point(x=-1., y=ycoord, z=spotRad-sinAn),
                endPoint    = pylsp.Point(x= 1., y=ycoord, z=spotRad+sinAn),
                timeProfile =laserTimeProfile,
                spaceProfile=laserSpaceProfile))

            ycoord += nSeqs*(2-overlap)*spotRad

            x=(laserBeams[-1].startPoint.x+laserBeams[-1].endPoint.x)/2
            y=(laserBeams[-1].startPoint.y+laserBeams[-1].endPoint.y)/2
            z=(laserBeams[-1].startPoint.z+laserBeams[-1].endPoint.z)/2

            xyz.append([x,y,z])

    ################## zespoda ve smeru z ################################
    for seq in range(nSeqs):
        # again, firtst the edge
        ycoord = (height/2) - initShift[seq]*(2-overlap)*spotRad
        for i in range(nPointsInSeq[seq]):
            laserBeams.append(pylsp.LaserBeam(
                startPoint  = pylsp.Point(z=-1., y=ycoord, x=-sinAn),
                endPoint    = pylsp.Point(z= 1., y=ycoord, x= sinAn),
                timeProfile =laserTimeProfile,
                spaceProfile=laserSpaceProfile))

            ycoord += nSeqs*(2-overlap)*spotRad

            x=(laserBeams[-1].startPoint.x+laserBeams[-1].endPoint.x)/2
            y=(laserBeams[-1].startPoint.y+laserBeams[-1].endPoint.y)/2
            z=(laserBeams[-1].startPoint.z+laserBeams[-1].endPoint.z)/2

            xyz.append([x,y,z])

        # shots above the shots on the edge (moved by 2r)
        ycoord = (height/2) - initShift[seq]*(2-overlap)*spotRad
        for i in range(nPointsInSeq[seq]):
            laserBeams.append(pylsp.LaserBeam(
                startPoint  = pylsp.Point(z=-1., y=ycoord, x=2*spotRad-sinAn),
                endPoint    = pylsp.Point(z= 1., y=ycoord, x=2*spotRad+sinAn),
                timeProfile =laserTimeProfile,
                spaceProfile=laserSpaceProfile))

            ycoord += nSeqs*(2-overlap)*spotRad

            x=(laserBeams[-1].startPoint.x+laserBeams[-1].endPoint.x)/2
            y=(laserBeams[-1].startPoint.y+laserBeams[-1].endPoint.y)/2
            z=(laserBeams[-1].startPoint.z+laserBeams[-1].endPoint.z)/2

            xyz.append([x,y,z])

    # all the remaining shot-lines in between
    for seq in range(nSeqs):
        ycoord = (height/2) - initShift[seq]*(2-overlap)*spotRad
        for i in range(nPointsInSeq[seq]):
            laserBeams.append(pylsp.LaserBeam(
                startPoint  = pylsp.Point(z=-1., y=ycoord, x=spotRad-sinAn),
                endPoint    = pylsp.Point(z= 1., y=ycoord, x=spotRad+sinAn),
                timeProfile =laserTimeProfile,
                spaceProfile=laserSpaceProfile))

            ycoord += nSeqs*(2-overlap)*spotRad

            x=(laserBeams[-1].startPoint.x+laserBeams[-1].endPoint.x)/2
            y=(laserBeams[-1].startPoint.y+laserBeams[-1].endPoint.y)/2
            z=(laserBeams[-1].startPoint.z+laserBeams[-1].endPoint.z)/2

            xyz.append([x,y,z])

    return laserBeams, xyz


