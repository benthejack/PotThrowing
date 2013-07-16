#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"

#include "TubeGenerator.h"
#include "GeometryRenderer.h"
#include "LayerManager.h"

using namespace ci;
using namespace ci::app;
using namespace std;

using namespace EyeCandy::GeomUtils;
using namespace EyeCandy::GfxUtils;

class PotThrowingApp : public AppBasic {
  public:
	void setup();
	void mouseDown( MouseEvent event );
	void mouseUp( MouseEvent event );

	void update();
	void draw();
    
private:
    GeometryGenerator_ptr tube;
    LayerManager_ptr layers;
    GeomRenderer_ptr rend;
    float rotation;
    bool mousePressed;
};

void PotThrowingApp::setup()
{
    mousePressed = false;
 
    rotation = 0;
    layers = LayerManager_ptr(new LayerManager(getWindowWidth(), getWindowHeight()));
    
    Layer_ptr tubeLayer = layers->pushLayer();
    
    tube = GeometryGenerator_ptr(new TubeGenerator(200,150,50, Vec3i(40,50,2)));
    tube->generate();
    
    rend = GeomRenderer_ptr(new GeometryRenderer(tube));
    rend->setPosition(Vec3f(getWindowWidth()/2, getWindowHeight()/2, 0));
   rend->renderWireFrame();
    
    tubeLayer->addRenderable(rend);
}

void PotThrowingApp::mouseDown( MouseEvent event )
{
    mousePressed = true;
}

void PotThrowingApp::mouseUp( MouseEvent event )
{
    mousePressed = false;
}

void PotThrowingApp::update()
{
    
    if(mousePressed){
        rotation += 0.01;
    }
}

void PotThrowingApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) );
    
    ci::Quaternion<float> rot(ci::Vec3f(0,1,0), rotation);
    rend->setRotation(rot);
    layers->render();
}

CINDER_APP_BASIC( PotThrowingApp, RendererGl )
