#include "fub_modelcar_tools/fub_modelcar_tools.h"
namespace fub_modelcar_tools {


    
    // void saveXML(CameraCalibrationData & myPair, const char *fileName)
    // {
    //     // make an archive, put myPair in an XML file fileName
    //     std::ofstream ofs(fileName);
    //     assert(ofs.good());
    //     boost::archive::xml_oarchive oa(ofs);
    //     oa << BOOST_SERIALIZATION_NVP(myPair);

    //     //text file
    //     //boost::archive::text_oarchive oa(ofs);
    //     // oa << myPair[i];
    // }
    // void restoreXML(CameraCalibrationData & myPair, const char *fileName)
    // {
    //     // open the fileName-archive and restore the map from the archive and put in myMap
    //     std::ifstream ifs(fileName);
    //     if (ifs.fail())
    //     {
    //         ROS_ERROR_STREAM("file " <<fileName << " opening failed");
    //     }
    //     else
    //     {
    //         assert(ifs.good());
    //         boost::archive::xml_iarchive ia(ifs);
    //         ia >> BOOST_SERIALIZATION_NVP(myPair);
    //     }
    // }

}
