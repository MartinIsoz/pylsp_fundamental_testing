[  3%] Building CXX object CMakeFiles/sub2mesh.dir/applications/utilities/sub2mesh/sub2mesh.C.o
[  7%] Building CXX object CMakeFiles/sub2mesh.dir/src/solids4FoamModels/solidModels/fvPatchFields/laserProcessingPressure/laserProcessingPressureFvPatchVectorField.C.o
In file included from /home/SOFT/modules/installs/foam/solids4foam_v2.1/src/solids4FoamModels/lnInclude/solidSubMeshes.H:394,
                 from /home/SOFT/modules/installs/foam/solids4foam_v2.1/src/solids4FoamModels/lnInclude/mechanicalModel.H:46,
                 from /home/SOFT/modules/installs/foam/solids4foam_v2.1/src/solids4FoamModels/lnInclude/solidModel.H:44,
                 from /home/SOFT/modules/installs/foam/solids4foam_v2.1/src/solids4FoamModels/lnInclude/lookupSolidModel.H:39,
                 from /home/prado/paper/Amarchinta_2010/AA_sof_pylsp/foam/src/solids4FoamModels/solidModels/fvPatchFields/laserProcessingPressure/laserProcessingPressureFvPatchVectorField.C:30:
/home/SOFT/modules/installs/foam/solids4foam_v2.1/src/solids4FoamModels/lnInclude/solidSubMeshesTemplates.C: In member function 'void Foam::solidSubMeshes::mapSubMeshPointFields(const Foam::PtrList<Foam::GeometricField<Type, Foam::pointPatchField, Foam::pointMesh> >&, Foam::GeometricField<Type, Foam::pointPatchField, Foam::pointMesh>&) const':
/home/SOFT/modules/installs/foam/solids4foam_v2.1/src/solids4FoamModels/lnInclude/solidSubMeshesTemplates.C:319:45: warning: 'Foam::label Foam::findIndex(const ListType&, typename ListType::const_reference, label) [with ListType = List<int>; label = int; typename ListType::const_reference = const int&]' is deprecated: Since 2017-10; use "UList find/found methods" [-Wdeprecated-declarations]
  319 |             const bool sharedPoint(findIndex(spLabels, curMeshPoint) != -1);
      |                                    ~~~~~~~~~^~~~~~~~~~~~~~~~~~~~~~~~
In file included from /home/SOFT/modules/spack/installs/linux-ubuntu22.04-broadwell/gcc-13.3.0/openfoam-2312-dryq5snbojskkuaqjhsxhtxqxmbrijvx/src/OpenFOAM/lnInclude/UPstream.H:49,
                 from /home/SOFT/modules/spack/installs/linux-ubuntu22.04-broadwell/gcc-13.3.0/openfoam-2312-dryq5snbojskkuaqjhsxhtxqxmbrijvx/src/OpenFOAM/lnInclude/FieldFunctions.H:31,
                 from /home/SOFT/modules/spack/installs/linux-ubuntu22.04-broadwell/gcc-13.3.0/openfoam-2312-dryq5snbojskkuaqjhsxhtxqxmbrijvx/src/OpenFOAM/lnInclude/Field.H:544,
                 from /home/SOFT/modules/spack/installs/linux-ubuntu22.04-broadwell/gcc-13.3.0/openfoam-2312-dryq5snbojskkuaqjhsxhtxqxmbrijvx/src/OpenFOAM/lnInclude/boolField.H:41,
                 from /home/SOFT/modules/spack/installs/linux-ubuntu22.04-broadwell/gcc-13.3.0/openfoam-2312-dryq5snbojskkuaqjhsxhtxqxmbrijvx/src/OpenFOAM/lnInclude/primitiveFields.H:40,
                 from /home/SOFT/modules/spack/installs/linux-ubuntu22.04-broadwell/gcc-13.3.0/openfoam-2312-dryq5snbojskkuaqjhsxhtxqxmbrijvx/src/OpenFOAM/lnInclude/pointField.H:38,
                 from /home/SOFT/modules/spack/installs/linux-ubuntu22.04-broadwell/gcc-13.3.0/openfoam-2312-dryq5snbojskkuaqjhsxhtxqxmbrijvx/src/OpenFOAM/lnInclude/edge.H:53,
                 from /home/SOFT/modules/spack/installs/linux-ubuntu22.04-broadwell/gcc-13.3.0/openfoam-2312-dryq5snbojskkuaqjhsxhtxqxmbrijvx/src/OpenFOAM/lnInclude/edgeList.H:31,
                 from /home/SOFT/modules/spack/installs/linux-ubuntu22.04-broadwell/gcc-13.3.0/openfoam-2312-dryq5snbojskkuaqjhsxhtxqxmbrijvx/src/OpenFOAM/lnInclude/PrimitivePatch.H:59,
                 from /home/SOFT/modules/spack/installs/linux-ubuntu22.04-broadwell/gcc-13.3.0/openfoam-2312-dryq5snbojskkuaqjhsxhtxqxmbrijvx/src/OpenFOAM/lnInclude/primitivePatch.H:50,
                 from /home/SOFT/modules/spack/installs/linux-ubuntu22.04-broadwell/gcc-13.3.0/openfoam-2312-dryq5snbojskkuaqjhsxhtxqxmbrijvx/src/OpenFOAM/lnInclude/polyPatch.H:46,
                 from /home/SOFT/modules/spack/installs/linux-ubuntu22.04-broadwell/gcc-13.3.0/openfoam-2312-dryq5snbojskkuaqjhsxhtxqxmbrijvx/src/finiteVolume/lnInclude/fvPatch.H:44,
                 from /home/SOFT/modules/spack/installs/linux-ubuntu22.04-broadwell/gcc-13.3.0/openfoam-2312-dryq5snbojskkuaqjhsxhtxqxmbrijvx/src/finiteVolume/lnInclude/fvPatchField.H:51,
                 from /home/SOFT/modules/spack/installs/linux-ubuntu22.04-broadwell/gcc-13.3.0/openfoam-2312-dryq5snbojskkuaqjhsxhtxqxmbrijvx/src/finiteVolume/lnInclude/fvPatchFields.H:31,
                 from /home/prado/paper/Amarchinta_2010/AA_sof_pylsp/foam/src/solids4FoamModels/solidModels/fvPatchFields/laserProcessingPressure/laserProcessingPressureFvPatchVectorField.H:46,
                 from /home/prado/paper/Amarchinta_2010/AA_sof_pylsp/foam/src/solids4FoamModels/solidModels/fvPatchFields/laserProcessingPressure/laserProcessingPressureFvPatchVectorField.C:27:
/home/SOFT/modules/spack/installs/linux-ubuntu22.04-broadwell/gcc-13.3.0/openfoam-2312-dryq5snbojskkuaqjhsxhtxqxmbrijvx/src/OpenFOAM/lnInclude/ListOps.H:397:7: note: declared here
  397 | label findIndex
      |       ^~~~~~~~~
/home/SOFT/modules/installs/foam/solids4foam_v2.1/src/solids4FoamModels/lnInclude/solidSubMeshesTemplates.C:323:42: warning: 'Foam::label Foam::findIndex(const ListType&, typename ListType::const_reference, label) [with ListType = List<int>; label = int; typename ListType::const_reference = const int&]' is deprecated: Since 2017-10; use "UList find/found methods" [-Wdeprecated-declarations]
  323 |                 const label k = findIndex(spLabels, curMeshPoint);
      |                                 ~~~~~~~~~^~~~~~~~~~~~~~~~~~~~~~~~
/home/SOFT/modules/spack/installs/linux-ubuntu22.04-broadwell/gcc-13.3.0/openfoam-2312-dryq5snbojskkuaqjhsxhtxqxmbrijvx/src/OpenFOAM/lnInclude/ListOps.H:397:7: note: declared here
  397 | label findIndex
      |       ^~~~~~~~~
/home/SOFT/modules/installs/foam/solids4foam_v2.1/src/solids4FoamModels/lnInclude/solidSubMeshesTemplates.C:351:47: warning: 'Foam::label Foam::findIndex(const ListType&, typename ListType::const_reference, label) [with ListType = List<int>; label = int; typename ListType::const_reference = const int&]' is deprecated: Since 2017-10; use "UList find/found methods" [-Wdeprecated-declarations]
  351 |             const label curSpIndex = findIndex(spAddressing, k);
      |                                      ~~~~~~~~~^~~~~~~~~~~~~~~~~
/home/SOFT/modules/spack/installs/linux-ubuntu22.04-broadwell/gcc-13.3.0/openfoam-2312-dryq5snbojskkuaqjhsxhtxqxmbrijvx/src/OpenFOAM/lnInclude/ListOps.H:397:7: note: declared here
  397 | label findIndex
      |       ^~~~~~~~~
[ 11%] Linking CXX executable sub2mesh
[ 11%] Built target sub2mesh
[ 14%] Building CXX object CMakeFiles/subsetMesh.dir/applications/utilities/subsetMesh/subsetMesh.C.o
[ 18%] Building CXX object CMakeFiles/subsetMesh.dir/src/solids4FoamModels/solidModels/fvPatchFields/laserProcessingPressure/laserProcessingPressureFvPatchVectorField.C.o
In file included from /home/SOFT/modules/installs/foam/solids4foam_v2.1/src/solids4FoamModels/lnInclude/solidSubMeshes.H:394,
                 from /home/SOFT/modules/installs/foam/solids4foam_v2.1/src/solids4FoamModels/lnInclude/mechanicalModel.H:46,
                 from /home/SOFT/modules/installs/foam/solids4foam_v2.1/src/solids4FoamModels/lnInclude/solidModel.H:44,
                 from /home/SOFT/modules/installs/foam/solids4foam_v2.1/src/solids4FoamModels/lnInclude/lookupSolidModel.H:39,
                 from /home/prado/paper/Amarchinta_2010/AA_sof_pylsp/foam/src/solids4FoamModels/solidModels/fvPatchFields/laserProcessingPressure/laserProcessingPressureFvPatchVectorField.C:30:
