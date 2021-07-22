//
//  VTKGeoMesh.h
//  FemSC
//
//  Created by Philippe Devloo on 17/04/18.
//

#ifndef VTKGeoMesh_h
#define VTKGeoMesh_h
///\cond
#include <string>
///\endcond
#include "DataTypes.h"

class GeoMesh;
class CompMesh;
class PostProcess;

/**
 @brief Output a .vtk file for a geometric mesh, computational mesh or PostProcess object
 @ingroup global
 */
class VTKGeoMesh
{
    public:
    /** @brief Generate an output of all geomesh to VTK */
    static void PrintGMeshVTK(GeoMesh *gmesh, const std::string &filename);

    /// Generate an output file for the solution and its gradient
    static void PrintCMeshVTK(CompMesh *cmesh, int dim, const std::string &filename);
    
    /// Generate an output file for the solution and its gradient
    static void PrintSolVTK(CompMesh *cmesh, PostProcess &defPostProc, const std::string &filename, bool AllDim = false);
    
};

#endif /* VTKGeoMesh_h */
