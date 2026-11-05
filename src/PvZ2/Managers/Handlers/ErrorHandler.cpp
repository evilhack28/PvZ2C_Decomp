//
//  ErrorHandler.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-05.
//

#include "SexyAppFramework/Common.h"
#include "SexyAppFramework/ImageLib/ImageJPEG.h"

/////////////// Lifecycle ///////////////

static void SetErrorExit(jpeg_error_mgr* err, jpeg_error_mgr** cinfoErr)
{
    *cinfoErr = jpeg_std_error(err);
    err->error_exit = ImageLib::ErrorHandler::OnErrorExit;
}

ImageLib::ErrorHandler::ErrorHandler(jpeg_decompress_struct* cinfo)
{
    SetErrorExit(this, (jpeg_error_mgr**)cinfo);
}

ImageLib::ErrorHandler::ErrorHandler(jpeg_compress_struct* cinfo)
{
    SetErrorExit(this, (jpeg_error_mgr**)cinfo);
}

/////////////// Error ///////////////

void ImageLib::ErrorHandler::OnErrorExit(jpeg_common_struct* cinfo)
{
    ErrorHandler* handler = (ErrorHandler*)cinfo->err;
    handler->output_message(cinfo);
    longjmp(handler->setjmp_buffer, 1);
}
