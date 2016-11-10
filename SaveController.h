////////////////////////////////////////////////////////////
// Author: Jon Bennett (jon@jondbennett.com) http://jondbennett.com
//
// Save data to and recover it from the Arduino EEPROM
////////////////////////////////////////////////////////////
#ifndef SAVECONTROLLER_H
#define SAVECONTROLLER_H

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
class CSaveController
{
	protected:

	uint8_t m_header1, m_header2, m_header3, m_header4;

	unsigned int m_dataIndex;

	void updateEEPROM(unsigned int _addr, uint8_t _data);

	public:

	CSaveController(uint8_t _h1, uint8_t _h2, uint8_t _h3, uint8_t _h4);
	virtual ~CSaveController();

	bool updateHeader(uint8_t _dataVersion);
	uint8_t getDataVersion();

	void rewind();

	void readData(uint8_t *_dest, unsigned int _len);
	void updateData(uint8_t *_src, unsigned int _len);

	bool readByte() { uint8_t v; readData((uint8_t *)&v, sizeof(v)); return v; }
	void writeByte(uint8_t _v) { updateData((uint8_t *)&_v, sizeof(_v)); }

	bool readBool() { bool v; readData((uint8_t *)&v, sizeof(v)); return v; }
	void writeBool(bool _v) { updateData((uint8_t *)&_v, sizeof(_v)); }

	int readInt() { int v; readData((uint8_t *)&v, sizeof(v)); return v; }
	void writeInt(int _v) { updateData((uint8_t *)&_v, sizeof(_v)); }

	float readFloat() { float v; readData((uint8_t *)&v, sizeof(v)); return v; }
	void writeFloat(float _v) { updateData((uint8_t *)&_v, sizeof(_v)); }

	double readDouble() { double v; readData((uint8_t *)&v, sizeof(v)); return v; }
	void writeDouble(double _v) { updateData((uint8_t *)&_v, sizeof(_v)); }
};

#define SC_INVALID_DATA_VERSION	(0)

#endif
