#ifndef IFUNCTIONH
#define IFUNCTIONH
#include "QuantStruct.h"
class IFunction
{
public:
	virtual void Release() = 0;

	//最近length周期最新价求和
	virtual double Sum(const char* lpInstrument, int length, TQuantDataPeriod period = QUANT_DATA_TICK) = 0;
	//length的移动平均
	virtual double MA(const char* lpInstrument ,int length, TQuantDataPeriod period = QUANT_DATA_TICK) = 0;
	//平均绝对偏差
	virtual double AVEDEV(const char* lpInstrument ,int length, TQuantDataPeriod period = QUANT_DATA_TICK) = 0;
	//偏差平方和 
	virtual double DEVSQ(const char* lpInstrument ,int length, TQuantDataPeriod period = QUANT_DATA_TICK) = 0;
	//线性回归值
	virtual double FORCAST(const char* lpInstrument ,int length, TQuantDataPeriod period = QUANT_DATA_TICK) = 0;
	//标准差
	virtual double STD(const char* lpInstrument ,int length, TQuantDataPeriod period = QUANT_DATA_TICK) = 0;
	//方差
	virtual double VAR(const char* lpInstrument ,int length, TQuantDataPeriod period = QUANT_DATA_TICK) = 0;
};

extern "C"
{
	IFunction* _cdecl GetFunction();
};

#endif