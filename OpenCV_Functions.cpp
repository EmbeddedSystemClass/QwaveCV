/** @mainpage qwavecv - None
 *
 * @author Supawat A <supawat@qwavesys.com>
 * @version 1.0.0
**/


#include "qwavecv.h"

typedef struct{
	int lowThreshold;
	int highThreshold;
	int apertureSize;
	int L2gradient;
}LVCannyOptions, *CannyOptions_t;

/*
EXTERN_C void QwaveCV_Template(lvError * errorHandle, CVImageHandle *hImage) {
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
*/


EXTERN_C void QwaveCV_Canny(lvError * errorHandle, CVImageHandle *hImage, CannyOptions_t options) {
    CVERROR error = ERR_SUCCESS;
    QwaveCV_ReturnOnPreviousError(errorHandle);
    try
    {
        if (!hImage || !options){
            QwaveCV_ThrowCVError(ERR_NULL_POINTER);
        }

        Mat image = QwaveCV_LVToMat(hImage);
        Canny(image, image, options->lowThreshold, options->highThreshold, options->apertureSize, options->L2gradient);
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

// https://docs.opencv.org/3.3.0/df/d4e/group__imgproc__c.html
EXTERN_C void QwaveCV_cvtColor(lvError * errorHandle, CVImageHandle *hImage, int code) {
	CVERROR error = ERR_SUCCESS;
	    QwaveCV_ReturnOnPreviousError(errorHandle);
	    try
	    {
	        if (!hImage){
	            QwaveCV_ThrowCVError(ERR_NULL_POINTER);
	        }

	        Mat image = QwaveCV_LVToMat(hImage);
			cvtColor(image, image, code);
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

/*
EXTERN_C void QwaveCV_cvuiInit(lvError * errorHandle, uchar * windows_name) {
    CVERROR error = ERR_SUCCESS;
    QwaveCV_ReturnOnPreviousError(errorHandle);
    try
    {
	string _windows_name = QwaveCV_CStrToString(windows_name);
	namedWindow(_windows_name, CV_WINDOW_NORMAL);
        setWindowProperty(_windows_name, CV_WND_PROP_FULLSCREEN, CV_WINDOW_FULLSCREEN);
        cvui::init(_windows_name, -1, false);
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