/home/SOFT/modules/installs/foam/solids4foam_v2.1/src/solids4FoamModels/lnInclude/solidSubMeshesTemplates.C: In member function 'void Foam::solidSubMeshes::mapSubMeshPointFields(const Foam::PtrList<Foam::GeometricField<Type, Foam::pointPatchField, Foam::pointMesh> >&, Foam::GeometricField<Type, Foam::pointPatchField, Foam::pointMesh>&) const':
/home/SOFT/modules/installs/foam/solids4foam_v2.1/src/solids4FoamModels/lnInclude/solidSubMeshesTemplates.C:319:45: warning: 'Foam::label Foam::findIndex(const ListType&, typename ListType::const_reference, label) [with ListType = List<int>; label = int; typename ListType::const_reference = const int&]' is deprecated: Since 2017-10; use "UList find/found methods" [-Wdeprecated-declarations]
  319 |             const bool sharedPoint(findIndex(spLabels, curMeshPoint) != -1);
      |                                    ~~~~~~~~~^~~~~~~~~~~~~~~~~~~~~~~~
In file included from /home/SOFT/modules/spack/installs/linux-ubuntu22.04-broadwell/gcc-13.3.0/openfoam-2312-dryq5snbojskkuaqjhsxhtxqxmbrijvx/src/OpenFOAM/lnInclude/UPstream.H:49,
                 from /home/SOFT/modules/spack/installs/linux-ubuntu22.04-broadwell/gcc-13.3.0/openfoam-2312-dryq5snbojskkuaqjhsxhtxqxmbrijvx/src/OpenFOAM/lnInclude/FieldFunctions.H:31,
                 from /home/SOFT/modules/spack/installs/linux-ubuntu22.04-broadwell/gcc-13.3.0/openfoam-2312-dryq5snbojskkuaqjhsxhtxqxmbrijvx/src/OpenFOAM/lnInclude/Field.H:544,
                 from /home/SOFT/modules/spack/installs/linux-ubuntu22.04-broadwell/gcc-13.3.0/openfoam-2312-dryq5snbojskkuaqjhsxhtxqxmbrijvx/src/OpenFOAM/lnInclude/boolField.H:41,
                 from /home/SOFT/modules/spack/installs/linux-ubuntu22.04-broadwell/gcc-13.3.0/openfoam-2312-dryq5snbojskkuaqjhsxhtxqxmbrijvx/src/OpenFOAM/lnInclude/primitiveFields.H:40,
                 from /home/SOFT/modules/spack/installs/linux-ubuntu22.04-broadwell/gcc-13.3.0/openfoam-2312-dryq5snbojskkuaqjhsxhtxqxmbrijvx/src/OpenFOAM/lnInclude/pointField.H:38,
                 from /home/SOFT/modules/spack/installs/linux-ubuntu22.04-broadwell/gcc-13.3.0/openfoam-2312-dryq5snbojskkuaqjhsxhtxqxmbrijvx/src/OpenFOAM/lnInclude/edge.H:53,
                 from /home/SOFT/modules/spack/installs/linux-ubuntu22.04-broadwell/gcc-13.3.0/openfoam-2312-dryq5snbojskkuaqjhsxhtxqxmbrijvx/src/OpenFOAM/lnInclude/edgeList.H:31,
                 from /home/SOFT/modules/spack/installs/linux-ubuntu22.04-broadwell/gcc-13.3.0/openfoam-2312-dryq5snbojskkuaqjhsxhtxqxmbrijvx/src/OpenFOAM/lnInclude/PrimitivePatch.H:59,
                 from /home/SOFT/modules/spack/installs/linux-ubuntu22.04-broadwell/gcc-13.3.0/openfoam-2312-dryq5snbojskkuaqjhsxhtxqxmbrijvx/src/OpenFOAM/lnInclude/primitivePatch.H:50,
                 from /home/SOFT/modules/spack/installs/linux-ubuntu22.04-broadwell/gcc-13.3.0/openfoam-2312-dryq5snbojskkuaqjhsxhtxqxmbrijvx/src/OpenFOAM/lnInclude/polyPatch.H:46,
                 from /home/SOFT/modules/spack/installs/linux-ubuntu22.04-broadwell/gcc-13.3.0/openfoam-2312-dryq5snbojskkuaqjhsxhtxqxmbrijvx/src/finiteVolume/lnInclude/fvPatch.H:44,
                 from /home/SOFT/modules/spack/installs/linux-ubuntu22.04-broadwell/gcc-13.3.0/openfoam-2312-dryq5snbojskkuaqjhsxhtxqxmbrijvx/src/finiteVolume/lnInclude/fvPatchField.H:51,
                 from /home/SOFT/modules/spack/installs/linux-ubuntu22.04-broadwell/gcc-13.3.0/openfoam-2312-dryq5snbojskkuaqjhsxhtxqxmbrijvx/src/finiteVolume/lnInclude/fvPatchFields.H:31,
                 from /home/prado/paper/Amarchinta_2010/AA_sof_pylsp/foam/src/solids4FoamModels/solidModels/fvPatchFields/laserProcessingPressure/laserProcessingPressureFvPatchVectorField.H:46,
                 from /home/prado/paper/Amarchinta_2010/AA_sof_pylsp/foam/src/solids4FoamModels/solidModels/fvPatchFields/laserProcessingPressure/laserProcessingPressureFvPatchVectorField.C:27:
/home/SOFT/modules/spack/installs/linux-ubuntu22.04-broadwell/gcc-13.3.0/openfoam-2312-dryq5snbojskkuaqjhsxhtxqxmbrijvx/src/OpenFOAM/lnInclude/ListOps.H:397:7: note: declared here
  397 | label findIndex
      |       ^~~~~~~~~
/home/SOFT/modules/installs/foam/solids4foam_v2.1/src/solids4FoamModels/lnInclude/solidSubMeshesTemplates.C:323:42: warning: 'Foam::label Foam::findIndex(const ListType&, typename ListType::const_reference, label) [with ListType = List<int>; label = int; typename ListType::const_reference = const int&]' is deprecated: Since 2017-10; use "UList find/found methods" [-Wdeprecated-declarations]
  323 |                 const label k = findIndex(spLabels, curMeshPoint);
      |                                 ~~~~~~~~~^~~~~~~~~~~~~~~~~~~~~~~~
/home/SOFT/modules/spack/installs/linux-ubuntu22.04-broadwell/gcc-13.3.0/openfoam-2312-dryq5snbojskkuaqjhsxhtxqxmbrijvx/src/OpenFOAM/lnInclude/ListOps.H:397:7: note: declared here
  397 | label findIndex
      |       ^~~~~~~~~
/home/SOFT/modules/installs/foam/solids4foam_v2.1/src/solids4FoamModels/lnInclude/solidSubMeshesTemplates.C:351:47: warning: 'Foam::label Foam::findIndex(const ListType&, typename ListType::const_reference, label) [with ListType = List<int>; label = int; typename ListType::const_reference = const int&]' is deprecated: Since 2017-10; use "UList find/found methods" [-Wdeprecated-declarations]
  351 |             const label curSpIndex = findIndex(spAddressing, k);
      |                                      ~~~~~~~~~^~~~~~~~~~~~~~~~~
/home/SOFT/modules/spack/installs/linux-ubuntu22.04-broadwell/gcc-13.3.0/openfoam-2312-dryq5snbojskkuaqjhsxhtxqxmbrijvx/src/OpenFOAM/lnInclude/ListOps.H:397:7: note: declared here
  397 | label findIndex
      |       ^~~~~~~~~
[ 22%] Linking CXX executable subsetMesh
[ 22%] Built target subsetMesh
[ 25%] Building CXX object CMakeFiles/createMaps.dir/applications/utilities/createMaps/createMaps.C.o
[ 29%] Linking CXX executable createMaps
[ 29%] Built target createMaps
[ 33%] Building CXX object CMakeFiles/patch2cell.dir/applications/utilities/patch2cell/patch2cell.C.o
[ 37%] Linking CXX executable patch2cell
[ 37%] Built target patch2cell
[ 40%] Building CXX object CMakeFiles/postprocessing.dir/applications/utilities/postprocessing/postprocessing.C.o
/home/prado/paper/Amarchinta_2010/AA_sof_pylsp/foam/applications/utilities/postprocessing/postprocessing.C: In function 'int main(int, char**)':
/home/prado/paper/Amarchinta_2010/AA_sof_pylsp/foam/applications/utilities/postprocessing/postprocessing.C:24:52: warning: 'T Foam::argList::optionRead(const Foam::word&) const [with T = Foam::List<Foam::word>]' is deprecated: Since 2018-01; use "get() method" [-Wdeprecated-declarations]
   24 |     wordList fieldNames = args.optionRead<wordList>("fieldNames");
      |                           ~~~~~~~~~~~~~~~~~~~~~~~~~^~~~~~~~~~~~~~
In file included from /home/SOFT/modules/spack/installs/linux-ubuntu22.04-broadwell/gcc-13.3.0/openfoam-2312-dryq5snbojskkuaqjhsxhtxqxmbrijvx/src/finiteVolume/lnInclude/fvCFD.H:27,
                 from /home/prado/paper/Amarchinta_2010/AA_sof_pylsp/foam/applications/utilities/postprocessing/postprocessing.C:1:
