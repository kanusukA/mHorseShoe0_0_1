#include "wxOgre.h"



// Required for the timer
const long ID_RENDERTIMER = wxNewId();

// Required for WX
IMPLEMENT_CLASS(wxOgre, wxControl)

// Required for WX
BEGIN_EVENT_TABLE(wxOgre, wxControl)
EVT_SIZE(wxOgre::OnSize)
// EVT_PAINT(wxOgre::OnPaint) // Produces flickers and runs too fast!
EVT_ERASE_BACKGROUND(wxOgre::OnEraseBackground)
EVT_TIMER(ID_RENDERTIMER, wxOgre::OnRenderTimer)
END_EVENT_TABLE()

wxOgre::wxOgre(wxFrame* parent) :
    wxControl(parent, -1),
    mTimer(this, ID_RENDERTIMER),
    mRoot(0),
    mViewPort(0),
    mCamera(0),
    mSceneMgr(0),
    mRenderWindow(0)
{
    // Create all Ogre objects
    createOgreRenderWindow();
    // Start the rendering timer
    toggleTimerRendering();
}

void wxOgre::createOgreRenderWindow()
{
    // Create a new Ogre ROOT
    mRoot = new Ogre::Root();
    Ogre::Root::getSingleton().restoreConfig();
    mRenderWindow = Ogre::Root::getSingleton().initialise(false);

    // --------------------
    // Create a new parameters list according to compiled OS
    Ogre::NameValuePairList params;
    Ogre::String handle;

    handle = Ogre::StringConverter::toString((size_t)((HWND)GetHandle()));

    params["externalWindowHandle"] = handle;

    // Get wx control window size
    int width;
    int height;
    GetSize(&width, &height);
    // Create the render window
    mRenderWindow = Ogre::Root::getSingleton().createRenderWindow("OgreRenderWindow", width, height, false, &params);

    // --------------------
    // Create the SceneManager, in this case a generic one
    mSceneMgr = mRoot->createSceneManager(Ogre::ST_GENERIC, "ExampleSMInstance");

    // --------------------
    // Create the camera
    mCamera = mSceneMgr->createCamera("PlayerCam");
    // Position it at 500 in Z direction
    mCamera->setPosition(Ogre::Vector3(0, 0, 500));
    // Look back along -Z
    mCamera->lookAt(Ogre::Vector3(0, 0, -300));
    mCamera->setNearClipDistance(5);
    // Set the viewport
    mViewPort = mRenderWindow->addViewport(mCamera);
    mViewPort->setBackgroundColour(Ogre::ColourValue(1.0f, 0.0f, 0.0f, 1.0f));
}

void wxOgre::toggleTimerRendering()
{
    // Toggle Start/Stop
    if (mTimer.IsRunning())
        mTimer.Stop();
    mTimer.Start(10);
}

wxOgre::~wxOgre()
{
    // destroy Viewport and RenderWindow
    if (mViewPort)
    {
        mRenderWindow->removeViewport(mViewPort->getZOrder());
        mViewPort = 0;
    }

    Ogre::Root::getSingleton().detachRenderTarget(mRenderWindow);
    mRenderWindow = 0;
}

void wxOgre::OnSize(wxSizeEvent& event)
{
    // Setting new size;
    int width;
    int height;
    GetSize(&width, &height);
    mRenderWindow->resize(width, height);
    // Letting Ogre know the window has been resized;
    mRenderWindow->windowMovedOrResized();
    // Set the aspect ratio for the new size;
    if (mCamera)
        mCamera->setAspectRatio(Ogre::Real(width) / Ogre::Real(height));

    update();
}
void wxOgre::OnPaint(wxPaintEvent& event)
{
    //    update(); // Produces flickers and runs too fast!
}
void wxOgre::OnEraseBackground(wxEraseEvent&)
{
    update();
}
void wxOgre::OnRenderTimer(wxTimerEvent& event)
{
    update();
}

void wxOgre::update()
{
    // ****************************************************
    // TODO: REMOVE THESE LINES! These are merely for test!
    static float redTone = 0;
    redTone += 0.01;
    if (redTone > 1.0)
        redTone = 0;
    // ****************************************************

    mViewPort->setBackgroundColour(Ogre::ColourValue(redTone, 0.0f, 0.0f, 1.0f));
    Ogre::Root::getSingletonPtr()->renderOneFrame();
}

template<> wxOgre* Ogre::Singleton<wxOgre>::ms_Singleton = 0;
wxOgre& wxOgre::getSingleton()
{
    return (*ms_Singleton);
}

wxOgre* wxOgre::getSingletonPtr()
{
    return ms_Singleton;
}
