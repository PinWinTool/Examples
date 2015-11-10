/*==========================================================
 * mexfunction.c
 *
 * This mex file use libusb.lib for function * tic;[bytes_read,data_read]=mxUsbGetBulkDataDebug(1003,8960);z=toc;
 * mex mxUsbGetBulkData.c libusb.lib
 *
============================================================*/

#include "usb.h"
#include "mex.h"

/* the device's vendor and product id */
#define MY_VID 0x03EB
#define MY_PID 0x2300

/* the device's endpoints */
#define EP_IN 0x81
#define EP_OUT 0x02

#define NONE 0
#define PARAMS_IN 1
#define PARAMS_OUT 2
#define DATA_IN 3
#define DATA_OUT 4
#define DEBUG 5
#define USB_SIGNTURE 0xc5c5

#define DATA_BUF_SIZE 500
#define TOTAL_CHANNELS_NUMBER_BUFF 14
#define CTMP_SIZE
(DATA_BUF_SIZE*TOTAL_CHANNELS_NUMBER_BUFF)
#define USB_TIMEOUT 500

typedef struct USB_MESSAGE
{
    unsigned char ucUSBMessageType;
    short sUsbSignture;
    short sValue1;
    short sValue2;
    short sValue3;
} xUSBMessage;

usb_dev_handle *open_dev(int my_vid, int my_pid);
int SHORT_little_endian_TO_big_endian(int i);
int INT_little_endian_TO_big_endian(int i);

usb_dev_handle *open_dev(int my_vid, int my_pid)
{
    struct usb_bus *bus;
    struct usb_device *dev;
    
    for(bus = usb_get_busses(); bus; bus = bus->next)
    {
        for(dev = bus->devices; dev; dev = dev->next)
        {
            if(dev->descriptor.idVendor == my_vid
            && dev->descriptor.idProduct == my_pid)
            {
                return usb_open(dev);
            }
        }
    }
    return NULL;
}