/home/SOFT/modules/spack/installs/linux-ubuntu22.04-broadwell/gcc-13.3.0/openfoam-2312-dryq5snbojskkuaqjhsxhtxqxmbrijvx/src/OpenFOAM/lnInclude/argList.H:813:11: note: declared here
  813 |         T optionRead(const word& optName) const
      |           ^~~~~~~~~~
[ 44%] Linking CXX executable postprocessing
[ 44%] Built target postprocessing
[ 48%] Building CXX object CMakeFiles/initCase.dir/applications/utilities/initCase/initCase.C.o
[ 51%] Linking CXX executable initCase
[ 51%] Built target initCase
[ 55%] Building CXX object CMakeFiles/lspfoam.dir/applications/solvers/solids4Foam/solids4Foam.C.o
[ 59%] Building CXX object CMakeFiles/lspfoam.dir/src/solids4FoamModels/solidModels/myExplicitUnsLinGeomTotalDispSolid/myExplicitUnsLinGeomTotalDispSolid.C.o
In file included from /home/SOFT/modules/installs/foam/solids4foam_v2.1/src/solids4FoamModels/lnInclude/solidSubMeshes.H:394,
                 from /home/SOFT/modules/installs/foam/solids4foam_v2.1/src/solids4FoamModels/lnInclude/mechanicalModel.H:46,
                 from /home/SOFT/modules/installs/foam/solids4foam_v2.1/src/solids4FoamModels/lnInclude/solidModel.H:44,
                 from /home/prado/paper/Amarchinta_2010/AA_sof_pylsp/foam/src/solids4FoamModels/solidModels/myExplicitUnsLinGeomTotalDispSolid/myExplicitUnsLinGeomTotalDispSolid.H:56,
                 from /home/prado/paper/Amarchinta_2010/AA_sof_pylsp/foam/src/solids4FoamModels/solidModels/myExplicitUnsLinGeomTotalDispSolid/myExplicitUnsLinGeomTotalDispSolid.C:27:
/home/SOFT/modules/installs/foam/solids4foam_v2.1/src/solids4FoamModels/lnInclude/solidSubMeshesTemplates.C: In member function 'void Foam::solidSubMeshes::mapSubMeshPointFields(const Foam::PtrList<Foam::GeometricField<Type, Foam::pointPatchField, Foam::pointMesh> >&, Foam::GeometricField<Type, Foam::pointPatchField, Foam::pointMesh>&) const':
/home/SOFT/modules/installs/foam/solids4foam_v2.1/src/solids4FoamModels/lnInclude/solidSubMeshesTemplates.C:319:45: warning: 'Foam::label Foam::findIndex(const ListType&, typename ListType::const_reference, label) [with ListType = List<int>; label = int; typename ListType::const_reference = const int&]' is deprecated: Since 2017-10; use "UList find/found methods" [-Wdeprecated-declarations]
  319 |             const bool sharedPoint(findIndex(spLabels, curMeshPoint) != -1);
      |                                    ~~~~~~~~~^~~~~~~~~~~~~~~~~~~~~~~~
In file included from /home/SOFT/modules/spack/installs/linux-ubuntu22.04-broadwell/gcc-13.3.0/openfoam-2312-dryq5snbojskkuaqjhsxhtxqxmbrijvx/src/OpenFOAM/lnInclude/UPstream.H:49,
                 from /home/SOFT/modules/spack/installs/linux-ubuntu22.04-broadwell/gcc-13.3.0/openfoam-2312-dryq5snbojskkuaqjhsxhtxqxmbrijvx/src/OpenFOAM/lnInclude/fileOperation.H:78,
                 from /home/SOFT/modules/spack/installs/linux-ubuntu22.04-broadwell/gcc-13.3.0/openfoam-2312-dryq5snbojskkuaqjhsxhtxqxmbrijvx/src/OpenFOAM/lnInclude/IOobjectTemplates.C:31,
                 from /home/SOFT/modules/spack/installs/linux-ubuntu22.04-broadwell/gcc-13.3.0/openfoam-2312-dryq5snbojskkuaqjhsxhtxqxmbrijvx/src/OpenFOAM/lnInclude/IOobject.H:739,
                 from /home/SOFT/modules/spack/installs/linux-ubuntu22.04-broadwell/gcc-13.3.0/openfoam-2312-dryq5snbojskkuaqjhsxhtxqxmbrijvx/src/OpenFOAM/lnInclude/regIOobject.H:44,
                 from /home/SOFT/modules/spack/installs/linux-ubuntu22.04-broadwell/gcc-13.3.0/openfoam-2312-dryq5snbojskkuaqjhsxhtxqxmbrijvx/src/OpenFOAM/lnInclude/baseIOdictionary.H:46,
                 from /home/SOFT/modules/spack/installs/linux-ubuntu22.04-broadwell/gcc-13.3.0/openfoam-2312-dryq5snbojskkuaqjhsxhtxqxmbrijvx/src/OpenFOAM/lnInclude/IOdictionary.H:44,
                 from /home/SOFT/modules/installs/foam/solids4foam_v2.1/src/solids4FoamModels/lnInclude/physicsModel.H:38,
                 from /home/SOFT/modules/installs/foam/solids4foam_v2.1/src/solids4FoamModels/lnInclude/solidModel.H:37:
/home/SOFT/modules/spack/installs/linux-ubuntu22.04-broadwell/gcc-13.3.0/openfoam-2312-dryq5snbojskkuaqjhsxhtxqxmbrijvx/src/OpenFOAM/lnInclude/ListOps.H:397:7: note: declared here
  397 | label findIndex
      |       ^~~~~~~~~
/home/SOFT/modules/installs/foam/solids4foam_v2.1/src/solids4FoamModels/lnInclude/solidSubMeshesTemplates.C:323:42: warning: 'Foam::label Foam::findIndex(const ListType&, typename ListType::const_reference, label) [with ListType = List<int>; label = int; typename ListType::const_reference = const int&]' is deprecated: Since 2017-10; use "UList find/found methods" [-Wdeprecated-declarations]
  323 |                 const label k = findIndex(spLabels, curMeshPoint);
      |                                 ~~~~~~~~~^~~~~~~~~~~~~~~~~~~~~~~~
/home/SOFT/modules/spack/installs/linux-ubuntu22.04-broadwell/gcc-13.3.0/openfoam-2312-dryq5snbojskkuaqjhsxhtxqxmbrijvx/src/OpenFOAM/lnInclude/ListOps.H:397:7: note: declared here
  397 | label findIndex
      |       ^~~~~~~~~
/home/SOFT/modules/installs/foam/solids4foam_v2.1/src/solids4FoamModels/lnInclude/solidSubMeshesTemplates.C:351:47: warning: 'Foam::label Foam::findIndex(const ListType&, typename ListType::const_reference, label) [with ListType = List<int>; label = int; typename ListType::const_reference = const int&]' is deprecated: Since 2017-10; use "UList find/found methods" [-Wdeprecated-declarations]
  351 |             const label curSpIndex = findIndex(spAddressing, k);
      |                                      ~~~~~~~~~^~~~~~~~~~~~~~~~~
/home/SOFT/modules/spack/installs/linux-ubuntu22.04-broadwell/gcc-13.3.0/openfoam-2312-dryq5snbojskkuaqjhsxhtxqxmbrijvx/src/OpenFOAM/lnInclude/ListOps.H:397:7: note: declared here
  397 | label findIndex
      |       ^~~~~~~~~
[ 62%] Building CXX object CMakeFiles/lspfoam.dir/src/solids4FoamModels/solidModels/myExplicitLinGeomTotalDispSolid/myExplicitLinGeomTotalDispSolid.C.o
In file included from /home/SOFT/modules/installs/foam/solids4foam_v2.1/src/solids4FoamModels/lnInclude/solidSubMeshes.H:394,
                 from /home/SOFT/modules/installs/foam/solids4foam_v2.1/src/solids4FoamModels/lnInclude/mechanicalModel.H:46,
                 from /home/SOFT/modules/installs/foam/solids4foam_v2.1/src/solids4FoamModels/lnInclude/solidModel.H:44,
                 from /home/prado/paper/Amarchinta_2010/AA_sof_pylsp/foam/src/solids4FoamModels/solidModels/myExplicitLinGeomTotalDispSolid/myExplicitLinGeomTotalDispSolid.H:4,
                 from /home/prado/paper/Amarchinta_2010/AA_sof_pylsp/foam/src/solids4FoamModels/solidModels/myExplicitLinGeomTotalDispSolid/myExplicitLinGeomTotalDispSolid.C:1:
/home/SOFT/modules/installs/foam/solids4foam_v2.1/src/solids4FoamModels/lnInclude/solidSubMeshesTemplates.C: In member function 'void Foam::solidSubMeshes::mapSubMeshPointFields(const Foam::PtrList<Foam::GeometricField<Type, Foam::pointPatchField, Foam::pointMesh> >&, Foam::GeometricField<Type, Foam::pointPatchField, Foam::pointMesh>&) const':
/home/SOFT/modules/installs/foam/solids4foam_v2.1/src/solids4FoamModels/lnInclude/solidSubMeshesTemplates.C:319:45: warning: 'Foam::label Foam::findIndex(const ListType&, typename ListType::const_reference, label) [with ListType = List<int>; label = int; typename ListType::const_reference = const int&]' is deprecated: Since 2017-10; use "UList find/found methods" [-Wdeprecated-declarations]
  319 |             const bool sharedPoint(findIndex(spLabels, curMeshPoint) != -1);
      |                                    ~~~~~~~~~^~~~~~~~~~~~~~~~~~~~~~~~
