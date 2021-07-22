//
//  ReadGmsh.h
//  FemSC
//
//  Created by Philippe Devloo on 17/04/18.
//

#ifndef ReadGmsh_h
#define ReadGmsh_h

///\cond
#include <string>
#include <vector>
#include <map>
///\endcond
#include "GeoMesh.h"

/**
@brief Read the definition of a geometry from a Gmsh file
@ingroup geometry
*/
class ReadGmsh
{
    
public:

    // Constructor of ReadGmsh
    ReadGmsh() : fMaterialDataVec(4)
    {
        
    }
    /** @brief Reads geometric mesh file from GMsh (.msh)
     * @param gmesh [output] Reference to a geometric mesh to be filled with elements from msh file
     * @param file_name Relative path to the .msh file you want to read
    */
    void Read(GeoMesh& gmesh, const std::string& file_name);
    
    
private:
    /** @brief Reads geometric mesh file from GMsh (.msh version 3)
     * @param gmesh [output] Reference to a geometric mesh to be filled with elements from msh file
     * @param file_name Relative path to the .msh file you want to read
    */
    void Read3(GeoMesh &gmesh, const std::string &file_name);


    /** @brief Reads geometric mesh file from GMsh (.msh version 4.1)
     * @param gmesh [output] Reference to a geometric mesh to be filled with elements from msh file
     * @param file_name Relative path to the .msh file you want to read
    */
    void Read4(GeoMesh &gmesh, const std::string &file_name);
protected:
    
    /** @brief MaterialVec */
    /** Structure of both, physical entities dimension and names */
    std::vector<std::map<int,std::string> > fMaterialDataVec;

};
#endif /* ReadGmsh_h */
