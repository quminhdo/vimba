/*=============================================================================
  Copyright (C) 2012 - 2016 Allied Vision Technologies.  All Rights Reserved.

  Redistribution of this file, in original or modified form, without
  prior written consent of Allied Vision Technologies is prohibited.

-------------------------------------------------------------------------------

  File:        CameraFactory.h

  Description: The CameraFactory example will create a suitable object for
               each known interface. The user can create his own factory and 
               camera classes for customization.

-------------------------------------------------------------------------------

  THIS SOFTWARE IS PROVIDED BY THE AUTHOR "AS IS" AND ANY EXPRESS OR IMPLIED
  WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF TITLE,
  NON-INFRINGEMENT, MERCHANTABILITY AND FITNESS FOR A PARTICULAR  PURPOSE ARE
  DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT,
  INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
  AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR
  TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

=============================================================================*/

#ifndef AVT_VMBAPI_EXAMPLES_CAMERAFACTORY
#define AVT_VMBAPI_EXAMPLES_CAMERAFACTORY

#include "VimbaCPP/Include/VimbaCPP.h"

namespace AVT {
namespace VmbAPI {
namespace Examples {

class UserCameraFactory;
class FirewireCamera;
class GigECamera;
class USBCamera;
class CLCamera;

typedef SP_DECL( UserCameraFactory )    UserCameraFactory_t;
typedef SP_DECL( FirewireCamera )       FirewireCamera_t;
typedef SP_DECL( GigECamera )           GigECamera_t;
typedef SP_DECL( USBCamera )            USBCamera_t;
typedef SP_DECL( CLCamera )             CLCamera_t;
typedef SP_DECL( Camera )               Camera_t;

//
// A class that derives from standard Vimba Camera with a function specific to fire wire
//
class FirewireCamera: 
    public Camera
{
public:
    FirewireCamera(     const char         *pCameraID,
                        const char         *pCameraName,
                        const char         *pCameraModel,
                        const char         *pCameraSerialNumber,
                        const char         *pInterfaceID,
                        VmbInterfaceType    interfaceType,
                        const char         *pInterfaceName,
                        const char         *pInterfaceSerialNumber,
                        VmbAccessModeType   interfacePermittedAccess );
    
    void addonFireWire( std::string &info );    // custom camera function
};

//
// A class that derives from standard Vimba Camera with a function specific to GigE
//
class GigECamera: 
    public Camera
{
public:
    GigECamera(     const char         *pCameraID,
                    const char         *pCameraName,
                    const char         *pCameraModel,
                    const char         *pCameraSerialNumber,
                    const char         *pInterfaceID,
                    VmbInterfaceType    interfaceType,
                    const char         *pInterfaceName,
                    const char         *pInterfaceSerialNumber,
                    VmbAccessModeType   interfacePermittedAccess );

    void addonGigE( std::string &info );    // custom camera function
};  

//
// A class that derives from standard Vimba Camera with a function specific to USB
//
class USBCamera: 
    public Camera
{
public:
    USBCamera(      const char         *pCameraID,
                    const char         *pCameraName,
                    const char         *pCameraModel,
                    const char         *pCameraSerialNumber,
                    const char         *pInterfaceID,
                    VmbInterfaceType    interfaceType,
                    const char         *pInterfaceName,
                    const char         *pInterfaceSerialNumber,
                    VmbAccessModeType   interfacePermittedAccess );
    
    void addonUSB( std::string &info );     // custom camera function
};

//
// A class that derives from standard Vimba Camera with a functions specific to CL
//
class CLCamera: 
    public Camera
{
public:
    CLCamera(       const char         *pCameraID,
                    const char         *pCameraName,
                    const char         *pCameraModel,
                    const char         *pCameraSerialNumber,
                    const char         *pInterfaceID,
                    VmbInterfaceType    interfaceType,
                    const char         *pInterfaceName,
                    const char         *pInterfaceSerialNumber,
                    VmbAccessModeType   interfacePermittedAccess );
    
    void addonCL( std::string &info );     // custom camera function
};

//
// A class with a static factory method creating specific camera classes dependent on the interface type
//
class UserCameraFactory :
    public ICameraFactory
{
  public:
    CameraPtr CreateCamera( const char *pCameraID,
                            const char *pCameraName,
                            const char *pCameraModel,
                            const char *pCameraSerialNumber,
                            const char *pInterfaceID,
                            VmbInterfaceType interfaceType,
                            const char *pInterfaceName,
                            const char *pInterfaceSerialNumber,
                            VmbAccessModeType interfacePermittedAccess);
};

}}} // namespace AVT::VmbAPI::Examples

#endif