In file included from /home/SOFT/modules/spack/installs/linux-ubuntu22.04-broadwell/gcc-13.3.0/openfoam-2312-dryq5snbojskkuaqjhsxhtxqxmbrijvx/src/OpenFOAM/lnInclude/UPstream.H:49,
                 from /home/SOFT/modules/spack/installs/linux-ubuntu22.04-broadwell/gcc-13.3.0/openfoam-2312-dryq5snbojskkuaqjhsxhtxqxmbrijvx/src/OpenFOAM/lnInclude/fileOperation.H:78,
                 from /home/SOFT/modules/spack/installs/linux-ubuntu22.04-broadwell/gcc-13.3.0/openfoam-2312-dryq5snbojskkuaqjhsxhtxqxmbrijvx/src/OpenFOAM/lnInclude/IOobjectTemplates.C:31,
                 from /home/SOFT/modules/spack/installs/linux-ubuntu22.04-broadwell/gcc-13.3.0/openfoam-2312-dryq5snbojskkuaqjhsxhtxqxmbrijvx/src/OpenFOAM/lnInclude/IOobject.H:739,
                 from /home/SOFT/modules/spack/installs/linux-ubuntu22.04-broadwell/gcc-13.3.0/openfoam-2312-dryq5snbojskkuaqjhsxhtxqxmbrijvx/src/OpenFOAM/lnInclude/regIOobject.H:44,
                 from /home/SOFT/modules/spack/installs/linux-ubuntu22.04-broadwell/gcc-13.3.0/openfoam-2312-dryq5snbojskkuaqjhsxhtxqxmbrijvx/src/OpenFOAM/lnInclude/baseIOdictionary.H:46,
                 from /home/SOFT/modules/spack/installs/linux-ubuntu22.04-broadwell/gcc-13.3.0/openfoam-2312-dryq5snbojskkuaqjhsxhtxqxmbrijvx/src/OpenFOAM/lnInclude/IOdictionary.H:44,
                 from /home/SOFT/modules/installs/foam/solids4foam_v2.1/src/solids4FoamModels/lnInclude/physicsModel.H:38,
                 from /home/SOFT/modules/installs/foam/solids4foam_v2.1/src/solids4FoamModels/lnInclude/solidModel.H:37:
/home/SOFT/modules/spack/installs/linux-ubuntu22.04-broadwell/gcc-13.3.0/openfoam-2312-dryq5snbojskkuaqjhsxhtxqxmbrijvx/src/OpenFOAM/lnInclude/ListOps.H:397:7: note: declared here
  397 | label findIndex
      |       ^~~~~~~~~
/home/SOFT/modules/installs/foam/solids4foam_v2.1/src/solids4FoamModels/lnInclude/solidSubMeshesTemplates.C:323:42: warning: 'Foam::label Foam::findIndex(const ListType&, typename ListType::const_reference, label) [with ListType = List<int>; label = int; typename ListType::const_reference = const int&]' is deprecated: Since 2017-10; use "UList find/found methods" [-Wdeprecated-declarations]
  323 |                 const label k = findIndex(spLabels, curMeshPoint);
      |                                 ~~~~~~~~~^~~~~~~~~~~~~~~~~~~~~~~~
/home/SOFT/modules/spack/installs/linux-ubuntu22.04-broadwell/gcc-13.3.0/openfoam-2312-dryq5snbojskkuaqjhsxhtxqxmbrijvx/src/OpenFOAM/lnInclude/ListOps.H:397:7: note: declared here
  397 | label findIndex
      |       ^~~~~~~~~
/home/SOFT/modules/installs/foam/solids4foam_v2.1/src/solids4FoamModels/lnInclude/solidSubMeshesTemplates.C:351:47: warning: 'Foam::label Foam::findIndex(const ListType&, typename ListType::const_reference, label) [with ListType = List<int>; label = int; typename ListType::const_reference = const int&]' is deprecated: Since 2017-10; use "UList find/found methods" [-Wdeprecated-declarations]
  351 |             const label curSpIndex = findIndex(spAddressing, k);
      |                                      ~~~~~~~~~^~~~~~~~~~~~~~~~~
/home/SOFT/modules/spack/installs/linux-ubuntu22.04-broadwell/gcc-13.3.0/openfoam-2312-dryq5snbojskkuaqjhsxhtxqxmbrijvx/src/OpenFOAM/lnInclude/ListOps.H:397:7: note: declared here
  397 | label findIndex
      |       ^~~~~~~~~
/home/prado/paper/Amarchinta_2010/AA_sof_pylsp/foam/src/solids4FoamModels/solidModels/myExplicitLinGeomTotalDispSolid/myExplicitLinGeomTotalDispSolid.H: In constructor 'Foam::solidModels::myExplicitLinGeomTotalDispSolid::myExplicitLinGeomTotalDispSolid(Foam::Time&, const Foam::word&)':
/home/prado/paper/Amarchinta_2010/AA_sof_pylsp/foam/src/solids4FoamModels/solidModels/myExplicitLinGeomTotalDispSolid/myExplicitLinGeomTotalDispSolid.H:21:18: warning: 'Foam::solidModels::myExplicitLinGeomTotalDispSolid::JSTScaleFactor_' will be initialized after [-Wreorder]
   21 |     const scalar JSTScaleFactor_;
      |                  ^~~~~~~~~~~~~~~
/home/prado/paper/Amarchinta_2010/AA_sof_pylsp/foam/src/solids4FoamModels/solidModels/myExplicitLinGeomTotalDispSolid/myExplicitLinGeomTotalDispSolid.H:17:24: warning:   'Foam::surfaceScalarField Foam::solidModels::myExplicitLinGeomTotalDispSolid::waveSpeed_' [-Wreorder]
   17 |     surfaceScalarField waveSpeed_;
      |                        ^~~~~~~~~~
/home/prado/paper/Amarchinta_2010/AA_sof_pylsp/foam/src/solids4FoamModels/solidModels/myExplicitLinGeomTotalDispSolid/myExplicitLinGeomTotalDispSolid.C:27:9: warning:   when initialized here [-Wreorder]
   27 |         myExplicitLinGeomTotalDispSolid::myExplicitLinGeomTotalDispSolid
      |         ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
[ 66%] Building CXX object CMakeFiles/lspfoam.dir/src/solids4FoamModels/solidModels/myUnsLinGeomSolid/myUnsLinGeomSolid.C.o
In file included from /home/SOFT/modules/installs/foam/solids4foam_v2.1/src/solids4FoamModels/lnInclude/solidSubMeshes.H:394,
                 from /home/SOFT/modules/installs/foam/solids4foam_v2.1/src/solids4FoamModels/lnInclude/mechanicalModel.H:46,
                 from /home/SOFT/modules/installs/foam/solids4foam_v2.1/src/solids4FoamModels/lnInclude/solidModel.H:44,
                 from /home/prado/paper/Amarchinta_2010/AA_sof_pylsp/foam/src/solids4FoamModels/solidModels/myUnsLinGeomSolid/myUnsLinGeomSolid.H:49,
                 from /home/prado/paper/Amarchinta_2010/AA_sof_pylsp/foam/src/solids4FoamModels/solidModels/myUnsLinGeomSolid/myUnsLinGeomSolid.C:27:
/home/SOFT/modules/installs/foam/solids4foam_v2.1/src/solids4FoamModels/lnInclude/solidSubMeshesTemplates.C: In member function 'void Foam::solidSubMeshes::mapSubMeshPointFields(const Foam::PtrList<Foam::GeometricField<Type, Foam::pointPatchField, Foam::pointMesh> >&, Foam::GeometricField<Type, Foam::pointPatchField, Foam::pointMesh>&) const':
/home/SOFT/modules/installs/foam/solids4foam_v2.1/src/solids4FoamModels/lnInclude/solidSubMeshesTemplates.C:319:45: warning: 'Foam::label Foam::findIndex(const ListType&, typename ListType::const_reference, label) [with ListType = List<int>; label = int; typename ListType::const_reference = const int&]' is deprecated: Since 2017-10; use "UList find/found methods" [-Wdeprecated-declarations]
  319 |             const bool sharedPoint(findIndex(spLabels, curMeshPoint) != -1);
      |                                    ~~~~~~~~~^~~~~~~~~~~~~~~~~~~~~~~~
In file included from /home/SOFT/modules/spack/installs/linux-ubuntu22.04-broadwell/gcc-13.3.0/openfoam-2312-dryq5snbojskkuaqjhsxhtxqxmbrijvx/src/OpenFOAM/lnInclude/UPstream.H:49,
                 from /home/SOFT/modules/spack/installs/linux-ubuntu22.04-broadwell/gcc-13.3.0/openfoam-2312-dryq5snbojskkuaqjhsxhtxqxmbrijvx/src/OpenFOAM/lnInclude/fileOperation.H:78,
                 from /home/SOFT/modules/spack/installs/linux-ubuntu22.04-broadwell/gcc-13.3.0/openfoam-2312-dryq5snbojskkuaqjhsxhtxqxmbrijvx/src/OpenFOAM/lnInclude/IOobjectTemplates.C:31,
                 from /home/SOFT/modules/spack/installs/linux-ubuntu22.04-broadwell/gcc-13.3.0/openfoam-2312-dryq5snbojskkuaqjhsxhtxqxmbrijvx/src/OpenFOAM/lnInclude/IOobject.H:739,
                 from /home/SOFT/modules/spack/installs/linux-ubuntu22.04-broadwell/gcc-13.3.0/openfoam-2312-dryq5snbojskkuaqjhsxhtxqxmbrijvx/src/OpenFOAM/lnInclude/regIOobject.H:44,
                 from /home/SOFT/modules/spack/installs/linux-ubuntu22.04-broadwell/gcc-13.3.0/openfoam-2312-dryq5snbojskkuaqjhsxhtxqxmbrijvx/src/OpenFOAM/lnInclude/baseIOdictionary.H:46,
                 from /home/SOFT/modules/spack/installs/linux-ubuntu22.04-broadwell/gcc-13.3.0/openfoam-2312-dryq5snbojskkuaqjhsxhtxqxmbrijvx/src/OpenFOAM/lnInclude/IOdictionary.H:44,
                 from /home/SOFT/modules/installs/foam/solids4foam_v2.1/src/solids4FoamModels/lnInclude/physicsModel.H:38,
                 from /home/SOFT/modules/installs/foam/solids4foam_v2.1/src/solids4FoamModels/lnInclude/solidModel.H:37:
