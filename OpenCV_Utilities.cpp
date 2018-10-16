/** @mainpage qwavecv - None
 *
 * @author Supawat A <supawat@qwavesys.com>
 * @version 1.0.0
**/


#include "qwavecv.h"

typedef struct{
	int32_t type;
	int32_t height;
	int32_t width;
	int32_t depth;
	int32_t channels;
}AttributesOptions, *AttributesOptions_t;

EXTERN_C void QwaveCV_matCopy(lvError * errorHandle, CVImageHandle *hImage1, CVImageHandle *hImage2, uint32_t x, uint32_t y) {
    CVERROR error = ERR_SUCCESS;
    QwaveCV_ReturnOnPreviousError(errorHandle);
    try
    {
        if (!hImage1 || !hImage2){
            QwaveCV_ThrowCVError(ERR_NULL_POINTER);
        }

        Mat Image1 = QwaveCV_LVToMat(hImage1);
        Mat Image2 = QwaveCV_LVToMat(hImage2);

        Mat matRoi = Image2(Rect(x, y, Image1.cols, Image1.rows));
        Image1.copyTo(matRoi);
	QwaveCV_MatToLV(hImage2, Image2);

    }
    catch(CVERROR _err){
        error = _err;
    }
    catch (...){
        error = ERR_OCV_USER;
    }
    QwaveCV_ProcessCVError(error, errorHandle);
}

EXTERN_C void QwaveCV_GetImage8bitsXY(lvError * errorHandle, CVImageHandle *hImage, int x, int y, int *data) {
    CVERROR error = ERR_SUCCESS;
    QwaveCV_ReturnOnPreviousError(errorHandle);
    try
    {
        if (!hImage){
            QwaveCV_ThrowCVError(ERR_NULL_POINTER);
        }

        Mat image = QwaveCV_LVToMat(hImage);
    	(*data) = image.at<uchar>(x, y);

    }
    catch(CVERROR _err){
        error = _err;
    }
    catch (...){
        error = ERR_OCV_USER;
    }
    QwaveCV_ProcessCVError(error, errorHandle);
}

EXTERN_C void QwaveCV_SetImage8bitsXY(lvError * errorHandle, CVImageHandle *hImage, int x, int y, uint8_t data) {
    CVERROR error = ERR_SUCCESS;
    QwaveCV_ReturnOnPreviousError(errorHandle);
    try
    {
        if (!hImage){
            QwaveCV_ThrowCVError(ERR_NULL_POINTER);
        }

        Mat image = QwaveCV_LVToMat(hImage);
        image.at<uint8_t>(x, y) = data;
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

EXTERN_C void  QwaveCV_ReadFile(lvError * errorHandle, char *filename, CVImageHandle *hImage) {
    CVERROR error = ERR_SUCCESS;
    QwaveCV_ReturnOnPreviousError(errorHandle);
    try
    {
        if (!hImage || !filename){
            QwaveCV_ThrowCVError(ERR_NULL_POINTER);
        }

        Mat image = QwaveCV_LVToMat(hImage);
        image = imread(filename, 1); // loads the image in the BGR format
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

EXTERN_C void QwaveCV_GetImageAttrtibutes(lvError * errorHandle, CVImageHandle *hImage, AttributesOptions_t attr) {
    CVERROR error = ERR_SUCCESS;
    QwaveCV_ReturnOnPreviousError(errorHandle);
    try
    {
        if (!hImage){
            QwaveCV_ThrowCVError(ERR_NULL_POINTER);
        }

        int typeOfImage[] = { CV_8UC1, CV_16SC1, CV_32FC1, CV_32FC2, CV_8UC4, CV_8UC4, CV_16UC4, CV_16UC1 };

        Mat image = QwaveCV_LVToMat(hImage);

        int lvImageType = 0;
        while(lvImageType<sizeof(typeOfImage)) {
        	if(typeOfImage[lvImageType] == image.type()) break;
        	lvImageType++;
        }
        attr->height = image.rows;
        attr->width = image.cols;
        attr->type = lvImageType;
        attr->depth = image.depth();
        attr->channels = image.channels();
    }
    catch(CVERROR _err){
        error = _err;
    }
    catch (...){
        error = ERR_OCV_USER;
    }
    QwaveCV_ProcessCVError(error, errorHandle);
}

EXTERN_C void QwaveCV_GetImageSize(lvError * errorHandle, CVImageHandle *hImage, int *img_rows, int *img_cols) {
    CVERROR error = ERR_SUCCESS;
    QwaveCV_ReturnOnPreviousError(errorHandle);
    try
    {
        if (!hImage){
            QwaveCV_ThrowCVError(ERR_NULL_POINTER);
        }

        Mat image = QwaveCV_LVToMat(hImage);

        (*img_rows) = image.rows;
        (*img_cols) = image.cols;

    }
    catch(CVERROR _err){
        error = _err;
    }
    catch (...){
        error = ERR_OCV_USER;
    }
    QwaveCV_ProcessCVError(error, errorHandle);
}

EXTERN_C void QwaveCV_ResizeImage(lvError * errorHandle, CVImageHandle *hImage, uint32_t width, uint32_t height) {
    CVERROR error = ERR_SUCCESS;
    QwaveCV_ReturnOnPreviousError(errorHandle);
    try
    {
        if (!hImage){
            QwaveCV_ThrowCVError(ERR_NULL_POINTER);
        }

        Mat image = QwaveCV_LVToMat(hImage);
	resize(image, image, Size(width, height));
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