void
mexFunction(int nlhs,mxArray *plhs[],int nrhs,const mxArray
*prhs[])
{
    struct usb_bus *bus;
    struct usb_device *dev;
    
    double *ptr_my_vid, *ptr_my_pid, *ptr_my_configuration,
*ptr_my_interface;
    int my_vid, my_pid, my_configuration, my_interface;
    int bytes_write, bytes_read;
    int i,j;
    
    unsigned short cTmp[CTMP_SIZE]={0};
    double *y;
    double *x;
    
    xUSBMessage sxUSBMessage;
    
    plhs[0]=mxCreateDoubleMatrix(1, 1, mxREAL);
    plhs[1]=mxCreateDoubleMatrix
(DATA_BUF_SIZE,TOTAL_CHANNELS_NUMBER_BUFF, mxREAL);
    y = mxGetPr(plhs[0]);
    x = mxGetPr(plhs[1]);
    
    // reset values
    y[0]=0;
    for (i=0;i<TOTAL_CHANNELS_NUMBER_BUFF;i++)
        for (j=0;j<DATA_BUF_SIZE;j++)
            x[(i*DATA_BUF_SIZE)+j]=0;
    
    /* Check for proper number of input and output
arguments */
    /* my_vid, my_pid, my_configuration, my_interface */
    if (nrhs ==4) {
        ptr_my_interface = mxGetPr(prhs[3]);
        ptr_my_configuration = mxGetPr(prhs[2]);
        ptr_my_pid = mxGetPr(prhs[1]);
        ptr_my_vid = mxGetPr(prhs[0]);
        my_interface = (int)(*ptr_my_interface);
        my_configuration = (int)(*ptr_my_configuration);
        my_pid = (int)(*ptr_my_pid);
        my_vid = (int)(*ptr_my_vid);
    }
    else if (nrhs ==3)
    {
        my_interface=0;
        
        ptr_my_configuration = mxGetPr(prhs[2]);
        ptr_my_pid = mxGetPr(prhs[1]);
        ptr_my_vid = mxGetPr(prhs[0]);
        my_configuration = (int)(*ptr_my_configuration);
        my_pid = (int)(*ptr_my_pid);
        my_vid = (int)(*ptr_my_vid);
    }
    
    else if (nrhs ==2) {
        my_interface=0;
        my_configuration=1;
        
        ptr_my_pid = mxGetPr(prhs[1]);
        ptr_my_vid = mxGetPr(prhs[0]);
        my_pid = (int)(*ptr_my_pid);
        my_vid = (int)(*ptr_my_vid);
    }
    else if ((nrhs <2)| (nrhs >4)){
        y[0]=-1;
        mexWarnMsgTxt("At least two input arguments
required.");
        return;
    }
    
    if(nlhs > 2){
        y[0]=-2;
        mexWarnMsgTxt("Too many output arguments.");
        return;
    }
    
    usb_init(); /* initialize the library */
    usb_find_busses(); /* find all busses */
    usb_find_devices(); /* find all connected devices */
  
    // open device
    if(!(dev = open_dev( my_vid, my_pid)))
    {
        y[0]=-3;
        mexWarnMsgTxt("error: device not found!\n");
        return;
    }
    
    // set configuration
    if(usb_set_configuration(dev, my_configuration) < 0)
    {
        y[0]=-4;
        mexWarnMsgTxt("error: setting config failed\n");
        usb_close(dev);
        return;
    }
    
    // claim interface
    if(usb_claim_interface(dev, my_interface) < 0)
    {
        y[0]=-5;
        mexWarnMsgTxt("error: claiming interface failed\n");
        usb_close(dev);
        return;
    }
    
    // arrange request struct for data
    sxUSBMessage.ucUSBMessageType=DATA_IN;
    
sxUSBMessage.sUsbSignture=SHORT_little_endian_TO_big_endian
(USB_SIGNTURE+(short)DATA_IN);
    sxUSBMessage.sValue1=SHORT_little_endian_TO_big_endian
(0);
    sxUSBMessage.sValue2=SHORT_little_endian_TO_big_endian
(0);
    sxUSBMessage.sValue3=SHORT_little_endian_TO_big_endian
(0);
    
    // send request data
    bytes_write=usb_bulk_write(dev, EP_OUT, (char *)
&sxUSBMessage, sizeof(sxUSBMessage), USB_TIMEOUT);
    if( bytes_write != sizeof(sxUSBMessage))
    {
        y[0]=-6;
        mexWarnMsgTxt("error: bulk write failed\n");
        usb_release_interface(dev, my_interface);
        usb_close(dev);
        return;
    }
    
    // get data
    bytes_read=usb_bulk_read(dev, EP_IN, (char *) &cTmp[0],
sizeof( cTmp), USB_TIMEOUT);
    if( bytes_read != sizeof(cTmp) && bytes_read != 1)
    {
        y[0]=-7;
        mexWarnMsgTxt("error: bulk read failed\n");
        usb_release_interface(dev, my_interface);
        usb_close(dev);
        return;
    }
    
    // change endian and write to matlab
    if(bytes_read==sizeof( cTmp))
        for (i=0;i<TOTAL_CHANNELS_NUMBER_BUFF;i++)
            for (j=0;j<DATA_BUF_SIZE;j++)
                x[(i*DATA_BUF_SIZE)+j]
=SHORT_little_endian_TO_big_endian(cTmp[(i*DATA_BUF_SIZE)
+j]);
    
    // get byte read if 1 still no full buffer
    y[0]=bytes_read;

    
    // release interface
    if(usb_release_interface(dev, my_interface) < 0)
    {
        y[0]=-8;
        usb_close(dev);
        mexWarnMsgTxt("error: releasing interface
failed\n");
        return;
    }
    
    // close device
    if(usb_close(dev) < 0)
    {
        y[0]=-9;
        mexWarnMsgTxt("error: closing device\n");
        return;
    }
    return;
}

// 2-byte number
int SHORT_little_endian_TO_big_endian(int i)
{
    return ((i>>8)&0xff)+((i << 8)&0xff00);
}

// 4-byte number
int INT_little_endian_TO_big_endian(int i)
{
    return((i&0xff)<<24)+((i&0xff00)<<8)+((i&0xff0000)>>8)+
((i>>24)&0xff);
}