/home/SOFT/modules/spack/installs/linux-ubuntu22.04-broadwell/gcc-13.3.0/openfoam-2312-dryq5snbojskkuaqjhsxhtxqxmbrijvx/src/OpenFOAM/lnInclude/ListOps.H:397:7: note: declared here
  397 | label findIndex
      |       ^~~~~~~~~
/home/SOFT/modules/installs/foam/solids4foam_v2.1/src/solids4FoamModels/lnInclude/solidSubMeshesTemplates.C:323:42: warning: 'Foam::label Foam::findIndex(const ListType&, typename ListType::const_reference, label) [with ListType = List<int>; label = int; typename ListType::const_reference = const int&]' is deprecated: Since 2017-10; use "UList find/found methods" [-Wdeprecated-declarations]
  323 |                 const label k = findIndex(spLabels, curMeshPoint);
      |                                 ~~~~~~~~~^~~~~~~~~~~~~~~~~~~~~~~~
/home/SOFT/modules/spack/installs/linux-ubuntu22.04-broadwell/gcc-13.3.0/openfoam-2312-dryq5snbojskkuaqjhsxhtxqxmbrijvx/src/OpenFOAM/lnInclude/ListOps.H:397:7: note: declared here
  397 | label findIndex
      |       ^~~~~~~~~
/home/SOFT/modules/installs/foam/solids4foam_v2.1/src/solids4FoamModels/lnInclude/solidSubMeshesTemplates.C:351:47: warning: 'Foam::label Foam::findIndex(const ListType&, typename ListType::const_reference, label) [with ListType = List<int>; label = int; typename ListType::const_reference = const int&]' is deprecated: Since 2017-10; use "UList find/found methods" [-Wdeprecated-declarations]
  351 |             const label curSpIndex = findIndex(spAddressing, k);
      |                                      ~~~~~~~~~^~~~~~~~~~~~~~~~~
/home/SOFT/modules/spack/installs/linux-ubuntu22.04-broadwell/gcc-13.3.0/openfoam-2312-dryq5snbojskkuaqjhsxhtxqxmbrijvx/src/OpenFOAM/lnInclude/ListOps.H:397:7: note: declared here
  397 | label findIndex
      |       ^~~~~~~~~
[ 70%] Building CXX object CMakeFiles/lspfoam.dir/src/solids4FoamModels/solidModels/myLinGeomTotalDispSolid/myLinGeomTotalDispSolid.C.o
In file included from /home/SOFT/modules/installs/foam/solids4foam_v2.1/src/solids4FoamModels/lnInclude/solidSubMeshes.H:394,
                 from /home/SOFT/modules/installs/foam/solids4foam_v2.1/src/solids4FoamModels/lnInclude/mechanicalModel.H:46,
                 from /home/SOFT/modules/installs/foam/solids4foam_v2.1/src/solids4FoamModels/lnInclude/solidModel.H:44,
                 from /home/prado/paper/Amarchinta_2010/AA_sof_pylsp/foam/src/solids4FoamModels/solidModels/myLinGeomTotalDispSolid/myLinGeomTotalDispSolid.H:46,
                 from /home/prado/paper/Amarchinta_2010/AA_sof_pylsp/foam/src/solids4FoamModels/solidModels/myLinGeomTotalDispSolid/myLinGeomTotalDispSolid.C:27:
/home/SOFT/modules/installs/foam/solids4foam_v2.1/src/solids4FoamModels/lnInclude/solidSubMeshesTemplates.C: In member function 'void Foam::solidSubMeshes::mapSubMeshPointFields(const Foam::PtrList<Foam::GeometricField<Type, Foam::pointPatchField, Foam::pointMesh> >&, Foam::GeometricField<Type, Foam::pointPatchField, Foam::pointMesh>&) const':
/home/SOFT/modules/installs/foam/solids4foam_v2.1/src/solids4FoamModels/lnInclude/solidSubMeshesTemplates.C:319:45: warning: 'Foam::label Foam::findIndex(const ListType&, typename ListType::const_reference, label) [with ListType = List<int>; label = int; typename ListType::const_reference = const int&]' is deprecated: Since 2017-10; use "UList find/found methods" [-Wdeprecated-declarations]
  319 |             const bool sharedPoint(findIndex(spLabels, curMeshPoint) != -1);
      |                                    ~~~~~~~~~^~~~~~~~~~~~~~~~~~~~~~~~
In file included from /home/SOFT/modules/spack/installs/linux-ubuntu22.04-broadwell/gcc-13.3.0/openfoam-2312-dryq5snbojskkuaqjhsxhtxqxmbrijvx/src/OpenFOAM/lnInclude/UPstream.H:49,
                 from /home/SOFT/modules/spack/installs/linux-ubuntu22.04-broadwell/gcc-13.3.0/openfoam-2312-dryq5snbojskkuaqjhsxhtxqxmbrijvx/src/OpenFOAM/lnInclude/fileOperation.H:78,
                 from /home/SOFT/modules/spack/installs/linux-ubuntu22.04-broadwell/gcc-13.3.0/openfoam-2312-dryq5snbojskkuaqjhsxhtxqxmbrijvx/src/OpenFOAM/lnInclude/IOobjectTemplates.C:31,
                 from /home/SOFT/modules/spack/installs/linux-ubuntu22.04-broadwell/gcc-13.3.0/openfoam-2312-dryq5snbojskkuaqjhsxhtxqxmbrijvx/src/OpenFOAM/lnInclude/IOobject.H:739,
                 from /home/SOFT/modules/spack/installs/linux-ubuntu22.04-broadwell/gcc-13.3.0/openfoam-2312-dryq5snbojskkuaqjhsxhtxqxmbrijvx/src/OpenFOAM/lnInclude/regIOobject.H:44,
                 from /home/SOFT/modules/spack/installs/linux-ubuntu22.04-broadwell/gcc-13.3.0/openfoam-2312-dryq5snbojskkuaqjhsxhtxqxmbrijvx/src/OpenFOAM/lnInclude/baseIOdictionary.H:46,
                 from /home/SOFT/modules/spack/installs/linux-ubuntu22.04-broadwell/gcc-13.3.0/openfoam-2312-dryq5snbojskkuaqjhsxhtxqxmbrijvx/src/OpenFOAM/lnInclude/IOdictionary.H:44,
                 from /home/SOFT/modules/installs/foam/solids4foam_v2.1/src/solids4FoamModels/lnInclude/physicsModel.H:38,
                 from /home/SOFT/modules/installs/foam/solids4foam_v2.1/src/solids4FoamModels/lnInclude/solidModel.H:37:
/home/SOFT/modules/spack/installs/linux-ubuntu22.04-broadwell/gcc-13.3.0/openfoam-2312-dryq5snbojskkuaqjhsxhtxqxmbrijvx/src/OpenFOAM/lnInclude/ListOps.H:397:7: note: declared here
  397 | label findIndex
      |       ^~~~~~~~~
/home/SOFT/modules/installs/foam/solids4foam_v2.1/src/solids4FoamModels/lnInclude/solidSubMeshesTemplates.C:323:42: warning: 'Foam::label Foam::findIndex(const ListType&, typename ListType::const_reference, label) [with ListType = List<int>; label = int; typename ListType::const_reference = const int&]' is deprecated: Since 2017-10; use "UList find/found methods" [-Wdeprecated-declarations]
  323 |                 const label k = findIndex(spLabels, curMeshPoint);
      |                                 ~~~~~~~~~^~~~~~~~~~~~~~~~~~~~~~~~
/home/SOFT/modules/spack/installs/linux-ubuntu22.04-broadwell/gcc-13.3.0/openfoam-2312-dryq5snbojskkuaqjhsxhtxqxmbrijvx/src/OpenFOAM/lnInclude/ListOps.H:397:7: note: declared here
  397 | label findIndex
      |       ^~~~~~~~~
/home/SOFT/modules/installs/foam/solids4foam_v2.1/src/solids4FoamModels/lnInclude/solidSubMeshesTemplates.C:351:47: warning: 'Foam::label Foam::findIndex(const ListType&, typename ListType::const_reference, label) [with ListType = List<int>; label = int; typename ListType::const_reference = const int&]' is deprecated: Since 2017-10; use "UList find/found methods" [-Wdeprecated-declarations]
  351 |             const label curSpIndex = findIndex(spAddressing, k);
      |                                      ~~~~~~~~~^~~~~~~~~~~~~~~~~
/home/SOFT/modules/spack/installs/linux-ubuntu22.04-broadwell/gcc-13.3.0/openfoam-2312-dryq5snbojskkuaqjhsxhtxqxmbrijvx/src/OpenFOAM/lnInclude/ListOps.H:397:7: note: declared here
  397 | label findIndex
      |       ^~~~~~~~~
