/*!
 * @author tau 
 * @date 12/30/20
*/

#include "openvectorcommand.h"

#include <QFileDialog>
#include <QFile>
#include <QObject>
#include <QMessageBox>

#include "../../ui/ui_mainwindow.h"
#include "../painter/glpainterfactory.h"
#include "../../core/layertree.h"
#include "../../utils/ptroperate.h"
#include "../../utils/log.h"
#include "../../core/vectorprovider.h"

void GisL::OpenVectorCommand::execute( QWidget *parent ) {

//    auto openFileName = QString( "../resource/mydata/hubei_hospital_voronoi_extract.shp" );
//    auto openFileName = QString( "../resource/practise_6/qu.geojson" );
    QString openFileName = QFileDialog::getOpenFileName(
            parent,
            QObject::tr( "open an vector file." ),
            "../",
            QObject::tr( "GeoJSON(*.geojson);;ESRI Shapefile(*.shp);;All files(*.*)" ),
            nullptr,
            QFileDialog::DontUseNativeDialog );
    if ( openFileName.isEmpty()) {
        QMessageBox::warning( parent, QObject::tr( "VectorProvider Warning!" ),
                              QObject::tr( "Cancel to open the file!" ));
    } else {
        vectorName = openFileName.toStdString();
        pVector = new GisL::VectorProvider( vectorName );
        if ( pVector->hasError()) {
            Log *log = Log::getLog();
            QMessageBox::warning( parent, QObject::tr( "VectorProvider Warning!" ), log->getLast());
            return;
        }
        LayerTree *layerTree = LayerTree::getLayerTree();
        VectorLayer *layer = layerTree->getLayer( "qu" );

        ui->openGLWidget->getLayerName( "qu" );
        ui->openGLWidget->getEnvelope( *layer->getEnvelope());

//    qDebug((openFileName.split(".")[0] + "-style.sld"));
        QFileInfo info1( openFileName );
//    QFileInfo::exists(info1.absolutePath() + info1.baseName() + "-style.sld");
//    QString q = openFileName.split(".")[0] + "-style.sld";
//    qDebug("%s", q.toStdString().c_str());
//    qDebug("%s", (info1.absolutePath() + info1.baseName() + "-style.sld").toStdString().c_str());
        if ( QFileInfo::exists( info1.absolutePath() + "/" + info1.baseName() + "-style.sld" )) {
            ui->openGLWidget->setSld(
                    new Sld(( info1.absolutePath() + "/" + info1.baseName() + "-style.sld" ).toStdString()));
        } else {
            ui->openGLWidget->setRandSld();
        }
        ui->openGLWidget->getLayer( *layer );
        layer->draw( *ui->openGLWidget );
    }

}

void GisL::OpenVectorCommand::getUi( Ui_MainWindow &p ) {
    ui = &p;
}

void GisL::OpenVectorCommand::reverse( ) {
    //todo dont draw vector

    PtrOperate::clear( pVector );
    vectorName = nullptr;
}

const std::string &GisL::OpenVectorCommand::output( ) {
    return vectorName;
}

GisL::OpenVectorCommand::~OpenVectorCommand( ) {
    PtrOperate::clear( pVector );
}
