#include "mdspi.h"
#include "ThostFtdcUserApiStruct.h"
#include <cassert>
#include <cstring>
#include <iostream>

/*
MdSpi::MdSpi(){

}
*/
	
MdSpi::~MdSpi(){
	
}


/*!
 * \brief MdSpi::OnFrontConnected
 *
 */
void MdSpi::OnFrontConnected()
{
    std::cout << "MdSpi::OnFrontConnected" << std::endl;

}

/*!
 * \brief MdSpi::OnFrontDisconnected
 *
 */
void MdSpi::OnFrontDisconnected(int nReason)
{
    std::cout << "MdSpi::OnFrontDisconnected  nReason:" << nReason << std::endl;
}

void MdSpi::OnHeartBeatWarning(int nTimeLapse)
{
    std::cout << "MdSpi::OnHeartBeatWarning  nTimeLapse:" << nTimeLapse << std::endl;
}

/*!
 * \brief MdSpi::OnRspUserLogin
 *
 */
void MdSpi::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    std::cout << "MdSpi::OnRspUserLogin"
              << "ErrorID:" << pRspInfo->ErrorID << "  "
              << "ErrorMsg:" << pRspInfo->ErrorMsg << "  "
              << "LoginTime:" << pRspUserLogin->LoginTime << "  "
              << "UserID:" << pRspUserLogin->UserID << "  "
              << "TradingDay:" << pRspUserLogin->TradingDay << "  "
              << std::endl;
}

/*!
 * \brief MdSpi::OnRspUserLogout
 *
 */
void MdSpi::OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    std::cout << "OnRspUserLogout" << std::endl;
}

/*!
 * \brief MdSpi::OnRspSubMarketData
 *
 */
void MdSpi::OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    std::cout << "MdSpi::OnRspSubMarketData "
              << pSpecificInstrument->InstrumentID
              << std::endl;
}

/*!
 * \brief MdSpi::OnRspUnSubMarketData
 *
 */
void MdSpi::OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    std::cout << "OnRspUnSubMarketData" << std::endl;
}

/*!
 * \brief MdSpi::OnRtnDepthMarketData
 *
 */
void MdSpi::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData)
{
    std::cout << "MdSpi::OnRtnDepthMarketData"
              << "TradingDay:" << pDepthMarketData->TradingDay << " "
              << "InstrumentID:" << pDepthMarketData->InstrumentID << " "
              << "LastPrice:" << pDepthMarketData->LastPrice << " "
              << std::endl;
}

