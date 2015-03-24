/////////////////////////////////////////////////////////////////////////
///@system   金融量化交易平台
///@company  中大期货
///@file IData.h
///@brief    定义了数据引擎接口
///@history 
///20141015	徐旦		创建该文件
/////////////////////////////////////////////////////////////////////////

#ifndef IDATAH
#define IDATAH

#include "QuantStruct.h"

typedef void (*OnRecvFuturesMarketData)(CQuantDepthQuoteDataField*, long lHandle);


class IDataCore
{
public:
	//注册期货数据回调
	virtual bool ReqRecvMarketData(OnRecvFuturesMarketData fRecv,  long lHandle) = 0;

	virtual long GetMarketData(const char* lpInstrument,CQuantDepthQuoteDataField** ppMarketData, long lDataNum) = 0;

	virtual long GetKLineData(const char* lpInstrument,CQuantKLineDataField** ppMarketData, long lDataNum, TQuantDataPeriod period) = 0;

	virtual void Release() = 0;

};

extern "C"
{
	IDataCore* GetDataCore();
};

#endif