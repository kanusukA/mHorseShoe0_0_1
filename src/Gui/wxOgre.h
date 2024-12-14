#pragma once

#ifndef __WXOGRE_H__
#define __WXOGRE_H__


#include <wx/wx.h>
#include <wx/timer.h>
#include <Ogre.h>




class wxOgre : public wxApp , public Ogre::Singleton<wxOgre>
{
public:
    /** A new wxOgre must receive a parent frame to which to attach
    itself to */
    wxOgre(wxFrame* parent);
    ~wxOgre();

    /** Renders a single Ogre frame */
    void update();

    /** Returns the currently used camera */
    inline Ogre::Camera* getCamera() { return mCamera; }
    /** Sets a new camera for rendering */
    inline void setCamera(Ogre::Camera* camera) { mCamera = camera; }

protected:
    DECLARE_EVENT_TABLE()

private:
    /** Creates an ogre rendering window and all other default objects
    such as the Ogre Root, default camera, default scene manager etc */
    void createOgreRenderWindow();
    /** Toggles the rendering timer on/off */
    void toggleTimerRendering();

    /** Callback function to a window resize event */
    void OnSize(wxSizeEvent& event);
    /** Callback function to a window paint event */
    void OnPaint(wxPaintEvent& event);
    /** Callback function to an EraseBackground event */
    void OnEraseBackground(wxEraseEvent&);
    /** Callback function to a timer "tick" event */
    void OnRenderTimer(wxTimerEvent& event);

    /* WX members */
    /** Rendering timer */
    wxTimer    mTimer;

    /* Ogre members */
    /** Local Ogre::Root pointer */
    Ogre::Root* mRoot;
    /** Local Ogre::Viewport pointer */
    Ogre::Viewport* mViewPort;
    /** Local Ogre::Camera pointer */
    Ogre::Camera* mCamera;
    /** Local Ogre::SceneManager pointer */
    Ogre::SceneManager* mSceneMgr;
    /** Local Ogre::RenderWindow pointer */
    Ogre::RenderWindow* mRenderWindow;

public:
    // *****************************************************

    // -----------------------------------------------------
    /**
    @remarks
    Why do we do this? Well, it's because the Singleton
    implementation is in a .h file, which means it gets compiled
    into anybody who includes it. This is needed for the
    Singleton template to work, but we actually only want it
    compiled into the implementation of the class based on the
    Singleton, not all of them. If we don't change this, we get
    link errors when trying to use the Singleton-based class from
    an outside dll.
    @par
    This method just delegates to the template version anyway,
    but the implementation stays in this single compilation unit,
    preventing link errors.
    */
    static wxOgre& getSingleton();
    /**
    @remarks
    Why do we do this? Well, it's because the Singleton
    implementation is in a .h file, which means it gets compiled
    into anybody who includes it. This is needed for the
    Singleton template to work, but we actually only want it
    compiled into the implementation of the class based on the
    Singleton, not all of them. If we don't change this, we get
    link errors when trying to use the Singleton-based class from
    an outside dll.
    @par
    This method just delegates to the template version anyway,
    but the implementation stays in this single compilation unit,
    preventing link errors.
    */
    static wxOgre* getSingletonPtr();


};

#endif // __WXOGRE_H__