/*=============================================================================
  Copyright (C) 2014 Allied Vision Technologies.  All Rights Reserved.

  Redistribution of this file, in original or modified form, without
  prior written consent of Allied Vision Technologies is prohibited.

-------------------------------------------------------------------------------

  File:        program.cpp

  Description: Main entry point of ListAncillaryDataFeatures example of VimbaCPP.

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

#include <iostream>

#include "ListAncillaryDataFeatures.h"

int main( int argc, char* argv[] )
{
    std::cout << "\n";
    std::cout << "//////////////////////////////////////////////////////\n";
    std::cout << "/// Vimba API List Ancillary Data Features Example ///\n";
    std::cout << "//////////////////////////////////////////////////////\n\n";

    if( 2 < argc )
    {
        std::cout << "Usage: ListAncillaryDataFeatures [CameraID]\n\n";
        std::cout << "Parameters:   CameraID    ID of the camera to use (using first camera if not specified)\n";
    }
    else if( 2 == argc )
    {
        AVT::VmbAPI::Examples::ListAncillaryDataFeatures::Print( argv[1] );
    }
    else
    {
        AVT::VmbAPI::Examples::ListAncillaryDataFeatures::Print( "" );
    }

    std::cout << "\n";
}
