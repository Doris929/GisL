/*!
 * @author tau 
 * @date 12/28/20
*/

#include <random>

#include "polygonsymbolizer.h"

namespace GisL {

    void PolygonSymbolizer::rand( ) {
        std::default_random_engine e(( unsigned ) time( nullptr ));
        std::uniform_int_distribution<> u( 0, 255 );
        polygonFill = true;
        polygonFillColor = QColor( u( e ), u( e ), u( e ));
        polygonStroke = true;
        polygonStrokeColor = QColor( u( e ), u( e ), u( e ));
        polygonStrokeWidth = 1.0;
        polygonStrokeLinejoin = "bevel";
    }

    void PolygonSymbolizer::init( QXmlStreamReader &sldStream ) {
        sldStream.readNextStartElement();
        polygonFill = true;
        sldStream.readNextStartElement();
        polygonFillColor.setNamedColor( sldStream.readElementText());

        sldStream.readNext();
        sldStream.readNext();
        sldStream.readNext();
        sldStream.readNext();
        polygonStroke = true;
        sldStream.readNextStartElement();
        polygonStrokeColor.setNamedColor( sldStream.readElementText());
        sldStream.readNextStartElement();
        polygonStrokeWidth = sldStream.readElementText().toFloat();
        sldStream.readNextStartElement();
        polygonStrokeLinejoin = sldStream.readElementText().toStdString();
    }
}
