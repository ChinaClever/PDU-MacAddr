
INCLUDEPATH += $$PWD

include(excel/excel.pri)
include(sqlcom/sqlcom.pri)
include(logcom/logcom.pri)
include(cfgcom/cfgcom.pri)
include(msgcom/msgcom.pri)
include(tabcom/tabcom.pri)
include(macaddr/macaddr.pri)
include(websocket/websocket.pri)
include(smtpclient/smtpclient.pri)
include(snmpclient/snmpclient.pri)
include(datapacket/datapacket.pri)
include(serialport/serialport.pri)
include(backcolour/backcolour.pri)
include(qtsingleapplication/qtsingleapplication.pri)

HEADERS += \	
    $$PWD/common.h
	
SOURCES += \	
    $$PWD/common.cpp

FORMS += \




