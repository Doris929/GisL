//
// Created by omega on 14/12/2020.
//

#include "spatialreference.h"

#include <string>
#include <ogr_spatialref.h>
#include <cpl_conv.h>

namespace GisL {
    SpatialReference::SpatialReference( OGRSpatialReference &poSRS ) {
        pmCRS = &poSRS;
    }

    void SpatialReference::toWKT( std::string &outWkt ) {
        char *rst;
        pmCRS->exportToWkt( &rst );
        outWkt.append( rst );
    }

    SpatialReference::~SpatialReference( ) = default;
}