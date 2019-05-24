/** @mainpage qwavecv - None
 *
 * @author Supawat A <supawat@qwavesys.com>
 * @version 1.0.0
**/


#include "qwavecv.h"

/*
EXTERN_C void QwaveCV_Template1(lvError * errorHandle, CVImageHandle *hImage) {
    CVERROR error = ERR_SUCCESS;
    QwaveCV_ReturnOnPreviousError(errorHandle);
    try
    {
        if (!hImage) {
            QwaveCV_ThrowCVError(ERR_NULL_POINTER);
        }

        Mat image = QwaveCV_LVToMat(hImage);
	// Add your code here!

        QwaveCV_MatToLV(hImage, image);
    }
    catch(CVERROR _err){
        error = _err;
    }
    catch (...){
        error = ERR_OCV_USER;
    }
    QwaveCV_ProcessCVError(error, errorHandle);
}

EXTERN_C void QwaveCV_Template2(lvError * errorHandle, CVImageHandle *hImageSrc, CVImageHandle *hImageDsc) {
    CVERROR error = ERR_SUCCESS;
    QwaveCV_ReturnOnPreviousError(errorHandle);
    try
    {
        if (!hImageSrc || !hImageDsc) {
            QwaveCV_ThrowCVError(ERR_NULL_POINTER);
        }

        Mat image_src = QwaveCV_LVToMat(hImageSrc);
	Mat image_dsc = QwaveCV_LVToMat(hImageDsc);
	// Add your code here!

        QwaveCV_MatToLV(hImageDsc, image_dsc);
    }
    catch(CVERROR _err){
        error = _err;
    }
    catch (...){
        error = ERR_OCV_USER;
    }
    QwaveCV_ProcessCVError(error, errorHandle);
}
*/
