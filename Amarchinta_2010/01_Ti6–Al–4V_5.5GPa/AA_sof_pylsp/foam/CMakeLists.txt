cmake_minimum_required(VERSION 3.10.0)
project(lspfoam)

########################
# USER MODIFIABLE PART #
########################
set(MACHINE "KRAKEN")


#############################
# DEVELOPER MODIFIABLE PART #
#############################
if(MACHINE STREQUAL KRAKEN)
    message("Building for KRAKEN")
    set(OpenFOAM_build linux64GccDPInt32-spack)
    set(SPACK /home/SOFT/modules/spack/installs/linux-ubuntu22.04-broadwell/gcc-13.3.0)
    set(foam_com_DIR ${SPACK}/openfoam-2312-dryq5snbojskkuaqjhsxhtxqxmbrijvx)
    set(solids4foam_DIR /home/SOFT/modules/installs/foam/solids4foam_v2.1)
    set(solids4foam_LIB ${solids4foam_DIR}/platforms/${OpenFOAM_build}/lib)
elseif(MACHINE STREQUAL LOCAL)
    message("Building for LOCAL")
    set(OpenFOAM_build linux64GccDPInt32Opt)
    set(foam_com_DIR REPLACE_THIS)
    set(solids4foam_DIR REPLACE_THIS)
    set(solids4foam_LIB REPLACE_THIS)
endif()    


set(solidModels_DIR src/solids4FoamModels/solidModels)
set(materialModels_DIR src/solids4FoamModels/materialModels)
set(fvPatchFields_DIR src/solids4FoamModels/solidModels/fvPatchFields)

list(APPEND APP_SRCS applications/solvers/solids4Foam/solids4Foam.C)
list(APPEND APP_SRCS ${solidModels_DIR}/myExplicitUnsLinGeomTotalDispSolid/myExplicitUnsLinGeomTotalDispSolid.C)
list(APPEND APP_SRCS ${solidModels_DIR}/myExplicitLinGeomTotalDispSolid/myExplicitLinGeomTotalDispSolid.C)
list(APPEND APP_SRCS ${solidModels_DIR}/myUnsLinGeomSolid/myUnsLinGeomSolid.C)
list(APPEND APP_SRCS ${solidModels_DIR}/myLinGeomTotalDispSolid/myLinGeomTotalDispSolid.C)
list(APPEND APP_SRCS ${solidModels_DIR}/laserIntenzitySolver/laserIntenzitySolver.C)
list(APPEND APP_SRCS ${solidModels_DIR}/materialPoint/materialPoint.C)
list(APPEND APP_SRCS ${materialModels_DIR}/mechanicalModel/linearGeometryLaws/myLinearElastic/myLinearElastic.C)
list(APPEND APP_SRCS ${materialModels_DIR}/mechanicalModel/linearGeometryLaws/myLinearElasticMisesPlastic/myLinearElasticMisesPlastic.C)
list(APPEND APP_SRCS ${materialModels_DIR}/mechanicalModel/linearGeometryLaws/linearElasticMisesPlasticJC/linearElasticMisesPlasticJC.C)
list(APPEND APP_SRCS ${materialModels_DIR}/mechanicalModel/linearGeometryLaws/linearElasticMisesPlasticLH/linearElasticMisesPlasticLH.C)


# FV_PATCH_FIELDS
list(APPEND PATCH_SRCS ${fvPatchFields_DIR}/laserProcessingPressure/laserProcessingPressureFvPatchVectorField.C)
set (CMAKE_CXX_STANDARD 14)



#############################
# DEVELOPER MODIFIABLE PART #
#############################

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_options(-m64 -Dlinux64 -DWM_DP -Wall -Wextra -Wno-unused-parameter -Wold-style-cast -Wnon-virtual-dtor -DNoRepository -ftemplate-depth-200)
else()
    add_compile_options(-m64 -Dlinux64 -DWM_DP -Wall -Wextra -Wno-unused-parameter -Wold-style-cast -Wnon-virtual-dtor -O3 -DNoRepository -ftemplate-depth-200)
endif()

add_definitions(-DWM_LABEL_SIZE=32)
add_definitions(-DOPENFOAM=2212)
add_definitions(-DOPENFOAM_NOT_EXTEND)
add_definitions(-DOPENFOAM_COM)
add_definitions(-Dpthread)
add_definitions(-DOPENFOAMESIORFOUNDATION)


set(foam_com_LIB ${foam_com_DIR}/platforms/${OpenFOAM_build}/lib)
set(MPI_LIBS ${foam_com_DIR}/ThirdParty/packages/openmpi-1.8.8/platforms/linux64GccDPInt32Opt/lib)
set(Pstream_LIB ${foam_com_DIR}/platforms/${OpenFOAM_build}/lib/dummy)
set(Pstream Pstream) 


set(foam_com_SRCS ${foam_com_DIR}/src)
set(solids4foam_SRCS ${solids4foam_DIR}/src)

include_directories(${foam_com_SRCS}/OpenFOAM/lnInclude
                    ${foam_com_SRCS}/finiteVolume/lnInclude     
                    ${foam_com_SRCS}/meshTools/lnInclude
                    ${foam_com_SRCS}/dynamicFvMesh/lnInclude
                    ${foam_com_SRCS}/dynamicMesh/lnInclude
                    ${foam_com_SRCS}/parallel/reconstruct/reconstruct/lnInclude
                    ${foam_com_SRCS}/OSspecific/POSIX/lnInclude
                    ${solids4foam_SRCS}/solids4FoamModels/lnInclude
                    ${solids4foam_SRCS}/blockCoupledSolids4FoamTools/lnInclude)

link_directories(BEFORE ${foam_com_LIB} ${solids4foam_LIB} ${MPI_LIBS} ${Pstream_LIB})

execute_process(COMMAND source ${foam_com_DIR}/etc/bashrc)

add_executable(sub2mesh applications/utilities/sub2mesh/sub2mesh.C ${PATCH_SRCS})
target_link_libraries(sub2mesh PUBLIC OpenFOAM ${Pstream} finiteVolume meshTools solids4FoamModels blockCoupledSolids4FoamTools)

add_executable(subsetMesh applications/utilities/subsetMesh/subsetMesh.C ${PATCH_SRCS})
target_link_libraries(subsetMesh PUBLIC OpenFOAM ${Pstream} finiteVolume meshTools dynamicMesh reconstruct genericPatchFields solids4FoamModels blockCoupledSolids4FoamTools)

add_executable(createMaps applications/utilities/createMaps/createMaps.C)
target_link_libraries(createMaps PUBLIC OpenFOAM ${Pstream} finiteVolume meshTools)

add_executable(patch2cell applications/utilities/patch2cell/patch2cell.C)
target_link_libraries(patch2cell PUBLIC OpenFOAM ${Pstream} finiteVolume meshTools)

add_executable(postprocessing applications/utilities/postprocessing/postprocessing.C)
target_link_libraries(postprocessing PUBLIC OpenFOAM ${Pstream} finiteVolume meshTools)

add_executable(initCase applications/utilities/initCase/initCase.C)
target_link_libraries(initCase PUBLIC OpenFOAM ${Pstream} finiteVolume meshTools)

add_executable(lspfoam ${APP_SRCS} ${PATCH_SRCS})
target_link_libraries(lspfoam PUBLIC solids4FoamModels blockCoupledSolids4FoamTools OpenFOAM ${Pstream} finiteVolume meshTools dynamicFvMesh dynamicMesh incompressibleTransportModels incompressibleTurbulenceModels interfaceProperties topoChangerFvMesh)
