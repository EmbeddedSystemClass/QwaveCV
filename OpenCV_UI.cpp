/** @mainpage qwavecv - None
 *
 * @author Supawat A <supawat@qwavesys.com>
 * @version 1.0.0
**/


#include "qwavecv.h"

#define CVUI_IMPLEMENTATION
#include "cvui.h"

EXTERN_C void QwaveCV_cvuiInit(lvError * errorHandle, uint8_t mode, uchar * window_name, uint32_t x, uint32_t y) {
    CVERROR error = ERR_SUCCESS;
    QwaveCV_ReturnOnPreviousError(errorHandle);
    try
    {
        string _window_name = QwaveCV_CStrToString(window_name);
	if(mode == 0) {
	    namedWindow(_window_name, WINDOW_AUTOSIZE);
            moveWindow(_window_name, x, y);
	}
	else {
            namedWindow(_window_name, CV_WINDOW_NORMAL);
            setWindowProperty(_window_name, CV_WND_PROP_FULLSCREEN, CV_WINDOW_FULLSCREEN);
	}
        cvui::init(_window_name, -1, false);
    }
    catch(CVERROR _err){
        error = _err;
    }
    catch (...){
        error = ERR_OCV_USER;
    }
    QwaveCV_ProcessCVError(error, errorHandle);
}

EXTERN_C void QwaveCV_CloseAllWindows(lvError * errorHandle) {
    CVERROR error = ERR_SUCCESS;
    QwaveCV_ReturnOnPreviousError(errorHandle);
    try
    {
        destroyAllWindows();
    }
    catch(CVERROR _err){
        error = _err;
    }
    catch (...){
        error = ERR_OCV_USER;
    }
    QwaveCV_ProcessCVError(error, errorHandle);
}

EXTERN_C void QwaveCV_DestroyWindow(lvError * errorHandle, uchar *window_name) {
    CVERROR error = ERR_SUCCESS;
    QwaveCV_ReturnOnPreviousError(errorHandle);
    try
    {
	string _window_name = QwaveCV_CStrToString(window_name);
        destroyWindow(_window_name);
    }
    catch(CVERROR _err){
        error = _err;
    }
    catch (...){
        error = ERR_OCV_USER;
    }
    QwaveCV_ProcessCVError(error, errorHandle);
}

EXTERN_C void QwaveCV_imshow(lvError * errorHandle, CVImageHandle *hImage, uchar *window_name) {
    CVERROR error = ERR_SUCCESS;
    QwaveCV_ReturnOnPreviousError(errorHandle);
    try
    {
        if (!hImage){
            QwaveCV_ThrowCVError(ERR_NULL_POINTER);
        }

        Mat image = QwaveCV_LVToMat(hImage);
        string _window_name = QwaveCV_CStrToString(window_name);

        imshow(_window_name, image);
    }
    catch(CVERROR _err){
        error = _err;
    }
    catch (...){
        error = ERR_OCV_USER;
    }
    QwaveCV_ProcessCVError(error, errorHandle);
}

EXTERN_C void QwaveCV_imshow2(lvError * errorHandle, CVImageHandle *hImage1, CVImageHandle *hImage2, uchar * window_name) {
    CVERROR error = ERR_SUCCESS;
    QwaveCV_ReturnOnPreviousError(errorHandle);
    try
    {
        if (!hImage1 || !hImage2){
            QwaveCV_ThrowCVError(ERR_NULL_POINTER);
        }

        string _window_name = QwaveCV_CStrToString(window_name);

        Mat Image1 = QwaveCV_LVToMat(hImage1);
        Mat Image2 = QwaveCV_LVToMat(hImage2);

        Mat matDst(Size(Image1.cols*2,Image1.rows),Image1.type(),Scalar::all(0));
        Mat matRoi = matDst(Rect(0,0,Image1.cols,Image1.rows));
        Image1.copyTo(matRoi);
        matRoi = matDst(Rect(Image1.cols,0,Image1.cols,Image1.rows));
        Image2.copyTo(matRoi);

        imshow(_window_name, matDst);

    }
    catch(CVERROR _err){
        error = _err;
    }
    catch (...){
        error = ERR_OCV_USER;
    }
    QwaveCV_ProcessCVError(error, errorHandle);
}