[ 74%] Building CXX object CMakeFiles/lspfoam.dir/src/solids4FoamModels/solidModels/laserIntenzitySolver/laserIntenzitySolver.C.o
In file included from /home/SOFT/modules/installs/foam/solids4foam_v2.1/src/solids4FoamModels/lnInclude/solidSubMeshes.H:394,
                 from /home/SOFT/modules/installs/foam/solids4foam_v2.1/src/solids4FoamModels/lnInclude/mechanicalModel.H:46,
                 from /home/SOFT/modules/installs/foam/solids4foam_v2.1/src/solids4FoamModels/lnInclude/solidModel.H:44,
                 from /home/prado/paper/Amarchinta_2010/AA_sof_pylsp/foam/src/solids4FoamModels/solidModels/laserIntenzitySolver/laserIntenzitySolver.H:4,
                 from /home/prado/paper/Amarchinta_2010/AA_sof_pylsp/foam/src/solids4FoamModels/solidModels/laserIntenzitySolver/laserIntenzitySolver.C:5:
/home/SOFT/modules/installs/foam/solids4foam_v2.1/src/solids4FoamModels/lnInclude/solidSubMeshesTemplates.C: In member function 'void Foam::solidSubMeshes::mapSubMeshPointFields(const Foam::PtrList<Foam::GeometricField<Type, Foam::pointPatchField, Foam::pointMesh> >&, Foam::GeometricField<Type, Foam::pointPatchField, Foam::pointMesh>&) const':
/home/SOFT/modules/installs/foam/solids4foam_v2.1/src/solids4FoamModels/lnInclude/solidSubMeshesTemplates.C:319:45: warning: 'Foam::label Foam::findIndex(const ListType&, typename ListType::const_reference, label) [with ListType = List<int>; label = int; typename ListType::const_reference = const int&]' is deprecated: Since 2017-10; use "UList find/found methods" [-Wdeprecated-declarations]
  319 |             const bool sharedPoint(findIndex(spLabels, curMeshPoint) != -1);
      |                                    ~~~~~~~~~^~~~~~~~~~~~~~~~~~~~~~~~
In file included from /home/SOFT/modules/spack/installs/linux-ubuntu22.04-broadwell/gcc-13.3.0/openfoam-2312-dryq5snbojskkuaqjhsxhtxqxmbrijvx/src/OpenFOAM/lnInclude/UPstream.H:49,
                 from /home/SOFT/modules/spack/installs/linux-ubuntu22.04-broadwell/gcc-13.3.0/openfoam-2312-dryq5snbojskkuaqjhsxhtxqxmbrijvx/src/OpenFOAM/lnInclude/fileOperation.H:78,
                 from /home/SOFT/modules/spack/installs/linux-ubuntu22.04-broadwell/gcc-13.3.0/openfoam-2312-dryq5snbojskkuaqjhsxhtxqxmbrijvx/src/OpenFOAM/lnInclude/IOobjectTemplates.C:31,
                 from /home/SOFT/modules/spack/installs/linux-ubuntu22.04-broadwell/gcc-13.3.0/openfoam-2312-dryq5snbojskkuaqjhsxhtxqxmbrijvx/src/OpenFOAM/lnInclude/IOobject.H:739,
                 from /home/SOFT/modules/spack/installs/linux-ubuntu22.04-broadwell/gcc-13.3.0/openfoam-2312-dryq5snbojskkuaqjhsxhtxqxmbrijvx/src/OpenFOAM/lnInclude/regIOobject.H:44,
                 from /home/SOFT/modules/spack/installs/linux-ubuntu22.04-broadwell/gcc-13.3.0/openfoam-2312-dryq5snbojskkuaqjhsxhtxqxmbrijvx/src/OpenFOAM/lnInclude/baseIOdictionary.H:46,
                 from /home/SOFT/modules/spack/installs/linux-ubuntu22.04-broadwell/gcc-13.3.0/openfoam-2312-dryq5snbojskkuaqjhsxhtxqxmbrijvx/src/OpenFOAM/lnInclude/IOdictionary.H:44,
                 from /home/SOFT/modules/installs/foam/solids4foam_v2.1/src/solids4FoamModels/lnInclude/physicsModel.H:38,
                 from /home/SOFT/modules/installs/foam/solids4foam_v2.1/src/solids4FoamModels/lnInclude/solidModel.H:37:
/home/SOFT/modules/spack/installs/linux-ubuntu22.04-broadwell/gcc-13.3.0/openfoam-2312-dryq5snbojskkuaqjhsxhtxqxmbrijvx/src/OpenFOAM/lnInclude/ListOps.H:397:7: note: declared here
  397 | label findIndex
      |       ^~~~~~~~~
/home/SOFT/modules/installs/foam/solids4foam_v2.1/src/solids4FoamModels/lnInclude/solidSubMeshesTemplates.C:323:42: warning: 'Foam::label Foam::findIndex(const ListType&, typename ListType::const_reference, label) [with ListType = List<int>; label = int; typename ListType::const_reference = const int&]' is deprecated: Since 2017-10; use "UList find/found methods" [-Wdeprecated-declarations]
  323 |                 const label k = findIndex(spLabels, curMeshPoint);
      |                                 ~~~~~~~~~^~~~~~~~~~~~~~~~~~~~~~~~
/home/SOFT/modules/spack/installs/linux-ubuntu22.04-broadwell/gcc-13.3.0/openfoam-2312-dryq5snbojskkuaqjhsxhtxqxmbrijvx/src/OpenFOAM/lnInclude/ListOps.H:397:7: note: declared here
  397 | label findIndex
      |       ^~~~~~~~~
/home/SOFT/modules/installs/foam/solids4foam_v2.1/src/solids4FoamModels/lnInclude/solidSubMeshesTemplates.C:351:47: warning: 'Foam::label Foam::findIndex(const ListType&, typename ListType::const_reference, label) [with ListType = List<int>; label = int; typename ListType::const_reference = const int&]' is deprecated: Since 2017-10; use "UList find/found methods" [-Wdeprecated-declarations]
  351 |             const label curSpIndex = findIndex(spAddressing, k);
      |                                      ~~~~~~~~~^~~~~~~~~~~~~~~~~
/home/SOFT/modules/spack/installs/linux-ubuntu22.04-broadwell/gcc-13.3.0/openfoam-2312-dryq5snbojskkuaqjhsxhtxqxmbrijvx/src/OpenFOAM/lnInclude/ListOps.H:397:7: note: declared here
  397 | label findIndex
      |       ^~~~~~~~~
[ 77%] Building CXX object CMakeFiles/lspfoam.dir/src/solids4FoamModels/solidModels/materialPoint/materialPoint.C.o
In file included from /home/SOFT/modules/installs/foam/solids4foam_v2.1/src/solids4FoamModels/lnInclude/solidSubMeshes.H:394,
                 from /home/SOFT/modules/installs/foam/solids4foam_v2.1/src/solids4FoamModels/lnInclude/mechanicalModel.H:46,
                 from /home/SOFT/modules/installs/foam/solids4foam_v2.1/src/solids4FoamModels/lnInclude/solidModel.H:44,
                 from /home/prado/paper/Amarchinta_2010/AA_sof_pylsp/foam/src/solids4FoamModels/solidModels/materialPoint/materialPoint.H:4,
                 from /home/prado/paper/Amarchinta_2010/AA_sof_pylsp/foam/src/solids4FoamModels/solidModels/materialPoint/materialPoint.C:1:
/home/SOFT/modules/installs/foam/solids4foam_v2.1/src/solids4FoamModels/lnInclude/solidSubMeshesTemplates.C: In member function 'void Foam::solidSubMeshes::mapSubMeshPointFields(const Foam::PtrList<Foam::GeometricField<Type, Foam::pointPatchField, Foam::pointMesh> >&, Foam::GeometricField<Type, Foam::pointPatchField, Foam::pointMesh>&) const':
/home/SOFT/modules/installs/foam/solids4foam_v2.1/src/solids4FoamModels/lnInclude/solidSubMeshesTemplates.C:319:45: warning: 'Foam::label Foam::findIndex(const ListType&, typename ListType::const_reference, label) [with ListType = List<int>; label = int; typename ListType::const_reference = const int&]' is deprecated: Since 2017-10; use "UList find/found methods" [-Wdeprecated-declarations]
  319 |             const bool sharedPoint(findIndex(spLabels, curMeshPoint) != -1);
      |                                    ~~~~~~~~~^~~~~~~~~~~~~~~~~~~~~~~~
In file included from /home/SOFT/modules/spack/installs/linux-ubuntu22.04-broadwell/gcc-13.3.0/openfoam-2312-dryq5snbojskkuaqjhsxhtxqxmbrijvx/src/OpenFOAM/lnInclude/UPstream.H:49,
                 from /home/SOFT/modules/spack/installs/linux-ubuntu22.04-broadwell/gcc-13.3.0/openfoam-2312-dryq5snbojskkuaqjhsxhtxqxmbrijvx/src/OpenFOAM/lnInclude/fileOperation.H:78,
                 from /home/SOFT/modules/spack/installs/linux-ubuntu22.04-broadwell/gcc-13.3.0/openfoam-2312-dryq5snbojskkuaqjhsxhtxqxmbrijvx/src/OpenFOAM/lnInclude/IOobjectTemplates.C:31,
                 from /home/SOFT/modules/spack/installs/linux-ubuntu22.04-broadwell/gcc-13.3.0/openfoam-2312-dryq5snbojskkuaqjhsxhtxqxmbrijvx/src/OpenFOAM/lnInclude/IOobject.H:739,
                 from /home/SOFT/modules/spack/installs/linux-ubuntu22.04-broadwell/gcc-13.3.0/openfoam-2312-dryq5snbojskkuaqjhsxhtxqxmbrijvx/src/OpenFOAM/lnInclude/regIOobject.H:44,
                 from /home/SOFT/modules/spack/installs/linux-ubuntu22.04-broadwell/gcc-13.3.0/openfoam-2312-dryq5snbojskkuaqjhsxhtxqxmbrijvx/src/OpenFOAM/lnInclude/baseIOdictionary.H:46,
                 from /home/SOFT/modules/spack/installs/linux-ubuntu22.04-broadwell/gcc-13.3.0/openfoam-2312-dryq5snbojskkuaqjhsxhtxqxmbrijvx/src/OpenFOAM/lnInclude/IOdictionary.H:44,
                 from /home/SOFT/modules/installs/foam/solids4foam_v2.1/src/solids4FoamModels/lnInclude/physicsModel.H:38,
                 from /home/SOFT/modules/installs/foam/solids4foam_v2.1/src/solids4FoamModels/lnInclude/solidModel.H:37:
