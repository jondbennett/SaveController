////////////////////////////////////////////////////////////
// Author: Jon Bennett (jon@jondbennett.com) http://jondbennett.com
//
// Save data to and recover it from the Arduino EEPROM
////////////////////////////////////////////////////////////
#include <Arduino.h>
#include <EEPROM.h>

#include "SaveController.h"

////////////////////////////////////////////////////////////
// General purpose read and write of the EEPROM.
// Constructor includes byte flags to identify program type.
// This can be any set of four NON-ZERO bytes. This allows
// an Arduino to be reused on more than one project without
// settings bleeding from one project to another. A good
// choice would be the project initials. After the header
// there is a data version to allow for changes in the program
// to trigger re-saves and loads of default settings.
////////////////////////////////////////////////////////////
#define DATA_START_ADDRESS	(5)

CSaveController::CSaveController(uint8_t _h1, uint8_t _h2, uint8_t _h3, uint8_t _h4)
{
	m_header1 = _h1;
	m_header2 = _h2;
	m_header3 = _h3;
	m_header4 = _h4;

	rewind();
}

CSaveController::~CSaveController()
{
}

void CSaveController::updateEEPROM(unsigned int _addr, uint8_t _data)
{
	if(EEPROM.read(_addr) != _data)
		EEPROM.write(_addr, _data);
}

bool CSaveController::updateHeader(uint8_t _dataVersion)
{
	// Sanity
	if(_dataVersion == SC_INVALID_DATA_VERSION)
		return false;

	// Write the data header
	updateEEPROM(0, (uint8_t)m_header1);
	updateEEPROM(1, (uint8_t)m_header2);
	updateEEPROM(2, (uint8_t)m_header3);
	updateEEPROM(3, (uint8_t)m_header4);
	updateEEPROM(4, (uint8_t)_dataVersion);

	if(getDataVersion() != _dataVersion)
		return false;

	return true;
}

uint8_t CSaveController::getDataVersion()
{
	if(EEPROM.read(0) != m_header1) return SC_INVALID_DATA_VERSION;
	if(EEPROM.read(1) != m_header2) return SC_INVALID_DATA_VERSION;
	if(EEPROM.read(2) != m_header3) return SC_INVALID_DATA_VERSION;
	if(EEPROM.read(3) != m_header4) return SC_INVALID_DATA_VERSION;

	return EEPROM.read(4);
}

void CSaveController::rewind()
{
	m_dataIndex = DATA_START_ADDRESS;
}

void CSaveController::readData(uint8_t *_dest, unsigned int _len)
{
	while(_len--)
		*_dest++ = EEPROM.read(m_dataIndex++);
}

void CSaveController::updateData(uint8_t *_src, unsigned int _len)
{
	while(_len--)
		updateEEPROM(m_dataIndex++, *_src++);
}