EXTERN_C void QwaveCV_waitKey(lvError * errorHandle, int ms, int *key) {
    CVERROR error = ERR_SUCCESS;
    QwaveCV_ReturnOnPreviousError(errorHandle);
    try
    {
        (*key) = waitKey(ms);
    }
    catch(CVERROR _err){
        error = _err;
    }
    catch (...){
        error = ERR_OCV_USER;
    }
    QwaveCV_ProcessCVError(error, errorHandle);
}

EXTERN_C void QwaveCV_UItrackbar(lvError * errorHandle, CVImageHandle *hImage, uint32_t x, uint32_t y, uint32_t width, uint32_t minValue, uint32_t maxValue, uint32_t *outValue) {
    CVERROR error = ERR_SUCCESS;
    QwaveCV_ReturnOnPreviousError(errorHandle);
    try
    {
        Mat image = QwaveCV_LVToMat(hImage);
        cvui::trackbar(image, x, y, width, outValue, minValue, maxValue);
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

EXTERN_C void QwaveCV_UIwindow(lvError * errorHandle, CVImageHandle *hImage, uchar *title, uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
    CVERROR error = ERR_SUCCESS;
    QwaveCV_ReturnOnPreviousError(errorHandle);
    try
    {
        Mat image = QwaveCV_LVToMat(hImage);
	string _title = QwaveCV_CStrToString(title);
        cvui::window(image, x, y, width, height, _title);
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

EXTERN_C void QwaveCV_UIbutton(lvError * errorHandle, CVImageHandle *hImage, uchar *label, uint32_t x, uint32_t y, uint32_t width, uint32_t height, uint8_t  *clicked) {
    CVERROR error = ERR_SUCCESS;
    QwaveCV_ReturnOnPreviousError(errorHandle);
    try
    {
        Mat image = QwaveCV_LVToMat(hImage);
        string _label = QwaveCV_CStrToString(label);
        *clicked = 0;
	if(cvui::button(image, x, y, width, height, _label)) {
	    *clicked = 1;
	}
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

EXTERN_C void QwaveCV_UIcheckbox(lvError * errorHandle, CVImageHandle *hImage, uint32_t x, uint32_t y, uchar *label, uint8_t *state, uint32_t color) {
    CVERROR error = ERR_SUCCESS;
    QwaveCV_ReturnOnPreviousError(errorHandle);
    try
    {
        Mat image = QwaveCV_LVToMat(hImage);
        string _label = QwaveCV_CStrToString(label);
        bool checked = false;
        if(*state) checked = true;
        cvui::checkbox(image, x, y, _label, &checked, color);
        if(checked)
            *state = 1;
        else
            *state = 0;
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

EXTERN_C void QwaveCV_UItext(lvError * errorHandle, CVImageHandle *hImage, uint32_t x, uint32_t y, uchar *text, double frontscale, uint32_t color) {
    CVERROR error = ERR_SUCCESS;
    QwaveCV_ReturnOnPreviousError(errorHandle);
    try
    {
        Mat image = QwaveCV_LVToMat(hImage);
        string _text = QwaveCV_CStrToString(text);
	cvui::text(image, x, y, _text, frontscale, color);
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

EXTERN_C void QwaveCV_UIpicture(lvError * errorHandle, CVImageHandle *hImage, uint32_t x, uint32_t y, char *picture) {
    CVERROR error = ERR_SUCCESS;
    QwaveCV_ReturnOnPreviousError(errorHandle);
    try
    {
        Mat frame = QwaveCV_LVToMat(hImage);
	Mat _picture = imread(picture, IMREAD_COLOR);
	cvtColor(_picture, _picture, 0);
	cvui::image(frame, x, y, _picture);

        QwaveCV_MatToLV(hImage, frame);
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
EXTERN_C void QwaveCV_UItrackbar(lvError * errorHandle, CVImageHandle *hImage, uint32_t x, uint32_t y, uint32_t width, uint32_t minValue, uint32_t maxValue, uint32_t outValue) {
    CVERROR error = ERR_SUCCESS;
    QwaveCV_ReturnOnPreviousError(errorHandle);
    try
    {
        Mat image = QwaveCV_LVToMat(hImage);
        bool out;
        cvui::window(image, 15, 50, 180, 180, "Settings");
        cvui::checkbox(image, 20, 80, "Use Canny Edge", &out);
        if(out == true)
            (*use_canny) = 1;
        else
           (*use_canny) = 0;
        cvui::trackbar(image, 15, 110, 165, low_threshold, 0, 150);
        cvui::trackbar(image, 15, 180, 165, high_threshold, 0, 300);
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
