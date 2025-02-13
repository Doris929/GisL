/*!
 * @author tau 
 * @date 12/20/20
*/

#include "vectorlayer.h"

#include <ogrsf_frmts.h>
#include <QObject>

#include "../utils/ptroperate.h"
#include "vectorfeature.h"

namespace GisL {

    int VectorLayer::fidInLayer = 100;

    void VectorLayer::seed( const int fidInVector ) {
        VectorLayer::fidInLayer = fidInVector * 100;
    }

    VectorLayer::VectorLayer( OGRLayer &poLayer ) {
        log = Log::getLog();
        fid = ++VectorLayer::fidInLayer;
        pmLayer = &poLayer;
        if ( nullptr == pmLayer->GetSpatialRef()) {
            pmCrs = nullptr;
//            mError = MError::GisLError::ErrSpatialRef;
            log->append( QObject::tr( "Warning: No spatial reference in this layer!\n" ));
        } else {
            pmCrs = new SpatialReference( *pmLayer->GetSpatialRef());
        }

        pmLayerPropertyTable = new LayerPropertyTable( fid );

        pmExtent = nullptr;
        initEnvelope();

        VectorFeature::seed( fid );
        featureCount = pmLayer->GetFeatureCount();
        pmLayerPropertyTable->getFeatureCount( featureCount );
        pmFeature = new VectorFeature *[featureCount];
        for ( int i = featureCount - 1; i >= 0; --i ) {
            pmFeature[i] = new VectorFeature( *pmLayer->GetFeature( i ));
            pmLayerPropertyTable->append( pmFeature[i]->getFid(), *pmFeature[i]->getPmFeatureProperty());
        }
    }

    void VectorLayer::initEnvelope( ) {
        OGREnvelope temp;
        OGRErr ddss = pmLayer->GetExtent( &temp );
//        pmLayer->GetExtent(pmExtent);
        pmExtent = new OGREnvelope( temp );
        if ( nullptr == pmExtent ) {
//            mError = MError::ErrExtent;
            log->append( QObject::tr( "Warning: can not fetch the extent of this layer!\n" ));
        }
    }

    VectorLayer &VectorLayer::operator=( const VectorLayer &rhs ) {
        return *this;
    }

    int VectorLayer::getFeatureCount( ) const {
        return featureCount;
    }

    VectorLayer::~VectorLayer( ) {
        PtrOperate::clear( pmExtent );
        PtrOperate::clear( pmFeature, featureCount );
        PtrOperate::clear( pmCrs );
        PtrOperate::clear( pmLayerPropertyTable );

    }

    void VectorLayer::draw( PainterFactory &p ) {
        for ( int i = 0; i < featureCount; ++i ) {
            pmFeature[i]->draw( p );
        }
    }

    Rectangle *VectorLayer::getEnvelope( ) const {
        return new Rectangle( *pmExtent );
    }

    OGRLayer *VectorLayer::getOgrLayer( ) const {
        return pmLayer;
    }

    VectorFeature **VectorLayer::getFeature( ) const {
        return pmFeature;
    }

}
