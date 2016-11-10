# SaveController
An arduino object to save data to and load it from the EEPROM

The save controller works a bit like a disk file. You create and check a header to make
sure the data is valid and its version is correct. Then you start reading and writing
data. Sequential calls to save data to the EEPROM displace the pointer by the data size,
so the data is serialized. It is best to call "rewind()" before loading or saving data.
There is no "seek" method.

Also, to save wear and tear on the EEPROM, all data is "updated," meaning that if the
value in EEPROM is already correct then it is not re-written.

Usage is ease:
Instantiate the object
CSaveController g_saveController('T', 'e', 's', 't');

Note that the four characters "Test" make up a header group so that if
you use the same arduino on multiple projects then you can detect that
the data from the last project is not of the correct kind. I use the
initials of the project, or some such, to uniquely identify each project.
After instantiating the object, check the version number of the data:
if(g_saveController.getDataVersion() != MY_DATA_VERSION)
	// save your default settings.

After that, have any objects that need to load and save settings do so
by giving them a loadSettings and saveSettings method:

void CDoorController::saveSettings(CSaveController &_saveController)
{
	// Save settings
	_saveController.writeInt(getSunriseType());
	_saveController.writeInt(getSunsetType());
}

void CDoorController::loadSettings(CSaveController &_saveController)
{
	// Load settings
	eSunrise_Sunset_T sunriseType = (eSunrise_Sunset_T)_saveController.readInt();
	setSunriseType(sunriseType);

	eSunrise_Sunset_T sunsetType = (eSunrise_Sunset_T)_saveController.readInt();
	setSunsetType(sunsetType);
}



