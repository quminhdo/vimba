/*=============================================================================
  Copyright (C) 2013 - 2017 Allied Vision Technologies.  All Rights Reserved.

  Redistribution of this file, in original or modified form, without
  prior written consent of Allied Vision Technologies is prohibited.

-------------------------------------------------------------------------------

  File:        FrameObserver.cpp

  Description: The frame observer that is used for notifications from VimbaCPP
               regarding the arrival of a newly acquired frame.

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
#include <iomanip>
#include <time.h>

#include "FrameObserver.h"

#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp"
using namespace cv;

namespace AVT {
namespace VmbAPI {
namespace Examples {

//
// We pass the camera that will deliver the frames to the constructor
//
// Parameters:
//  [in]    pCamera             The camera the frame was queued at
//  [in]    eFrameInfos         Indicates how the frame will be displayed
//  [in]    eColorProcessing    Indicates how color processing is applied
//
FrameObserver::FrameObserver( CameraPtr pCamera )
    :   IFrameObserver( pCamera ) {}
// #ifdef WIN32
//     ,   m_dFrequency( 0.0 )
// #endif //WIN32
// {
// #ifdef WIN32
//     LARGE_INTEGER nFrequency;
//     QueryPerformanceFrequency( &nFrequency );
//     m_dFrequency = (double)nFrequency.QuadPart;
// #endif //WIN32
// }

//
// Gets the current timestamp for interval measurement
//
double FrameObserver::GetTime()
{
    double dTime = 0.0;

// #ifdef WIN32
//     LARGE_INTEGER nCounter;
//     QueryPerformanceCounter( &nCounter );
//     dTime = ( (double)nCounter.QuadPart ) / m_dFrequency;
// #else
    //clock_t nTime = times(NULL);
    //dTime = ((double)(nTime) * 10000.0) / ((double)CLOCKS_PER_SEC);
    struct timespec now;
    clock_gettime( CLOCK_REALTIME, &now );
    dTime = ( (double)now.tv_sec ) + ( (double)now.tv_nsec ) / 1000000000.0;
// #endif //WIN32

    return dTime;
}

//
// Prints out frame parameters such as 
// - width
// - height
// - pixel format
//
// Parameters:
//  [in]    pFrame          The frame to work on
//
void PrintFrameInfo( const FramePtr &pFrame )
{
    std::cout<<" Size:";
    VmbUint32_t     nWidth = 0;
    VmbErrorType    res;
    res = pFrame->GetWidth(nWidth);
    if( VmbErrorSuccess == res )
    {
        std::cout<<nWidth;
    }
    else
    {
        std::cout<<"?";
    }

    std::cout<<"x";
    VmbUint32_t nHeight = 0;
    res = pFrame->GetHeight(nHeight);
    if( VmbErrorSuccess == res )
    {
        std::cout<< nHeight;
    }
    else
    {
        std::cout<<"?";
    }

    std::cout<<" Format:";
    VmbPixelFormatType ePixelFormat = VmbPixelFormatRgb8;
    res = pFrame->GetPixelFormat( ePixelFormat );
    if( VmbErrorSuccess == res )
    {
        std::cout<<"0x"<<std::hex<<ePixelFormat<<std::dec;
    }
    else
    {
        std::cout<<"?";
    }
}

//
// Prints out frame status codes as readable status messages
//
// Parameters:
//  [in]    eFrameStatus    The error code to be converted and printed out
//
void PrintFrameStatus( VmbFrameStatusType eFrameStatus )
{
    switch( eFrameStatus )
    {
    case VmbFrameStatusComplete:
        std::cout<<"Complete";
        break;

    case VmbFrameStatusIncomplete:
        std::cout<<"Incomplete";
        break;

    case VmbFrameStatusTooSmall:
        std::cout<<"Too small";
        break;

    case VmbFrameStatusInvalid:
        std::cout<<"Invalid";
        break;

    default:
        std::cout<<"unknown frame status";
        break;
    }
}

//
// Prints out details of a frame such as
// - ID
// - receive status
// - width, height, pixel format
// - current frames per second
//
// Parameters:
//  [in]    pFrame          The frame to work on
//
void FrameObserver::ShowFrameInfos( const FramePtr &pFrame ) 
{
    bool                bShowFrameInfos     = false;
    VmbUint64_t         nFrameID            = 0;
    bool                bFrameIDValid       = false;
    VmbFrameStatusType  eFrameStatus        = VmbFrameStatusComplete;
    bool                bFrameStatusValid   = false;
    VmbErrorType        res                 = VmbErrorSuccess;
    double              dFPS                = 0.0;
    bool                bFPSValid           = false;
    VmbUint64_t         nFramesMissing      = 0;
    // if( FrameInfos_Show == m_eFrameInfos )
    // {
    //     bShowFrameInfos = true;
    // }

    res = pFrame->GetFrameID( nFrameID );
    if( VmbErrorSuccess == res )
    {
        bFrameIDValid = true;

        if( m_FrameID.IsValid() )
        {
            if( nFrameID != ( m_FrameID() + 1 ) )
            {
                nFramesMissing = nFrameID - m_FrameID() - 1;
                if( 1 == nFramesMissing )
                {
                    std::cout<<"1 missing frame detected\n";
                }
                else
                {
                    std::cout<<nFramesMissing<<"missing frames detected\n";
                }
            }
        }

        m_FrameID( nFrameID );
        double dFrameTime = GetTime();
        if(     ( m_FrameTime.IsValid() )
            &&  ( 0 == nFramesMissing ) )
        {
            double dTimeDiff = dFrameTime - m_FrameTime();
            if( dTimeDiff > 0.0 )
            {
                dFPS = 1.0 / dTimeDiff;
                bFPSValid = true;
            }
            else
            {
                bShowFrameInfos = true;
            }
        }

        m_FrameTime( dFrameTime );
    }
    else
    {
        bShowFrameInfos = true;
        m_FrameID.Invalidate();
        m_FrameTime.Invalidate();
    }

    res = pFrame->GetReceiveStatus( eFrameStatus );
    if( VmbErrorSuccess == res )
    {
        bFrameStatusValid = true;

        if( VmbFrameStatusComplete != eFrameStatus )
        {
            bShowFrameInfos = true;
        }
    }
    else
    {
        bShowFrameInfos = true;
    }
    if( bShowFrameInfos )
    {
        std::cout<<"Frame ID:";
        if( bFrameIDValid )
        {
            std::cout<<nFrameID;
        }
        else
        {
            std::cout<<"?";
        }

        std::cout<<" Status:";
        if( bFrameStatusValid )
        {
            PrintFrameStatus( eFrameStatus);
        }
        else
        {
            std::cout<<"?";
        }
        PrintFrameInfo( pFrame );
        
        std::cout<<" FPS:";
        if( bFPSValid )
        {
            std::streamsize s = std::cout.precision();
            std::cout<<std::fixed<<std::setprecision(2)<<dFPS<<std::setprecision(s);
        }
        else
        {
            std::cout<<"?";
        }

        std::cout<<"\n";
    }
    else
    {
        std::cout<<".";
    }
}

//
// This is our callback routine that will be executed on every received frame.
// Triggered by the API.
//
// Parameters:
//  [in]    pFrame          The frame returned from the API
//
void FrameObserver::FrameReceived( const FramePtr pFrame )
{
    VmbErrorType err = VmbErrorSuccess;
    VmbFrameStatusType status;
    if(! SP_ISNULL( pFrame ) )
    {
        ShowFrameInfos( pFrame);
        err = pFrame->GetReceiveStatus( status );
        if (    VmbErrorSuccess == err
             && VmbFrameStatusComplete == status )
        {
            VmbPixelFormatType ePixelFormat = VmbPixelFormatMono8;
            err = pFrame->GetPixelFormat( ePixelFormat );
            if ( VmbErrorSuccess == err )
            {
                if (    ( VmbPixelFormatMono8 != ePixelFormat )
                    &&  ( VmbPixelFormatRgb8 != ePixelFormat ))
                {
                    err = VmbErrorInvalidValue;
                }
                else
                {   
                    if (VmbPixelFormatMono8 == ePixelFormat){
                        std::cout << "Mono8" << std::endl;
                    }
                    else if (VmbPixelFormatRgb8 == ePixelFormat){
                        std::cout << "Rgb8" << std::endl;
                    }
                    else{
                        std::cout << "other format" << std::endl;
                    }
                    VmbUint32_t nImageSize = 0; 
                    err = pFrame->GetImageSize( nImageSize );
                    if ( VmbErrorSuccess == err )
                    {
                        VmbUint32_t nWidth = 0;
                        err = pFrame->GetWidth( nWidth );
                        if ( VmbErrorSuccess == err )
                        {
                            VmbUint32_t nHeight = 0;
                            err = pFrame->GetHeight( nHeight );
                            if ( VmbErrorSuccess == err )
                            {
                                VmbUint64_t nFrameID = 0;
                                err = pFrame->GetFrameID( nFrameID );
                                if ( VmbErrorSuccess == err ){
                                    VmbUchar_t *pImage = NULL;
                                    err = pFrame->GetImage( pImage );
                                    if ( VmbErrorSuccess == err )
                                    {
                                        Mat cvMat(nHeight, nWidth, CV_8UC3, pImage);
                                        cvtColor(cvMat, cvMat, COLOR_RGB2BGR);
                                        cvFrame = cvMat;
                                        // char filename[1000];
                                        // sprintf(filename, "gsc_%03d.jpg", (int) nFrameID);
                                        // imwrite(filename, cvMat);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        // VmbFrameStatusType status;
        VmbErrorType Result;
        Result = SP_ACCESS( pFrame)->GetReceiveStatus( status);
        if( VmbErrorSuccess == Result && VmbFrameStatusComplete == status)
        {
            // deleted some transform code
        }
        else
        {
            std::cout<<"frame incomplete\n";
        }
    }
    else
    {
        std::cout <<" frame pointer NULL\n";
    }

    m_pCamera->QueueFrame( pFrame );
}
}}} // namespace AVT::VmbAPI::Examples