/home/SOFT/modules/spack/installs/linux-ubuntu22.04-broadwell/gcc-13.3.0/openfoam-2312-dryq5snbojskkuaqjhsxhtxqxmbrijvx/src/OpenFOAM/lnInclude/ListOps.H:397:7: note: declared here
  397 | label findIndex
      |       ^~~~~~~~~
/home/SOFT/modules/installs/foam/solids4foam_v2.1/src/solids4FoamModels/lnInclude/solidSubMeshesTemplates.C:323:42: warning: 'Foam::label Foam::findIndex(const ListType&, typename ListType::const_reference, label) [with ListType = List<int>; label = int; typename ListType::const_reference = const int&]' is deprecated: Since 2017-10; use "UList find/found methods" [-Wdeprecated-declarations]
  323 |                 const label k = findIndex(spLabels, curMeshPoint);
      |                                 ~~~~~~~~~^~~~~~~~~~~~~~~~~~~~~~~~
/home/SOFT/modules/spack/installs/linux-ubuntu22.04-broadwell/gcc-13.3.0/openfoam-2312-dryq5snbojskkuaqjhsxhtxqxmbrijvx/src/OpenFOAM/lnInclude/ListOps.H:397:7: note: declared here
  397 | label findIndex
      |       ^~~~~~~~~
/home/SOFT/modules/installs/foam/solids4foam_v2.1/src/solids4FoamModels/lnInclude/solidSubMeshesTemplates.C:351:47: warning: 'Foam::label Foam::findIndex(const ListType&, typename ListType::const_reference, label) [with ListType = List<int>; label = int; typename ListType::const_reference = const int&]' is deprecated: Since 2017-10; use "UList find/found methods" [-Wdeprecated-declarations]
  351 |             const label curSpIndex = findIndex(spAddressing, k);
      |                                      ~~~~~~~~~^~~~~~~~~~~~~~~~~
/home/SOFT/modules/spack/installs/linux-ubuntu22.04-broadwell/gcc-13.3.0/openfoam-2312-dryq5snbojskkuaqjhsxhtxqxmbrijvx/src/OpenFOAM/lnInclude/ListOps.H:397:7: note: declared here
  397 | label findIndex
      |       ^~~~~~~~~
[ 81%] Building CXX object CMakeFiles/lspfoam.dir/src/solids4FoamModels/materialModels/mechanicalModel/linearGeometryLaws/myLinearElastic/myLinearElastic.C.o
[ 85%] Building CXX object CMakeFiles/lspfoam.dir/src/solids4FoamModels/materialModels/mechanicalModel/linearGeometryLaws/myLinearElasticMisesPlastic/myLinearElasticMisesPlastic.C.o
[ 88%] Building CXX object CMakeFiles/lspfoam.dir/src/solids4FoamModels/materialModels/mechanicalModel/linearGeometryLaws/linearElasticMisesPlasticJC/linearElasticMisesPlasticJC.C.o
In file included from /home/prado/paper/Amarchinta_2010/AA_sof_pylsp/foam/src/solids4FoamModels/materialModels/mechanicalModel/linearGeometryLaws/linearElasticMisesPlasticJC/linearElasticMisesPlasticJC.C:26:
/home/prado/paper/Amarchinta_2010/AA_sof_pylsp/foam/src/solids4FoamModels/materialModels/mechanicalModel/linearGeometryLaws/linearElasticMisesPlasticJC/linearElasticMisesPlasticJC.H: In constructor 'Foam::linearElasticMisesPlasticJC::linearElasticMisesPlasticJC(const Foam::word&, const Foam::fvMesh&, const Foam::dictionary&, const Foam::nonLinearGeometry::nonLinearType&)':
/home/prado/paper/Amarchinta_2010/AA_sof_pylsp/foam/src/solids4FoamModels/materialModels/mechanicalModel/linearGeometryLaws/linearElasticMisesPlasticJC/linearElasticMisesPlasticJC.H:95:27: warning: 'Foam::linearElasticMisesPlasticJC::nu_' will be initialized after [-Wreorder]
   95 |         dimensionedScalar nu_;
      |                           ^~~
/home/prado/paper/Amarchinta_2010/AA_sof_pylsp/foam/src/solids4FoamModels/materialModels/mechanicalModel/linearGeometryLaws/linearElasticMisesPlasticJC/linearElasticMisesPlasticJC.H:76:22: warning:   'const Foam::scalar Foam::linearElasticMisesPlasticJC::A_' [-Wreorder]
   76 |         const scalar A_;
      |                      ^~
/home/prado/paper/Amarchinta_2010/AA_sof_pylsp/foam/src/solids4FoamModels/materialModels/mechanicalModel/linearGeometryLaws/linearElasticMisesPlasticJC/linearElasticMisesPlasticJC.C:368:1: warning:   when initialized here [-Wreorder]
  368 | Foam::linearElasticMisesPlasticJC::linearElasticMisesPlasticJC
      | ^~~~
[ 92%] Building CXX object CMakeFiles/lspfoam.dir/src/solids4FoamModels/materialModels/mechanicalModel/linearGeometryLaws/linearElasticMisesPlasticLH/linearElasticMisesPlasticLH.C.o
In file included from /home/prado/paper/Amarchinta_2010/AA_sof_pylsp/foam/src/solids4FoamModels/materialModels/mechanicalModel/linearGeometryLaws/linearElasticMisesPlasticLH/linearElasticMisesPlasticLH.C:26:
/home/prado/paper/Amarchinta_2010/AA_sof_pylsp/foam/src/solids4FoamModels/materialModels/mechanicalModel/linearGeometryLaws/linearElasticMisesPlasticLH/linearElasticMisesPlasticLH.H: In constructor 'Foam::linearElasticMisesPlasticLH::linearElasticMisesPlasticLH(const Foam::word&, const Foam::fvMesh&, const Foam::dictionary&, const Foam::nonLinearGeometry::nonLinearType&)':
/home/prado/paper/Amarchinta_2010/AA_sof_pylsp/foam/src/solids4FoamModels/materialModels/mechanicalModel/linearGeometryLaws/linearElasticMisesPlasticLH/linearElasticMisesPlasticLH.H:98:27: warning: 'Foam::linearElasticMisesPlasticLH::nu_' will be initialized after [-Wreorder]
   98 |         dimensionedScalar nu_;
      |                           ^~~
/home/prado/paper/Amarchinta_2010/AA_sof_pylsp/foam/src/solids4FoamModels/materialModels/mechanicalModel/linearGeometryLaws/linearElasticMisesPlasticLH/linearElasticMisesPlasticLH.H:76:22: warning:   'const Foam::scalar Foam::linearElasticMisesPlasticLH::K0_' [-Wreorder]
   76 |         const scalar K0_;
      |                      ^~~
/home/prado/paper/Amarchinta_2010/AA_sof_pylsp/foam/src/solids4FoamModels/materialModels/mechanicalModel/linearGeometryLaws/linearElasticMisesPlasticLH/linearElasticMisesPlasticLH.C:381:1: warning:   when initialized here [-Wreorder]
  381 | Foam::linearElasticMisesPlasticLH::linearElasticMisesPlasticLH
      | ^~~~
/home/prado/paper/Amarchinta_2010/AA_sof_pylsp/foam/src/solids4FoamModels/materialModels/mechanicalModel/linearGeometryLaws/linearElasticMisesPlasticLH/linearElasticMisesPlasticLH.H:82:22: warning: 'Foam::linearElasticMisesPlasticLH::p_' will be initialized after [-Wreorder]
   82 |         const scalar p_;
      |                      ^~
/home/prado/paper/Amarchinta_2010/AA_sof_pylsp/foam/src/solids4FoamModels/materialModels/mechanicalModel/linearGeometryLaws/linearElasticMisesPlasticLH/linearElasticMisesPlasticLH.H:78:22: warning:   'const Foam::scalar Foam::linearElasticMisesPlasticLH::n_' [-Wreorder]
   78 |         const scalar n_;
      |                      ^~
/home/prado/paper/Amarchinta_2010/AA_sof_pylsp/foam/src/solids4FoamModels/materialModels/mechanicalModel/linearGeometryLaws/linearElasticMisesPlasticLH/linearElasticMisesPlasticLH.C:381:1: warning:   when initialized here [-Wreorder]
  381 | Foam::linearElasticMisesPlasticLH::linearElasticMisesPlasticLH
      | ^~~~
/home/prado/paper/Amarchinta_2010/AA_sof_pylsp/foam/src/solids4FoamModels/materialModels/mechanicalModel/linearGeometryLaws/linearElasticMisesPlasticLH/linearElasticMisesPlasticLH.H:78:22: warning: 'Foam::linearElasticMisesPlasticLH::n_' will be initialized after [-Wreorder]
   78 |         const scalar n_;
      |                      ^~
/home/prado/paper/Amarchinta_2010/AA_sof_pylsp/foam/src/solids4FoamModels/materialModels/mechanicalModel/linearGeometryLaws/linearElasticMisesPlasticLH/linearElasticMisesPlasticLH.H:77:22: warning:   'const Foam::scalar Foam::linearElasticMisesPlasticLH::eps0_' [-Wreorder]
   77 |         const scalar eps0_;
      |                      ^~~~~
/home/prado/paper/Amarchinta_2010/AA_sof_pylsp/foam/src/solids4FoamModels/materialModels/mechanicalModel/linearGeometryLaws/linearElasticMisesPlasticLH/linearElasticMisesPlasticLH.C:381:1: warning:   when initialized here [-Wreorder]
  381 | Foam::linearElasticMisesPlasticLH::linearElasticMisesPlasticLH
      | ^~~~
[ 96%] Building CXX object CMakeFiles/lspfoam.dir/src/solids4FoamModels/solidModels/fvPatchFields/laserProcessingPressure/laserProcessingPressureFvPatchVectorField.C.o
In file included from /home/SOFT/modules/installs/foam/solids4foam_v2.1/src/solids4FoamModels/lnInclude/solidSubMeshes.H:394,
                 from /home/SOFT/modules/installs/foam/solids4foam_v2.1/src/solids4FoamModels/lnInclude/mechanicalModel.H:46,
                 from /home/SOFT/modules/installs/foam/solids4foam_v2.1/src/solids4FoamModels/lnInclude/solidModel.H:44,
                 from /home/SOFT/modules/installs/foam/solids4foam_v2.1/src/solids4FoamModels/lnInclude/lookupSolidModel.H:39,
                 from /home/prado/paper/Amarchinta_2010/AA_sof_pylsp/foam/src/solids4FoamModels/solidModels/fvPatchFields/laserProcessingPressure/laserProcessingPressureFvPatchVectorField.C:30:
/home/SOFT/modules/installs/foam/solids4foam_v2.1/src/solids4FoamModels/lnInclude/solidSubMeshesTemplates.C: In member function 'void Foam::solidSubMeshes::mapSubMeshPointFields(const Foam::PtrList<Foam::GeometricField<Type, Foam::pointPatchField, Foam::pointMesh> >&, Foam::GeometricField<Type, Foam::pointPatchField, Foam::pointMesh>&) const':
/home/SOFT/modules/installs/foam/solids4foam_v2.1/src/solids4FoamModels/lnInclude/solidSubMeshesTemplates.C:319:45: warning: 'Foam::label Foam::findIndex(const ListType&, typename ListType::const_reference, label) [with ListType = List<int>; label = int; typename ListType::const_reference = const int&]' is deprecated: Since 2017-10; use "UList find/found methods" [-Wdeprecated-declarations]
  319 |             const bool sharedPoint(findIndex(spLabels, curMeshPoint) != -1);
      |                                    ~~~~~~~~~^~~~~~~~~~~~~~~~~~~~~~~~
In file included from /home/SOFT/modules/spack/installs/linux-ubuntu22.04-broadwell/gcc-13.3.0/openfoam-2312-dryq5snbojskkuaqjhsxhtxqxmbrijvx/src/OpenFOAM/lnInclude/UPstream.H:49,
                 from /home/SOFT/modules/spack/installs/linux-ubuntu22.04-broadwell/gcc-13.3.0/openfoam-2312-dryq5snbojskkuaqjhsxhtxqxmbrijvx/src/OpenFOAM/lnInclude/FieldFunctions.H:31,
                 from /home/SOFT/modules/spack/installs/linux-ubuntu22.04-broadwell/gcc-13.3.0/openfoam-2312-dryq5snbojskkuaqjhsxhtxqxmbrijvx/src/OpenFOAM/lnInclude/Field.H:544,
                 from /home/SOFT/modules/spack/installs/linux-ubuntu22.04-broadwell/gcc-13.3.0/openfoam-2312-dryq5snbojskkuaqjhsxhtxqxmbrijvx/src/OpenFOAM/lnInclude/boolField.H:41,
                 from /home/SOFT/modules/spack/installs/linux-ubuntu22.04-broadwell/gcc-13.3.0/openfoam-2312-dryq5snbojskkuaqjhsxhtxqxmbrijvx/src/OpenFOAM/lnInclude/primitiveFields.H:40,
                 from /home/SOFT/modules/spack/installs/linux-ubuntu22.04-broadwell/gcc-13.3.0/openfoam-2312-dryq5snbojskkuaqjhsxhtxqxmbrijvx/src/OpenFOAM/lnInclude/pointField.H:38,
                 from /home/SOFT/modules/spack/installs/linux-ubuntu22.04-broadwell/gcc-13.3.0/openfoam-2312-dryq5snbojskkuaqjhsxhtxqxmbrijvx/src/OpenFOAM/lnInclude/edge.H:53,
                 from /home/SOFT/modules/spack/installs/linux-ubuntu22.04-broadwell/gcc-13.3.0/openfoam-2312-dryq5snbojskkuaqjhsxhtxqxmbrijvx/src/OpenFOAM/lnInclude/edgeList.H:31,
                 from /home/SOFT/modules/spack/installs/linux-ubuntu22.04-broadwell/gcc-13.3.0/openfoam-2312-dryq5snbojskkuaqjhsxhtxqxmbrijvx/src/OpenFOAM/lnInclude/PrimitivePatch.H:59,
                 from /home/SOFT/modules/spack/installs/linux-ubuntu22.04-broadwell/gcc-13.3.0/openfoam-2312-dryq5snbojskkuaqjhsxhtxqxmbrijvx/src/OpenFOAM/lnInclude/primitivePatch.H:50,
                 from /home/SOFT/modules/spack/installs/linux-ubuntu22.04-broadwell/gcc-13.3.0/openfoam-2312-dryq5snbojskkuaqjhsxhtxqxmbrijvx/src/OpenFOAM/lnInclude/polyPatch.H:46,
                 from /home/SOFT/modules/spack/installs/linux-ubuntu22.04-broadwell/gcc-13.3.0/openfoam-2312-dryq5snbojskkuaqjhsxhtxqxmbrijvx/src/finiteVolume/lnInclude/fvPatch.H:44,
                 from /home/SOFT/modules/spack/installs/linux-ubuntu22.04-broadwell/gcc-13.3.0/openfoam-2312-dryq5snbojskkuaqjhsxhtxqxmbrijvx/src/finiteVolume/lnInclude/fvPatchField.H:51,
                 from /home/SOFT/modules/spack/installs/linux-ubuntu22.04-broadwell/gcc-13.3.0/openfoam-2312-dryq5snbojskkuaqjhsxhtxqxmbrijvx/src/finiteVolume/lnInclude/fvPatchFields.H:31,
                 from /home/prado/paper/Amarchinta_2010/AA_sof_pylsp/foam/src/solids4FoamModels/solidModels/fvPatchFields/laserProcessingPressure/laserProcessingPressureFvPatchVectorField.H:46,
                 from /home/prado/paper/Amarchinta_2010/AA_sof_pylsp/foam/src/solids4FoamModels/solidModels/fvPatchFields/laserProcessingPressure/laserProcessingPressureFvPatchVectorField.C:27:
/home/SOFT/modules/spack/installs/linux-ubuntu22.04-broadwell/gcc-13.3.0/openfoam-2312-dryq5snbojskkuaqjhsxhtxqxmbrijvx/src/OpenFOAM/lnInclude/ListOps.H:397:7: note: declared here
  397 | label findIndex
      |       ^~~~~~~~~
/home/SOFT/modules/installs/foam/solids4foam_v2.1/src/solids4FoamModels/lnInclude/solidSubMeshesTemplates.C:323:42: warning: 'Foam::label Foam::findIndex(const ListType&, typename ListType::const_reference, label) [with ListType = List<int>; label = int; typename ListType::const_reference = const int&]' is deprecated: Since 2017-10; use "UList find/found methods" [-Wdeprecated-declarations]
  323 |                 const label k = findIndex(spLabels, curMeshPoint);
      |                                 ~~~~~~~~~^~~~~~~~~~~~~~~~~~~~~~~~
/home/SOFT/modules/spack/installs/linux-ubuntu22.04-broadwell/gcc-13.3.0/openfoam-2312-dryq5snbojskkuaqjhsxhtxqxmbrijvx/src/OpenFOAM/lnInclude/ListOps.H:397:7: note: declared here
  397 | label findIndex
      |       ^~~~~~~~~
/home/SOFT/modules/installs/foam/solids4foam_v2.1/src/solids4FoamModels/lnInclude/solidSubMeshesTemplates.C:351:47: warning: 'Foam::label Foam::findIndex(const ListType&, typename ListType::const_reference, label) [with ListType = List<int>; label = int; typename ListType::const_reference = const int&]' is deprecated: Since 2017-10; use "UList find/found methods" [-Wdeprecated-declarations]
  351 |             const label curSpIndex = findIndex(spAddressing, k);
      |                                      ~~~~~~~~~^~~~~~~~~~~~~~~~~
/home/SOFT/modules/spack/installs/linux-ubuntu22.04-broadwell/gcc-13.3.0/openfoam-2312-dryq5snbojskkuaqjhsxhtxqxmbrijvx/src/OpenFOAM/lnInclude/ListOps.H:397:7: note: declared here
  397 | label findIndex
      |       ^~~~~~~~~
[100%] Linking CXX executable lspfoam
[100%] Built target lspfoam
